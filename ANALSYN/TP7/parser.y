%{
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char type;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(char type, Node* left, Node* right) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->type = type;
    node->left = left;
    node->right = right;
    return node;
}

void printTree(Node* node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%c\n", node->type);
    printTree(node->left, depth + 1);
    printTree(node->right, depth + 1);
}

void yyerror(const char *s) {
    fprintf(stderr, "Erreur : %s\n", s);
}

extern int yylex();
%}

%union {
    char character;
    struct Node* node;
}

%token LETTER EPSILON EMPTY_SET
%token UNION KLEENE_STAR LEFT_PAREN RIGHT_PAREN
%token UNKNOWN

%type <node> expr term factor

%%

input: 
    expr { 
        printf("Arbre syntaxique :\n");
        printTree($1, 0);
    }
    ;

expr:
    expr UNION term { $$ = createNode('|', $1, $3); }
    | term          { $$ = $1; }
    ;

term:
    term factor { $$ = createNode('.', $1, $2); } // Concaténation implicite
    | factor    { $$ = $1; }
    ;

factor:
    factor KLEENE_STAR { $$ = createNode('*', $1, NULL); }
    | LETTER           { $$ = createNode(yytext[0], NULL, NULL); }
    | EPSILON          { $$ = createNode('@', NULL, NULL); }
    | EMPTY_SET        { $$ = createNode('0', NULL, NULL); }
    | LEFT_PAREN expr RIGHT_PAREN { $$ = $2; }
    ;

%%

int main() {
    printf("Entrez une expression régulière : ");
    yyparse();
    return 0;
}
