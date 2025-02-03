%{
#include <stdio.h>
#include <stdlib.h>

int ligne = 1;   // Compteur de lignes, utile pour afficher la ligne d'erreur
%}

%%

[a-zA-Z]+          { printf("Jeton: MOT, Lexème: %s\n", yytext); }
[0-9]+             { printf("Jeton: NOMBRE, Lexème: %s\n", yytext); }
"+"                { printf("Jeton: PLUS, Lexème: %s\n", yytext); }
"-"                { printf("Jeton: MOINS, Lexème: %s\n", yytext); }
"*"                { printf("Jeton: FOIS, Lexème: %s\n", yytext); }
"/"                { printf("Jeton: DIVISE, Lexème: %s\n", yytext); }
"("                { printf("Jeton: PARENTHESE_OUVRANTE, Lexème: %s\n", yytext); }
")"                { printf("Jeton: PARENTHESE_FERMANTE, Lexème: %s\n", yytext); }
[ \t\n\r]+         { /* Ignore les espaces et les retours à la ligne */ }
.                  { printf("Jeton: AUTRE, Lexème: %s\n", yytext); }  // Pour tout autre caractère (reconnaît tout caractère isolé)

%%

int main() {
    yylex();
    return 0;
}
