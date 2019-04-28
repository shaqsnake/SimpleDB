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

void read_input(InputBuffer *input_buffer)
{
    ssize_t bytes_read = getline(&input_buffer->buffer, &input_buffer->buf_size, stdin);

    if (bytes_read <= 0)
    {
        perror("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // Remove '\n' at trailing
    input_buffer->buffer[bytes_read - 1] = 0;
    input_buffer->input_len = bytes_read - 1;
}

void close_input_buffer(InputBuffer *input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}

void main(int argc, const char *argv[])
{
    InputBuffer *input_buffer = new_input_buffer();

    while (1)
    {
        printf("sdb > ");
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0)
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("Unreconized command '%s'.\n", input_buffer->buffer);
        }
    }
}