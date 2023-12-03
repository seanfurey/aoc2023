#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

char *map;
int width;
int height;
int stride;

int find_width()
{
    int w=0;
    while (map[w]!='\n') { w++; }
    return w;
}

int main(int argc, const char *argv[])
{

const char *filepath = argv[1];
int fd = open(filepath, O_RDONLY, (mode_t)0600);
struct stat fileInfo = {0};

fstat(fd, &fileInfo);
map = (char*)mmap(0, fileInfo.st_size, PROT_READ, MAP_SHARED, fd, 0);

width = find_width();
height = fileInfo.st_size / width;
stride = width + 1;
for (int y=0; y<fileInfo.st_size; y+=stride)
{
for (int x=0; x<width; x+=1)
{
printf("%c", map[y+x]);
}
printf("\n");
}
printf("%d\n", width);
return 0;
}
