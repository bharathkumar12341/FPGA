#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// AST Node Types
typedef enum { NODE_VAR_DECL, NODE_ASSIGN, NODE_EXPR, NODE_IF } NodeType;

// Define AST Node Structure
typedef struct ASTNode {
    NodeType type;
    struct ASTNode *left, *right;
    char value[MAX_TOKEN_LEN]; // Holds data like variable names or literals
} ASTNode;

// Function to create a new AST node
ASTNode* createNode(NodeType type, const char *value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->left = node->right = NULL;
    strcpy(node->value, value);
    return node;
}

// Example function to parse a variable declaration
ASTNode* parseVarDecl(FILE *file, Token *token) {
    // Expecting "int varName;"
    if (token->type == TOKEN_INT) {
        getNextToken(file, token); // Get the next token (variable name)
        if (token->type == TOKEN_IDENTIFIER) {
            ASTNode* node = createNode(NODE_VAR_DECL, token->text);
            getNextToken(file, token); // Expect semicolon
            if (token->type == TOKEN_SEMICOLON) {
                return node;
            }
        }
    }
    return NULL; // Invalid syntax
}

// Main function to test parsing
int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    Token token;
    getNextToken(file, &token);
    ASTNode* root = parseVarDecl(file, &token);

    // Print the parsed AST for the first variable declaration
    if (root) {
        printf("Parsed Variable Declaration: %s\n", root->value);
    }

    fclose(file);
    return 0;
}
