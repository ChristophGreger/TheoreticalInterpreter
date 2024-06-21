//
// Created by Christoph Greger on 21.06.24.
//

#include "parser.h"
#include <stdlib.h>




struct ASTNodeHelper *parseHelp(TokenStruct *firstToken) {
    struct ASTNodeHelper *firstNode = malloc(sizeof(struct ASTNodeHelper));
    struct ASTNodeHelper *currentNode = firstNode;
    TokenStruct *currentToken = firstToken;
    while (currentToken->token != EOFT) {
        switch (currentToken->token) {
            case Loop:
                currentNode->node->type = LOOP;
                currentNode->node->value.loop.x = *((int *) currentToken->value);
                currentToken = currentToken->next;
                struct ASTNodeHelper *body = parseHelp(currentToken);
                currentNode->node->value.loop.body = body->node;
                currentToken = body->nextToken;
                break;
            case Increment:
                currentNode->node->type = INCREMENT;
                currentNode->node->value.increment = *((int *) currentToken->value);
                currentToken = currentToken->next;
                break;
            case Reset:
                currentNode->node->type = RESET;
                currentNode->node->value.reset = *((int *) currentToken->value);
                currentToken = currentToken->next;
                break;
            case closecurly:
                firstNode->nextToken = currentToken->next;
                return firstNode;
            default:
                exit(1);
        }
        if (currentToken != NULL) {
            currentNode->node->next = malloc(sizeof(struct ASTNode));
            currentNode = currentNode->node->next;
        }
    }
    return firstNode;

}


struct ASTNode *parse(TokenStruct *firstToken) {
    struct ASTNodeHelper *helper = parseHelp(firstToken);
    return helper->node;
}