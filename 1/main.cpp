#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
int main(int argc, const char *argv[])
{

const char *filepath = argv[1];
int fd = open(filepath, O_RDONLY, (mode_t)0600);
struct stat fileInfo = {0};

fstat(fd, &fileInfo);
char *map = (char*)mmap(0, fileInfo.st_size, PROT_READ, MAP_SHARED, fd, 0);
int t_first = 0;
int t_second = 0;
int first = -1;
int second = 0;
auto start = map;
auto end = start + fileInfo.st_size;

for (auto p = start; p != end ; ++p)
{
    if (*p >= '0' && *p <= '9')
    {
        second = *p - '0';
        if (first == -1)
            first = second;
    }
    else if (*p == '\n')
    {
        t_first += first;
        t_second += second;
        first = -1;
    }
}
printf("%d\n", t_first*10 + t_second);
return 0;
}
