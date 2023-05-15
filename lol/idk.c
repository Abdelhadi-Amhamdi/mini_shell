#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Abstract syntax tree (AST) node structure
typedef struct ASTNode {
    char type;              // 'N' for numeric value, 'O' for operator
    int value;              // Value (for numeric nodes)
    struct ASTNode* left;   // Left child
    struct ASTNode* right;  // Right child
} ASTNode;

// Global variables
char *input;    // Input expression
char token;     // Current token

// Function prototypes
ASTNode* expr();
ASTNode* term();
ASTNode* factor();
ASTNode* createNumericNode(int value);
ASTNode* createOperatorNode(char type, ASTNode* left, ASTNode* right);
void error();

// Function to get the next token

// Function to handle syntax errors
void error() {
    fprintf(stderr, "Syntax error.\n");
    exit(1);
}

// Function to get the next token
void getNextToken() {
    while (isspace(*input))
        input++;
    token = *input++;
}

// Function to match a specific token
void match(char expectedToken) {
    if (token == expectedToken)
        getNextToken();
    else
        error();
}

// Grammar rules implementation

ASTNode* expr() {
    ASTNode* result = term();
    
    while (token == '+' || token == '-') {
        char operatorType = token;
        match(token);
        ASTNode* rightOperand = term();
        result = createOperatorNode(operatorType, result, rightOperand);
    }
    
    return result;
}

ASTNode* term() {
    ASTNode* result = factor();
    
    while (token == '*' || token == '/') {
        char operatorType = token;
        match(token);
        ASTNode* rightOperand = factor();
        result = createOperatorNode(operatorType, result, rightOperand);
    }
    
    return result;
}

ASTNode* factor() {
    ASTNode* result;
    
    if (isdigit(token)) {
        int value = token - '0';
        match(token);
        result = createNumericNode(value);
    } else if (token == '(') {
        match('(');
        result = expr();
        match(')');
    } else {
        error();    // Invalid token
    }
    
    return result;
}

// Function to create a numeric node in the AST
ASTNode* createNumericNode(int value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = 'N';
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to create an operator node in the AST
ASTNode* createOperatorNode(char type, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = 'O';
    node->value = type;
    node->left = left;
    node->right = right;
    return node;
}

// Function to print the AST in postfix notation
// void printAST(ASTNode* node) {
//     if (node == NULL)
//         return;
    
//     printAST(node->left);
//     printAST(node->right);
    
//     if (node->type == 'N')
//         printf("%d ", node->value);
//     else if (node->type == 'O')
//         printf("%c ", node->value);
// }
void printAST(ASTNode* node, int indent) {
    if (node == NULL)
        return;

    if (node->type == 'N') {
        printf("%*s%d\n", indent, "", node->value);
    } else if (node->type == 'O') {
        printf("%*s%c\n", indent, "", node->value);
        printAST(node->left, indent + 4);
        printAST(node->right, indent + 4);
    }
}
// void printTreeHelper(ASTNode *root, int depth) {
//     if (root == NULL) {
//         return;
//     }
//     printTreeHelper(root->right, depth + 1);
//     for (int i = 0; i < depth; i++) {
//         printf("    ");
//     }
//     printf("%c\n", root->value);
//     printTreeHelper(root->left, depth + 1);
// }

// // Function to print the binary tree structure
// void printTree(ASTNode *root) {
//     printTreeHelper(root, 0);
// }
// Entry point of the program
int main() {
    printf("Enter an arithmetic expression: ");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    input = buffer;
    
    getNextToken();
    
    ASTNode* ast = expr();
    
    if (token == '\0') {
        printf("AST (postfix notation): \n");
        printAST(ast, 0);
        printf("\n");
    } else {
        error();    // Extra tokens remaining
    }
    
    return 0;
}
