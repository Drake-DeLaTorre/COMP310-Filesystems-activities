#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "fat.h"

int read_sector(int fd, unsigned int sector_num, char *buf) {
 // Seek to the sector
 if (lseek(fd, 512*sector_num, SEEK_SET) == -1) {
    perror("Error seeking");
    return -1;
 }

 // Read the sector
 if (read(fd, buf, 512) != 512) {
    perror("Error reading");
    return -1;
 }

 return 0;
}

int main() {
 int fd;
 char sector_buf[512];

 // Open the disk image
 fd = open("test.img", O_RDONLY);

 // Read the sector
 if (read_sector(fd, 0, sector_buf) == -1) {
    return 1;
 }

 // Print the contents of the sector in hex
 for (int i = 0; i < 512; i++) {
    printf("%02x ", sector_buf[i]);
 }
 printf("\n");
// Define a boot sector buffer.
char boot_sector[512];

// Inside main:

// Read in the boot sector from the disk image.
read_sector( 0, 512, boot_sector);

// Define a pointer to the boot sector.
struct boot_sector *bsptr = (struct boot_sector *) boot_sector;

// Extract the relevant data from the boot sector.
printf("num_sectors_per_cluster = %d\n", bsptr->num_sectors_per_cluster);
printf("num_reserved_sectors = %d\n", bsptr->num_reserved_sectors);
printf("num_fat_tables = %d\n", bsptr->num_fat_tables);
printf("num_root_dir_entries = %d\n", bsptr->num_root_dir_entries);
 // Close the disk image
 close(fd);

 return 0;
}

