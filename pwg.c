#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_password(int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "0123456789"
                           "!@#$%^&*()-_=+";
    int charset_size = sizeof(charset) - 1;

    char *password = malloc(length + 1);
    if (!password) {
        printf("Memory allocation failed!\n");
        return;
    }

    srand((unsigned int)time(NULL));

    for (int i = 0; i < length; i++) {
        password[i] = charset[rand() % charset_size];
    }
    password[length] = '\0';

    printf("Generated Password: %s\n", password);
    free(password);
}

int main(int argc, char *argv[]) {
    int length = 16;

    if (argc > 1) {
        length = atoi(argv[1]);
    }

    if (length <= 0 || length > 32) {
        printf("Please provide a valid length (1-32).\n");
        return 1;
    }

    generate_password(length);
    return 0;
}
