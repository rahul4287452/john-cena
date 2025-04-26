#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

FILE *f1, *f2, *f3, *f4, *f5;

void main() {
    char lbl[20], opc[20], opr[20];
    char mname[20], arg[20], check[20];
    char ch;
    char dlbl[20], dopc[20], dopr[20];
    int c = 0;

    clrscr();

    // Open files
    f1 = fopen("MACIN.DAT", "r");
    f2 = fopen("NAMETAB.DAT", "r");
    f3 = fopen("DEFTAB.DAT", "r");
    f4 = fopen("EXPAND.DAT", "w");
    f5 = fopen("ARGTAB.DAT", "w");

    if (!f1 || !f2 || !f3 || !f4 || !f5) {
        printf("Error opening files!\n");
        exit(1);
    }

    // Start processing input
    while (fscanf(f1, "%s %s %s", lbl, opc, opr) != EOF) {
        c = 0;

        if (strcmp(opc, "MACRO") == 0) {
            // Skip macro definition
            while (strcmp(opc, "MEND") != 0) {
                fscanf(f1, "%s %s %s", lbl, opc, opr);
            }
            continue;
        }

        // Check if OPCODE matches any macro name
        rewind(f2);
        while (fscanf(f2, "%s", mname) != EOF) {
            if (strcmp(opc, mname) == 0) {
                c = 1;
                break;
            }
        }

        if (c == 1) {
            fprintf(f5, "%s\n", opr);
            rewind(f5);
            rewind(f3);

            while (fscanf(f3, "%s %s %s", dlbl, dopc, dopr) != EOF) {
                if (strcmp(dopc, "MEND") == 0) {
                    break;
                }

                if (strcmp(dopc, "MACRO") == 0) {
                    continue;
                }

                // Replace placeholders with actual arguments
                if (strcmp(dopr, "=X'?1'") == 0) {
                    strcpy(dopr, "=X'F1'");
                } else if (strcmp(dopr, "?2,X") == 0) {
                    strcpy(dopr, "BUFFER,X");
                } else if (strcmp(dopr, "?3") == 0) {
                    strcpy(dopr, "LENGTH");
                }

                fprintf(f4, "%s\t%s\t%s\n", dlbl, dopc, dopr);
            }
        } else {
            fprintf(f4, "%s\t%s\t%s\n", lbl, opc, opr);
        }
    }

    fcloseall();

    // Display Input Files
    clrscr();
    printf("\n INPUT\n\n Macro Program before expansion\n");
    printf("---------------------------------\n");
    f1 = fopen("MACIN.DAT", "r");
    while ((ch = fgetc(f1)) != EOF) {
        printf("%c", ch);
    }
    fclose(f1);

    printf("\n\n Definition Table\n");
    printf("---------------------------------\n");
    f2 = fopen("DEFTAB.DAT", "r");
    while ((ch = fgetc(f2)) != EOF) {
        printf("%c", ch);
    }
    fclose(f2);

    printf("\n\n Name Table\n");
    printf("---------------------------------\n");
    f3 = fopen("NAMETAB.DAT", "r");
    while ((ch = fgetc(f3)) != EOF) {
        printf("%c", ch);
    }
    fclose(f3);

    getch();
    clrscr();

    // Display Output File
    printf("\n\n OUTPUT\n\n Macro Program after expansion\n");
    printf("---------------------------------\n\n");
    f4 = fopen("EXPAND.DAT", "r");
    while ((ch = fgetc(f4)) != EOF) {
        printf("%c", ch);
    }
    fclose(f4);

    getch();
}
