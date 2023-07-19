#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

time_t get_current_time() {
    return time(NULL);
}

int get_random_value() {
    return rand() % (100 - 80 + 1);
}

void clear_file(char filename[255]) {
    FILE *file = fopen(filename, "w");
    fclose(file);
}

int get_count_lines(char filename[255]) {
    int countLines = 0;
    int symbol;
    FILE *file = fopen(filename, "r");
    if ( file == NULL ) {
        return -1;
    }
    do {
        symbol = fgetc(file);
        if (symbol == '\n') {
            countLines++;
        }
    }
    while(  symbol != EOF);
    fclose(file);
    return countLines;
}

void timerCallBack(struct tm *timeStructure, int randomValue, FILE *file1, FILE *file2, int maxLines, char file1Name[255], char file2Name[255]) {
    file1 = fopen(file1Name, "a");
    file2 = fopen(file2Name, "a");

    fprintf (file1,"%d\n", randomValue);

    if (timeStructure->tm_sec % 2 == 0)
        fprintf (file2,"%d\n", randomValue);

    fclose(file1);
    fclose(file2);

    if (get_count_lines(file2Name) == maxLines)
        clear_file(file2Name);
}

int main() {
    char file1Name[255] = "file1.txt";
    char file2Name[255] = "file2.txt";
    int maxLines = 10;
    time_t currentTime;
    int randomValue;
    struct tm *timeStructure;

    FILE *file1 = fopen(file1Name, "w");
    FILE *file2 = fopen(file2Name, "w");

    fclose(file1);
    fclose(file2);

    time_t previousTime = get_current_time();

    while (1)
    {
        currentTime = get_current_time();
        if (currentTime - previousTime >= 1)
        {
            timeStructure = localtime(&currentTime);
            randomValue = get_random_value();
            previousTime = currentTime;
            timerCallBack(timeStructure, randomValue, file1, file2, maxLines, file1Name, file2Name);
        }
    }
}