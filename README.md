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



dan ini untuk hasil setelah di run

![image](https://github.com/Nopitrasari/Sisop-2-2024-MH-IT19/assets/151911480/977c664c-b672-43c7-8aae-8b63802a5c17)


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

![image](https://github.com/Nopitrasari/Sisop-2-2024-MH-IT19/assets/151911480/c0faf4e9-b702-4526-bded-15da6f798dc0)

diatas adalah bukti bahwa file sudah berjalan secara daemon.


d. agar program berjalan secara terus menerus dengan jeda 15 detik, disini menggunakan kode berikut :

```
```

e. untuk menjawab soal e, hasil dari penghapusan file akan muncul di file virus.log sesuai dengan format di soal menggunakan fungsi berikut :

```

```

![image](https://github.com/Nopitrasari/Sisop-2-2024-MH-IT19/assets/151911480/fa42c0e3-ad3f-450a-a953-747668cad68b)

diatas adalah isi dari file virus.log

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
