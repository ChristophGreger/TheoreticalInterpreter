//
// Created by Christoph Greger on 21.06.24.
//

#include "parser.h"
#include <stdlib.h>




struct ASTNodeHelper *parseHelp(TokenStruct *firstToken) {
    struct ASTNodeHelper *firstNode = malloc(sizeof(struct ASTNodeHelper));
    firstNode->node = malloc(sizeof(struct ASTNode));
    struct ASTNode *currentNode = firstNode->node;
    TokenStruct *currentToken = firstToken;
    while (currentToken->token != EOFT) {
        switch (currentToken->token) {
            case Loop:
                currentNode->type = LOOP;
                currentNode->value.loop.x = *((int *) currentToken->value);
                currentToken = currentToken->next;
                struct ASTNodeHelper *body = parseHelp(currentToken);
                currentNode->value.loop.body = body->node;
                currentToken = body->nextToken;
                break;
            case Increment:
                currentNode->type = INCREMENT;
                currentNode->value.increment = *((int *) currentToken->value);
                currentToken = currentToken->next;
                break;
            case Reset:
                currentNode->type = RESET;
                currentNode->value.reset = *((int *) currentToken->value);
                currentToken = currentToken->next;
                break;
            case closecurly:
                firstNode->nextToken = currentToken->next;
                return firstNode;
            default:
                exit(1);
        }
        if (currentToken != NULL) {
            currentNode->next = malloc(sizeof(struct ASTNode));
            currentNode = currentNode->next;
        }
    }
    return firstNode;

}


struct ASTNode *parse(TokenStruct *firstToken) {
    struct ASTNodeHelper *helper = parseHelp(firstToken);
    return helper->node;
}

void printAST(struct ASTNode *node) {
    while (node != NULL) {
        switch (node->type) {
            case LOOP:
                printf("Loop(%d) {\n", node->value.loop.x);
                printAST(node->value.loop.body);
                printf("}\n");
                break;
            case INCREMENT:
                printf("Increment(%d)\n", node->value.increment);
                break;
            case RESET:
                printf("Reset(%d)\n", node->value.reset);
                break;
        }
        node = node->next;
    }
}