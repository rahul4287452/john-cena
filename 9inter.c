#include <stdio.h>
#include <string.h>

struct op {
    char l;        // Left variable
    char r[20];    // Right expression
} op[10], pr[10];  // Arrays for original operations and processed operations

void main() {
    int a, i, k, j, n, z = 0, m, q;
    char *p, *l;
    char temp, t;
    char *tem;

    clrscr(); // Clear the screen in Turbo C

    // Input number of operations
    printf("Enter the Number of Values: ");
    scanf("%d", &n);

    // Input operations
    for (i = 0; i < n; i++) {
        printf("Left: ");
        fflush(stdin);       // Clear the input buffer in Turbo C
        scanf("%c", &op[i].l);

        printf("Right: ");
        scanf("%s", op[i].r);
    }

    // Display intermediate code
    printf("\nIntermediate Code:\n");
    for (i = 0; i < n; i++) {
        printf("%c = %s\n", op[i].l, op[i].r);
    }

    // Perform Dead Code Elimination
    for (i = 0; i < n - 1; i++) {
        temp = op[i].l;
        for (j = 0; j < n; j++) {
            p = strchr(op[j].r, temp);
            if (p) {
                pr[z].l = op[i].l;
                strcpy(pr[z].r, op[i].r);
                z++;
                break; // Move to next op[i] after finding a match
            }
        }
    }

    // Last operation always considered useful
    pr[z].l = op[n - 1].l;
    strcpy(pr[z].r, op[n - 1].r);
    z++;

    // Display after Dead Code Elimination
    printf("\nAfter Dead Code Elimination:\n");
    for (k = 0; k < z; k++) {
        printf("%c = %s\n", pr[k].l, pr[k].r);
    }

    // Perform Common Subexpression Elimination
    for (m = 0; m < z; m++) {
        tem = pr[m].r;
        for (j = m + 1; j < z; j++) {
            if (strcmp(tem, pr[j].r) == 0) { // If exact same expression
                t = pr[j].l;
                pr[j].l = pr[m].l;

                // Replace occurrences of t with pr[m].l
                for (i = 0; i < z; i++) {
                    l = strchr(pr[i].r, t);
                    if (l) {
                        a = l - pr[i].r;
                        pr[i].r[a] = pr[m].l;
                    }
                }
            }
        }
    }

    // Display code after eliminating common expressions
    printf("\nAfter Eliminating Common Expressions:\n");
    for (i = 0; i < z; i++) {
        printf("%c = %s\n", pr[i].l, pr[i].r);
    }

    // Further optimization: eliminate duplicates
    for (i = 0; i < z; i++) {
        for (j = i + 1; j < z; j++) {
            if ((pr[i].l == pr[j].l) && (strcmp(pr[i].r, pr[j].r) == 0)) {
                pr[j].l = '\0'; // Mark as eliminated
            }
        }
    }

    // Display final optimized code
    printf("\nOptimized Code:\n");
    for (i = 0; i < z; i++) {
        if (pr[i].l != '\0') {
            printf("%c = %s\n", pr[i].l, pr[i].r);
        }
    }

    getch(); // Wait for keypress before closing
}
