#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


//Oleh Benjamin Khawarizmi Habibi

void launchApplications(const char *applicationName, int windowCount) {
    for (int idx = 0; idx < windowCount; idx++) {
        pid_t childProcessID = fork(); // Membuat proses anak
        if (childProcessID == 0) { // Jika ini adalah proses anak
            execlp(applicationName, applicationName, (char *)NULL); // Menjalankan aplikasi
            perror("exec");
            exit(EXIT_FAILURE);
        } else if (childProcessID < 0) { // Jika gagal membuat proses anak
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }
}

void processConfigFile(const char *configFilePath) {
    FILE *configFile = fopen(configFilePath, "r");
    if (configFile == NULL) {
        perror("Error opening config file");
        exit(EXIT_FAILURE);
    }

    char appName[256];
    int windowCount;
    while (fscanf(configFile, "%255s %d", appName, &windowCount) == 2) {
        launchApplications(appName, windowCount);
    }

    fclose(configFile);
}


int main(int argc, char *argv[]) {
    if (argc < 3 || (argc - 2) % 2 != 0) {
        fprintf(stderr, "Usage: %s -o <app1> <num1> <app2> <num2> ... <appN> <numN>\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int idx = 2; idx < argc; idx += 2) {
        const char *applicationName = argv[idx];
        int windowCount = atoi(argv[idx + 1]);
        launchApplications(applicationName, windowCount);
    }

    // Menunggu semua proses anak selesai
    for (int idx = 0; idx < (argc - 2) / 2; idx++) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
