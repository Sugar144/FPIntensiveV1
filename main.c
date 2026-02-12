#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
 * =========================================================
 * CONSTANTS
 * =========================================================
 */

#define MAX_TOPICS 5
#define MAX_EXAMPLES 10
#define MAX_LINES 50
#define MAX_LINE 514
#define MAX_TITLE 100


/*
 * =========================================================
 * TYPES
 * =========================================================
 */

typedef struct {
    char title[MAX_TITLE];

    char description[MAX_LINES][MAX_LINE];
    int nDescriptionLines;

    char pseudocode[MAX_LINES][MAX_LINE];
    int nPseudocodeLines;

    char cCode[MAX_LINES][MAX_LINE];
    int nCLines;

} tExample;


typedef struct {
    char title[MAX_TITLE];
    tExample examples[MAX_EXAMPLES];
    int nExamples;

} tTopic;


/*
 * =========================================================
 * FUNCTION: isValidOption
 * =========================================================
 * Checks if an option is within range.
 */

bool isValidOption(int value, int maxValue)
{
    bool valid;

    if (value >= 1 && value <= maxValue) {
        valid = true;
    } else {
        valid = false;
    }

    return valid;
}


/*
 * =========================================================
 * ACTION: loadExample
 * =========================================================
 * Reads one complete example from file.
 * Uses pointer to modify example directly.
 */

void loadExample(FILE *fin, tExample *example)
{
    char line[MAX_LINE];
    int lineLength;

    int lineIndex;

    /* ===== Read title ===== */
    fgets(example->title, MAX_TITLE - 1, fin);

    lineLength = (int)strlen(example->title);
    if (lineLength > 0 && example->title[lineLength - 1] == '\n') {
        example->title[lineLength - 1] = '\0';
    }

    /* ===== DESCRIPTION ===== */
    example->nDescriptionLines = 0;

    fgets(line, MAX_LINE - 1, fin);
    lineLength = (int)strlen(line);
    if (lineLength > 0 && line[lineLength - 1] == '\n') {
        line[lineLength - 1] = '\0';
    }

    while (strcmp(line, "END_DESCRIPTION") != 0) {

        lineIndex = example->nDescriptionLines;

        strcpy(example->description[lineIndex], line);

        example->nDescriptionLines++;

        fgets(line, MAX_LINE - 1, fin);
        lineLength = (int)strlen(line);
        if (lineLength > 0 && line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0';
        }
    }

    /* ===== PSEUDOCODE ===== */
    example->nPseudocodeLines = 0;

    fgets(line, MAX_LINE - 1, fin);
    lineLength = (int)strlen(line);
    if (lineLength > 0 && line[lineLength - 1] == '\n') {
        line[lineLength - 1] = '\0';
    }

    while (strcmp(line, "END_PSEUDOCODE") != 0) {

        lineIndex = example->nPseudocodeLines;

        strcpy(example->pseudocode[lineIndex], line);

        example->nPseudocodeLines++;

        fgets(line, MAX_LINE - 1, fin);
        lineLength = (int)strlen(line);
        if (lineLength > 0 && line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0';
        }
    }

    /* ===== C CODE ===== */
    example->nCLines = 0;

    fgets(line, MAX_LINE - 1, fin);
    lineLength = (int)strlen(line);
    if (lineLength > 0 && line[lineLength - 1] == '\n') {
        line[lineLength - 1] = '\0';
    }

    while (strcmp(line, "END_C") != 0) {

        lineIndex = example->nCLines;

        strcpy(example->cCode[lineIndex], line);

        example->nCLines++;

        fgets(line, MAX_LINE - 1, fin);
        lineLength = (int)strlen(line);
        if (lineLength > 0 && line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0';
        }
    }
}


/*
 * =========================================================
 * ACTION: loadTopic
 * =========================================================
 */

