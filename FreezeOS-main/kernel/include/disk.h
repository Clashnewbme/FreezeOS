#ifndef DISK_H
#define DISK_H

#include <stdint.h>

void ata_wait_busy();
void ata_wait_drq();

void read_sector(char* buffer, uint32_t lba);
void read_sectors(char* buffer, uint32_t lba, char sector_count);
void read_bytes(char* buffer, uint32_t lba, uint16_t offset, uint16_t bytes_count);
void load_cluster(char* buffer, uint32_t lba);

void fz_write_sector(char* buffer, uint32_t lba);
void fz_write_sectors(char* buffer, uint32_t lba, char sector_count);
void write_cluster(char* buffer, uint32_t lba);

#endif