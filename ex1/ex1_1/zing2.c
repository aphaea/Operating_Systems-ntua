#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
void zing()
{
char *getlogin();
char *name;
name = getlogin();
if (name == NULL) {
perror("getlogin");
exit(1);
}if (write(1, "Bye bye ", strlen("Bye bye ")) < 0) {
perror("write");
exit(1);
}
write(1, name, strlen(name));
write(1, "!\n", strlen("!\n"));
}