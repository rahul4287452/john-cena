#include <stdio.h>
#include <conio.h>
#include <string.h>

#define MAX_PRODUCTIONS 10
#define MAX_SYMBOLS 10
#define MAX_RULES 10

// Structure to store grammar rules
struct Rule {
    char left;
    char right[MAX_SYMBOLS];
};

// Structure to store sets
struct Set {
    char symbols[MAX_SYMBOLS];
    int count;
};

// Function to initialize a set
void initSet(struct Set *set) {
    set->count = 0;
}

// Function to add a symbol to the set
void addToSet(struct Set *set, char symbol) {
    int i;
    int found = 0;
    for (i = 0; i < set->count; i++) {
        if (set->symbols[i] == symbol) {
            found = 1;
            break;
        }
    }
    if (!found && set->count < MAX_SYMBOLS) {
        set->symbols[set->count++] = symbol;
    }
}

// Function to check if a symbol is in the set
int isInSet(struct Set *set, char symbol) {
    int i;
    for (i = 0; i < set->count; i++) {
        if (set->symbols[i] == symbol) {
            return 1;
        }
    }
    return 0;
}

// Function to find FIRST set
void findFirst(struct Rule grammar[], int numRules, struct Set first[]) {
    int i, j, k;
    int changed;
    char left;
    char *right;
    
    do {
        changed = 0;
        for (i = 0; i < numRules; i++) {
            left = grammar[i].left;
            right = grammar[i].right;
            
            if (right[0] >= 'a' && right[0] <= 'z') {
                if (!isInSet(&first[left - 'A'], right[0])) {
                    addToSet(&first[left - 'A'], right[0]);
                    changed = 1;
                }
            } else if (right[0] >= 'A' && right[0] <= 'Z') {
                for (j = 0; j < numRules; j++) {
                    if (grammar[j].left == right[0]) {
                        for (k = 0; k < first[right[0] - 'A'].count; k++) {
                            if (!isInSet(&first[left - 'A'], first[right[0] - 'A'].symbols[k])) {
                                addToSet(&first[left - 'A'], first[right[0] - 'A'].symbols[k]);
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }
    } while (changed);
}

// Function to find FOLLOW set
void findFollow(struct Rule grammar[], int numRules, struct Set follow[], struct Set first[]) {
    int changed;
    int i, j, k;
    char left;
    char *right;
    
    addToSet(&follow[grammar[0].left - 'A'], '$');
    
    do {
        changed = 0;
        
        for (i = 0; i < numRules; i++) {
            left = grammar[i].left;
            right = grammar[i].right;
            
            for (j = 0; right[j] != '\0'; j++) {
                if (right[j] >= 'A' && right[j] <= 'Z') {
                    if (right[j+1] != '\0') {
                        if (right[j+1] >= 'a' && right[j+1] <= 'z') {
                            if (!isInSet(&follow[right[j] - 'A'], right[j+1])) {
                                addToSet(&follow[right[j] - 'A'], right[j+1]);
                                changed = 1;
                            }
                        } else {
                            for (k = 0; k < first[right[j+1] - 'A'].count; k++) {
                                if (!isInSet(&follow[right[j] - 'A'], first[right[j+1] - 'A'].symbols[k])) {
                                    addToSet(&follow[right[j] - 'A'], first[right[j+1] - 'A'].symbols[k]);
                                    changed = 1;
                                }
                            }
                        }
                    } else {
                        for (k = 0; k < follow[left - 'A'].count; k++) {
                            if (!isInSet(&follow[right[j] - 'A'], follow[left - 'A'].symbols[k])) {
                                addToSet(&follow[right[j] - 'A'], follow[left - 'A'].symbols[k]);
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }
    } while (changed);
}

int main() {
    struct Rule grammar[MAX_RULES];
    struct Set first[26];
    struct Set follow[26];
    int numRules;
    int i, j;
    char left;
    char right[MAX_SYMBOLS];
    
    clrscr();
    
    printf("Enter number of grammar rules: ");
    scanf("%d", &numRules);
    
    for (i = 0; i < 26; i++) {
        initSet(&first[i]);
        initSet(&follow[i]);
    }
    
    printf("Enter grammar rules (e.g., A->aB):\n");
    for (i = 0; i < numRules; i++) {
        printf("Rule %d: ", i + 1);
        scanf(" %c->%s", &left, right);
        grammar[i].left = left;
        strcpy(grammar[i].right, right);
    }
    
    findFirst(grammar, numRules, first);
    findFollow(grammar, numRules, follow, first);
    
    printf("\nFIRST Sets:\n");
    for (i = 0; i < 26; i++) {
        if (first[i].count > 0) {
            printf("FIRST(%c) = {", 'A' + i);
            for (j = 0; j < first[i].count; j++) {
                printf("%c", first[i].symbols[j]);
                if (j < first[i].count - 1) {
                    printf(", ");
                }
            }
            printf("}\n");
        }
    }
    
    printf("\nFOLLOW Sets:\n");
    for (i = 0; i < 26; i++) {
        if (follow[i].count > 0) {
            printf("FOLLOW(%c) = {", 'A' + i);
            for (j = 0; j < follow[i].count; j++) {
                printf("%c", follow[i].symbols[j]);
                if (j < follow[i].count - 1) {
                    printf(", ");
                }
            }
            printf("}\n");
        }
    }
    
    getch();
    return 0;
}
