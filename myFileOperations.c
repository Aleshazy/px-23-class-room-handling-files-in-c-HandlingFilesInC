#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 100
#define MAX_TEXT 1000

// Function prototypes
void readFile(const char *filename);
void writeFile(const char *filename, int append);
void countFile(const char *filename);

int main() {
    char filename[MAX_FILENAME];
    int choice;
    int append;

    // Ask the user to input the filename
    printf("Enter the filename: ");
    scanf("%s", filename);

    while (1) {
        // Display menu
        printf("\nMenu:\n");
        printf("1. Read file\n");
        printf("2. Write to file (overwrite)\n");
        printf("3. Append to file\n");
        printf("4. Count words, lines, and characters\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readFile(filename);
                break;
            case 2:
                append = 0;
                writeFile(filename, append);
                break;
            case 3:
                append = 1;
                writeFile(filename, append);
                break;
            case 4:
                countFile(filename);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    char ch;

    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    printf("File content:\n");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
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

    printf("Updated file content:\n");
    readFile(filename);
}

void countFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    char ch;
    int words = 0, lines = 0, characters = 0;
    int inWord = 0;

    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    while ((ch = fgetc(file)) != EOF) {
        characters++;
        if (ch == '\n') {
            lines++;
        }
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            words++;
        }
    }
    fclose(file);

    printf("Word count: %d\n", words);
    printf("Line count: %d\n", lines);
    printf("Character count: %d\n", characters);
}
