#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* letters[9] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

int main(void) {
    char *line = NULL;
    size_t size = 0;
    ssize_t len ;
    int match, first, last;
    int sum = 0;

    FILE *file = fopen("res/d1.txt", "r");
    while ((len = getline(&line, &size, file)) != -1) {
        first = -1;
        last = -1;

        for (int i=0; i<len-1; i++) {
            match = -1;

            if (isdigit(line[i])) {
                match = line[i] - '0';
            } else {
                for (int j=0; j<9; j++) {
                    if (strncmp(letters[j], line + i, strlen(letters[j])) == 0) {
                        match = j + 1;
                        i += (strlen(letters[j]) - 1);
                        break;
                    }
                }
            }

            if (match != -1) {
                if (first == -1) {
                    first = match;
                } else {
                    last = match;
                }
            }
        }

        if (last == -1) {
            last = first;
        }

        sum += first * 10 + last;
    }

    printf("Sum: %d\n", sum);
    fclose(file);
    free(line);

    return EXIT_SUCCESS;
}