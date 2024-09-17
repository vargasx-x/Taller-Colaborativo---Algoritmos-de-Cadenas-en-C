#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/**
* Metodo que permite verificar si una cadena de texto es palíndroma
 * @param cadena cadena a verificar
 * @return 1 si la cadena es palindroma, 0 si la cadena no es palindroma
 */
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

/**
 * Metodo que permite validar paréntesis.
 * @param cadena cadena a validar los parentecis
 * @return el numero de parentesis que estan bien en la cadena, si no -1.
 */
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

/**
 * Metodo que permite dividir una cadena
 * @param str cadena de texto
 * @return apuntador de la cadena de texto
 */
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

/**
 * Metodo que permite unir palabras en una cadena usando un separador
 * @param string Cadena de texto a unir
 * @param separator separador con el que se van a unir
 * @return una cadena de caracteres que muestra la cadena unida
 */
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

/**
 * Metodo que permite buscar la última ocurrencia de una subcadena
 * @param cadena Cadena de texto principal
 * @param subcadena cadena de texto a validar
 * @return retorna la posicion en donde empieza la subcadena si cumple con la ultima ocurrencia, si no hay retorna 0.
 */
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

/**
 * Metodo que permite Capitalizar una cadena de texto
 * @param cadena cadena a capitalizar
 */
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

/**
 * Metodo que permite verificar si una cadena de texto termina con una subcadena
 * @param cadena Cadena principal
 * @param subcadena Subcadena a verificar
 * @return retorna 1 si la cadena termina con la subcadena, en caso contrario retorna 0.
 */
int verificar_final_cadena(char cadena[], char subcadena[]) {
    int long_cadena = strlen(cadena);       // Longitud de la cadena
    int long_subcadena = strlen(subcadena);

    // Verificar si la subcadena es más la rga que la cadena principal
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

/**
 * Metodo que permite formatear un valor numerico en una cadena de caracteres
 * @param valor Valor a formatear.
 */
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
/**
 * Metodo principal
 */
int main() {
    char* array = NULL;
    int opcion;
    do {
        mostrar_menu();
        if (scanf("%d", &opcion) != 1) {
            // Si scanf no puede leer un número
            printf("Opción no válida. Por favor, ingrese un número.\n");
            // Limpiar el búfer de entrada
            while (getchar() != '\n');
            continue; // Saltar el resto del ciclo y volver a mostrar el menú
        }

        // Limpiar el búfer de entrada
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
                    printf(" %d, La subcadena no finaliza la cadena principal \n", bool);
                else
                    printf(" %d, La subcadena finaliza la cadena principal\n", bool);
                break;
            }

            case 6: {
                int valor;
                printf("Ingrese el numero a formatear: ");
                scanf("%d", &valor);

                // Aquí llamamos a la función que formatea el valor
                formatear_valor_numerico(valor);

                // Volverá a mostrar el menú sin salir del programa
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
                    printf("La cadena de texto es un palindromo.\n");
                } else {
                    printf("La cadena de texto NO es un palindromo.\n");
                }


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

}

/**
 * Metodo que permite mostrar el menú
 */
void mostrar_menu() {
    printf("\n--- MENU PRINCIPAL ---\n");
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
