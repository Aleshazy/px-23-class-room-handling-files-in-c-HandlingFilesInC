#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME 100

// Function to count words in a string
int countWords(const char *str) {
    int count = 0;
    int inWord = 0;

    while (*str) {
        if (*str == ' ' || *str == '\n' || *str == '\t') {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            count++;
        }
        str++;
    }
    return count;
}

int main() {
    char filename[MAX_FILENAME];
    FILE *file;
    char *buffer;
    long fileSize;
    int wordCount;

    // Ask the user to input the filename
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Handle empty file case
    if (fileSize == 0) {
        printf("The file is empty.\n");
        fclose(file);
        return 0;
    }

    // Allocate memory to read the file
    buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    // Read the file content
    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    // Count the number of words
    wordCount = countWords(buffer);

    // Print the file content and word count
    printf("File content:\n%s\n", buffer);
    printf("Word count: %d\n", wordCount);

    // Clean up
    free(buffer);
    fclose(file);

    return 0;
}
