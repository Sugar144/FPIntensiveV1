#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
 * CONSTANTES
 */

#define MAX_TOPICS 5
#define MAX_EXAMPLES 10
#define MAX_LINES 50
#define MAX_LINE 514
#define MAX_TITLE 100

/*
 * TIPOS
 */

typedef struct {
    char description[MAX_LINES][MAX_LINE]; // Array de arrays (Matriz)
    int nDescriptionLines; // Contador de lineas de descripciones

    char pseudocode[MAX_LINES][MAX_LINE];
    int nPseudocodeLines;

    char cCode[MAX_LINES][MAX_LINE];
    int nCLines;

    char title[MAX_TITLE];
} tExample;

typedef struct {
    char title[MAX_TITLE];
    tExample examples[MAX_EXAMPLES];
    int nExamples;
} tTopic;

/*
 * MAIN FUNCTION
 */

int main(int argc, char **argv)
{
    /*
     * topics:
     * Vector donde se almacenan todos los topics cargados desde el fichero.
     */
    tTopic topics[MAX_TOPICS];

    /*
     * nTopics:
     * Número real de topics cargados.
     */
    int nTopics;

    /*
     * fin:
     * Puntero al fichero de entrada.
     */
    FILE *fin;

    /*
     * fileName:
     * Nombre del fichero introducido por el usuario.
     */
    char fileName[MAX_TITLE];

    /*
     * line:
     * Buffer auxiliar para leer líneas del fichero.
     */
    char line[MAX_LINE];

    /*
     * optionInt:
     * Variable auxiliar para leer opciones de menú.
     */
    int optionInt;

    /*
     * currentTopicIndex:
     * Índice del topic seleccionado.
     */
    int currentTopicIndex;

    /*
     * currentExampleIndex:
     * Índice del ejemplo seleccionado.
     */
    int currentExampleIndex;

    /*
     * lineIndex:
     * Índice para recorrer líneas de description, pseudocode y cCode.
     */
    int lineIndex;

    /*
     * lineLength:
     * Longitud de la línea actualmente leída.
     */
    int lineLength;

    /*
     * titleLength:
     * Longitud de un título (topic o example).
     */
    int titleLength;

    /*
     * exitProgram:
     * Controla la salida del menú principal.
     */
    bool exitProgram;

    /*
     * Inicialización
     */

    nTopics = 0;
    exitProgram = false;

    printf("LOAD TOPICS FROM FILE >> ");
    scanf("%s", fileName);
    getchar();

    fin = fopen(fileName, "r");

    if (fin == NULL) {

        printf("ERROR: unable to open file\n");

    } else {

        /*
         * LECTURA COMPLETA DEL FICHERO
         */

        while (!feof(fin)) {

            line[0] = '\0';
            fgets(line, MAX_LINE - 1, fin);
            line[MAX_LINE - 1] = '\0';

            lineLength = strlen(line);

            if (lineLength > 0 && line[lineLength - 1] == '\n') {
                line[lineLength - 1] = '\0';
            }

            if (strcmp(line, "TOPIC") == 0) {

                nTopics = nTopics + 1;

                fgets(topics[nTopics].title, MAX_TITLE - 1, fin);
                topics[nTopics].title[MAX_TITLE - 1] = '\0';

                titleLength = strlen(topics[nTopics].title);

                if (titleLength > 0 &&
                    topics[nTopics].title[titleLength - 1] == '\n') {

                    topics[nTopics].title[titleLength - 1] = '\0';
                }

                topics[nTopics].nExamples = 0;

                fgets(line, MAX_LINE - 1, fin);

                lineLength = strlen(line);

                if (lineLength > 0 && line[lineLength - 1] == '\n') {
                    line[lineLength - 1] = '\0';
                }

                while (strcmp(line, "END_TOPIC") != 0 && !feof(fin)) {

                    if (strcmp(line, "EXAMPLE") == 0) {

                        topics[nTopics].nExamples = topics[nTopics].nExamples + 1;

                        currentExampleIndex = topics[nTopics].nExamples;

                        fgets(topics[nTopics].examples[currentExampleIndex]
                                  .title, MAX_TITLE - 1,fin);

                        titleLength = strlen(topics[nTopics].
                                        examples[currentExampleIndex].title);

                        if (titleLength > 0 && topics[nTopics]
                                .examples[currentExampleIndex]
                                .title[titleLength - 1] == '\n') {

                            topics[nTopics].examples[currentExampleIndex]
                                .title[titleLength - 1] = '\0';
                        }

                        /*
                         * DESCRIPTION
                         */

                        topics[nTopics].examples[currentExampleIndex].nDescriptionLines = 0;

                        fgets(line, MAX_LINE - 1, fin);

                        lineLength = strlen(line);

                        if (lineLength > 0 && line[lineLength - 1] == '\n') {
                            line[lineLength - 1] = '\0';
                        }

                        while (strcmp(line, "END_DESCRIPTION") != 0) {

                            topics[nTopics].examples[currentExampleIndex]
                                .nDescriptionLines = topics[nTopics]
                                                    .examples[currentExampleIndex]
                                                    .nDescriptionLines + 1;

                            lineIndex = topics[nTopics].examples[currentExampleIndex]
                                        .nDescriptionLines;

                            strcpy(topics[nTopics].examples[currentExampleIndex]
                                    .description[lineIndex],line);

                            fgets(line, MAX_LINE - 1, fin);

                            lineLength = strlen(line);

                            if (lineLength > 0 && line[lineLength - 1] == '\n') {
                                line[lineLength - 1] = '\0';
                            }
                        }

                        /*
                         * PSEUDOCODE
                         */

                        topics[nTopics].examples[currentExampleIndex]
                            .nPseudocodeLines = 0;

                        fgets(line, MAX_LINE - 1, fin);

                        lineLength = (int)strlen(line);

                        if (lineLength > 0 && line[lineLength - 1] == '\n') {
                            line[lineLength - 1] = '\0';
                        }

                        while (strcmp(line, "END_PSEUDOCODE") != 0) {

                            topics[nTopics].examples[currentExampleIndex]
                                .nPseudocodeLines = topics[nTopics]
                                                    .examples[currentExampleIndex]
                                                    .nPseudocodeLines + 1;

                            lineIndex = topics[nTopics]
                                    .examples[currentExampleIndex]
                                    .nPseudocodeLines;

                            strcpy(topics[nTopics].examples[currentExampleIndex]
                                    .pseudocode[lineIndex], line);

                            fgets(line, MAX_LINE - 1, fin);

                            lineLength = strlen(line);

                            if (lineLength > 0 &&
                                line[lineLength - 1] == '\n') {
                                line[lineLength - 1] = '\0';
                            }
                        }

                        /*
                         * C CODE
                         */

                        topics[nTopics].examples[currentExampleIndex].nCLines = 0;

                        fgets(line, MAX_LINE - 1, fin);

                        lineLength = strlen(line);

                        if (lineLength > 0 && line[lineLength - 1] == '\n') {
                            line[lineLength - 1] = '\0';
                        }

                        while (strcmp(line, "END_C") != 0) {

                            topics[nTopics].examples[currentExampleIndex]
                                .nCLines = topics[nTopics]
                                            .examples[currentExampleIndex]
                                            .nCLines + 1;

                            lineIndex = topics[nTopics]
                                        .examples[currentExampleIndex]
                                        .nCLines;

                            strcpy(topics[nTopics].examples[currentExampleIndex]
                                    .cCode[lineIndex], line);

                            fgets(line, MAX_LINE - 1, fin);

                            lineLength = strlen(line);

                            if (lineLength > 0 &&
                                line[lineLength - 1] == '\n') {
                                line[lineLength - 1] = '\0';
                            }
                        }
                    }

                    fgets(line, MAX_LINE - 1, fin);

                    lineLength = strlen(line);

                    if (lineLength > 0 && line[lineLength - 1] == '\n') {
                        line[lineLength - 1] = '\0';
                    }
                }
            }
        }

        fclose(fin);
    }

    /*
     * MENÚ PRINCIPAL
     */

    do {

        printf("==== LEARNING MOTOR (Sprint 3) ====\n");

        for (currentTopicIndex = 1;
             currentTopicIndex <= nTopics;
             currentTopicIndex++) {

            printf("%d) %s\n", currentTopicIndex,
                   topics[currentTopicIndex].title);
        }

        printf("0) Exit\n");
        printf("Select topic >> ");
        scanf("%d", &optionInt);

        if (optionInt == 0) {

            exitProgram = true;

        } else {

            if (optionInt >= 1 && optionInt <= nTopics) {

                currentTopicIndex = optionInt;

                printf("---- EXAMPLES ----\n");

                for (currentExampleIndex = 1;
                     currentExampleIndex <=
                         topics[currentTopicIndex].nExamples;
                     currentExampleIndex++) {

                    printf("%d) %s\n", currentExampleIndex,
                            topics[currentTopicIndex]
                            .examples[currentExampleIndex].title);
                }

                printf("Select example >> ");
                scanf("%d", &optionInt);

                if (optionInt >= 1 &&
                    optionInt <= topics[currentTopicIndex].nExamples) {

                    currentExampleIndex = optionInt;

                    printf("---- DESCRIPTION ----\n");

                    for (lineIndex = 1;
                         lineIndex <=
                             topics[currentTopicIndex]
                                 .examples[currentExampleIndex]
                                 .nDescriptionLines;
                         lineIndex++) {

                        printf("%s\n",
                               topics[currentTopicIndex]
                                   .examples[currentExampleIndex]
                                   .description[lineIndex]);
                    }

                    printf("---- PSEUDOCODE ----\n");

                    for (lineIndex = 1;
                         lineIndex <= topics[currentTopicIndex]
                                 .examples[currentExampleIndex]
                                 .nPseudocodeLines;
                         lineIndex++) {

                        printf("%s\n", topics[currentTopicIndex]
                                   .examples[currentExampleIndex]
                                   .pseudocode[lineIndex]);
                    }

                    printf("---- C CODE ----\n");

                    for (lineIndex = 1;
                         lineIndex <= topics[currentTopicIndex]
                                 .examples[currentExampleIndex]
                                 .nCLines; lineIndex++) {

                        printf("%s\n",
                               topics[currentTopicIndex]
                                   .examples[currentExampleIndex]
                                   .cCode[lineIndex]);
                    }
                }
            }
        }

    } while (exitProgram == false);

    return 0;
}
