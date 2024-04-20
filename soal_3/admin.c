#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h> // Menambahkan header untuk menggunakan kill()

// Fungsi untuk mendapatkan waktu saat ini dalam format tertentu
char *get_current_time() {
    time_t now;
    struct tm *local_time;
    static char current_time[20];

    now = time(NULL);
    local_time = localtime(&now);

    strftime(current_time, sizeof(current_time), "%d:%m:%Y-%H:%M:%S", local_time);

    return current_time;
}

// Fungsi untuk memeriksa status proses
char *check_process_status(int pid) {
    // Mengirim sinyal ke proses dengan ID yang diberikan
    int result = kill(pid, 0);

    // Memeriksa hasil pemanggilan kill()
    if (result == 0) {
        return "JALAN"; // Proses sedang berjalan
    } else {
        return "GAGAL"; // Proses tidak berjalan
    }
}

// Fungsi untuk memantau proses
void monitor_processes(char *user) {
    // Implementasi pemantauan proses di sini
    // Contoh: menggunakan ps command untuk mendapatkan daftar proses user
    char command[100];
    sprintf(command, "ps -u %s", user);

    // Membuka proses pipe untuk membaca output dari ps command
    FILE *pipe = popen(command, "r");
    if (pipe == NULL) {
        perror("Error opening pipe");
        exit(EXIT_FAILURE);
    }

    // Membuka file log untuk ditulis
    char logfile[50];
    sprintf(logfile, "%s.log", user);
    FILE *log_file = fopen(logfile, "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    // Membaca output dari ps command dan menuliskannya ke stdout dan file log
    printf("Time\t\tUser\tPID\tProcess Name\tStatus\n");
    fprintf(log_file, "Time\t\tUser\tPID\tProcess Name\tStatus\n");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        // Ekstrak pid dan nama proses dari buffer
        char *token;
        char *saveptr;
        token = strtok_r(buffer, " ", &saveptr); // Pemisahan pertama dengan spasi
        int pid = atoi(token);
        token = strtok_r(NULL, "\n", &saveptr); // Pemisahan kedua dengan newline
        char *process_name = token;

        if (pid != 0 && process_name != NULL) {
            // Mendapatkan status proses
            char *status = check_process_status(pid);

            // Cetak ke stdout
            printf("[%s]\t%s\t%d\t%s\t%s\n", get_current_time(), user, pid, process_name, status);

            // Tulis ke file log
            fprintf(log_file, "[%s]\t%s\t%d\t%s\t%s\n", get_current_time(), user, pid, process_name, status);
        }
    }

    // Menutup proses pipe
    int status = pclose(pipe);
    if (status == -1) {
        perror("Error closing pipe");
        exit(EXIT_FAILURE);
    } else if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        if (exit_status != 0) {
            fprintf(stderr, "Command execution failed with exit status %d\n", exit_status);
            exit(EXIT_FAILURE);
        }
    } else if (WIFSIGNALED(status)) {
        int signal_number = WTERMSIG(status);
        fprintf(stderr, "Command terminated by signal %d\n", signal_number);
        exit(EXIT_FAILURE);
    }

    // Menutup file log
    fclose(log_file);
}

// Fungsi untuk menghentikan pemantauan proses
void stop_monitoring(char *user) {
    printf("Stop monitoring for user %s\n", user);
    // Implementasi untuk menghentikan pemantauan proses di sini
}

// Fungsi untuk mengendalikan proses
void control_processes(char *user) {
    printf("Control processes for user %s\n", user);
    // Implementasi untuk mengendalikan proses di sini
}

// Fungsi untuk menghentikan pengendalian proses
void stop_control(char *user) {
    printf("Stop controlling processes for user %s\n", user);
    // Implementasi untuk menghentikan pengendalian proses di sini
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s -m <user>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *option = argv[1];
    char *user = argv[2];

    if (strcmp(option, "-m") == 0) {
        monitor_processes(user);
    } else if (strcmp(option, "-s") == 0) {
        stop_monitoring(user);
    } else if (strcmp(option, "-c") == 0) {
        control_processes(user);
    } else if (strcmp(option, "-a") == 0) {
        stop_control(user);
    } else {
        fprintf(stderr, "Invalid option\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
