#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "JoinArray.h"
#include "SplitString.h"

// Prototipos de funciones
int buscar_ultima_ocurrencia(char cadena[], char subcadena[]);

void capitalizar_cadena(char cadena[]);

int verificar_final_cadena(char cadena[], char subcadena[]);

void formatear_valor_numerico(int valor, char *resultado);

int es_palindromo(char cadena[]);

int validar_parentesis(char cadena[]);

void mostrar_menu();

void intoSplitString() {

    char cadena[100];

    printf("Ingrese una cadena: ");
    fgets(cadena, sizeof(cadena), stdin);

    cadena[strcspn(cadena, "\n")] = '\0';

    char *arreglo = splitString(cadena);

    if (arreglo != NULL) {
        printf("El apuntador al arreglo de caracteres es: %p\n", (void *) arreglo);
        printf("La cadena copiada en el arreglo es: %s\n", arreglo);
        free(arreglo);
    }
}

void intoJoinString() {
    char separador;
    printf("Introduce el separador de palabras: ");
    scanf(" %c", &separador);

    getchar();

    char cadena[1000];
    printf("Introduce la cadena de palabras separadas por espacios: ");
    fgets(cadena, sizeof(cadena), stdin);

    cadena[strcspn(cadena, "\n")] = 0;

    char* resultado = unir_cadena(cadena, separador);

    printf("Cadena resultante: %s\n", resultado);

    free(resultado);
}

// Función principal
int main() {
    int opcion;
    do {
        mostrar_menu();
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1: {
                char cadena[100], subcadena[50];
                printf("Ingrese la cadena principal: ");
                fgets(cadena, 100, stdin);
                printf("Ingrese la subcadena a buscar: ");
                fgets(subcadena, 50, stdin);
                int posicion = buscar_ultima_ocurrencia(cadena, subcadena);
                if (posicion > 0)
                    printf("La ultima ocurrencia comienza en la posicion %d\n", posicion);
                else
                    printf("Subcadena no encontrada\n");
                break;
            }
            case 2: {
                char cadena[100];
                printf("Ingrese una cadena para capitalizar: ");
                fgets(cadena, 100, stdin);
                capitalizar_cadena(cadena);
                printf("Cadena capitalizada: %s\n", cadena);
                break;
            }
            case 3:{
                intoSplitString();
                break;
            }
            case 4:{
                intoJoinString();
                break;
            }
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida\n");
        }
    } while (opcion != 0);

    return 0;
}

// Función para mostrar el menú
void mostrar_menu() {
    printf("\n--- Menu de Opciones ---\n");
    printf("1. Buscar la ultima ocurrencia de una subcadena\n");
    printf("2. Capitalizar una cadena de texto\n");
    printf("3. Dividir una Cadena en un arreglo de Caracteres\n");
    printf("4. Unir arreglo de caracteres en una cadena\n");

    printf("0. Salir\n");
    printf("Elija una opcion: ");
}

// Función para buscar la última ocurrencia de una subcadena
int buscar_ultima_ocurrencia(char cadena[], char subcadena[]) {
    int ultima_pos = -1;
    char *ptr = strstr(cadena, subcadena); // Buscar la primera ocurrencia

    // Iterar mientras se encuentren ocurrencias
    while (ptr != NULL) {
        ultima_pos = ptr - cadena; // Actualizar la última posición encontrada
        ptr = strstr(ptr + 1, subcadena); // Buscar desde la siguiente posición
    }

    return ultima_pos >= 0 ? ultima_pos + 1 : 0; // Retornar 0 si no hay ocurrencia
}

// Capitalizar una cadena de texto
void capitalizar_cadena(char cadena[]) {
    int capitalizar = 1;
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (isspace(cadena[i])) {
            capitalizar = 1;
        } else if (capitalizar && isalpha(cadena[i])) {
            cadena[i] = toupper(cadena[i]);
            capitalizar = 0;
        }
    }
}
