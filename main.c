#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TOPICS 5
#define MAX_EXAMPLES 10
#define MAX_LINES 50
#define MAX_TEXT 512

/*
 * ============================
 * TYPES
 * ============================
 */

typedef struct {
    char title[MAX_TEXT];

    char description[MAX_LINES][MAX_TEXT];
    int nDescriptionLines;

    char pseudocode[MAX_LINES][MAX_TEXT];
    int nPseudocodeLines;

    char cCode[MAX_LINES][MAX_TEXT];
    int nCLines;

} tExample;

typedef struct {
    char title[MAX_TEXT];

    tExample examples[MAX_EXAMPLES];
    int nExamples;

} tTopic;

/*
 * ============================
 * AUXILIARY FUNCTIONS
 * ============================
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
 * ============================
 * LOAD EXAMPLE
 * ============================
 */

void loadExample(FILE *fin, tExample *example)
{
    char line[MAX_TEXT];
    int lineLength;
    int lineIndex;

    /* Read title */
    fgets(example->title, MAX_TEXT - 1, fin);
    example->title[MAX_TEXT - 1] = '\0';

    lineLength = strlen(example->title);
    if (lineLength > 0 && example->title[lineLength - 1] == '\n') {
        example->title[lineLength - 1] = '\0';
    }

    /* DESCRIPTION */
    example->nDescriptionLines = 0;

    fgets(line, MAX_TEXT - 1, fin);
    line[MAX_TEXT - 1] = '\0';

    lineLength = strlen(line);
    if (lineLength > 0 && line[lineLength - 1] == '\n') {
        line[lineLength - 1] = '\0';
    }

    while (strcmp(line, "END_DESCRIPTION") != 0) {

        example->nDescriptionLines = example->nDescriptionLines + 1;
        lineIndex = example->nDescriptionLines - 1;

        if (lineIndex < MAX_LINES) {
            strcpy(example->description[lineIndex], line);
        }

        fgets(line, MAX_TEXT - 1, fin);
        line[MAX_TEXT - 1] = '\0';

        lineLength = strlen(line);
        if (lineLength > 0 && line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0';
        }
    }

    /* PSEUDOCODE */
    example->nPseudocodeLines = 0;

    fgets(line, MAX_TEXT - 1, fin);
    line[MAX_TEXT - 1] = '\0';

    lineLength = strlen(line);
    if (lineLength > 0 && line[lineLength - 1] == '\n') {
        line[lineLength - 1] = '\0';
    }

    while (strcmp(line, "END_PSEUDOCODE") != 0) {

        example->nPseudocodeLines = example->nPseudocodeLines + 1;
        lineIndex = example->nPseudocodeLines - 1;

        if (lineIndex < MAX_LINES) {
            strcpy(example->pseudocode[lineIndex], line);
        }

        fgets(line, MAX_TEXT - 1, fin);
        line[MAX_TEXT - 1] = '\0';

        lineLength = strlen(line);
        if (lineLength > 0 && line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0';
        }
    }

    /* C CODE */
    example->nCLines = 0;

    fgets(line, MAX_TEXT - 1, fin);
    line[MAX_TEXT - 1] = '\0';

    lineLength = strlen(line);
    if (lineLength > 0 && line[lineLength - 1] == '\n') {
        line[lineLength - 1] = '\0';
    }

    while (strcmp(line, "END_C") != 0) {

        example->nCLines = example->nCLines + 1;
        lineIndex = example->nCLines - 1;

        if (lineIndex < MAX_LINES) {
            strcpy(example->cCode[lineIndex], line);
        }

        fgets(line, MAX_TEXT - 1, fin);
        line[MAX_TEXT - 1] = '\0';

        lineLength = strlen(line);
        if (lineLength > 0 && line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0';
        }
    }
}

/*
 * ============================
 * LOAD TOPIC
 * ============================
 */

