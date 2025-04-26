#include <stdio.h>
#include <conio.h>   // Turbo C uses conio.h for clrscr() and getch()
#include <string.h>

struct ThreeAddressCode {
    char op;        // Operator (+, -, *, /, =)
    char arg1[10];  // First operand
    char arg2[10];  // Second operand
    char result[10];// Result variable
};

struct ThreeAddressCode intermediateCode[100];  // Array to store intermediate code
int codeIndex = 0;                               // Index for intermediate code array
int tempCount = 0;                               // Count for temporary variables

// Generate a new temporary variable name
void newTemp(char temp[]) {
    sprintf(temp, "t%d", tempCount++);
}

// Generate three-address code for an expression
void generateThreeAddressCode(char op, char arg1[], char arg2[], char result[]) {
    struct ThreeAddressCode instr;
    instr.op = op;
    strcpy(instr.arg1, arg1);
    strcpy(instr.arg2, arg2);
    strcpy(instr.result, result);
    intermediateCode[codeIndex++] = instr;
}

// Generate target code from three-address code
void generateTargetCode() {
    int i;
    printf("\nGenerated Target Code:\n\n");

    for (i = 0; i < codeIndex; i++) {
        struct ThreeAddressCode instr = intermediateCode[i];

        switch (instr.op) {
            case '+':
                printf("MOV R0, %s\n", instr.arg1);
                printf("ADD R0, %s\n", instr.arg2);
                printf("MOV %s, R0\n", instr.result);
                break;
            case '-':
                printf("MOV R0, %s\n", instr.arg1);
                printf("SUB R0, %s\n", instr.arg2);
                printf("MOV %s, R0\n", instr.result);
                break;
            case '*':
                printf("MOV R0, %s\n", instr.arg1);
                printf("MUL R0, %s\n", instr.arg2);
                printf("MOV %s, R0\n", instr.result);
                break;
            case '/':
                printf("MOV R0, %s\n", instr.arg1);
                printf("DIV R0, %s\n", instr.arg2);
                printf("MOV %s, R0\n", instr.result);
                break;
            case '=':
                printf("MOV %s, %s\n", instr.result, instr.arg1);
                break;
        }
        printf("\n");
    }
}

// Example expression: a = (b + c) * (d - e)
void generateCodeForExampleExpression() {
    char t1[10], t2[10], t3[10];

    newTemp(t1);
    generateThreeAddressCode('+', "b", "c", t1);

    newTemp(t2);
    generateThreeAddressCode('-', "d", "e", t2);

    newTemp(t3);
    generateThreeAddressCode('*', t1, t2, t3);

    generateThreeAddressCode('=', t3, "", "a");
}

void main() {
    int i;
    clrscr();  // Clear screen for Turbo C

    printf("Generating code for expression: a = (b + c) * (d - e)\n");

    // Generate three-address code for the example expression
    generateCodeForExampleExpression();

    // Print generated intermediate (three-address) code
    printf("\nGenerated Three-Address Code:\n\n");

    for (i = 0; i < codeIndex; i++) {
        struct ThreeAddressCode instr = intermediateCode[i];
        if (instr.op == '=') {
            printf("%s = %s\n", instr.result, instr.arg1);
        } else {
            printf("%s = %s %c %s\n", instr.result, instr.arg1, instr.op, instr.arg2);
        }
    }

    // Generate target code
    generateTargetCode();

    getch();  // Wait for key press
}
