# SoalShift_modul2_E08

#### Bagas Yanuar Sudrajad - 05111740000074 

#### Octavianus Giovanni Yaunatan - 05111740000113

## SOAL 1

### Langkah-langkah

1. Akses direktori tempat file yang akan dipindahkan.
2. Baca entry dari direktori tersebut.
3. Untuk masing-masing file cek apakah berekstensi .png. Jika iya pindah dan beri tambahan nama "_grey.png"
4. Untuk otomasi proses ini, dapat dibuat daemon.

### Implementasi

- Deklarasikan variabel-variabel yang akan digunakan

  ``` c
  struct dirent *de;
  DIR *dr;
  char* ext;
  char *add = "_grey.png";
  char oldName[1000];
  char newName[1000];
  char * path= "/home/siung2/modul2/";
  char* s;
  ```

  

- Baca direktori tempat file dan simpan dalam `dr`. Untuk kasus ini foldernya adalah folder di mana program diletakkan dan dijalankan.

  ```c
  dr = opendir(".");
  ```

- Baca setiap entry dari direktori tersebut. Simpan nama setiap entry pada variable `s` , ambil ekstensi file dan simpan pada variabel `ext`.

- Jika file berekstensi .png maka rename file tersebut ke nama baru di alamat direktori yang baru.

  ```c
  while ((de = readdir(dr)) != NULL){
      s = de->d_name;
      ext=strrchr(s,'.');
      if(ext && !strcmp(ext, ".png")){ // jika mengandung ext
      	int x= ext-s; //panjang nama file tanpa ekstensi
          memset(oldName, 0, strlen(oldName)); //memastikan variabel kosong
          memset(newName, 0, strlen(newName));
          strncpy(oldName,s,x); //oldName berisi nama file tanpa ekstensi
          strcat(newName,"/home/siung2/modul2/gambar/"); //newName berisi alamat baru
          strcat(newName,oldName);//tambahkan nama file
          strcat(newName,add);//tambahkan "_grey.png"
          rename(s,newName); //eksekusi penggantian nama.
       }
  }
  closedir(dr);
  ```

