#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

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

 // Close the disk image
 close(fd);

 return 0;
}
