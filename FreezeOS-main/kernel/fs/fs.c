#include <console.h>
#include <disk.h>
#include <fs.h>
#include <io.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

// Constants
#define SECTOR_SIZE 512
#define BYTES_PER_SECTOR 512
#define SECTORS_PER_CLUSTER 4
#define RESERVED_SECTORS 4
#define NUMBER_OF_FATS 2
#define ROOT_ENTRIES 512
#define ROOT_ENTRIES_SIZE 32
#define TOTAL_SECTORS 20480
#define SECTORS_PER_FAT 20
#define SECTOR_SIZE 512
#define CLUSTER_SIZE 2048
#define DATA_SECTOR_START 68
#define END_OF_CLUSTER 0xFFFF

DirEntry_t root_entries[256];
ClusterChain_t fat[512];

DirEntry_t empty_entry = {.extra = {0},
                          .name = {0},
                          .extension = {0},
                          .attribute = 0,
                          .reserved = 0,
                          .create_time_tenth = 0,
                          .create_time = 0,
                          .create_date = 0,
                          .last_access_date = 0,
                          .first_cluster_high = 0,
                          .write_time = 0,
                          .write_date = 0,
                          .first_cluster_low = 0,
                          .size = 0};

uint32_t fat_start = RESERVED_SECTORS;
uint32_t root_entries_start = RESERVED_SECTORS + (SECTORS_PER_FAT * 2);

void load_root_entries()
{
    read_sectors((char*)root_entries, root_entries_start, 1);
}

void load_fat()
{
    read_sectors((char*)fat, fat_start, 1);
}

void make_fname(char* dest, const char* src, size_t size)
{
    to_uppercase((char*)src);
    strncpy(dest, src, size);
    strpad(dest, size, ' ');
}

void make_fat16_filename(char* filename, char* name, char* ext)
{
    // To uppercase the name
    to_uppercase(filename);

    // Allocate memory
    char* tname = strtok(filename, ".");
    char* text = strtok(NULL, " ");

    // Copy filename to dest
    strcpy(name, tname);
    strcpy(ext, text);

    // Pad with spaceing
    strpad(name, 8, ' ');
    strpad(ext, 3, ' ');
}

DirEntry_t find_file(char* filename)
{
    // Filename
    char name[9];
    char ext[4];
    make_fat16_filename(filename, name, ext);

    for (int i = 0; i < 256; i++)
    {
        if (strncmp(name, (char*)root_entries[i].name, 8) == 0 &&
            strncmp(ext, (char*)root_entries[i].extension, 3) == 0)
        {
            return root_entries[i];
        }
    }
    return empty_entry;
}

int get_next_cluster_number(int current_cluster)
{
    return ((int*)fat)[current_cluster];
}

uint32_t get_sector_number(int current_cluster, int add)
{
    return DATA_SECTOR_START + (current_cluster * 4) + add;
}

void load_file(char* buffer, DirEntry_t file)
{
    uint32_t size = (uint32_t)file.size;
    int current_cluster_number = file.first_cluster_low;
    int sector_count = 0;

    // Load clusters
    while (current_cluster_number != 0xff && size >= 2048)
    {
        load_cluster(buffer, get_sector_number(current_cluster_number, sector_count));
        size -= CLUSTER_SIZE;
        current_cluster_number = get_next_cluster_number(current_cluster_number);
        buffer += CLUSTER_SIZE;
        sector_count += 4;
    }

    // Load sectors
    int i = 0;
    while (size >= 512)
    {
        read_sector(buffer, get_sector_number(current_cluster_number, sector_count));
        size -= SECTOR_SIZE;
        buffer += SECTOR_SIZE;
        sector_count++;
        i++;
    }

    // Load bytes
    if (size > 0)
    {
        read_bytes(buffer, get_sector_number(current_cluster_number, sector_count), 0, size);
    }
}

void* file_read(char* filename)
{
    // Find file
    DirEntry_t file = find_file(filename);
    // Create buffer to hold the file
    void* buffer = malloc((size_t)file.size);
    // Load the file data in buffer
    load_file(buffer, file);
    // Return buffer
    return buffer;
}

void fz_create_file(char* filename)
{
    // Filename
    char name[9];
    char ext[4];
    make_fat16_filename(filename, name, ext);

    int index = 0;
    // Find empty file entry
    for (int i = 0; i < 255; i++)
    {
        if (root_entries[i].first_cluster_low == 0)
        {
            index = i;
            break;
        }
    }

    // Find emty cluster chain
    int cluster_position = 0;
    for (int i = 3; i < 512; i++)
    {
        if (fat[i] == 0)
        {
            cluster_position = i;
            break;
        }
    }

    // Save file informations
    root_entries[index] = (DirEntry_t){
        .extra = "--------------------------------",
        .name = "        ",
        .extension = "   ",
        .attribute = 1,
        .first_cluster_high = 0,
        .first_cluster_low = cluster_position,
        .size = 0,
    };

    // Update fat
    fat[cluster_position] = 0xFFFF;

    // Copy contents
    strncpy((char*)root_entries[index].name, name, 8);
    strncpy((char*)root_entries[index].extension, ext, 3);

    // Write with new entry data
    fz_write_sector((char*)fat, fat_start);
    fz_write_sector((char*)root_entries, root_entries_start);
}

