#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct InputBuffer
{
    char *buffer;
    size_t buf_size;
    ssize_t input_len;
} InputBuffer;

InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buf_size = 0;
    input_buffer->input_len = 0;
    return input_buffer;
}

void main(int argc, const char *argv[])
{
    InputBuffer *input_buffer = new_input_buffer();

    while (1)
    {
        printf("sdb > ");
        ssize_t bytes_read = getline(&input_buffer->buffer, &input_buffer->buf_size, stdin);
        input_buffer->buffer[bytes_read - 1] = 0;
        if (strcmp(input_buffer->buffer, ".exit") == 0)
        {
            exit(0);
        }
        else
        {
            printf("Unreconized command '%s'.\n", input_buffer->buffer);
        }
    }
}