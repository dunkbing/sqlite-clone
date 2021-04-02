#include <iostream>
#include <cstring>

typedef struct
{
    char* buffer;
    size_t bufferLength;
    size_t inputLength;
} InputBuffer;

InputBuffer* newInputBuffer()
{
    InputBuffer* inputBuffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->bufferLength = 0;
    inputBuffer->inputLength = 0;
    return inputBuffer;
}

void printPrompt()
{
    printf("db > ");
}

void readInput(InputBuffer* inputBuffer)
{
    ssize_t bytesRead = getline(&(inputBuffer->buffer), &(inputBuffer->bufferLength), stdin);
    if (bytesRead <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    // Ignore trailing newline
    inputBuffer->inputLength = bytesRead - 1;
    inputBuffer->buffer[bytesRead - 1] = 0;
}

void closeInputBuffer(InputBuffer* inputBuffer) {
    free(inputBuffer->buffer);
    free(inputBuffer);
}

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
} MetaCommandResult;

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;

MetaCommandResult doMetaCommand(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

int main() {
    InputBuffer* inputBuffer = newInputBuffer();
    while (true) {
        printPrompt();
        readInput(inputBuffer);

        if (inputBuffer->buffer[0] == '.') {
            switch (doMetaCommand(inputBuffer)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", inputBuffer->buffer);
                continue;
            }
        }
    }
}