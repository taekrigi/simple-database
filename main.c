#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
    char* buffer;
    size_t bufferLength;
    ssize_t inputLength;
} InputBuffer;

typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE + 1];
  char email[COLUMN_EMAIL_SIZE + 1];
} Row;

InputBuffer* createInputBuffer() {
    InputBuffer* inputBuffer = malloc(sizeof(InputBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->bufferLength = 0;
    inputBuffer->inputLength = 0;

    return inputBuffer;
}

void printPrompt() {
    printf("db > ");
}

void readInput(InputBuffer *inputBuffer) {
    ssize_t bytesRead = getline(&(inputBuffer->buffer), &(inputBuffer->bufferLength), stdin);

    if (bytesRead <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    inputBuffer->inputLength = bytesRead - 1;
    inputBuffer->buffer[bytesRead - 1] = 0;
}

void prepareInsert(InputBuffer* inputBuffer, Row* row) {
    char* keyword = strtok(inputBuffer->buffer, " ");
    char* idString = strtok(NULL, " ");
    char* username = strtok(NULL, " ");
    char* email = strtok(NULL, " ");

    int id = atoi(idString);

    row->id = id;
    strcpy(row->username, username);
    strcpy(row->email, email);
    
}

int main(int argc, char* argv[]) {
    char* filename = "test.db";

    InputBuffer* inputBuffer = createInputBuffer();

    while (true) {
        printPrompt();
        readInput(inputBuffer);
        Row row;
        prepareInsert(inputBuffer, &row);
    }

    return 0;
}