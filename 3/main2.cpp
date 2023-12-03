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
int size;

int find_width()
{
    int w=0;
    while (map[w]!='\n') { w++; }
    return w;
}

bool is_gear(char c)
{
    return c=='*';
}

bool is_digit(int x, int y)
{
    if (x < 0 || x >= width) return false;
    if (y < 0 || y >= height) return false;
    char c = map[y*stride + x];
    return c>='0' && c<='9';
}

bool find_number(int x, int y, int *store, int & index)
{
    if (!is_digit(x,y)) return false;
    while (is_digit(x-1,y)) x--;
    int number = 0;
    while (is_digit(x,y))
    {
        number*=10;
        number += map[y*stride+x] - '0';
        x++;
    }
    store[index++] = number;
    return true;

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
    size = fileInfo.st_size;
    stride = width + 1;
    int total=0;
    for (int y=0; y<height; y+=1)
    {
        for (int x=0; x<width; x+=1)
        {
            if (!is_gear(map[x+y*stride]))
            {
                continue;
            }
            printf("*\n");
            int index = 0;
            int store[4];
            if (!find_number(x, y-1, store, index))
            {
                find_number(x-1, y-1, store, index);
                find_number(x+1, y-1, store, index);
            }
            find_number(x-1, y, store, index);
            find_number(x+1, y, store, index);
            if (!find_number(x, y+1, store, index))
            {
                find_number(x-1, y+1, store, index);
                find_number(x+1, y+1, store, index);
            }
            if (index == 2)
                total += store[0] * store[1];
        }
    }
    printf("%d\n", total);
    return 0;
}
