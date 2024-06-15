//
// Created by Christoph Greger on 15.06.24.
//

#include "main.h"

//Das Programm hat genau ein Argument, den Dateinamen mit dem Quellcode der interpretiert werden soll.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];
    printf("Benutztes File: %s\n", filename);

    FILE *file = fopen(filename, "r"); // Öffnet die Datei im Lese-Modus
    if (file == NULL) {
        printf("Die Datei existiert nicht oder konnte nicht geöffnet werden!\n");
        return 1;
    }

    TokenStruct *tokenList = lexicalAnalysis(file); // Erstellt eine Liste von Tokens

    fclose(file); // Schließt die Datei


    return 0;
}