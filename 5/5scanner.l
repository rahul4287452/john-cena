%{
#include <stdio.h>
%}

%%

abb         { printf("Token: abb\n"); }
babb        { printf("Token: babb\n"); }
abbabba     { printf("Token: abbabba\n"); }
/(.|\n)/    { /* Ignore other characters */ }

%%

int main() {
    yylex();  // Invoke the lexical analyzer
    return 0;
}
	