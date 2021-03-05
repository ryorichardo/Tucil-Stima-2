# Rencana Studi Organizer
## Deskripsi
Rencana Studi Organizer adalah sebuah aplikasi yang dapat membantu anda mengurutkan mata kuliah apa yang harus dipenuhi terlebih dahulu sebelum mata kuliah lain yang memiliki prerequsite tertentu. Anda hanya perlu memasukkan daftar mata kuliah yang ingin diambil beserta prerequsitenya, dan aplikasi Rencana Studi Organizer akan langsung menyajikan mata kuliah yang dapat anda ambil di setiap semesternya.

## Decrease and Conquer
Dalam membangun aplikasi ini, digunakan algoritma Topological Sort yang merupakan implementasi dari algoritma Decrease and Conquer. Decrease and Conquer memiliki arti "kurangi dan taklukan", yang berarti jumlah masukkan yang diproses akan dikurangi setiap kali iterasi dalam menyelesaikan sebuah permasalahan. Dalam aplikasi Rencana Studi Organizer, algoritma Decrease and Conquer diimplementasikan dengan cara mengurangi mata kuliah yang sudah diambil di semester sebelum dalam mengevaluasi pemilihan mata kuliah semester berikutnya. Proses evaluasi dilakukan dengan cara berulang (looping) dengan jumlah elemen yang semakin sedikit.

## Requirements
Aplikasi Rencana Studi Organizer dapat dijalankan di sistem operasi Windows, Linux, maupun MacOS. Aplikasi dalam bentuk executable dapat dijalankan tanpa memerlukan instalasi aplikasi lain. Jika ingin menjalankan kode program dalam bahasa C, silakan meng-install [GNU Compiler Collection (GCC)](https://gcc.gnu.org/) yang kompatibel dengan perangkat anda. 

## How to use
Untuk menjalankan program, silakan jalankan file `13519193.exe` yang terletak pada folder `bin`. Kemudian, silakan masukkan nama file yang berada pada folder `test` ketika program meminta masukkan. Untuk menambah file baru, silakan menambahkan file dengan extensi txt dalam folder `test`. Beberapa hal yang perlu diperhatikan:

* Ketika program meminta masukkan nama file, tuliskan seluruh nama file beserta ekstensinya. Contoh masukkan: `tc1.txt`.
* Jika ingin menambahkan file, pastikan format penulisan sudah sesuai. Silahkan ikuti format penulisan pada file-file bernama `tc1.txt` hingga `tc8.txt` dalam folder `test`. Untuk lebih jelasnya, silakan mengikuti format tulisan yang tertera pada [spesifikasi](http://informatika.stei.itb.ac.id/~rinaldi.munir/Stmik/2020-2021/Tugas-Kecil-2-(2021).pdf).
* Jika masih ada kendala lain, silakan menghubungi nama yang tertera pada kolom [contact](#contact), atau cari referensi lain di internet.

## Contact
Program ini dibuat oleh:
* Nama    : [Ryo Richardo](https://github.com/ryorichardo)
* NIM     : 13519193
* Jurusan : Teknik Informatika