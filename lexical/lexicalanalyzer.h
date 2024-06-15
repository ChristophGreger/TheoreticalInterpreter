//
// Created by Christoph Greger on 15.06.24.
//

#ifndef THEORETICALINTERPRETER_LEXICALANALYZER_H
#define THEORETICALINTERPRETER_LEXICALANALYZER_H


#include <stdio.h>

typedef enum {
    Equal, //value ist NULL
    Delimiter, //value ist NULL
    X, //value ist der int der Bezeichnung
    opencurly, //value ist NULL
    closecurly, //value ist NULL
    opennormal, //value ist NULL
    closenormal, //value ist NULL
    zero, //value ist NULL
    one, //value ist NULL
    plus, //value ist NULL
    ERROR, //value ist weitere Infos zum Fehler
    EOFT //value ist NULL
} Token;

typedef struct TokenStruct{ //Implementation als linked List
    Token token;
    void *value;
    struct TokenStruct *next;
} TokenStruct;

TokenStruct *lexicalAnalysis(FILE *file);



#endif //THEORETICALINTERPRETER_LEXICALANALYZER_H
