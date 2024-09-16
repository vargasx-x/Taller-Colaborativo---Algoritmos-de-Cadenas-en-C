#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Prototipos de funciones
int buscar_ultima_ocurrencia(char cadena[], char subcadena[]);

void capitalizar_cadena(char cadena[]);

int verificar_final_cadena(char cadena[], char subcadena[]);

void formatear_valor_numerico(int valor);

int es_palindromo(char cadena[]);

int validar_parentesis(char cadena[]);

void mostrar_menu();

// Función para Dividir una cadena
char* splitString(const char *str) {
    // Calcular la longitud de la cadena de entrada
    int len = strlen(str);

    // Reservar memoria para la nueva cadena, incluyendo espacio para el carácter nulo
    char* array = (char*) malloc((len + 1) * sizeof(char));

    // Verificar si la asignación de memoria fue exitosa
    if (array == NULL) {
        printf("Error al asignar memoria.\n");  // Mensaje de error en español
        return NULL;  // Devolver NULL para indicar fallo
    }

    // Copiar la cadena de entrada a la memoria recién asignada
    strcpy(array, str);

    // Devolver el puntero a la nueva cadena
    return array;
}

// Función para unir palabras en una cadena usando un separador
char* joinString(char* string, char separator) {
    // Calcular la longitud de la cadena de entrada
    int length = strlen(string);

    // Contar el número de palabras en la cadena (asumiendo que las palabras están separadas por espacios)
    int word_count = 1;
    for (int i = 0; i < length; i++) {
        if (string[i] == ' ') {
            word_count++;
        }
    }

    // Calcular la longitud total de la nueva cadena, considerando el separador
    // longitud original + (número de palabras - 1) + 1 (para el carácter nulo)
    int total_length = length + (word_count - 1) + 1;

    // Reservar memoria para la nueva cadena
    char* result = (char*)malloc(total_length * sizeof(char));
    if (result == NULL) {
        printf("Error al asignar memoria.\n");  // Mensaje de error en inglés
        exit(1);  // Terminar el programa si la asignación de memoria falla
    }

    // Copiar la cadena original a la nueva cadena, reemplazando los espacios con el separador
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (string[i] == ' ') {
            result[j++] = separator;  // Reemplazar espacio con el separador
        } else {
            result[j++] = string[i];  // Copiar el carácter original
        }
    }
    result[j] = '\0';  // Añadir el carácter nulo al final de la nueva cadena

    // Devolver el puntero a la nueva cadena
    return result;
}


// Función principal
int main() {
    char* array = NULL;
    int opcion;
    do {
        mostrar_menu();
        scanf("%d", &opcion);
        getchar();

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
                char input[100];

                printf("Ingrese una cadena: ");
                fgets(input, sizeof(input), stdin);

                input[strcspn(input, "\n")] = '\0';

                char *array = splitString(input);

                if (array != NULL) {
                    printf("El apuntador al arreglo de caracteres es: %p\n", (void *) array);
                    printf("La cadena copiada en el arreglo es: %s\n", array);
                    free(array);
                }

                break;
            }
            case 4:{
                char separator;
                printf("Introduce el separador de palabras: ");
                scanf(" %c", &separator);

                getchar();

                char string[1000];
                printf("Introduce la cadena de palabras separadas por espacios: ");
                fgets(string, sizeof(string), stdin);

                string[strcspn(string, "\n")] = 0;

                char* result = joinString(string, separator);

                printf("Cadena resultante: %s\n", result);

                free(result);
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
                scanf("%d", &valor);
                formatear_valor_numerico(valor);
                printf("Valor formateado: %s\n", valor);
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