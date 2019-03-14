# Laporan

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

## Soal 3

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

