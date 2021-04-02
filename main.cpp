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

int main() {
    InputBuffer* input_buffer = newInputBuffer();
    while (true) {
        printPrompt();
        readInput(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            closeInputBuffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }
}