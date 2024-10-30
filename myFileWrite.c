#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 100
#define MAX_TEXT 1000

void writeFile(const char *filename, int append);

int main() {
    char filename[MAX_FILENAME];
    char text[MAX_TEXT];
    FILE *file;
    int choice;

    // Ask the user to input the filename
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Check if the file already exists
    file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        printf("File already exists. Do you want to:\n");
        printf("1. Overwrite the file\n");
        printf("2. Append to the file\n");
        printf("Enter your choice (1 or 2): ");
        scanf("%d", &choice);
        if (choice == 1) {
            writeFile(filename, 0);
        } else if (choice == 2) {
            writeFile(filename, 1);
        } else {
            printf("Invalid choice. Exiting.\n");
            return 1;
        }
    } else {
        writeFile(filename, 0);
    }

    return 0;
}

void writeFile(const char *filename, int append) {
    FILE *file;
    char text[MAX_TEXT];

    if (append) {
        file = fopen(filename, "a");
    } else {
        file = fopen(filename, "w");
    }

    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    printf("Enter text to write to the file:\n");
    getchar(); // To consume the newline character left by scanf
    fgets(text, MAX_TEXT, stdin);

    fprintf(file, "%s", text);
    fclose(file);

    printf("Text successfully written to the file.\n");
}
