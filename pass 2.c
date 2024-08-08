#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void display(FILE *intermediate_fp, FILE *symtab_fp, FILE *output_fp, FILE *objcode_fp);

int main()
 {
    // Declare file pointers
    FILE *intermediate_fp, *symtab_fp, *output_fp, *objcode_fp;

    // Open files for reading and writing
    intermediate_fp = fopen("out.txt", "r");
    symtab_fp = fopen("symtbl.txt", "r");
    output_fp = fopen("output1.txt", "w");
    objcode_fp = fopen("objcode.txt", "w");

    // Check if files opened successfully
    if (intermediate_fp == NULL || symtab_fp == NULL || output_fp == NULL || objcode_fp == NULL) 
	{
        perror("Error opening files");
        return EXIT_FAILURE;
    }

    // Initialize variables
    char label[10], opcode[10], operand[10], mnemonic[20][20] = {"LDA", "STA", "LDCH", "STCH", "MUL"};
    char code[20][20] = {"33", "44", "53", "57", "20"};
    int address, start, finaddr, prevaddr, diff;

    // Read first line of intermediate file
    fscanf(intermediate_fp, "%s %s %s", label, opcode, operand);

    // Handle START directive
    if (strcmp(opcode, "START") == 0) 
	{
        fprintf(output_fp, "\t%s\t%s\t%s\n", label, opcode, operand);
        fprintf(objcode_fp, "H^%s^00%s^00%d\n", label, operand, finaddr);
        fscanf(intermediate_fp, "%d %s %s %s", &address, label, opcode, operand);
        start = address;
        diff = prevaddr - start;
        fprintf(objcode_fp, "T^00%d^%d", address, diff);
    }

    // Process each line until END directive is encountered
    while (strcmp(opcode, "END") != 0) 
	{
        if (strcmp(opcode, "BYTE") == 0) 
		{
            fprintf(output_fp, "%d\t%s\t%s\t%s\t", address, label, opcode, operand);
            int len = strlen(operand);
            int actual_len = len - 3;
            fprintf(objcode_fp, "^");
            for (int i = 2; i < (actual_len + 2); i++) 
			{
                fprintf(output_fp, "%c", operand[i]);
                fprintf(objcode_fp, "%c", operand[i]);
            }
            fprintf(output_fp, "\n");
        } 
		else if (strcmp(opcode, "WORD") == 0) 
		{
            int value = atoi(operand);
            fprintf(output_fp, "%d\t%s\t%s\t%s\t00000%d\n", address, label, opcode, operand, value);
            fprintf(objcode_fp, "^00000%d", value);
        } 
		else if (strcmp(opcode, "RESB") == 0 || strcmp(opcode, "RESW") == 0)
		{
            fprintf(output_fp, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);
        } else 
		{
            int j = 0;
            while (strcmp(opcode, mnemonic[j]) != 0 && j < 5) 
			{
                j++;
            }
            if (j < 5) 
			{
                if (strcmp(operand, "COPY") == 0) 
				{
                    fprintf(output_fp, "%d\t%s\t%s\t%s\t%s0000\n", address, label, opcode, operand, code[j]);
                } 
				else 
				{
                    char symbol[10];
                    int add;
                    rewind(symtab_fp);
                    while (fscanf(symtab_fp, "%s %d", symbol, &add) != EOF && strcmp(operand, symbol) != 0);
                    fprintf(output_fp, "%d\t%s\t%s\t%s\t%s%d\n", address, label, opcode, operand, code[j], add);
                    fprintf(objcode_fp, "^%s%d", code[j], add);
                }
            }
        }
        prevaddr = address;
        fscanf(intermediate_fp, "%d %s %s %s", &address, label, opcode, operand);
    }

    // Write END directive
    fprintf(output_fp, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);
    fprintf(objcode_fp, "\nE^00%d", start);

    // Close all files
    fclose(objcode_fp);
    fclose(output_fp);
    fclose(symtab_fp);
    fclose(intermediate_fp);

    // Display contents of files
    display(intermediate_fp, symtab_fp, output_fp, objcode_fp);

    return 0;
}

// Function to display contents of files
void display(FILE *intermediate_fp, FILE *symtab_fp, FILE *output_fp, FILE *objcode_fp) 
{
    char ch;

    // Display intermediate file
    printf("\n\nThe contents of Intermediate file:\n\n");
    rewind(intermediate_fp);
    while ((ch = fgetc(intermediate_fp)) != EOF) 
	{
        printf("%c", ch);
    }

    // Display symbol table file
    printf("\n\nThe contents of Symbol Table:\n\n");
    rewind(symtab_fp);
    while ((ch = fgetc(symtab_fp)) != EOF) 
	{
        printf("%c", ch);
    }

    // Display output file
    printf("\n\nThe contents of Output file:\n\n");
    rewind(output_fp);
    while ((ch = fgetc(output_fp)) != EOF) 
	{
        printf("%c", ch);
    }

    // Display object code file
    printf("\n\nThe contents of Object code file:\n\n");
    rewind(objcode_fp);
    while ((ch = fgetc(objcode_fp)) != EOF) 
	{
        printf("%c", ch);
    }
}
