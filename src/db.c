#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void main(int argc, const char *argv[])
{
    char *buffer;
    size_t bufsize = 32;
    buffer = (char *)malloc(sizeof(char) * bufsize);

    while (1)
    {
        printf("sdb > ");
        ssize_t bytes_read = getline(&buffer, &bufsize, stdin);
        buffer[bytes_read - 1] = 0;
        if (strcmp(buffer, ".exit") == 0)
        {
            exit(0);
        }
        else
        {
            printf("Unreconized command '%s'.\n", buffer);
        }
    }
}