//
// Created by Christoph Greger on 15.06.24.
//

#ifndef THEORETICALINTERPRETER_LEXICALANALYZER_H
#define THEORETICALINTERPRETER_LEXICALANALYZER_H


#include <stdio.h>

typedef enum {
    Loop, //value ist die Nummer des x--> loop(x12) wird zu Loop mit value 12
    Increment, //value ist Liste mit zwei ints, das x in das geschrieben wird und das x, das mit eins addiert wird
    Reset, //value ist der int des x das Resetet wird
    opencurly, //value ist NULL
    closecurly, //value ist NULL
    ERROR, //value ist weitere Infos zum Fehler
    EOFT //value ist NULL
} Token;

typedef struct TokenStruct{ //Implementation als linked List
    Token token;
    void *value;
    struct TokenStruct *next;
} TokenStruct;

TokenStruct *lexicalAnalysis(FILE *file);

void cleanUp(TokenStruct *firstToken);

void printToken(TokenStruct *token);



#endif //THEORETICALINTERPRETER_LEXICALANALYZER_H
