ain# Sisop-2-2024-MH-IT19
# Laporan Resmi Sistem Operasi Modul 2 Kelompok IT19

Anggota Kelompok IT19 : 
1. Riskiyatul Nur Oktarani (5027231013)
2. Aswaliya Novitriasari (5027231012)
3. Benjamin Khawarizmi Habibi (5027231078)

# Deskripsi Praktikum Soal Shift Modul 1

# SOAL 1

Gavriel adalah seorang cyber security enthusiast. Suatu hari, ia dikontrak oleh sebuah perusahaan ternama untuk membuat sebuah program yang cukup rumit dengan bayaran jutaan rupiah. Karena tergoda dengan nominal bayaran tersebut, Gavriel langsung menerima tawaran tersebut. Setelah mencoba membuat dan mengembangkan program tersebut selama seminggu, laptop yang digunakan Gavriel mengalami overheat dan mati total sehingga harus dilarikan ke tukang servis terdekat. Karena keterbatasan waktu dalam pembuatan program dan tidak ingin mengecewakan perusahaan, Gavriel meminta bantuan kalian untuk membuat program tersebut dengan ketentuan sebagai berikut:
a. Program dapat menerima input path berupa ‘argv’ untuk mengatur folder dimana file akan dieksekusi

b. Program tersebut berfungsi untuk mereplace string dengan ketentuan sebagai berikut:

  String m4LwAr3 direplace dengan string [MALWARE]

  String 5pYw4R3 direplace dengan string [SPYWARE]

  String R4nS0mWaR3 direplace dengan string [RANSOMWARE]

c. Program harus berjalan secara daemon, dan tidak diperbolehkan menggunakan command system() dalam pembuatan program

d. Program akan secara terus menerus berjalan di background dengan jeda 15 detik

e. Catat setiap penghapusan string yang dilakukan oleh program pada sebuah file bernama virus.log dengan format: [dd-mm-YYYY][HH:MM:SS] Suspicious string at <file_name> successfully replaced!

Contoh penggunaan: ./virus /home/user/virus

Contoh isi file sebelum program dijalankan:

