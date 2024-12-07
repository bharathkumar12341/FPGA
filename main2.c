#include <stdio.h>

// Example of Code Generation Function
void generateAssembly(ASTNode *node) {
    if (node == NULL) return;
    
    // Handle Variable Declaration
    if (node->type == NODE_VAR_DECL) {
        printf("; Declaring variable: %s\n", node->value);
        // Example: Allocate memory for the variable
        printf("ALLOC %s\n", node->value);
    }
    // Handle Assignment
    if (node->type == NODE_ASSIGN) {
        // Example: Generate assembly for an assignment operation
        printf("MOV %s, %s\n", node->left->value, node->right->value); // Move operation
    }
    // Recursively generate for child nodes
    generateAssembly(node->left);
    generateAssembly(node->right);
}

// Main function to test code generation
int main() {
    ASTNode *root = createNode(NODE_VAR_DECL, "a");
    ASTNode *assign = createNode(NODE_ASSIGN, "=");
    assign->left = createNode(NODE_EXPR, "a");
    assign->right = createNode(NODE_EXPR, "10");

    generateAssembly(root); // Example output for variable declaration
    generateAssembly(assign); // Example output for assignment

    return 0;
}
