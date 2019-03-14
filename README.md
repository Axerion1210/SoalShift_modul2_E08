# SoalShift_modul2_E08

#### Bagas Yanuar Sudrajad - 05111740000074 <br> Octavianus Giovanni Yaunatan - 05111740000113

<ol>
  <li>Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
  <br>Catatan : Tidak boleh menggunakan crontab.</li>
  <li>Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
  <br>Catatan: Tidak boleh menggunakan crontab</li>
  <li>Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
  Buatlah program C yang dapat :
    <ol>
      <li>mengekstrak file zip tersebut.</li>
      <li>menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt.</li>
    </ol>
  Catatan:
    <ul>
      <li>Gunakan fork dan exec.</li>
      <li>Gunakan minimal 3 proses yang diakhiri dengan exec.</li>
      <li>Gunakan pipe</li>
      <li>Pastikan file daftar.txt dapat diakses dari text editor</li>
    </ul>
    
    ```
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <unistd.h>
    #include <syslog.h>
    #include <string.h>
    #include <time.h>

    int main() {
      pid_t pid, sid;

      pid = fork();

      if (pid < 0) {
        exit(EXIT_FAILURE);
      }

      if (pid > 0) {
        exit(EXIT_SUCCESS);
      }

      umask(0);

      sid = setsid();

      if (sid < 0) {
        exit(EXIT_FAILURE);
      }

      if ((chdir("/home/ivan/Sisop/Praktikum2")) < 0) {
        exit(EXIT_FAILURE);
      }

      close(STDIN_FILENO);
      close(STDOUT_FILENO);
      close(STDERR_FILENO);

      int x = 1;

      while(1) {
        time_t wkt = (unsigned)time(NULL);
        struct tm dt1 = *localtime(&wkt);

        struct stat filestat;
        stat("/home/ivan/Documents/makanan/makan_enak.txt",&filestat);
        struct tm dt2 = *localtime(&filestat.st_atime);

        if(dt1.tm_sec-dt2.tm_sec<=30 && dt1.tm_min==dt2.tm_min && dt1.tm_hour==dt2.tm_hour && dt1.tm_mday==dt2.tm_mday && dt1.tm_mon==dt2.tm_mon && dt1.tm_year==dt2.tm_year)
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
      exit(EXIT_SUCCESS);
    }
    ```
    
  </li>
  <li>Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).<br>
  Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.
  <br>Contoh:
  <br>File makan_enak.txt terakhir dibuka pada detik ke-1
  <br>Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt 
  <br>Catatan: 
    <ul>
      <li>Dilarang menggunakan crontab</li>
      <li>Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst</li>
    </ul>
  </li>
  <li>Kerjakan poin i dan ii di bawah:
    <ol>
      <li>Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
      <br>Ket:
        <ul>
          <li>Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]</li>
          <li>Per menit memasukkan log#.log ke dalam folder tersebut
              <br>‘#’ : increment per menit. Mulai dari 1</li>
        </ul></li>
      <li>Buatlah program c untuk menghentikan program di atas.</li>
    </ol>
  NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.
  </li>
</ol>
