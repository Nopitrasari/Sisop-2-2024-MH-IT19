# Sisop-2-2024-MH-IT19
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

Setelah dekripsi selesai, akan terlihat bahwa setiap file memuat salah satu dari kode berikut: r3N4mE, d3Let3, dan m0V3. Untuk setiap file dengan nama yang memuat kode d3Let3, hapus file tersebut. Sementara itu, untuk setiap file dengan nama yang memuat kode r3N4mE, lakukan hal berikut:
Jika ekstensi file adalah “.ts”, rename filenya menjadi “helper.ts”
Jika ekstensi file adalah “.py”, rename filenya menjadi “calculator.py”
Jika ekstensi file adalah “.go”, rename filenya menjadi “server.go”
Jika file tidak memuat salah satu dari ekstensi diatas, rename filenya menjadi “renamed.file”

Atasan Paul juga meminta agar program ini dapat membackup dan merestore file. Oleh karena itu, bantulah Paul untuk membuat program ini menjadi 3 mode, yaitu:
default: program berjalan seperti biasa untuk me-rename dan menghapus file. Mode ini dieksekusi ketika program dijalankan tanpa argumen tambahan, yaitu dengan command ./management saja
backup: program memindahkan file dengan kode m0V3 ke sebuah folder bernama “backup”
restore: program mengembalikan file dengan kode m0V3 ke folder sebelum file tersebut dipindahkan
Contoh penggunaan: ./management -m backup





Terkadang, Paul perlu mengganti mode dari program ini tanpa menghentikannya terlebih dahulu. Oleh karena itu, bantulan Paul untuk mengintegrasikan kemampuan untuk mengganti mode ini dengan mengirim sinyal ke daemon, dengan ketentuan:
SIGRTMIN untuk mode default
SIGUSR1 untuk mode backup
SIGUSR2 untuk mode restore
Contoh penggunaan: kill -SIGUSR2 <pid_program>

Program yang telah dibuat ini tidak mungkin akan dijalankan secara terus-menerus karena akan membebani sistem. Maka dari itu, bantulah Paul untuk membuat program ini dapat dimatikan dengan aman dan efisien

Terakhir, program ini harus berjalan setiap detik dan mampu mencatat setiap peristiwa yang terjadi ke dalam file .log yang bernama “history.log” dengan ketentuan:
Format: [nama_user][HH:MM:SS] - <nama_file> - <action>
nama_user adalah username yang melakukan action terhadap file
Format action untuk setiap kode:
kode r3N4mE: Successfully renamed.
kode d3Let3: Successfully deleted.
mode backup: Successfully moved to backup.
mode restore: Successfully restored from backup.
Contoh pesan log:
[paul][00:00:00] - r3N4mE.ts - Successfully renamed.
[paul][00:00:00] - m0V3.xk1 - Successfully restored from backup.

Berikut adalah struktur folder untuk pengerjaan nomor 2:
    soal_2/
    ├── history.log
    ├── management.c
    └── library/
        └── backup/

