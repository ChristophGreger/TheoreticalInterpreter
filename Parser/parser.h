//
// Created by Christoph Greger on 21.06.24.
//

#ifndef THEORETICALINTERPRETER_PARSER_H
#define THEORETICALINTERPRETER_PARSER_H

#include "../lexical/lexicalanalyzer.h"

typedef struct ASTNodeHelper {
    int error; //0 wenn kein Fehler, 1 wenn Fehler
    TokenStruct *nextToken;
    struct ASTNode *node;
};

typedef struct ASTNode {
    enum { //enum für die verschiedenen Typen von Knoten
        LOOP,
        INCREMENT,
        RESET,
    } type;
    union {
        struct { //struct für Loop
            int x;
            struct ASTNode *body; //Pointer auf den Body des Loops
        } loop;
        int increment; //int für Increment
        int reset; //int für Reset
    } value;
    struct ASTNode *next; //Pointer auf den nächsten Knoten
};

struct ASTNode *parse(TokenStruct *firstToken);


#endif //THEORETICALINTERPRETER_PARSER_H
