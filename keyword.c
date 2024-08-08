#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    // List of C keywords
    const char* keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
    };
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    char word[100];
    
    printf("Enter your code (end with Ctrl+D):\n");
    
    int ch, i = 0;
    while ((ch = getchar()) != EOF) {
        // Skip non-alphabetic characters
        if (!isalpha(ch)) {
            continue;
        }

        // Read the word
        i = 0;
        do {
            word[i++] = ch;
            ch = getchar();
        } while (isalnum(ch) || ch == '_');
        word[i] = '\0';

        // Check if the word is a keyword
        for (int j = 0; j < num_keywords; ++j) {
            if (strcmp(word, keywords[j]) == 0) {
                printf("%s\n", word);
                break;
            }
        }
    }

    return 0;
}


	
