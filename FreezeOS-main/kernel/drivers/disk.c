#include <disk.h>
#include <io.h>
#include <stdio.h>
#include <string.h>

// Constants
#define ATA_PRIMARY_IO 0x1F0
#define ATA_PRIMARY_CONTROL 0x3F6
#define ATA_MASTER 0xA0
#define ATA_SLAVE 0xB0
#define ATA_ERROR 0x01
#define ATA_SECTOR_COUNT 0x02
#define ATA_SECTOR_NUMBER 0x03
#define ATA_CYLINDER_LOW 0x04
#define ATA_CYLINDER_HIGH 0x05
#define ATA_DRIVE_SELECT 0x06
#define ATA_COMMAND 0x07
#define ATA_DATA 0x00
#define ATA_STATUS 0x07
#define ATA_STATUS_BUSY 0x80
#define ATA_STATUS_DRQ 0x08
#define ATA_CMD_READ_PIO 0x20
#define ATA_CMD_WRITE_PIO 0x30

static inline void insl(uint16_t port, const void* address, uint32_t cnt)
{
    asm volatile("cld; rep insl"
                 : "=D"(address), "=c"(cnt)
                 : "d"(port), "0"(address), "1"(cnt)
                 : "memory", "cc");
}

static inline void outsl(uint16_t port, const void* address, uint32_t cnt)
{
    asm volatile("cld; rep outsl"
                 : "=S"(address), "=c"(cnt)
                 : "d"(port), "0"(address), "1"(cnt)
                 : "memory", "cc");
}

void ata_wait_busy()
{
    while (inb(ATA_PRIMARY_IO + ATA_STATUS) & ATA_STATUS_BUSY)
        ;
}
void ata_wait_ready()
{
    while (inb(ATA_PRIMARY_IO + ATA_STATUS) & ATA_STATUS_BUSY)
        ;
}

void ata_wait_drq()
{
    while (!(inb(ATA_PRIMARY_IO + ATA_STATUS) & ATA_STATUS_DRQ))
        ;
}

void read_sector(char* buffer, uint32_t lba)
{
    outb(ATA_PRIMARY_CONTROL, 0x02);  // Disable IRQ's

    outb(ATA_PRIMARY_IO + ATA_SECTOR_COUNT, 1);
    outb(ATA_PRIMARY_IO + ATA_SECTOR_NUMBER, (char)lba);
    outb(ATA_PRIMARY_IO + ATA_CYLINDER_LOW, (char)(lba >> 8));
    outb(ATA_PRIMARY_IO + ATA_CYLINDER_HIGH, (char)(lba >> 16));
    outb(ATA_PRIMARY_IO + ATA_DRIVE_SELECT, 0xE0 | ((lba >> 24) & 0x0F));
    outb(ATA_PRIMARY_IO + ATA_COMMAND, ATA_CMD_READ_PIO);

    // Load the data
    ata_wait_busy();
    ata_wait_drq();
    insl(ATA_PRIMARY_IO + ATA_DATA, buffer, 256);  // 256 Words
}

void fz_write_sector(char* buffer, uint32_t lba)
{
    // printf("fz_write_sector -> lba : %d, buffer : %s\n", lba, buffer);
    ata_wait_ready();
    // outb(ATA_PRIMARY_CONTROL, 0x02);  // Disable IRQ's

    outb(ATA_PRIMARY_IO + ATA_SECTOR_COUNT, 1);
    outb(ATA_PRIMARY_IO + ATA_SECTOR_NUMBER, (char)lba);
    outb(ATA_PRIMARY_IO + ATA_CYLINDER_LOW, (char)(lba >> 8));
    outb(ATA_PRIMARY_IO + ATA_CYLINDER_HIGH, (char)(lba >> 16));
    outb(ATA_PRIMARY_IO + ATA_DRIVE_SELECT, 0xE0 | ((lba >> 24) & 0x0F));
    outb(ATA_PRIMARY_IO + ATA_COMMAND, ATA_CMD_WRITE_PIO);

    ata_wait_drq();

    // for (int i = 0; i < 256; i++)
    // {
    //     outw(ATA_PRIMARY_IO + ATA_DATA, ((uint16_t*)buffer)[i]);
    // }

    outsl(ATA_PRIMARY_IO + ATA_DATA, buffer, 256);  // 256 Words

    ata_wait_ready();

    char status = inb(ATA_PRIMARY_IO + ATA_STATUS);
    if (status & ATA_ERROR)
    {
        puts("Somethis went wrong in fz_write_sector");
    }
}

void read_sectors(char* buffer, uint32_t lba, char sector_count)
{
    for (char i = 0; i < sector_count; i++)
    {
        read_sector(buffer, lba + i);
        buffer = buffer + 512;  // Advance the buffer pointer by 512 bytes
    }
}

void fz_write_sectors(char* buffer, uint32_t lba, char sector_count)
{
    for (char i = 0; i < sector_count; i++)
    {
        fz_write_sector(buffer, lba + i);
        buffer = buffer + 512;  // Advance the buffer pointer by 512 bytes
    }
}

void read_bytes(char* buffer, uint32_t lba, uint16_t offset, uint16_t bytes_count)
{
    char* placeholder[512];

    outb(ATA_PRIMARY_CONTROL, 0x02);  // Disable IRQ's

    outb(ATA_PRIMARY_IO + ATA_SECTOR_COUNT, 1);
    outb(ATA_PRIMARY_IO + ATA_SECTOR_NUMBER, (char)lba);
    outb(ATA_PRIMARY_IO + ATA_CYLINDER_LOW, (char)(lba >> 8));
    outb(ATA_PRIMARY_IO + ATA_CYLINDER_HIGH, (char)(lba >> 16));
    outb(ATA_PRIMARY_IO + ATA_DRIVE_SELECT, 0xE0 | ((lba >> 24) & 0x0F));
    outb(ATA_PRIMARY_IO + ATA_COMMAND, ATA_CMD_READ_PIO);

    // Load the data
    ata_wait_busy();
    ata_wait_drq();
    insl(ATA_PRIMARY_IO + ATA_DATA, placeholder, 256);  // 256 Words

    for (uint16_t i = 0; i <= bytes_count; i++)
    {
        buffer[i] = ((char*)placeholder)[offset + i];
    }
}

void load_cluster(char* buffer, uint32_t lba)
{
    for (char i = 0; i < 4; i++)
    {
        read_sector(buffer, lba + i);
        buffer = buffer + 512;  // Advance the buffer pointer by 512 bytes
    }
}

void write_cluster(char* buffer, uint32_t lba)
{
    // puts(buffer);
    // puti(lba);
    for (char i = 0; i < 4; i++)
    {
        fz_write_sector(buffer, lba + i);
        buffer = buffer + 512;  // Advance the buffer pointer by 512 bytes
    }
}