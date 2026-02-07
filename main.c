#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* ===== CONSTANTES ===== */

#define MAX_TOPICS 5
#define MAX_EXAMPLES 10
#define MAX_LINES 50
#define MAX_LINE 514
#define MAX_TITLE 100

/* ===== TIPOS ===== */

typedef struct {
    char description[MAX_LINES][MAX_LINE];
    int nDescriptionLines;

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

/* ===== MAIN ===== */

int main(int argc, char **argv)
{
    tTopic topics[MAX_TOPICS];
    int nTopics;

    FILE *fin;
    char fileName[MAX_TITLE];
    char line[MAX_LINE];

    int topicIndex;
    int exampleIndex;
    int optionInt;

    bool exitProgram;

    /* ===== Inicialización ===== */

    nTopics = 0;
    exitProgram = false;

    printf("LOAD TOPICS FROM FILE >> ");
    scanf("%s", fileName);
    getchar(); /* consumir salto de línea */

    fin = fopen(fileName, "r");

    if (fin == NULL) {

        printf("ERROR: unable to open file\n");

    } else {

        /* ===== LECTURA COMPLETA DEL FICHERO ===== */

        while (!feof(fin)) {

            line[0] = '\0';
            fgets(line, MAX_LINE - 1, fin);
            line[MAX_LINE - 1] = '\0';

            if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
                line[strlen(line) - 1] = '\0';
            }

            if (strcmp(line, "TOPIC") == 0) {

                nTopics = nTopics + 1;

                fgets(topics[nTopics].title, MAX_TITLE - 1, fin);
                topics[nTopics].title[MAX_TITLE - 1] = '\0';

                if (topics[nTopics].title[strlen(topics[nTopics].title) - 1] == '\n') {
                    topics[nTopics].title[strlen(topics[nTopics].title) - 1] = '\0';
                }

                topics[nTopics].nExamples = 0;

                fgets(line, MAX_LINE - 1, fin);

                if (line[strlen(line) - 1] == '\n') {
                    line[strlen(line) - 1] = '\0';
                }

                while (strcmp(line, "END_TOPIC") != 0 && !feof(fin)) {

                    if (strcmp(line, "EXAMPLE") == 0) {

                        topics[nTopics].nExamples =
                            topics[nTopics].nExamples + 1;

                        exampleIndex = topics[nTopics].nExamples;

                        fgets(topics[nTopics].examples[exampleIndex].title,
                              MAX_TITLE - 1, fin);

                        if (topics[nTopics].examples[exampleIndex].title[
                                strlen(topics[nTopics].examples[exampleIndex].title) - 1] == '\n') {

                            topics[nTopics].examples[exampleIndex].title[
                                strlen(topics[nTopics].examples[exampleIndex].title) - 1] = '\0';
                        }

                        /* ===== DESCRIPTION ===== */

                        topics[nTopics].examples[exampleIndex].nDescriptionLines = 0;

                        fgets(line, MAX_LINE - 1, fin);

                        if (line[strlen(line) - 1] == '\n') {
                            line[strlen(line) - 1] = '\0';
                        }

                        while (strcmp(line, "END_DESCRIPTION") != 0) {

                            topics[nTopics].examples[exampleIndex].nDescriptionLines =
                                topics[nTopics].examples[exampleIndex].nDescriptionLines + 1;

                            strcpy(
                                topics[nTopics].examples[exampleIndex].description[
                                    topics[nTopics].examples[exampleIndex].nDescriptionLines
                                ],
                                line
                            );

                            fgets(line, MAX_LINE - 1, fin);

                            if (line[strlen(line) - 1] == '\n') {
                                line[strlen(line) - 1] = '\0';
                            }
                        }

                        /* ===== PSEUDOCODE ===== */

                        topics[nTopics].examples[exampleIndex].nPseudocodeLines = 0;

                        fgets(line, MAX_LINE - 1, fin);

                        if (line[strlen(line) - 1] == '\n') {
                            line[strlen(line) - 1] = '\0';
                        }

                        while (strcmp(line, "END_PSEUDOCODE") != 0) {

                            topics[nTopics].examples[exampleIndex].nPseudocodeLines =
                                topics[nTopics].examples[exampleIndex].nPseudocodeLines + 1;

                            strcpy(
                                topics[nTopics].examples[exampleIndex].pseudocode[
                                    topics[nTopics].examples[exampleIndex].nPseudocodeLines
                                ],
                                line
                            );

                            fgets(line, MAX_LINE - 1, fin);

                            if (line[strlen(line) - 1] == '\n') {
                                line[strlen(line) - 1] = '\0';
                            }
                        }

                        /* ===== C CODE ===== */

                        topics[nTopics].examples[exampleIndex].nCLines = 0;

                        fgets(line, MAX_LINE - 1, fin);

                        if (line[strlen(line) - 1] == '\n') {
                            line[strlen(line) - 1] = '\0';
                        }

                        while (strcmp(line, "END_C") != 0) {

                            topics[nTopics].examples[exampleIndex].nCLines =
                                topics[nTopics].examples[exampleIndex].nCLines + 1;

                            strcpy(
                                topics[nTopics].examples[exampleIndex].cCode[
                                    topics[nTopics].examples[exampleIndex].nCLines
                                ],
                                line
                            );

                            fgets(line, MAX_LINE - 1, fin);

                            if (line[strlen(line) - 1] == '\n') {
                                line[strlen(line) - 1] = '\0';
                            }
                        }
                    }

                    fgets(line, MAX_LINE - 1, fin);

                    if (line[strlen(line) - 1] == '\n') {
                        line[strlen(line) - 1] = '\0';
                    }
                }
            }
        }

        fclose(fin);
    }

    /* ===== MENÚ ===== */

    do {

        printf("==== LEARNING MOTOR (Sprint 3) ====\n");

        for (topicIndex = 1; topicIndex <= nTopics; topicIndex++) {
            printf("%d) %s\n", topicIndex, topics[topicIndex].title);
        }

        printf("0) Exit\n");
        scanf("%d", &optionInt);

        if (optionInt == 0) {
            exitProgram = true;
        } else {

            if (optionInt >= 1 && optionInt <= nTopics) {

                topicIndex = optionInt;

                for (exampleIndex = 1;
                     exampleIndex <= topics[topicIndex].nExamples;
                     exampleIndex++) {

                    printf("%d) %s\n",
                           exampleIndex,
                           topics[topicIndex].examples[exampleIndex].title);
                }

                scanf("%d", &exampleIndex);

                if (exampleIndex >= 1 &&
                    exampleIndex <= topics[topicIndex].nExamples) {

                    printf("---- DESCRIPTION ----\n");

                    for (optionInt = 1;
                         optionInt <= topics[topicIndex]
                                           .examples[exampleIndex]
                                           .nDescriptionLines;
                         optionInt++) {

                        printf("%s\n",
                               topics[topicIndex]
                                   .examples[exampleIndex]
                                   .description[optionInt]);
                    }

                    printf("---- PSEUDOCODE ----\n");

                    for (optionInt = 1;
                         optionInt <= topics[topicIndex]
                                           .examples[exampleIndex]
                                           .nPseudocodeLines;
                         optionInt++) {

                        printf("%s\n",
                               topics[topicIndex]
                                   .examples[exampleIndex]
                                   .pseudocode[optionInt]);
                    }

                    printf("---- C CODE ----\n");

                    for (optionInt = 1;
                         optionInt <= topics[topicIndex]
                                           .examples[exampleIndex]
                                           .nCLines;
                         optionInt++) {

                        printf("%s\n",
                               topics[topicIndex]
                                   .examples[exampleIndex]
                                   .cCode[optionInt]);
                    }
                }
            }
        }

    } while (exitProgram == false);

    return 0;
}
