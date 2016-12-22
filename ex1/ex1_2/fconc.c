#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
void doWrite(int fd, const char *buff, int len)
{
ssize_t idx;
ssize_t wcnt;
idx = 0;
do {
wcnt = write(fd, buff + idx, len - idx);
if (wcnt < 0) {
perror("write");
exit(1);
}
idx += wcnt;
} while (idx < len);
}
void write_file(int fd, const char *infile)
{
int fd1;
fd1 = open(infile, O_RDONLY);
if (fd1 < 0) {
perror("open");
exit(1);
}
char buff[1024];
ssize_t rcnt;
do {
rcnt = read(fd1, buff, 1024);
if (rcnt < 0) {
perror("read");
exit(1);
}
else {
doWrite(fd, buff, rcnt);
}
} while (rcnt != 0);if (close(fd1) < 0) {
perror("close");
exit(1);
}
}
int main(int argc, char **argv) {
int fd;
if (argc < 3 || argc > 4) {
write(1, "Usage: ./fconc infile1 infile2 [outfile (default:fconc.out)]\n", strlen("Usage:
./fconc infile1 infile2 [outfile (default:fconc.out)]\n"));
exit(1);
}
if (argc < 4) {
fd = open("fconc.out", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
if (fd < 0) {
perror("open");
exit(1);
}
}
if (argc == 4) {
if ((strcmp(argv[1],argv[3])==0) || (strcmp(argv[2],argv[3])==0)) {
write(1, "error: give another outfile\n", strlen("error: give another outfile\n"));
exit(1);
}
fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
if (fd < 0) {
perror("open");
exit(1);
}
}
write_file(fd, argv[1]);
write_file(fd, argv[2]);
if (close(fd) < 0) {
perror("close");
exit(1);
}