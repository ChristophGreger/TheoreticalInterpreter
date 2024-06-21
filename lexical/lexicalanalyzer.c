//
// Created by Christoph Greger on 15.06.24.
//

#include "lexicalanalyzer.h"
#include <stdlib.h>

void cleanUp(TokenStruct *firstToken) { //Funktion zum Freigeben des Speichers einer TokenStruct linked List
    TokenStruct *currentToken = firstToken;
    while (currentToken->next != NULL) {
        TokenStruct *nextToken = currentToken->next;
        free(currentToken->value);
        free(currentToken);
        currentToken = nextToken;
    }
    free(currentToken);
}

typedef struct { //Struct um x zu "parsen"
    char next;
    int x;
} XStruct;

XStruct * checkforx(FILE *file, char c) { //Funktion um x zu "parsen"
    XStruct *xstruct = malloc(sizeof(XStruct));
    if (c != 'x') {     //Fehler wenn kein x
        xstruct->next = c;
        xstruct->x = -1;
        return xstruct;
    }
    c = getc(file);
    int xnumber = 0;
    while (c >= '0' && c <= '9') {
        xnumber = xnumber * 10 + c - '0';
        c = getc(file);
    }

    xstruct->next = c;
    xstruct->x = xnumber;
    return xstruct;
}

int checkloop(FILE *file, char c) { //Funktion um loop( zu "parsen"
    if (c != 'l') {
        return 0;
    }
    c = getc(file);
    if (c != 'o') {
        return 0;
    }
    c = getc(file);
    if (c != 'o') {
        return 0;
    }
    c = getc(file);
    if (c != 'p') {
        return 0;
    }
    c = getc(file);
    while (c == ' ') {
        c = getc(file);
    }
    if (c != '(') {
        return 0;
    }
    return 1;
}


TokenStruct *lexicalAnalysis(FILE *file) {
    TokenStruct *firstToken = malloc(sizeof(TokenStruct));
    TokenStruct *currentToken = firstToken;
    char c = getc(file);
    while (c != EOF) {
        switch (c) {

            case ' ': //whitespace
                c = getc(file);
                break;
            case '\n': //newline
                c = getc(file);
                break;

            case 'l': //loop
                if (!checkloop(file, c)) {
                    currentToken->token = ERROR;
                    c = getc(file);
                    currentToken->next = malloc(sizeof(TokenStruct));
                    currentToken = currentToken->next;
                    break;
                }
                c = getc(file);
                XStruct *xstruct2 = checkforx(file, c);
                if (xstruct2->x == -1) {
                    currentToken->token = ERROR;
                    c = xstruct2->next;
                    currentToken->next = malloc(sizeof(TokenStruct));
                    currentToken = currentToken->next;
                    break;
                }
                c = xstruct2->next;
                if (c != ')') {
                    currentToken->token = ERROR;
                    currentToken->next = malloc(sizeof(TokenStruct));
                    currentToken = currentToken->next;
                    break;
                }
                c = getc(file);
                currentToken->token = Loop;
                int * value = malloc(sizeof(int));
                *value = xstruct2->x;
                currentToken->value = value;
                currentToken->next = malloc(sizeof(TokenStruct));
                currentToken = currentToken->next;
                break;

            case 'x': //increment, reset
                XStruct *xstruct3 = checkforx(file, c);
                if (xstruct3->x == -1) {
                    currentToken->token = ERROR;
                    c = xstruct3->next;
                    currentToken->next = malloc(sizeof(TokenStruct));
                    currentToken = currentToken->next;
                    break;
                }
                c = xstruct3->next;
                while (c == ' ') {
                    c = getc(file);
                }
                if (c != '=') { //increment
                    if (c != '+') {
                        currentToken->token = ERROR;
                        currentToken->next = malloc(sizeof(TokenStruct));
                        currentToken = currentToken->next;
                        break;
                    }
                    c = getc(file);
                    while (c == ' ') {
                        c = getc(file);
                    }
                    if (c != '1') {
                        currentToken->token = ERROR;
                        currentToken->next = malloc(sizeof(TokenStruct));
                        currentToken = currentToken->next;
                        break;
                    }
                    c = getc(file);
                    while (c == ' ') {
                        c = getc(file);
                    }
                    if (c != ';') {
                        currentToken->token = ERROR;
                        currentToken->next = malloc(sizeof(TokenStruct));
                        currentToken = currentToken->next;
                        break;
                    }
                    currentToken->token = Increment;
                    int * value = malloc(sizeof(int));
                    *value = xstruct3->x;
                    currentToken->value = value;
                    currentToken->next = malloc(sizeof(TokenStruct));
                    currentToken = currentToken->next;
                    c = getc(file);
                    break;
                }
                c = getc(file);
                while (c == ' ') {
                    c = getc(file);
                }
                if (c == '0') { //reset
                    c = getc(file);
                    while (c == ' ') {
                        c = getc(file);
                    }
                    if (c == ';') {
                        currentToken->token = Reset;
                        int *value = malloc(sizeof(int));
                        *value = xstruct3->x;
                        currentToken->value = value;
                        currentToken->next = malloc(sizeof(TokenStruct));
                        currentToken = currentToken->next;
                        c = getc(file);
                        break;
                    } else {
                        currentToken->token = ERROR;
                        currentToken->next = malloc(sizeof(TokenStruct));
                        currentToken = currentToken->next;
                        c = getc(file);
                        break;
                    }
                } else {
                    currentToken->token = ERROR;
                    currentToken->next = malloc(sizeof(TokenStruct));
                    currentToken = currentToken->next;
                    c = getc(file);
                    break;
                }
            case '{': //opencurly
                currentToken->token = opencurly;
                c = getc(file);
                currentToken->next = malloc(sizeof(TokenStruct));
                currentToken = currentToken->next;
                break;
            case '}': //closecurly
                currentToken->token = closecurly;
                c = getc(file);
                currentToken->next = malloc(sizeof(TokenStruct));
                currentToken = currentToken->next;
                break;

            default:
                currentToken->token = ERROR;
                currentToken->next = malloc(sizeof(TokenStruct));
                currentToken = currentToken->next;
                c = getc(file);
                break;
        }
    }
    currentToken->token = EOFT;
    return firstToken;
}


void printToken(TokenStruct *token) { //Funktion um Token auszugeben
    while (token->token != EOFT) {
        switch (token->token) {
            case Loop:
                printf("Loop(%d)\n", *((int *) token->value));
                break;
            case Increment:
                printf("Increment x%d\n", *((int *) token->value));
                break;
            case Reset:
                printf("Reset x%d\n", *((int *) token->value));
                break;
            case opencurly:
                printf("{\n");
                break;
            case closecurly:
                printf("}\n");
                break;
            case ERROR:
                printf("ERROR\n");
                break;
            default:
                printf("ERROR\n");
                break;
        }
        token = token->next;
    }
}
