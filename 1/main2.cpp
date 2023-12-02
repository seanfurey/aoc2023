#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>

const char numbers[][8] =
{
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};
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
    int second = -1;
    auto start = map;
    auto end = start + fileInfo.st_size;
    int tracker[9] = {0};

    for (auto p = start; p != end ; ++p)
    {
        for (unsigned i=0; i<9; i++)
        {
            if (*p == numbers[i][tracker[i]])
            {
                tracker[i]++;
                if (tracker[i] == strlen(numbers[i]))
                    second = i+1;
                else
                    continue;
            }
            tracker[i]=0;
            if (*p == numbers[i][tracker[i]])
                tracker[i]++;
        }
        if (*p >= '0' && *p <= '9')
        {
            second = *p - '0';
        }
        if (first == -1 && second != -1)
            first = second;
        if (*p == '\n')
        {
            t_first += first;
            t_second += second;
            second = first = -1;
            memset(tracker, 0, sizeof tracker);
        }
    }
    printf("%d\n", t_first*10 + t_second);
    return 0;
}