pU=-JWQ$5$)D-[??%AVh]$cB6bm4LwAr3jEQC2p3R{HV]=-AUaxj:Qe+h
!aNX,i:!z3W=2;.tHc3&S+}6F)CFf%tfZLP1*w5m1PAzZJUux(
Pd&f8$F5=E?@#[6jd{TJKj]5pYw4R3{KK1?hz384$ge@iba5GAj$gqB41
#C&&a}M9C#f64Eb.?%c)dGbCvJXtU[?SE4h]BY4e1PR4nS0mWaR3{]S/{w?*


Contoh isi file setelah setelah program dijalankan:
pU=-JWQ$5$)D-[??%AVh]$cB6b[MALWARE]jEQC2p3R{HV]=-AUaxj:Qe+h
!aNX,i:!z3W=2;.tHc3&S+}6F)CFf%tfZLP1*w5m1PAzZJUux(
Pd&f8$F5=E?@#[6jd{TJKj][SPYWARE]{KK1?hz384$ge@iba5GAj$gqB41
#C&&a}M9C#f64Eb.?%c)dGbCvJXtU[?SE4h]BY4e1P[RANSOMWARE]{]S/{w?*

# PENYELESAIAN

a. untuk soal a saya menggunakan kode dibawah, Program dapat menerima input path berupa ‘argv’

```
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

```

b. untuk menjawab soal b, saya menggunakan fungsi dibawah ini, fungsi ini akan berjalan sesuai dengan format di soal

```
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

```

ini file sebelum di run

![image](https://github.com/Nopitrasari/Sisop-2-2024-MH-IT19/assets/151911480/537d2d25-0758-4283-a55a-4ff525def926)


dan ini untuk hasil setelah di run

![image](https://github.com/Nopitrasari/Sisop-2-2024-MH-IT19/assets/151911480/88ff4125-f5cc-46bf-b495-8627db040a95)


c. sesuai dengan soal yang c, file harus berjalan secara daemon, menggunakan kode berikut :

```
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


```

![image](https://github.com/Nopitrasari/Sisop-2-2024-MH-IT19/assets/151911480/f28209ec-5434-4289-9775-8a3a45f032b0)


diatas adalah bukti bahwa file sudah berjalan secara daemon.


d. agar program berjalan secara terus menerus dengan jeda 15 detik, disini menggunakan kode berikut :

```

    daemonize();
    while (1) {
        fileProses(argv[1]);
        sleep(15); //terus berjalan dengan jeda 15 detik
    }
    return EXIT_SUCCESS;

```

e. untuk menjawab soal e, hasil dari penghapusan file akan muncul di file virus.log sesuai dengan format di soal menggunakan fungsi berikut :

```
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

```

![image](https://github.com/Nopitrasari/Sisop-2-2024-MH-IT19/assets/151911480/67b7e2f6-afb9-4506-bce1-09954fe8730f)

diatas adalah isi dari file virus.log

berikut adalah fungsi untuk memproses file 

```
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


```


# REVISI 

mohon maaf mas sebenarnya kemarin pas demo saya kurang teliti dan buru buru, jadi ada kesalahan disaat ngerun
seharusnya 

```
./virus home/riskiya/Documents/tes

```

yang saya demokan kemarin 

```
./virus home/riskiya/Document/tes

```
jadi kesalahan dalam penulisan 'document', setelah saya coba lagi dengan code yang sama akhirnya bisa jalan


# SOAL 2

Paul adalah seorang mahasiswa semester 4 yang diterima magang di perusahaan XYZ. Pada hari pertama magang, ia diberi tugas oleh atasannya untuk membuat program manajemen file sederhana. Karena kurang terbiasa dengan bahasa C dan environment Linux, ia meminta bantuan kalian untuk mengembangkan program tersebut.
a. Atasannya meminta agar program tersebut dapat berjalan secara daemon dan dapat mengunduh serta melakukan unzip terhadap file berikut. Atasannya juga meminta program ini dibuat tanpa menggunakan command system()

b. Setelah ditelusuri, ternyata hanya 6 file teratas yang nama filenya tidak dienkripsi. Oleh karena itu, bantulah Paul untuk melakukan dekripsi terhadap nama file ke-7 hingga terakhir menggunakan algoritma ROT19

c. Setelah dekripsi selesai, akan terlihat bahwa setiap file memuat salah satu dari kode berikut: r3N4mE, d3Let3, dan m0V3. Untuk setiap file dengan nama yang memuat kode   
   d3Let3, hapus file tersebut. Sementara itu, untuk setiap file dengan nama yang memuat kode r3N4mE, lakukan hal berikut:
   - Jika ekstensi file adalah “.ts”, rename filenya menjadi “helper.ts”
   - Jika ekstensi file adalah “.py”, rename filenya menjadi “calculator.py”
   - Jika ekstensi file adalah “.go”, rename filenya menjadi “server.go”
   - Jika file tidak memuat salah satu dari ekstensi diatas, rename filenya menjadi “renamed.file”

d. Atasan Paul juga meminta agar program ini dapat membackup dan merestore file. Oleh karena itu, bantulah Paul untuk membuat program ini menjadi 3 mode, yaitu:
  - default: program berjalan seperti biasa untuk me-rename dan menghapus file. Mode ini dieksekusi ketika program dijalankan tanpa argumen tambahan, yaitu dengan command       ./management saja
  - backup: program memindahkan file dengan kode m0V3 ke sebuah folder bernama “backup”
  - restore: program mengembalikan file dengan kode m0V3 ke folder sebelum file tersebut dipindahkan
  - Contoh penggunaan: ./management -m backup

e. Terkadang, Paul perlu mengganti mode dari program ini tanpa menghentikannya terlebih dahulu. Oleh karena itu, bantulan Paul untuk mengintegrasikan kemampuan untuk            mengganti mode ini dengan mengirim sinyal ke daemon, dengan ketentuan:
  - SIGRTMIN untuk mode default
  - SIGUSR1 untuk mode backup
  - SIGUSR2 untuk mode restore
  - Contoh penggunaan: kill -SIGUSR2 <pid_program>

f. Program yang telah dibuat ini tidak mungkin akan dijalankan secara terus-menerus karena akan membebani sistem. Maka dari itu, bantulah Paul untuk membuat program ini        dapat dimatikan dengan aman dan efisien

g. Terakhir, program ini harus berjalan setiap detik dan mampu mencatat setiap peristiwa yang terjadi ke dalam file .log yang bernama “history.log” dengan ketentuan:
  - Format: [nama_user][HH:MM:SS] - <nama_file> - <action>
  - nama_user adalah username yang melakukan action terhadap file
  - Format action untuk setiap kode:
    1. kode r3N4mE: Successfully renamed.
    2. kode d3Let3: Successfully deleted.
    3. mode backup: Successfully moved to backup.
    4. mode restore: Successfully restored from backup.
  - Contoh pesan log:
    1. [paul][00:00:00] - r3N4mE.ts - Successfully renamed.
    2. [paul][00:00:00] - m0V3.xk1 - Successfully restored from backup.

h. Berikut adalah struktur folder untuk pengerjaan nomor 2:
    soal_2/
    ├── history.log
    ├── management.c
    └── library/
        └── backup/

Dikarenakan nomor 2 tidak didemokan maka kita melakukan revisi seadanya

# REVISI

untuk penyelesaian dari nomer 2 belum selesai jadi kita hanya menampilkan program c 
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define URL "https://drive.google.com/file/d/1rUIZmp10lXLtCIH3LAZJzRPeRks3Crup/view.zip"
#define OUTPUT_FILE "libary.zip"
#define EXTRACT_DIR "extracted_files"

void downloadFile(const char *url, const char *outputFile) {
    CURL *curl;
    FILE *fp;

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outputFile, "wb");
        if (fp) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_perform(curl);
            fclose(fp);
        }
        curl_easy_cleanup(curl);
    }
}
```
setelah saya command dengan 
```
gcc management.c -o management
```
muncul seperti ini :

<img width="749" alt="Output management c file" src="https://github.com/Nopitrasari/Sisop-2-2024-MH-IT19/assets/149749135/3c6fbf8b-8c65-4128-90ad-f0cd6bf5bb47">


<img width="742" alt="Output management c file config 2 " src="https://github.com/Nopitrasari/Sisop-2-2024-MH-IT19/assets/149749135/09a77c72-f5f0-471e-b2d0-e8075f7970b8">

memang muncul beberapa syntax yang error.

Sejujurnya saya mohon maaf tidak bisa menyelesaikan soal 2 ini dikarenakan kami semua memang kesulitan untuk nomor 2


# SOAL 3

Pak Heze adalah seorang admin yang baik. Beliau ingin membuat sebuah program admin yang dapat memantau para pengguna sistemnya. Bantulah Pak Heze untuk membuat program  tersebut!

  a. Nama program tersebut dengan nama ``admin.c``
  
  b. Program tersebut memiliki fitur menampilkan seluruh proses yang dilakukan oleh seorang user dengan menggunakan command:
    ``./admin <user>``
    
  c. Program dapat memantau proses apa saja yang dilakukan oleh user. Fitur ini membuat program berjalan secara daemon dan
  berjalan terus menerus. Untuk menjalankan fitur ini menggunakan command: 
    ``./admin -m <user>``
    Dan untuk mematikan fitur tersebut menggunakan: 
    ``./admin -s <user>``
    
  d. Program akan mencatat seluruh proses yang dijalankan oleh user di file <user>.log dengan format:
  	[dd:mm:yyyy]-[hh:mm:ss]_pid-process_nama-process_GAGAL/JALAN
   Program dapat menggagalkan proses yang dijalankan user setiap detik secara terus menerus dengan menjalankan: 
   ``./admin -c user``
   sehingga user tidak bisa menjalankan proses yang dia inginkan dengan baik. Fitur ini dapat dimatikan dengan command:
   ``./admin -a user``
    
  e. Ketika proses yang dijalankan user digagalkan, program juga akan melog dan menset log tersebut sebagai GAGAL. Dan jika
  	di log menggunakan fitur poin c, log akan ditulis dengan JALAN
   
   # PENYELESAIAN
a. buat program `` admin.c ``
b. berikut adalah isi dari `` admin.c ``
```
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

    // Membaca output dari ps command dan menuliskannya ke file log
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

            // Tulis ke file log
            fprintf(log_file, "[%s]\t%s\t%d\t%s\t%s\n", get_current_time(), user, pid, process_name, status);

            // Cetak informasi ke terminal
            printf("[%s]\t%s\t%d\t%s\t%s\n", get_current_time(), user, pid, process_name, status);
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
    if (strcmp(user, "nopii") != 0) {
        fprintf(stderr, "Error: Only 'nopii' user is allowed to stop monitoring.\n");
        exit(EXIT_FAILURE);
    }
    printf("Stop monitoring for user %s\n", user);
    // Implementasi untuk menghentikan pemantauan proses di sini
}

// Fungsi untuk mengendalikan proses
void control_processes(char *user) {
    printf("Control processes for user %s\n", user);
    // Implementasi untuk mengendalikan proses di sini

    // Misalnya, untuk tujuan demonstrasi, kita akan mengirim sinyal SIGSTOP ke semua proses pengguna
    // Ini hanya contoh dan mungkin perlu disesuaikan dengan kebutuhan Anda
    char command[100];
    sprintf(command, "pkill -STOP -U %s", user);

    // Melakukan kontrol proses dengan mengirim sinyal SIGSTOP
    int result = system(command);
    if (result == -1) {
        perror("Error controlling processes");
        exit(EXIT_FAILURE);
    } else if (result != 0) {
        fprintf(stderr, "Failed to control processes for user %s\n", user);
        exit(EXIT_FAILURE);
    }
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
```












# SOAL 4

Salomo memiliki passion yang sangat dalam di bidang sistem operasi. Saat ini, dia ingin mengotomasi kegiatan-kegiatan yang ia lakukan agar dapat bekerja secara efisien. Bantulah Salomo untuk membuat program yang dapat mengotomasi kegiatan dia!
(NB: Soal di uji coba dan berhasil di sistem yang menggunakan MacOS dan linux yang menggunakan dual boot dan VM. Untuk teman-teman yang menggunakan WSL bisa mengerjakan soal yang lain ya)

a. Salomo ingin dapat membuka berbagai macam aplikasi dengan banyak jendela aplikasi dalam satu command. Namai file program tersebut setup.c
  
b. Program dapat membuka berbagai macam aplikasi dan banyak jendela aplikasi sekaligus (bisa membuka 1 atau lebih aplikasi dengan 1 atau lebih window (kecuali aplikasi yang    tidak bisa dibuka dengan banyak window seperti discord)) dengan menjalankan: 
    ./setup -o <app1> <num1> <app2> <num2>.....<appN> <numN>
    Contoh penggunaannya adalah sebagai berikut: 
    ./setup -o firefox 2 wireshark 2
    Program akan membuka 2 jendela aplikasi firefox dan 2 jendela aplikasi wireshark.

c. Program juga dapat membuka aplikasi dengan menggunakan file konfigurasi dengan menggunakan 
    ./setup -f file.conf 
    Format file konfigurasi dibebaskan, namun pastikan dapat menjalankan fitur dari poin 2.
    Contoh isi file.conf:
    Firefox 2
    Wireshark 3
    Ketika menjalankan command contoh, program akan membuka 2 jendela aplikasi firefox dan 3 jendela aplikasi wireshark.

d. Program dapat mematikan semua aplikasi yg dijalankan oleh program tersebut dengan: 
    ./setup -k

e. Program juga dapat mematikan aplikasi yang dijalankan sesuai dengan file konfigurasi. 
  Contohnya: 
  ./setup -k file.conf 
  Command ini hanya mematikan aplikasi yang dijalankan dengan 
  ./setup -f file.conf

# PENYELESAIAN

Untuk point a saya tinggal menggunakan command 
```
touch setup.c
```
kemuadian masuk ke dalam file c tersebut agar bisa dimasukkan program sesuai soal
```
nano setup.c
```
lalu masukkan programnya dengan
```

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
            perror("fork"0
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc !=2) {
     	fprint(stderr, "Usage : %s <configFilePath>\n",argv[0]);
	return EXIT_FAILUR;
    }

    const char *configFIlePath + 
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
```
untuk menjawab point b maka saya menyimpan program saya di setup.c file dan memberikan command sesuai soalnya 
```
./setup -o firefox 2 wireshark 2
```
Dengan begitu muncul tampilan browser firefox 2 window

<img width="835" alt="Buka jendela firefox" src="https://github.com/Nopitrasari/Sisop-2-2024-MH-IT19/assets/149749135/59d806ec-ce0d-4b97-8086-8c25d82e1872">

serta 2 aplikasi wireshark yang sudah menampilkan tampilan 

<img width="860" alt="Buka Wireshark 2 " src="https://github.com/Nopitrasari/Sisop-2-2024-MH-IT19/assets/149749135/ff823f47-6290-4230-bd70-4e4217c07ca3">


jika saya menjalankan program saya maka hasil dari 
```
./setup -f file.conf
```
menghasilkan output : 

<img width="739" alt="Output dengan file config" src="https://github.com/Nopitrasari/Sisop-2-2024-MH-IT19/assets/149749135/2f20dce8-caf0-4d1c-bfec-e2c8ff614330">

Jadi, sejujurnya saya masih belum bisa menyelesaikan soal nomor 4 sepenuhnya.





