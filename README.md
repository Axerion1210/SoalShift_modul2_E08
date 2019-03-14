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
    
  Pada soal ini, kita memerlukan 2 variabel, yang pertama untuk mengambil waktu sekarang, yang kedua untuk mengambil waktu dari file makan_enak.txt, yang diambil adalah waktu aksesnya (waktu terakhir kali dibuka). Lalu diperlukan struct untuk masing-masing variabel, untuk mengkonversi variabel waktu menjadi kumpulan integer, kemudian dibandingkan kedua struct tersebut. Apabila detikn
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
