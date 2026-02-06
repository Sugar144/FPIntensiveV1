#include <stdio.h>      // Funciones de entrada y salida estándar (printf, scanf, fopen, fclose, fgets, etc.)
#include <string.h>     // Funciones para trabajar con strings (strlen, strcpy, etc.)
#include <stdbool.h>    // Tipo booleano (bool) y constantes true/false

/* 
 * MAX_LINE: tamaño máximo de una línea que leeremos del fichero.
 * +1 se reserva para el carácter '\0' que marca el final de un string en C.
 */
#define MAX_LINE 514+1

/* 
 * MAX_FILENAME: tamaño máximo del nombre del fichero del tema.
 * +1 se reserva para el carácter '\0'.
 */
#define MAX_FILENAME 25+1

/*
 * Enumerado que representa las opciones del menú.
 * En C, los enums se guardan como enteros. 
 * TOPIC_TYPES empieza en 1 y el resto se incrementa automáticamente (2, 3, 4, 5).
 */
typedef enum {
    TOPIC_TYPES = 1,        // 1) Primitive data types
    TOPIC_VARIABLES,        // 2) Variables and constants
    TOPIC_ENUMS,            // 3) Enumerated types
    TOPIC_EXPRESSIONS,      // 4) Expressions
    EXIT                    // 5) Exit
} tMainOption;

/*
 * main: punto de entrada del programa.
 * argc y argv existen aunque aquí no los usemos (parámetros de línea de comandos).
 */
int main(int argc, char **argv)
{
    /* optionInt: almacena el número que escribe el usuario (1..5) */
    int optionInt;

    /* option: almacena la opción ya convertida al enumerado (tMainOption) */
    tMainOption option;

    /* fileName: nombre del fichero que se abrirá según el tema elegido */
    char fileName[MAX_FILENAME];

    /* line: buffer para guardar una línea leída del fichero */
    char line[MAX_LINE];

    /* fin: puntero a FILE para acceder al fichero abierto */
    FILE *fin;

    /*
     * validOption: indica si la opción introducida es válida (rango 1..5).
     * mustLoadFile: indica si, con esa opción, toca cargar y mostrar un fichero.
     * exitProgram: controla la repetición del menú (false = seguir, true = salir).
     */
    bool validOption;
    bool mustLoadFile;
    bool exitProgram;

    /* Estado inicial: arrancamos sin salir del programa */
    exitProgram = false;

    /*
     * Bucle principal del menú usando do-while:
     * - do-while garantiza que el menú se muestra al menos una vez.
     * - se repite hasta que exitProgram se ponga a true.
     */
    do {

        /* 
         * Al inicio de cada iteración:
         * - asumimos que la opción es válida
         * - asumimos que NO hay que cargar fichero hasta que se demuestre lo contrario
         */
        validOption = true;
        mustLoadFile = false;

        /* Mostrar el menú principal */
        printf("==== LEARNING MOTOR (Sprint 2) ====\n");
        printf("1) Primitive data types\n");
        printf("2) Variables and constants\n");
        printf("3) Enumerated types\n");
        printf("4) Expressions\n");
        printf("5) Exit\n");
        printf("Select option >> \n");

        /* 
         * Leer la opción como entero.
         * Se usa scanf (entrada desde teclado).
         */
        scanf("%d", &optionInt);

        /*
         * getchar() consume el '\n' (ENTER) que queda en el buffer tras scanf.
         * Esto evita problemas si luego se usaran lecturas por línea (por ejemplo, fgets de teclado).
         * Aquí no es estrictamente necesario para el resto del programa, pero es un patrón común y correcto.
         */
        getchar(); /* Consumir salto de línea */

        /* Validar que el número esté dentro del rango permitido */
        if (optionInt < 1 || optionInt > 5) {
            /* Si está fuera de rango, marcamos opción inválida y avisamos */
            printf("Invalid option\n");
            validOption = false;
        } else {
            /* Convertimos el entero al enumerado (misma representación interna: entero) */
            option = (tMainOption) optionInt;
        }

        /*
         * Solo si la opción es válida, decidimos qué hacer.
         * Aquí se separan claramente:
         * - la validación del número
         * - la selección de fichero/salida
         */
        if (validOption == true) {

            /*
             * switch: selecciona el caso según la opción.
             * IMPORTANTE: break aquí SOLO “sale del switch”, NO sale del bucle do-while.
             */
            switch (option) {

                case TOPIC_TYPES:
                    /* Copiar el nombre del fichero del tema elegido */
                    strcpy(fileName, "topic_1_types.txt");
                    /* Indicar que se debe abrir y mostrar contenido */
                    mustLoadFile = true;
                    break;

                case TOPIC_VARIABLES:
                    strcpy(fileName, "topic_2_variables.txt");
                    mustLoadFile = true;
                    break;

                case TOPIC_ENUMS:
                    strcpy(fileName, "topic_3_enums.txt");
                    mustLoadFile = true;
                    break;

                case TOPIC_EXPRESSIONS:
                    strcpy(fileName, "topic_4_expressions.txt");
                    mustLoadFile = true;
                    break;

                case EXIT:
                    /*
                     * Salida del programa:
                     * - mostramos mensaje
                     * - marcamos exitProgram = true para terminar el do-while
                     * - NO cargamos fichero
                     */
                    printf("Bye!\n");
                    exitProgram = true;
                    break;

                default:
                    /*
                     * Caso de seguridad:
                     * teóricamente no debería pasar porque validamos 1..5,
                     * pero es buena práctica mantenerlo.
                     */
                    validOption = false;
                    break;
            }
        }

        /*
         * Carga y muestra del contenido:
         * Solo se entra si:
         * - la opción era válida
         * - esa opción requiere cargar fichero (no EXIT)
         */
        if (validOption == true && mustLoadFile == true) {

            /* Abrir el fichero en modo lectura */
            fin = fopen(fileName, "r");

            if (fin == NULL) {
                /* Si fopen falla, el puntero es NULL: no se puede leer */
                printf("ERROR: unable to open topic file\n");
            } else {

                /* Encabezado del bloque de contenido */
                printf("---- CONTENT ----\n");

                /*
                 * Leer todo el fichero línea a línea.
                 * - fgets lee como máximo MAX_LINE-1 caracteres y añade '\0' al final.
                 * - feof(fin) se usa como condición del bucle en el estilo típico de la asignatura.
                 */
                while (!feof(fin)) {

                    /* Limpiar el buffer por claridad (no estrictamente necesario) */
                    line[0] = '\0';

                    /* Leer una línea del fichero */
                    fgets(line, MAX_LINE - 1, fin);

                    /* Asegurar fin de cadena por seguridad */
                    line[MAX_LINE - 1] = '\0';

                    /*
                     * Si la línea tiene contenido, la imprimimos.
                     * strlen(line) > 0 evita imprimir líneas vacías (aunque cuidado: una línea "\n" tiene strlen 1).
                     */
                    if (strlen(line) > 0) {
                        printf("%s", line);
                    }
                }

                /* Pie del bloque de contenido */
                printf("-----------------\n");

                /* Cerrar el fichero para liberar el recurso */
                fclose(fin);
            }
        }

    } while (exitProgram == false);  /* Repetir mientras no se haya elegido EXIT */

    /* Único punto de salida del programa (como pide la asignatura) */
    return 0;
}
