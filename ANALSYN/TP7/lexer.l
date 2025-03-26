%{
#include "parser.tab.h"
%}

%%

[a-z]           { return LETTER; }
"@"             { return EPSILON; }
"0"             { return EMPTY_SET; }
"|"             { return UNION; }
"*"             { return KLEENE_STAR; }
"("             { return LEFT_PAREN; }
")"             { return RIGHT_PAREN; }
[ \t\r\n]       { /* Ignorer les espaces */ }
.               { return UNKNOWN; }

%%
int yywrap() {
    return 1;
}