void loadTopic(FILE *fin, tTopic *topic)
{
    char line[MAX_TEXT];
    int lineLength;
    int exampleIndex;

    fgets(topic->title, MAX_TEXT - 1, fin);
    topic->title[MAX_TEXT - 1] = '\0';

    lineLength = strlen(topic->title);
    if (lineLength > 0 && topic->title[lineLength - 1] == '\n') {
        topic->title[lineLength - 1] = '\0';
    }

    topic->nExamples = 0;

    fgets(line, MAX_TEXT - 1, fin);
    line[MAX_TEXT - 1] = '\0';

    lineLength = strlen(line);
    if (lineLength > 0 && line[lineLength - 1] == '\n') {
        line[lineLength - 1] = '\0';
    }

    while (strcmp(line, "END_TOPIC") != 0) {

        if (strcmp(line, "EXAMPLE") == 0) {

            topic->nExamples = topic->nExamples + 1;
            exampleIndex = topic->nExamples - 1;

            if (exampleIndex < MAX_EXAMPLES) {
                loadExample(fin, &topic->examples[exampleIndex]);
            }
        }

        fgets(line, MAX_TEXT - 1, fin);
        line[MAX_TEXT - 1] = '\0';

        lineLength = strlen(line);
        if (lineLength > 0 && line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0';
        }
    }
}

/*
 * ============================
 * LOAD TOPICS FROM FILE
 * ============================
 */

void loadTopicsFromFile(char fileName[MAX_TEXT],
                        tTopic topics[MAX_TOPICS],
                        int *nTopics,
                        bool *isRead)
{
    FILE *fin;
    char line[MAX_TEXT];
    int lineLength;
    int topicIndex;

    fin = fopen(fileName, "r");

    if (fin != NULL) {

        *nTopics = 0;

        while (fgets(line, MAX_TEXT - 1, fin) != NULL) {

            line[MAX_TEXT - 1] = '\0';

            lineLength = strlen(line);
            if (lineLength > 0 && line[lineLength - 1] == '\n') {
                line[lineLength - 1] = '\0';
            }

            if (strcmp(line, "TOPIC") == 0) {

                *nTopics = *nTopics + 1;
                topicIndex = *nTopics - 1;

                if (topicIndex < MAX_TOPICS) {
                    loadTopic(fin, &topics[topicIndex]);
                }
            }
        }

        fclose(fin);
        *isRead = true;

    } else {
        *isRead = false;
    }
}

/*
 * ============================
 * SHOW EXAMPLE
 * ============================
 */

void showExampleContent(tExample example)
{
    int lineIndex;

    printf("---- DESCRIPTION ----\n");
    for (lineIndex = 0; lineIndex < example.nDescriptionLines; lineIndex++) {
        printf("%s\n", example.description[lineIndex]);
    }

    printf("---- PSEUDOCODE ----\n");
    for (lineIndex = 0; lineIndex < example.nPseudocodeLines; lineIndex++) {
        printf("%s\n", example.pseudocode[lineIndex]);
    }

    printf("---- C CODE ----\n");
    for (lineIndex = 0; lineIndex < example.nCLines; lineIndex++) {
        printf("%s\n", example.cCode[lineIndex]);
    }
}

/*
 * ============================
 * SHOW EXAMPLES MENU
 * ============================
 */

void showExamplesMenu(tTopic topic)
{
    int optionInt;
    int exampleIndex;

    printf("---- EXAMPLES ----\n");

    for (exampleIndex = 0; exampleIndex < topic.nExamples; exampleIndex++) {
        printf("%d) %s\n", exampleIndex + 1, topic.examples[exampleIndex].title);
    }

    printf("Select example >> ");
    scanf("%d", &optionInt);
    getchar();

    if (isValidOption(optionInt, topic.nExamples)) {
        exampleIndex = optionInt - 1;
        showExampleContent(topic.examples[exampleIndex]);
    } else {
        printf("INVALID OPTION\n");
    }
}

/*
 * ============================
 * MAIN
 * ============================
 */

int main(void)
{
    tTopic topics[MAX_TOPICS];
    int nTopics;

    bool isRead;
    bool exitProgram;

    int optionInt;
    int topicIndex;

    char fileName[MAX_TEXT];

    exitProgram = false;

    printf("LOAD TOPICS FROM FILE >> ");
    scanf("%s", fileName);
    getchar();

    loadTopicsFromFile(fileName, topics, &nTopics, &isRead);

    if (isRead == true) {

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
                    showExamplesMenu(topics[topicIndex]);

                } else {

                    printf("INVALID OPTION\n");
                }
            }

        } while (exitProgram == false);

    } else {

        printf("ERROR: unable to load file\n");
    }

    return 0;
}
