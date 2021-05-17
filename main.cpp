#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

struct InputBuffer
{
    std::string buffer;
    size_t bufferLength{};
    size_t inputLength{};
};

InputBuffer* newInputBuffer()
{
    auto inputBuffer = new InputBuffer;
    inputBuffer->buffer = "";
    inputBuffer->bufferLength = 0;
    inputBuffer->inputLength = 0;
    return inputBuffer;
}

void printPrompt()
{
    std::cout << "db > ";
}

void readInput(InputBuffer* inputBuffer)
{
    std::getline(std::cin, inputBuffer->buffer);
    if (inputBuffer->buffer.length() <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    // Ignore trailing newline
    inputBuffer->inputLength = inputBuffer->buffer.length() - 1;
}

void closeInputBuffer(InputBuffer* inputBuffer) {
    delete inputBuffer;
}

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
} MetaCommandResult;

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
  StatementType type;
} Statement;

MetaCommandResult doMetaCommand(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer.c_str(), ".exit") == 0) {
        exit(EXIT_SUCCESS);
    }
    return META_COMMAND_UNRECOGNIZED_COMMAND;
}

PrepareResult prepareStatement(InputBuffer* inputBuffer, Statement* statement) {
    if (strncmp(inputBuffer->buffer.c_str(), "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strcmp(inputBuffer->buffer.c_str(), "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            printf("This is where we would do an insert.\n");
            break;
        case (STATEMENT_SELECT):
            printf("This is where we would do a select.\n");
            break;
    }
}

void main() {
    InputBuffer* inputBuffer = newInputBuffer();
    while (true) {
        printPrompt();
        readInput(inputBuffer);

        if (inputBuffer->buffer[0] == '.') {
            switch (doMetaCommand(inputBuffer)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    std::cout << "Unrecognized command '" << inputBuffer->buffer << "'.\n";
                continue;
            }
        }

        Statement statement;
        switch (prepareStatement(inputBuffer, &statement)) {
          case (PREPARE_SUCCESS):
            break;
          case (PREPARE_UNRECOGNIZED_STATEMENT):
              std::cout << "Unrecognized keyword at start of '" << inputBuffer->buffer << "'.\n";
            continue;
        }

        execute_statement(&statement);
        printf("Executed.\n");
    }
}
