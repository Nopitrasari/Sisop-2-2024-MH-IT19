#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#define MAX_LINE_LEN 512
#define MAX_PATH_LEN 512

//fungsi untuk mengganti string
void gantiString(char *str)
{
    if (strstr(str, "5pYw4R3") != NULL)
    {
        strcpy(str, "[SPYWARE]");
    }

    if (strstr(str, "m4LwAr3") != NULL)
    {
        strcpy(str, "[MALWARE]");
    }

    if (strstr(str, "R4nS0mWaR3") != NULL)
    {
        strcpy(str, "[RANSOMWARE]");
    }
}

//untuk menjalankan file dalam bentuk daemon
void daemonize()
{
    pid_t pid;
    pid_t sid;

    pid = fork();
    if (pid > 0){
        exit(EXIT_SUCCESS);
    }
    if (pid < 0){
        exit(EXIT_FAILURE);
    }

    umask(0);

    sid = setsid();

    if (sid < 0){
        exit(EXIT_FAILURE);
    }
    if ((chdir("/")) < 0){
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDERR_FILENO);
    close(STDOUT_FILENO);
}


//fungsi untuk mencatat penghapusan string oleh virus.log
void hapusString(const char *namaFile)
{
    struct tm *local_time;
    char time_str[50];
    time_t waktu;
    time(&waktu);
    local_time = localtime(&waktu);
    strftime(time_str, sizeof(time_str), "%d-%m-%Y %H:%M:%S", local_time);

    FILE *virusLog = fopen("/home/riskiya/Documents/tes/virus.log", "a"); //penempatan vitus.log
        if (virusLog != NULL) {
        fprintf(virusLog, "[%s] Suspicious string at %s successfully replaced!\n", time_str, namaFile); //format dalam file virus.log
        fclose(virusLog);
    }

        else {
        perror("error:tidak bisa membuka");
    }
}

//fungsi untuk memproses file
void fileProses(const char *pathFolder)
{
    DIR *dir;
    char pathFile[MAX_PATH_LEN];
    struct dirent *ent;

    dir = opendir(pathFolder);
    if (dir == NULL) {
        perror("Error: tidak bisa membuka folder");
        exit(EXIT_FAILURE);
    }
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG) {
            snprintf(pathFile, sizeof(pathFile), "%s/%s", pathFolder, ent->d_name);
            FILE *file = fopen(pathFile, "r+");
            if (file == NULL) {
                perror("Error: tidak bisa membuka file");
                continue;
            }

            char line[MAX_LINE_LEN];
            while (fgets(line, sizeof(line), file) != NULL) {
                gantiString(line);
                fseek(file, -strlen(line), SEEK_CUR);
                fputs(line, file);
                fflush(file);
            }

            fclose(file);
            hapusString(ent->d_name);
        }
    }

    closedir(dir);
}

//fungsi main
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <folder_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    daemonize();
    while (1) {
        fileProses(argv[1]);
        sleep(15); //terus berjalan dengan jeda 15 detik
    }
    return EXIT_SUCCESS;
}
