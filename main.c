#include <stdio.h>
#include <stdbool.h>
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
    int count_lines = 0;
    int symbol;
    FILE *file = fopen(filename, "r");
    if ( file == NULL ) {
        return -1;
    }
    do {
        symbol = fgetc(file);
        if (symbol == '\n') {
            count_lines++;
        }
    } while(symbol != EOF);
    fclose(file);
    return count_lines;
}

int main() {
    char file1_name[255] = "file1.txt";
    char file2_name[255] = "file2.txt";
    int max_lines = 10;
    time_t currentTime;
    int random_value;
    struct tm *timeStructure;

    FILE *file1 = fopen(file1_name, "w");
    FILE *file2 = fopen(file2_name, "w");
    fclose(file1);
    fclose(file2);

    while (true)
    {
        file1 = fopen(file1_name, "a");
        file2 = fopen(file2_name, "a");

        currentTime = get_current_time();
        timeStructure = localtime(&currentTime);
        random_value = get_random_value();

        fprintf (file1,"%d\n", random_value);

        if (timeStructure->tm_sec % 2 == 0 && timeStructure->tm_sec != 0) {
            fprintf (file2,"%d\n", random_value);
        }

        fclose(file1);
        fclose(file2);

        if (get_count_lines(file2_name) == max_lines)
            clear_file(file2_name);

        //printf("Count Lines: %d\n", get_count_lines(file2_name));
        //printf("Time: %d:%d:%d\n", timeStructure->tm_hour, timeStructure->tm_min, timeStructure->tm_sec);
        //printf("Random Value: %d\n", random_value);
    }
    return 0;
}