#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define bool int
#define true 1
#define false 0

// Returns 'true' if the character is a DELIMITER (e.g., spaces, operators, parentheses).
bool isDelimiter(char ch) {
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return true;
    return false;
}

// Returns 'true' if the character is an OPERATOR (e.g., +, -, *, /).
bool isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
        ch == '>' || ch == '<' || ch == '=')
        return true;
    return false;
}

// Returns 'true' if the string is a VALID IDENTIFIER (e.g., starts with a letter).
bool validIdentifier(char* str) {
    if ((str[0] >= '0' && str[0] <= '9') || isDelimiter(str[0]))
        return false;
    return true;
}

// Returns 'true' if the string is a KEYWORD (e.g., if, else, while, int).
bool isKeyword(char* str) {
    if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") ||
        !strcmp(str, "do") || !strcmp(str, "break") || !strcmp(str, "continue") ||
        !strcmp(str, "int") || !strcmp(str, "double") || !strcmp(str, "float") ||
        !strcmp(str, "return") || !strcmp(str, "char") || !strcmp(str, "case") ||
        !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") ||
        !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned") ||
        !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") ||
        !strcmp(str, "goto"))
        return true;
    return false;
}

// Returns 'true' if the string is an INTEGER (e.g., 123, -456).
bool isInteger(char* str) {
    int i, len;
    len = strlen(str);

    if (len == 0)
        return false;

    for (i = 0; i < len; i++) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            if (str[i] == '-' && i == 0)
                continue;
            return false;
        }
    }
    return true;
}

// Returns 'true' if the string is a REAL NUMBER (e.g., 3.14, -0.99).
bool isRealNumber(char* str) {
    int i, len;
    int hasDecimal = false;

    len = strlen(str);

    if (len == 0)
        return false;

    for (i = 0; i < len; i++) {
        if (str[i] == '.') {
            if (hasDecimal)  // already has decimal point
                return false;
            hasDecimal = true;
        } else if (!(str[i] >= '0' && str[i] <= '9')) {
            if (str[i] == '-' && i == 0)
                continue;
            return false;
        }
    }
    return hasDecimal;
}

// Extracts the SUBSTRING from a given string.
char* subString(char* str, int left, int right) {
    int i;
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return subStr;
}

// Parsing the input STRING and classifying tokens.
void parse(char* str) {
    int left = 0, right = 0;
    int len = strlen(str);
    char* subStr;

    while (right <= len && left <= right) {
        if (isDelimiter(str[right]) == false)
            right++;

        if (isDelimiter(str[right]) == true && left == right) {
            if (isOperator(str[right]) == true)
                printf("'%c' IS AN OPERATOR\n", str[right]);
            right++;
            left = right;
        } else if ((isDelimiter(str[right]) == true && left != right) || (right == len && left != right)) {
            subStr = subString(str, left, right - 1);

            if (isKeyword(subStr) == true)
                printf("'%s' IS A KEYWORD\n", subStr);
            else if (isInteger(subStr) == true)
                printf("'%s' IS AN INTEGER\n", subStr);
            else if (isRealNumber(subStr) == true)
                printf("'%s' IS A REAL NUMBER\n", subStr);
            else if (validIdentifier(subStr) == true)
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);
            else
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);

            free(subStr);
            left = right;
        }
    }
}

// DRIVER FUNCTION
int main() {
    char str[100];
    clrscr();

    printf("Enter a string:\n");
    gets(str);

    parse(str);

    getch();
    return 0;
}
