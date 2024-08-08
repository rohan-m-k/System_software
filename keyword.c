#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_KEYWORDS 32
#define MAX_BUFFER_SIZE 256
#define MAX_SOURCE_SIZE 1024

const char *keywords[MAX_KEYWORDS] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", 
    "double", "else", "enum", "extern", "float", "for", "goto", "if", 
    "int", "long", "register", "return", "short", "signed", "sizeof", 
    "static", "struct", "switch", "typedef", "union", "unsigned", 
    "void", "volatile", "while"
};

int isKeyword(const char *str) {
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void lexicalAnalysis(const char *sourceCode) {
    char buffer[MAX_BUFFER_SIZE];
    int i = 0, j = 0;

    while (sourceCode[i] != '\0') {
        if (isalnum(sourceCode[i])) {
            buffer[j++] = sourceCode[i];
        } else if ((sourceCode[i] == ' ' || sourceCode[i] == '\n' || sourceCode[i] == '\t' || 
                    sourceCode[i] == ',' || sourceCode[i] == ';' || sourceCode[i] == '(' || 
                    sourceCode[i] == ')') && j > 0) {
            buffer[j] = '\0';
            j = 0;
            
            if (isKeyword(buffer)) {
               printf("Keyword: %s\n", buffer);
            }
        }
        i++;
    }
}


int main() {
    char sourceCode[MAX_SOURCE_SIZE];
    char filename[MAX_BUFFER_SIZE];

    printf("Enter the filename of the source code: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    printf("Source Code:\n");
    while (fgets(sourceCode, MAX_SOURCE_SIZE, file)) {
        printf("%s", sourceCode);
        lexicalAnalysis(sourceCode);
    }

    fclose(file);
    return 0;
}
