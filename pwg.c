#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef _WIN32
    #include <windows.h>
    #include <ntstatus.h>
    #include <bcrypt.h>
    #pragma comment(lib, "bcrypt.lib")
#else
    #include <sys/random.h>
    #include <unistd.h>
#endif

int get_secure_random(uint8_t *buffer, size_t length) {
#ifdef _WIN32
    if (BCRYPT_SUCCESS(BCryptGenRandom(NULL, buffer, (ULONG)length, BCRYPT_USE_SYSTEM_PREFERRED_RNG))) {
        return 0;
    }
    return -1;
#else
    if (getrandom(buffer, length, 0) == (ssize_t)length) {
        return 0;
    }
    return -1;
#endif
}

void generate_secure_password(int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "0123456789"
                           "!@#$%^&*()-_=+";
    int charset_size = sizeof(charset) - 1;

    uint8_t *random_data = malloc(length);
    char *password = malloc(length + 1);

    if (!random_data || !password) {
        printf("Memory allocation error.\n");
        return;
    }

    if (get_secure_random(random_data, length) != 0) {
        printf("Error: Failed to generate secure random data.\n");
        free(random_data);
        free(password);
        return;
    }

    for (int i = 0; i < length; i++) {
        password[i] = charset[random_data[i] % charset_size];
    }
    password[length] = '\0';

    printf("Secure Password: %s\n", password);

    free(random_data);
    free(password);
}

int main(int argc, char *argv[]) {
    int length = (argc > 1) ? atoi(argv[1]) : 16;

    if (length <= 0 || length > 32) {
        printf("Usage: %s [length (1-32)]\n", argv[0]);
        return 1;
    }

    generate_secure_password(length);
    return 0;
}