int get_file_index_in_root_directories(DirEntry_t file)
{
    int index = -1;
    for (int i = 0; i < 20; i++)
    {
        if (strncmp((char*)file.name, (char*)root_entries[i].name, 8) == 0 &&
            strncmp((char*)file.extension, (char*)root_entries[i].extension, 3) == 0)
        {
            index = i;
            break;
        }
    }

    return index;
}

void fz_fwrite(DirEntry_t file, const char* data)
{
    // Variables
    int length = strlen(data);
    // int size = (int)file.size;
    int clusters_to_write = 0;
    ClusterChain_t first_cluster = file.first_cluster_low;
    // ClusterChain_t last_cluster = first_cluster;
    // ClusterChain_t end_cluster = 0;

    // Last cluster
    // int rem = size % CLUSTER_SIZE;
    // int offset = rem;

    int rem = length;
    while (rem >= CLUSTER_SIZE)
    {
        clusters_to_write++;
        rem -= CLUSTER_SIZE;
    }

    if (rem > 0)
        clusters_to_write += 1;

    // Write back last cluster with new data
    write_cluster((char*)data, DATA_SECTOR_START + (first_cluster * SECTORS_PER_CLUSTER));

    int file_index = get_file_index_in_root_directories(file);
    // Update file and cluster chain
    root_entries[file_index].size = length;

    // Write with new entry data
    // fz_write_sector((char*)fat, fat_start);
    fz_write_sector((char*)root_entries, root_entries_start);

    // end_cluster = fat[last_cluster];
    // fat[last_cluster] = 0xFFFF;

    // while (end_cluster != END_OF_CLUSTER)
    // {
    //     fat[end_cluster] = 0;
    //     last_cluster = end_cluster;
    //     end_cluster = fat[last_cluster];
    // }

    // fat[end_cluster] = 0;
}

void fz_fappend(DirEntry_t file, const char* data)
{
    // Variables
    int length = strlen(data);
    int size = (int)file.size;
    int clusters_to_write = 0;
    ClusterChain_t last_cluster = file.first_cluster_low;
    ClusterChain_t end_cluster = 0;

    // Last cluster
    int rem = size % CLUSTER_SIZE;
    int offset = rem;

    rem += length;
    while (rem >= CLUSTER_SIZE)
    {
        clusters_to_write++;
        rem -= CLUSTER_SIZE;
    }

    if (rem > 0)
        clusters_to_write += 1;

    end_cluster = fat[last_cluster];
    while (end_cluster != END_OF_CLUSTER)
    {
        last_cluster = end_cluster;
        end_cluster = fat[last_cluster];
    }

    // Read last cluster
    char* buffer = malloc(SECTOR_SIZE * clusters_to_write);
    memset(buffer, 0, SECTOR_SIZE * clusters_to_write);
    if (size > 0)
    {
        load_cluster(buffer, DATA_SECTOR_START + (last_cluster * SECTORS_PER_CLUSTER));
    }
    strncpy((buffer + offset), data, length);

    // Write back last cluster with new data
    write_cluster(buffer, DATA_SECTOR_START + (last_cluster * SECTORS_PER_CLUSTER));
    // Make free the memory
    free(buffer);

    int file_index = get_file_index_in_root_directories(file);
    // Update file and cluster chain
    root_entries[file_index].size += length;

    // Write with new entry data
    // fz_write_sector((char*)fat, fat_start);
    fz_write_sector((char*)root_entries, root_entries_start);
}

void fz_fdelete(DirEntry_t file)
{
    int file_index = get_file_index_in_root_directories(file);
    root_entries[file_index] = empty_entry;
    ClusterChain_t current_cluster = file.first_cluster_low;
    while (current_cluster != 0xFFFF)
    {
        ClusterChain_t next_culster = fat[current_cluster];
        fat[current_cluster] = 0;
        current_cluster = next_culster;
    }

    fz_write_sector((char*)fat, fat_start);
    fz_write_sector((char*)root_entries, root_entries_start);
}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

// FILE* fopen(const char* filename, const char* mode)
// {
//     // Open a file and get a file descriptor
//     int fd = open_file(filename, mode);
//     if (fd < 0)
//         return NULL;

//     // Allocate and initilize the fie structure
//     FILE* file = malloc(sizeof(FILE));
//     if (!file)
//         return NULL;

//     file->fd = fd;
//     file->buffer = malloc(MAX_BUFFER_SIZE);
//     if (!file->buffer)
//     {
//         free(file);
//         return NULL;
//     }

//     // Save file info
//     file->mode = READ;
//     file->size = MAX_BUFFER_SIZE;
//     file->pos = 0;
//     file->flags = 0;

//     // Return the file
//     return file;
// }
