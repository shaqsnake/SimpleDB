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

#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)
// const uint32_t ID_SIZE = size_of_attribute(Row, id);
// const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
// const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
// const uint32_t ID_OFFSET = 0;
#define ID_SIZE size_of_attribute(Row, id)
#define USERNAME_SIZE size_of_attribute(Row, username)
#define EMAIL_SIZE size_of_attribute(Row, email)
#define ID_OFFSET 0
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = ID_OFFSET + ID_SIZE + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;