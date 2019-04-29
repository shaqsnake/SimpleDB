#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct InputBuffer
{
    char *buffer;
    size_t buf_size;
    ssize_t input_len;
} InputBuffer;

typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_FAIL
} MetaCommandResult;

typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT,
} StatementType;

typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_FAIL,
    PREPARE_SYSTAX_ERROR
} PrepareResult;

typedef struct Row
{
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

typedef struct Statement
{
    StatementType type;
    Row row_to_insert;
} Statement;