#ifndef LOADER_H
#define LOADER_H

#include "types.h"

typedef struct
{
    uint16_t position;
} ClusterChain_t;

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

void print_string(char c);
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);
void insl(uint16_t port, void* address, int cnt);
int str_cmp_in(char* str1, char* str2, int count);
void ata_wait_busy();
void ata_wait_drq();
void read_sector(uint8_t* buffer, uint32_t lba);
void read_sectors(uint8_t* buffer, uint32_t lba, uint8_t sector_count);
void read_bytes(uint8_t* buffer, uint32_t lba, uint16_t offset, uint16_t bytes_count);
void load_cluster(uint8_t* buffer, uint32_t lba);
void load_root_entries();
void load_fat();
DirEntry_t find_file(char name[], char extension[]);
uint16_t get_next_cluster_number(uint16_t current_cluster);
uint32_t get_sector_number(int current_cluster, int add);
void load_file(uint8_t* buffer, DirEntry_t file);

#endif