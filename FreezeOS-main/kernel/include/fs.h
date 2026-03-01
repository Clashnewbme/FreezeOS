
#ifndef FS_H
#define FS_H

#include <stdint.h>
typedef uint16_t ClusterChain_t;

typedef struct
{
    uint8_t extra[32];
    uint8_t name[8];
    uint8_t extension[3];
    uint8_t attribute;
    uint8_t reserved;
    uint8_t create_time_tenth;
    uint16_t create_time;
    uint16_t create_date;
    uint16_t last_access_date;
    uint16_t first_cluster_high;
    uint16_t write_time;
    uint16_t write_date;
    uint16_t first_cluster_low;
    uint32_t size;

} __attribute__((packed)) DirEntry_t;

typedef struct
{
    char byte[512];
} __attribute__((packed)) singleSector_t;

void load_fat();
void load_root_entries();
DirEntry_t find_file(char* filename);

void make_fat16_filename(char* filename, char* name, char* ext);
void load_file(char* buffer, DirEntry_t file);
int get_next_cluster_number(int current_cluster);

void* file_read(char* filename);

void fz_create_file(char* filename);

void fz_fwrite(DirEntry_t file, const char* data);
void fz_fappend(DirEntry_t file, const char* data);
void fz_fdelete(DirEntry_t file);

#endif