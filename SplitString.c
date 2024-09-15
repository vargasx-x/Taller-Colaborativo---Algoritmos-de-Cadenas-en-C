//
// Created by ASUS on 12/09/2024.
//

#include "SplitString.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* splitString(const char * str) {

    int len = strlen(str);
    char* arreglo = (char*) malloc((len + 1) * sizeof(char));
    if (arreglo == NULL) {
        printf("Error al asignar memoria.\n");
        return NULL;
    }

    strcpy(arreglo, str);

    return arreglo;
}