#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check(char *password) {
    int auth = 0;
    char buffer[4];
    strcpy(buffer, password);

    if (strcmp(buffer, "abcd") == 0) {
        auth = 1;
    }

    return auth;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./overflow <password>\n");
        exit(1);
    }

    if (check(argv[1])) {
        printf("Correct password.\n");
    } else {
        printf("Incorrect password.\n");
    }

    return 0;
}
