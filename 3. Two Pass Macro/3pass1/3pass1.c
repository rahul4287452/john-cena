#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    FILE *f1, *f2, *f3;
    char mne[20], opnd[20], la[20];

    clrscr();

    f1 = fopen("MINP2.TXT", "r");
    f2 = fopen("NTAB2.TXT", "w");
    f3 = fopen("DTAB2.TXT", "w");

    if (f1 == NULL || f2 == NULL || f3 == NULL) {
        printf("Error: Unable to open files.\n");
        getch();
        return;
    }

    printf("Processing input file...\n");

    fscanf(f1, "%s %s %s", la, mne, opnd);

    while (strcmp(mne, "MEND") != 0 && !feof(f1)) {
        if (strcmp(mne, "MACRO") == 0) {
            fprintf(f2, "%s\n", la);          // Save macro name into NTAB
            fprintf(f3, "%s\t%s\n", la, opnd); // Save first line into DTAB
        } else {
            fprintf(f3, "%s\t%s\n", mne, opnd); // Save rest of macro body
        }
        fscanf(f1, "%s %s %s", la, mne, opnd);
    }
    fprintf(f3, "%s\n", mne); // Write final MEND

    fclose(f1);
    fclose(f2);
    fclose(f3);

    printf("\nPASS 1 is successful.\n");

    // Display contents of NTAB
    printf("\nSymbol Table (NTAB2.TXT):\n");
    printf("-----------------------------------\n");
    f2 = fopen("NTAB2.TXT", "r");
    if (f2 == NULL) {
        printf("Error: Unable to open NTAB2.TXT for reading.\n");
        getch();
        return;
    }
    while (fscanf(f2, "%s", la) != EOF) {
        printf("%s\n", la);
    }
    fclose(f2);

    // Display contents of DTAB
    printf("\nDefinition Table (DTAB2.TXT):\n");
    printf("-----------------------------------\n");
    f3 = fopen("DTAB2.TXT", "r");
    if (f3 == NULL) {
        printf("Error: Unable to open DTAB2.TXT for reading.\n");
        getch();
        return;
    }
    while (fscanf(f3, "%s %s", la, opnd) != EOF) {
        printf("%s\t%s\n", la, opnd);
    }
    fclose(f3);

    getch();
}
