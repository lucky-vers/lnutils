#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 1024

int read_file(char name[]) {
    FILE *file;
    char filename[1024];
    int lines;

    strncpy(filename, name, sizeof(filename));

    file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: file '%s' does not exist\n", filename);
        return 1;
    }

    char *buffer = (char *)malloc(INITIAL_BUFFER_SIZE);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    size_t buffer_size = INITIAL_BUFFER_SIZE;
    size_t line_length;

    while (fgets(buffer, buffer_size, file) != NULL) {
        line_length = strlen(buffer);

        if (buffer[line_length - 1] != '\n' && !feof(file)) {
            buffer_size *= 2;
            buffer = (char *)realloc(buffer, buffer_size);

            if (buffer == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                fclose(file);
                return 1;
            }

            // Move file pointer back to the beginning of the line
            fseek(file, -((long)line_length), SEEK_CUR);
            continue;
        }

        lines++;
    }

    printf("%d %s\n", lines, filename);

    free(buffer);
    fclose(file);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc >= 2) {
        read_file(argv[1]);
    }

    return 0;
}

