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

void formatear_valor_numerico(int valor);

int isPalindrome(char cadena[]) {
    int inicio = 0;
    int fin = strlen(cadena) - 1;

    for (int i = 0; cadena[i] != '\0'; i++) {
        if (isdigit(cadena[i])) {
            printf("Error: La cadena contiene valores numericos, solo se permiten letras.\n");
            return 0; // Si contiene números, no es válida.
        }
    }

    // Recorremos la cadena de extremo a extremo
    while (inicio < fin) {

        // Ignoramos los caracteres que no sean letras o dígitos numéricos
        if (!isalnum(cadena[inicio])) {
            inicio++;
        } else if (!isalnum(cadena[fin])) {
            fin--;
        } else {
            // Comparar los caracteres en minúsculas
            if (tolower(cadena[inicio]) != tolower(cadena[fin])) {
                return 0; // No es un palíndromo
            }
            inicio++;
            fin--;
        }
    }
    return 1; // Es un palíndromo
}

int validate_parentheses(char cadena[]) {
    
    int apertura = 0; 
    int pares = 0;   
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] == '(') {
            apertura++; // Encontrar paréntesis de apertura
        } else if (cadena[i] == ')') {
            if (apertura > 0) {
                apertura--; // Encontrar paréntesis de cierre que corresponde al de apertura
                pares++;   // Incrementamos el número de pares
            } else {
                // Si encontramos un paréntesis de cierre sin uno de apertura correspondiente
                return -1; // Indicar que los paréntesis no están balanceados
            }
        }
    }
    if (apertura == 0) {
        // Retorna el número de parentesis pares, si no queda ningún paréntesis sin cerrar
        return pares;
    } else {
        // Si la apertura es diferente de 0, hay paréntesis de apertura sin cerrar
        return -1;
    }
}

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
            case 5:{
                char cadena[100], subcadena[50];
                printf("Ingrese la cadena principal: ");
                fgets(cadena, 100, stdin);
                printf("Ingrese la subcadena a revisar: ");
                fgets(subcadena, 50, stdin);
                int bool = verificar_final_cadena(cadena, subcadena);
                if (bool == 0)
                    printf("La subcadena no finaliza la cadena principal \n");
                else
                    printf("La subcadena finaliza la cadena principal\n");
                break;
                break;
            }

            case 6: {
                int valor;
                printf("Ingrese el numero a formatear ");
                scanf("%d", &valor);  // Leer el número ingresado por teclado
                formatear_valor_numerico(valor);
                printf("Valor formateado: %s\n", valor);
                break;
            }

            case 7:{
                char cadena[50];
                
                printf("Introduce una cadena de texto: ");
                fgets(cadena, sizeof(cadena), stdin);

            // Eliminamos el salto de línea
                cadena[strcspn(cadena, "\n")] = 0;

            // Verificar si la cadena de texto es palíndroma
                if (isPalindrome(cadena)) {
                    printf("La cadena es un palíndromo.\n");
                } else {
                    printf("La cadena NO es un palíndromo.\n");
                }

                return 0;

                break;
            }

            case 8:{
                char cadena[100];
                printf("Ingrese una cadena para validar los parentesis: ");
                fgets(cadena, 100, stdin);
    
                int resultado = validate_parentheses(cadena);
    
                if (resultado == -1) {
                    printf("Los parentesis de apertura NO corresponden a los de cierre.\n");
                } else {
                    printf("Los parentesis de apertura y cierre son correctos, y hay %d pares correctos.\n", resultado);
                }
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
    printf("5. Verificar si una cadena de texto termina con otra\n");
    printf("6. Formatear un valor numerico\n");
    printf("7. Verificar si una cadena de texto es palíndroma\n");
    printf("8. Validar parentesis\n");

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
int verificar_final_cadena(char cadena[], char subcadena[]) {
    int long_cadena = strlen(cadena);       // Longitud de la cadena
    int long_subcadena = strlen(subcadena);

    // Verificar si la subcadena es más larga que la cadena principal
    if (long_subcadena > long_cadena) {
        return 0;
    }

    int pos_inicio_sub = long_cadena - long_subcadena;

    // Comparamos cada carácter de la subcadena con los caracteres finales de la cadena
    for (int i = 0; i < long_subcadena; i++) {
        char caracter_cadena = cadena[pos_inicio_sub + i];
        char caracter_subcadena = subcadena[i];

        if (caracter_cadena != caracter_subcadena) {
            return 0;
        }
    }

    return 1;
}

void formatear_valor_numerico(int valor) {
    char num[20];
    char num_formateado[30]; // Arreglo para almacenar la versión con separadores y signo de pesos
    int len_num, i, j = 0;
    int contador = 0;

    // Convertir el número a cadena de texto
    sprintf(num, "%d", valor);

    len_num = strlen(num);

    num_formateado[j++] = '$';

    // Calcular cuántos dígitos vienen antes del primer separador de miles
    int primeros_digitos = strlen(num) % 3;
    if (primeros_digitos == 0) {
        primeros_digitos = 3;
    }

    // Copiar los primeros dígitos sin separador
    for (i = 0; i < primeros_digitos; i++) {
        num_formateado[j++] = num[i];
    }

    // Añadir separadores de miles para el resto de los dígitos
    for (; i < len_num; i++) {
        if ((i - primeros_digitos) % 3 == 0) {
            num_formateado[j++] = ',';  
        }
        num_formateado[j++] = num[i];
    }

    // Imprimir el número formateado
    printf("Valor formateado: %s\n", num_formateado);
}