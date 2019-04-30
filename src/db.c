#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdint.h>
#include "db.h"

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

MetaCommandResult exec_meta_command(InputBuffer *input_buffer)
{
    if (strcmp(input_buffer->buffer, ".exit") == 0)
    {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_COMMAND_FAIL;
    }
}

PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement)
{
    if (strncmp(input_buffer->buffer, "insert", 6) == 0)
    {
        statement->type = STATEMENT_INSERT;
        int args_assigned = sscanf(input_buffer->buffer, "insert %d %s %s", &(statement->row_to_insert.id), statement->row_to_insert.username, statement->row_to_insert.email);
        if (args_assigned < 3)
        {
            return PREPARE_SYSTAX_ERROR;
        }
        return PREPARE_SUCCESS;
    }
    if (strncmp(input_buffer->buffer, "select", 6) == 0)
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_FAIL;
}

void execute_statement(Statement *statement)
{
    switch (statement->type)
    {
    case (STATEMENT_INSERT):
        printf("Inserting...\n");
        break;
    case (STATEMENT_SELECT):
        printf("Selecting...\n");
        break;
    }
}

void serialize_row(Row *src, void *dest)
{
    memcpy(dest + ID_OFFSET, &(src->id), ID_SIZE);
    memcpy(dest + USERNAME_OFFSET, &(src->username), USERNAME_SIZE);
    memcpy(dest + EMAIL_OFFSET, &(src->email), EMAIL_SIZE);
}

void deserialize_row(void *src, Row *dest)
{
    memcpy(&(dest->id), src + ID_OFFSET, ID_SIZE);
    memcpy(&(dest->username), src + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(dest->email), src + EMAIL_OFFSET, EMAIL_SIZE);
}

void main(int argc, const char *argv[])
{
    InputBuffer *input_buffer = new_input_buffer();

    while (1)
    {
        printf("sdb > ");
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.')
        {
            switch (exec_meta_command(input_buffer))
            {
            case (META_COMMAND_SUCCESS):
                continue;
            case (META_COMMAND_FAIL):
                printf("Unreconized command '%s'.\n", input_buffer->buffer);
                continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
        case (PREPARE_SUCCESS):
            break;
        case (PREPARE_SYSTAX_ERROR):
            printf("Syntax error. Could not parse statement '%s'.\n", input_buffer->buffer);
            continue;
        case (PREPARE_FAIL):
            printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
            continue;
        }

        execute_statement(&statement);
        printf("Executed %s\n", input_buffer->buffer);
    }
}