#include <stdio.h>
#include <string.h>
#include <conio.h>

int main() {
    char input[100];
    int state = 0; // Start in state q0 (even number of zeros)
    int i;
    char c;
    
    clrscr();
    
    printf("Enter a binary string (only 0s and 1s): ");
    scanf("%s", input);
    
    for (i = 0; i < strlen(input); i++) {
        c = input[i];
        
        if (c == '0') {
            // Transition on '0'
            state = 1 - state; // Toggle between state 0 and state 1
        } else if (c == '1') {
            // Stay in the same state on '1'
            continue;
        } else {
            // Invalid character
            printf("Invalid character detected: %c\n", c);
            getch();
            return 1; // Exit the program with error code
        }
    }
    
    // Check if the final state is q0 (even number of zeros)
    if (state == 0) {
        printf("Accepted: The string has an even number of zeros.\n");
    } else {
        printf("Rejected: The string has an odd number of zeros.\n");
    }
    
    getch(); // Wait for a keypress before exiting
    return 0;
}