void loadTopic(FILE *fin, tTopic *topic)
{
    char line[MAX_LINE];
    int lineLength;

    int exampleIndex;

    /* Read topic title */
    fgets(topic->title, MAX_TITLE - 1, fin);

    lineLength = (int)strlen(topic->title);
    if (lineLength > 0 && topic->title[lineLength - 1] == '\n') {
        topic->title[lineLength - 1] = '\0';
    }

    topic->nExamples = 0;

    fgets(line, MAX_LINE - 1, fin);
    lineLength = (int)strlen(line);
    if (lineLength > 0 && line[lineLength - 1] == '\n') {
        line[lineLength - 1] = '\0';
    }

    while (strcmp(line, "END_TOPIC") != 0) {

        if (strcmp(line, "EXAMPLE") == 0) {

            exampleIndex = topic->nExamples;

            loadExample(fin, &topic->examples[exampleIndex]);

            topic->nExamples++;
        }

        fgets(line, MAX_LINE - 1, fin);
        lineLength = (int)strlen(line);
        if (lineLength > 0 && line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0';
        }
    }
}


/*
 * =========================================================
 * ACTION: loadTopicsFromFile
 * =========================================================
 */

void loadTopicsFromFile(char fileName[MAX_TITLE], tTopic topics[MAX_TOPICS],
                        int *nTopics, bool *isRead)
{
    FILE *fin;
    char line[MAX_LINE];
    int lineLength;
    int topicIndex;

    fin = fopen(fileName, "r");

    if (fin == NULL) {

        *isRead = false;

    } else {

        *nTopics = 0;

        while (fgets(line, MAX_LINE - 1, fin) != NULL) {

            line[MAX_LINE - 1] = '\0';
            
            lineLength = (int)strlen(line);
            if (lineLength > 0 && line[lineLength - 1] == '\n') {
                line[lineLength - 1] = '\0';
            }

            if (strcmp(line, "TOPIC") == 0) {

                topicIndex = *nTopics;

                loadTopic(fin, &topics[topicIndex]);

                (*nTopics)++;
            }
            
        }

        fclose(fin);
        *isRead = true;
    }
}


/*
 * =========================================================
 * MAIN
 * =========================================================
 */

int main(void)
{
    tTopic topics[MAX_TOPICS];
    int nTopics;

    bool isRead;
    bool exitProgram;

    int optionInt;

    int topicIndex;
    int exampleIndex;
    int lineIndex;

    tTopic currentTopic;
    tExample currentExample;

    char fileName[MAX_TITLE];

    printf("LOAD TOPICS FROM FILE >> ");
    scanf("%s", fileName);
    getchar();

    loadTopicsFromFile(fileName, topics, &nTopics, &isRead);

    if (isRead == false) {

        printf("ERROR loading file\n");

    } else {

        exitProgram = false;

        do {

            printf("==== LEARNING MOTOR (Sprint 4) ====\n");

            for (topicIndex = 0; topicIndex < nTopics; topicIndex++) {
                printf("%d) %s\n", topicIndex + 1, topics[topicIndex].title);
            }

            printf("0) Exit\n");
            printf("Select topic >> ");
            scanf("%d", &optionInt);
            getchar();

            if (optionInt == 0) {

                exitProgram = true;

            } else {

                if (isValidOption(optionInt, nTopics)) {

                    topicIndex = optionInt - 1;
                    currentTopic = topics[topicIndex];

                    printf("---- EXAMPLES ----\n");

                    for (exampleIndex = 0;
                         exampleIndex < currentTopic.nExamples;
                         exampleIndex++) {

                        printf("%d) %s\n",
                               exampleIndex + 1,
                               currentTopic.examples[exampleIndex].title);
                    }

                    printf("Select example >> ");
                    scanf("%d", &optionInt);
                    getchar();

                    if (isValidOption(optionInt,
                                      currentTopic.nExamples)) {

                        exampleIndex = optionInt - 1;
                        currentExample =
                            currentTopic.examples[exampleIndex];

                        printf("---- DESCRIPTION ----\n");

                        for (lineIndex = 0;
                             lineIndex < currentExample.nDescriptionLines;
                             lineIndex++) {

                            printf("%s\n",
                                   currentExample.description[lineIndex]);
                        }

                        printf("---- PSEUDOCODE ----\n");

                        for (lineIndex = 0;
                             lineIndex < currentExample.nPseudocodeLines;
                             lineIndex++) {

                            printf("%s\n",
                                   currentExample.pseudocode[lineIndex]);
                        }

                        printf("---- C CODE ----\n");

                        for (lineIndex = 0;
                             lineIndex < currentExample.nCLines;
                             lineIndex++) {

                            printf("%s\n",
                                   currentExample.cCode[lineIndex]);
                        }
                    }
                }
            }

        } while (exitProgram == false);
    }

    return 0;
}