[Code untuk soal 1](https://github.com/Axerion1210/SoalShift_modul2_E08/blob/master/Jawaban/soal1/soal1.c)

## SOAL 2

### Langkah-langkah

Buat daemon yang berjalan setiap 3 detik yang melakukan:

1. Mengakses folder `hatiku` 
2. Memeriksa apakah ada file bernama `elen.ku`
3. Jika ada, memeriksa apakah file tersebut memiliki owner dan group "www-data"
4. Jika iya, ubah hak ases dari file tersebut lalu hapus file tersebut.

### Implementasi

- Deklarasikan variabel-variabel yang dibutuhkan di luar while dari daemon

  ```c
  struct stat info;
      char *owner; //Untuk menampung nama owner
      char *group;//Untuk menampung nama group
      char *file = "hatiku/elen.ku"; //letak elen.ku
      struct group *gr;//untuk mengakses info group
      struct passwd *pw;//untuk mengakses info owner
  ```

- Dalam while daemon yang berulang setiap 3 detik, lakukan hal berikut:

  ```c
  if(!(stat(file, &info))){ // Jika terapat elen.ku
          gr = getgrgid(info.st_gid);
          pw = getpwuid(info.st_uid);
          owner = pw->pw_name; // simpan nama owner
          group = gr->gr_name;// simpan nama group
          if(!(strcmp(owner,"www-data")) && !(strcmp(group,"www-data"))){ // Jika owner dan group bernama "www-data"
              chmod(file, S_IRWXU|S_IRWXG|S_IRWXO); //ubah hak askses menjadi 777
              remove(file);//hapus file
          }
      }
  ```

[Code untuk soal 2](https://github.com/Axerion1210/SoalShift_modul2_E08/blob/master/Jawaban/soal2/soal2.c)

## SOAL 3

### Langkah-langkah

1. Unzip file campur2.zip
2. buat file daftar.txt
3. Simpan semua file dalam folder campur2 yang berekstensi .txt ke file daftar.txt

### Implementasi

Ke-tiga langkah-langkah di atas dilakukan menggunakan 3 proses,  dengan 2 kali fork(). Langkah 1 dilakukan oleh Grand Child, langkah 2 oleh Child, lalu langkah 3 dilakukan oleh Parent. Dalam implementasinya, Parent menunggu Child dan Child menunggu Grand Child.

Struktur program:

```c
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(){
    pid_t child_id;
    int status;
    chdir("/home/siung2/modul2");
    child_id = fork();
    if(child_id < 0){
        exit(EXIT_FAILURE);
    }
    if(child_id==0){
        pid_t gChild_id;
        int status2;
        gChild_id = fork();
        if(gChild_id < 0){
            exit(EXIT_FAILURE);
        }
        if(gChild_id == 0){
            //1. Gchild;
            // Lakukan langkah 1
        }else{
            while((wait(&status2))>0);
            //2. Child;
            //Lakukan langkah 2
        }

    }else{
        while((wait(&status))>0);
        //3. Parent;
        // Lakukan langkah 3
    }
}


```

#### Langkah 1

Menggunakan execv untuk me-unzip campur2.zip.

```c
char *argv[] = {"unzip", "campur2.zip", NULL};
execv("/usr/bin/unzip", argv);
```

#### Langkah 2

Jika langkah 1 telah selesai, buat file touch.txt dengan execv.

```c
while((wait(&status2))>0);
char *argv[] = {"touch", "daftar.txt", NULL};
execv("/usr/bin/touch", argv);
```

#### Langkah 3

Deklarasikan variabel-variabel yang akan dipakai

```c
FILE *fp; //untuk membaca
FILE *write;//untuk menulis
char s[100];//untuk menyimpan nama file
```

Masuk ke direktori campur2

```c
chdir("/home/siung2/modul2/campur2");
```

Lakukan command `ls` untuk semua file ber-ekstensi .txt di campur2, masukkan hasil ke variabel `fp` . Buka daftar.txt dengan variabel `write` lalu print fp ke sana.

```c

		
        fp = popen("ls *.txt", "r");
        if(fp==NULL)exit(EXIT_FAILURE);
        write = fopen ("../daftar.txt", "w+");
        while (fgets(s, 100, fp) != NULL){
            fprintf(write, "%s", s);
        }
         pclose(fp);
         fclose(write);
```

Ubah hak akses daftar.txt untuk memastikan file dapat dibuka. Beri akses penuh untuk owner, read eksekusi untuk group, dan read saja untuk other.

```c
chmod("../daftar.txt",  S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);
return 0;
```

[Code untuk soal 3 dengan `popen() `](https://github.com/Axerion1210/SoalShift_modul2_E08/blob/master/Jawaban/soal3/soal3.c)

Di atas adalah pengerjaan menggunakan popen. Untuk solusi yang menggunakan pipe() adalah sebagai berikut:

```c
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(){
    pid_t child_id;
    int status;
    chdir("/home/siung2/modul2");
    child_id = fork();
    if(child_id < 0){
        exit(EXIT_FAILURE);
    }
    if(child_id==0){
        pid_t gChild_id;
        int status2;
        gChild_id = fork();
        if(gChild_id < 0){
            exit(EXIT_FAILURE);
        }
        if(gChild_id == 0){
            //1. Gchild;
            char *argv[] = {"unzip", "campur2.zip", NULL};
            execv("/usr/bin/unzip", argv);
        }else{
            while((wait(&status2))>0);
            //2. Child;
            char *argv[] = {"touch", "daftar.txt", NULL};
            execv("/usr/bin/touch", argv);
        }

    }else{
        while((wait(&status))>0);
        //3. Parent;
        int fd[2];
        pipe(fd);

        if(fork()==0){
            close(fd[0]);
            dup2(fd[1],1);
            dup2(fd[1],2);
            close(fd[1]);
            execl("/bin/ls", "ls", "/home/siung2/modul2/campur2", (char *)NULL);
        }else{
            char buffer[10000]={0};
            read(fd[0],buffer,sizeof(buffer));
            close(fd[0]);
            close(fd[1]);
            chdir("/home/siung2/modul2/campur2");
            FILE *write;
            write = fopen ("../tes.txt", "w+");
            fprintf(write, "%s", buffer);
            fclose(write);
            FILE *text;
            text = fopen("../tes.txt", "r+");
            write = fopen ("../daftar.txt", "w+");
            char* ext;
            char* s;
            while(fgets(buffer, 200, (FILE*) text)) {
                s= buffer;
                ext=strrchr(s,'.');
                if (!strcmp(ext, ".txt\n")){
                    fprintf(write, "%s", s);
                }
            }
            remove("../tes.txt");
            chmod("../daftar.txt",  S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);
        fclose(text);
        fclose(write);
	return 0;
        }
    }
}
```

[Code untuk soal 3 dengan `pipe() `](https://github.com/Axerion1210/SoalShift_modul2_E08/blob/master/Jawaban/soal3/soal3R.c)

## SOAL 4

### Langkah-langkah

Buat daemon yang berjalan setiap 5 detik yang melakukan:

1. Mengecek apakah file `makan_enak.txt` di directory `/home/user/Documents/makanan` pernah diakses setidaknya 30 detik yang lalu.
2. Jika iya, maka akan membuat file `makan_sehat#.txt` di directory tersebut. '#' increment per 5 detik mulai dari 1.

### Implementasi

- Deklarasikan variabel dengan tipe data `time_t` untuk mengambil waktu sekarang, dan sebuah variabel counter (variabel counter terletak di luar loop). 

```c
int x = 1;

while(1) {
    time_t wkt = (unsigned)time(NULL);
```

- Kemudian deklarasikan variabel dengan tipe data `struct stat` untuk mengambil stat (Properties jika dalam Windows) file `makan_enak.txt` di directory `/home/user/Documents/makanan`.

```c
    struct stat filestat;
    stat("/home/ivan/Documents/makanan/makan_enak.txt",&filestat);
```

- Gunakan fungsi `(int)difftime(waktu1,waktu2)` untuk menghitung selisih waktu sekarang dengan waktu file `makan_enak.txt` terakhir dibuka (dengan menggunakan `st_atime`, yaitu waktu dimana file terakhir kali diakses) lalu diconvert ke dalam integer. Jika hasilnya kurang dari atau sama dengan 30, maka akan membuat file `makan_sehat#.txt`, '#' adalah variabel counter yang sudah disiapkan sebelumnya di luar loop, setelah selesai dibuat, variabel counter diincrement. Terakhir sleep program selama 5 detik sebelum loop.

```c
    if((int)difftime(wkt,filestat.st_atime)<=30)
    {
      char filename[200];
      sprintf(filename,"/home/ivan/Documents/makanan/makan_sehat%d.txt",x);
      FILE *fPoint;
      fPoint = fopen(filename, "a");
      fclose(fPoint);
      x++;
    }

    sleep(5);
  }
```
[Code untuk soal 4 ](https://github.com/Axerion1210/SoalShift_modul2_E08/blob/master/Jawaban/soal4/soal1.4)

## SOAL 5

### Langkah-langkah

1. Soal 5a
  1. Buat daemon yang berjalan setiap 1 menit
  2. Buat directory log di /home/user jika tidak ada.
  3. Setiap 30 menit buat directory format dd:MM:yyyy-hh:mm di dalam directory log tersebut.
  4. Copy file syslog pada /var/log ke dalam directory tersebut dengan nama log#.log. # diincrement mulai dari 1.
2. Soal 5b
  1. Mencari file daemon
  2. Cari pid daemon tersebut
  3. Kill proses daemon tersebut dengan menggunakan pid.
  4. Ulangi jika terdapat proses daemon dengan nama yang sama yang masih berjalan.

### Implementasi

Pada soal 5a:

- Buat directory `log` di dalam `/home/user` jika tidak ada
```c
    struct stat st = {0};

    if (stat("/home/ivan/log", &st) == -1) {
        mkdir("/home/ivan/log", 0777);
    }
```

- Di dalam directory tersebut buat folder dengan format dd:MM:yyyy-hh:mm. Format ini dapat dicari dengan menggunakan variabel time_t, mengkonversi ke dalam kumpulan integer, lalu mengambil tanggal, bulan, tahun, jam, dan menit dari waktu sekarang, lalu membuat directory tersebut. Variabel counter diset ke 0 terlebih dahulu untuk membuat directory ini setiap 30 menit, kemudian counter ini diincrement. Nama directory dan counter diletakkan di luar loop agar terus update.

```c
int x=0;
char filedir[200]; 

  while(1) {
    .
    .
    .
    if(x%30==0){
      time_t now = (unsigned)time(NULL);
      struct tm cur = *localtime(&now);
      sprintf(filedir,"/home/ivan/log/%02d:%02d:%04d-%02d:%02d",cur.tm_mday,cur.tm_mon+1,cur.tm_year+1900,cur.tm_hour,cur.tm_min);
      mkdir(filedir,0777);
    }
    x++;
```

- Lalu kita perlu nama dan lokasi file syslog untuk dicopy ke dalam directory dd:MM:yyyy-hh:mm (yang telah dibuat sebelumnya) berupa log#.log. # berupa angka increment yang telah dideklarasikan sebelumnya. Kemudian daemon di sleep selama 1 menit sebelum loop berjalan lagi.

```c
    char ch, dfile[100];
    FILE *source, *target;    

    char sfile[100] = "/var/log/syslog";
    sprintf(dfile,"%s/log%d.log",filedir,x);

    source = fopen(sfile,"r");
    target = fopen(dfile,"w");

    while ((ch = fgetc(source)) != EOF)
      fputc(ch,target);

    fclose(source);
    fclose(target);

    sleep(60);
  }
```

Pada soal 5b:

- Mencari pid daemon. Kita memerlukan variabel untuk mendapatkan karakter tertentu, yaitu pid untuk diconvert ke dalam variabel pid_t dengan 

```c
    char line[100];

    FILE *cmd = popen("pidof /home/ivan/Sisop/Praktikum2/soal5a", "r");
    fgets(line, 100, cmd);
    pid_t pid = strtoul(line, NULL, 10);
    pclose(cmd);
```

- Kill daemon tersebut dengan menggunakan SIGKILL.

```c
    while(pid!=0){
        kill(pid, SIGKILL);
```

- Reset memory untuk mencari pid baru dari daemon yang sama (jika dijalankan lebih dari 1 kali). Ulangi sampai tidak ada proses daemon lagi yang berjalan.

```c
	cmd = popen("pidof /home/ivan/Sisop/Praktikum2/soal5a", "r");
        memset(line,0,100);            
        fgets(line, 100, cmd);
        pclose(cmd);
        pid = strtoul(line, NULL, 10);
    }
```

[Code untuk soal 5 a](https://github.com/Axerion1210/SoalShift_modul2_E08/blob/master/Jawaban/soal5/soal5a.c)

[Code untuk soal 5 b](https://github.com/Axerion1210/SoalShift_modul2_E08/blob/master/Jawaban/soal5/soal5b.c)