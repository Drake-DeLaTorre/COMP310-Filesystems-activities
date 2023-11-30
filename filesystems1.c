#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int read_sector(int fd, unsigned int sector_num, char *buf) {
 if (lseek(fd, 512*sector_num, SEEK_SET) == -1) {
    perror("Error seeking");
    return -1;
 }

 if (read(fd, buf, 512) != 512) {
    perror("Error reading");
    return -1;
 }

 return 0;
}

int main() {
 int fd;
 char sector_buf[512];

 fd = open("test.img", O_RDONLY);

 if (read_sector(fd, 0, sector_buf) == -1) {
    return 1;
 }

 for (int i = 0; i < 512; i++) {
    printf("%02x ", sector_buf[i]);
 }
 printf("\n");

 close(fd);

 return 0;
}
