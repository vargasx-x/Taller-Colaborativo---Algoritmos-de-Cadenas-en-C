//
// Created by ASUS on 12/09/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JoinArray.h"

char* unir_cadena(char* cadena, char separador) {
    int longitud = strlen(cadena);

    int n_palabras = 1;
    for (int i = 0; i < longitud; i++) {
        if (cadena[i] == ' ') {
            n_palabras++;
        }
    }

    int longitud_total = longitud + (n_palabras - 1) + 1;

    char* resultado = (char*)malloc(longitud_total * sizeof(char));
    if (resultado == NULL) {
        printf("Error al reservar memoria\n");
        exit(1);
    }

    int j = 0;
    for (int i = 0; i < longitud; i++) {
        if (cadena[i] == ' ') {
            resultado[j++] = separador;
        } else {
            resultado[j++] = cadena[i];
        }
    }
    resultado[j] = '\0';

    return resultado;
}