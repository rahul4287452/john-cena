#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

struct Symbol {
    char name[20];
    int address;
} symtab[50];

struct Literal {
    char name[20];
    int address;
} littab[50];

void main() {
    FILE *source, *intermediate;
    char line[100], label[20], opcode[20], operand[20];
    int lc = 0, symIndex = 0, litIndex = 0, i;
    int reg[16] = {0};

    clrscr();

    source = fopen("pg1.ASM", "r");
    intermediate = fopen("intermediate.txt", "w");

    if(source == NULL || intermediate == NULL) {
        printf("Error opening file.\n");
        getch();
        exit(1);
    }

    while(fgets(line, sizeof(line), source)) {
        // Initialize label, opcode, operand
        strcpy(label, "");
        strcpy(opcode, "");
        strcpy(operand, "");

        sscanf(line, "%s %s %s", label, opcode, operand);

        if(strcmp(opcode, "START") == 0) {
            lc = atoi(operand);
            // Save program label to symbol table
            strcpy(symtab[symIndex].name, label);
            symtab[symIndex].address = lc;
            symIndex++;
            continue;
        }

        if(strcmp(label, "USING") == 0) {
            reg[15] = 1; // Set Base Register
            continue;
        }

        if(strcmp(opcode, "DC") == 0 || strcmp(opcode, "DS") == 0) {
            // Save Data Symbol to Symbol Table
            strcpy(symtab[symIndex].name, label);
            symtab[symIndex].address = lc;
            symIndex++;
            lc += 4; // assuming each DC/DS reserves 4 bytes
            continue;
        }

        if(strcmp(label, "END") == 0) {
            // Assign addresses to literals
            for(i = 0; i < litIndex; i++) {
                littab[i].address = lc;
                lc += 4;
            }
            break;
        }

        // Normal instruction line
        fprintf(intermediate, "%d %s", lc, line);

        if(operand[0] == '=') {
            // It is a literal
            strcpy(littab[litIndex].name, operand);
            litIndex++;
        }

        lc += 4;
    }

    fclose(source);
    fclose(intermediate);

    // Print Symbol Table
    printf("\nSymbol Table:\n");
    for(i = 0; i < symIndex; i++) {
        printf("%s\t%d\n", symtab[i].name, symtab[i].address);
    }

    // Print Literal Table
    printf("\nLiteral Table:\n");
    for(i = 0; i < litIndex; i++) {
        printf("%s\t%d\n", littab[i].name, littab[i].address);
    }

    getch();
}
