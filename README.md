# SoalShift_modul2_F05
Praktikum Soal Shift Sisop modul 2

Soal Latihan Modul 2

Latihan 1

Modifikasi code soal1 agar output nya menjadi huruf abjad urut dari A sampai Z, tanpa menghapus fungsi yang sudah ada.

Penyelesaian :
- Dari code soal1 kami mendapatkan input N - Z dan A - M, sehingga tidak terurut. Dalam hal ini, jika kami membalikkan ```printf ``` dari abjad_shift_1 dan abjad_shift_2, maka akan langsung urut
- Namun kami diminta untuk membuat perintah ```wait```
- Maka kami deklarasikan sebuah variabel status dan dalam pemrograman kami membuat perintah ```while((wait(&status)) > 0);``` sebelum memanggil perintah abjad_shift_2
- Maka hasil dari program tersebut akan melakukan output urut dari A sampai Z

```bash
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void abjad_shift_1() {
  int i;
  for (i = 65; i < 78; i++) {
    printf("%c\n", i);
  }
}

void abjad_shift_2() {
  int i;
  for (i = 78; i < 91; i++) {
    printf("%c\n", i);
  }
}

int main() {
  pid_t child_id;
  int status;

  child_id = fork();
  
  if (child_id < 0) {
    exit(EXIT_FAILURE);
  }

  if (child_id == 0) {
    abjad_shift_1();
  } else {
    while((wait(&status)) > 0);
    abjad_shift_2();
  }
}

```
Latihan 2

Buatlah program yang bisa membuat folder "anak" yang berisi salinan file warisan.txt.
Hint: gunakan fork, exec, dan wait.

Penyelesaian :
- Pertama deklarasikan parent
- Setelah itu fork menggunakan fungsi ```fork()```
- Dalam child, buat perintah ```mkdir``` untuk membuat folder anak
- Lalu, dalam parent, buat status wait, agar perintah child yang dijalankan duluan
- Dalam parent, copy file warisan.txt menggunakan perintah ```cp``` ke dalam folder anak

```bash
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_id;
    int status;

    child_id = fork();

    if ( child_id == 0) {
        char *argv[3] = {"mkdir", "/home/justfachry/modul2/anak/", NULL};
        execv("/bin/mkdir", argv);
    }
    else {
        while ((wait(&status)) > 0);

        char *argv[4] = {"cp", "/home/justfachry/modul2/warisan.txt", "/home/justfachry/modul2/anak/", NULL};
        execv("/bin/cp", argv);
    }
}
```

Latihan 3

Buatlah sebuah daemon yang dapat melakukan backup isi dari file sampah.txt yang disimpan dalam file log.log lalu menghapus file sampah.txt tersebut. Tidak diperbolehkan menggunakan exec dan system.

Penyelesaian :
- Pertama buka file sampah.txt dan log.log menggunakan ```fopen```
- Lalu copy data dari sampah.txt ke dalam log.log
- Hapus file sampah.txt
- Tutup file log.log

```bash
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

int running = 1;

int main(void)
{
	int pid, sid;
	FILE* log;
	FILE* fp;
	char str[100];
	int done = 0;

	pid = fork();
	if(pid < 0) {
		perror("fork");
		exit(1);
	}
	if(pid > 0) exit(0);

	umask(0);

	fp = fopen("/home/cheese/sampah.txt","r");
	log = fopen("/home/cheese/log.log","w+");

	sid = setsid();
	if(sid < 0) {
		perror("setsid");
		exit(3);
	}

	if((chdir("/")) < 0) {
		perror("chdir");
		exit(4);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while(running)
	{

		while(fgets (str, 100, fp) != NULL) 
		{
			fprintf(log, "%s", str);
		}
		fclose(log);
		sleep(10);
		remove("/home/cheese/sampah.txt");		
		running = 0;
	}
	
	return EXIT_SUCCESS;

}

```

Soal Shift

Nomor 1

Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

Penyelesaian : 
- Pertama masuk ke dalam folder /home/justfachry/modul2/nomor1
- Setelah itu baca nama file yang ada di dalam folder tersebut
- Jika ekstensi file tersebut adalah .png, maka ambil nama file tersebut
- Gabungkan nama file tersebut dengan "_grey.png" menggunakan ```strcat```
- Lalu rename nama file dengan nama file baru yang ditambahkan "_grey.png"

```bash
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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

  if ((chdir("/home/justfachry/modul2/nomor1")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // main program here
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
  
         int ext = strlen(dir->d_name)-4;
         if(strstr(&dir->d_name[ext], ".png")){
           char nama[200];
           memset(nama, 0, sizeof(nama));
           strncpy(nama, dir->d_name, ext);
           strcat(nama, "_grey.png");
           char loc[200];
           memset(loc, 0, sizeof(loc));
           strcpy(loc, "/home/justfachry/modul2/gambar/");
           strcat(loc, nama);
           char file[200];
           memset(file, 0, sizeof(file));
           strcpy(file, dir->d_name);
           rename(file, loc);
        }
    }
    closedir(d);
}
    sleep(10);
  }
  
  exit(EXIT_SUCCESS);
}
```
Nomor 2

Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

Penyelesaian : 
- Pertama buat struct untuk menyimpan data dari file elen.ku
- Lalu atur agar siapapun dapat mengakses file tersebut dengan mengubah mode file tersebut menggunakan ```chmod```
- Setelah itu ambil data grup dan owner dari elen.ku
- Lalu jika owner dan grupnya adalah www-data, maka "elen.ku" akan dihapus

 ```bash
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // main program here
    struct stat file;
    struct group *group;
    struct passwd *owner;
    char dir[] = "/home/justfachry/modul2/hatiku/elen.ku";
    stat(dir, &file);


    group = getgrgid(file.st_gid);
    owner = getpwuid(file.st_uid);

    chmod(dir, 0777);
    if (strcmp(owner->pw_name, "www-data") == 0 && strcmp(group->gr_name, "www-data") == 0) 
       remove(dir);

    sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}
 ```

Nomor 3

Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
Gunakan fork dan exec.
Gunakan minimal 3 proses yang diakhiri dengan exec.
Gunakan pipe
Pastikan file daftar.txt dapat diakses dari text editor

Penyelesaian :
- Pertama unzip file campur2.zip menggunakan exec
- Buat exec untuk membuat daftar.txt menggunakan perintah ```touch```
- Lalu buka file daftar.txt
- Masukkan data campur2.txt ke dalam file daftar.txt

```bash
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

const int PATH_MAX = 2048;

int main() {


	FILE *source;
	FILE *destination;
	char path[PATH_MAX];
	int status;
	
	pid_t child_pid = fork();


	if(child_pid == 0)
	{
		execl("/usr/bin/unzip", "unzip", "campur2.zip", NULL);
	}

	child_pid = fork();

	if(child_pid == 0)
	{
		execl("/usr/bin/touch", "touch", "daftar.txt", NULL);
	}

	while ((wait(&status)) > 0);

	FILE *daftar = fopen("daftar.txt", "w");
	int ret = chdir("campur2");
	
	if(ret != 0) {
		perror("Error");
	}
	
	source = popen("ls *txt", "r");
	while (fgets(path, PATH_MAX, source) != NULL)
	{
		fprintf(daftar,"%s", path);
	}
	fclose(daftar); 

return 0;
}

```

nomor 4

Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan: 
dilarang menggunakan crontab
Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

Penyelesaian :
- Pertama buat struct stat untuk mengambil data dari file makan_enak.txt
- Ambil waktu sekarang dan waktu akses terakhir dari file makan_enak.txt
- Lalu, jika file makan_enak.txt pernah diakses dalam selang 30 detik, maka akan dibuat file makan_sehat#.txt yang dimana # berisikan angka 1 sampai tak hingga

```bash
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
    int i;
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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // main program here
    struct stat lala;
    char* dir = "/home/justfachry/Dokumen/makanan/makan_enak.txt";
    stat(dir, &lala);

    time_t now = time(NULL);
    time_t op = lala.st_atime;

    if(difftime(now, op)<=30){
        char  iter [10];
        sprintf(iter, "%d", i);

        char *file = "/home/justfachry/Dokumen/makanan/makan_sehat";
        strcat(file, iter);
        strcat(file, "txt");
        i++;
    }
    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
```

nomor 5

Kerjakan poin a dan b di bawah:
Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
Per menit memasukkan log#.log ke dalam folder tersebut
‘#’ : increment per menit. Mulai dari 1
Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

Penyelesaian : 
- Pertama ambil waktu sekarang menggubakan perintah localtime
- Lalu atur format time menjadi dd:MM:yyyy-hh:mm menggunakan fungsi ```strftime```
- Lalu per 30 menit, buat folder yang namanya sesuai dengan nama waktu saat itu
- Lalu gabungkan nama folder yang telah dibuat dengan directory foldernya
- lalu setiap 1 menit, buat sebuah file yang berisikan isi dari /var/log/syslog

```bash
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

int main() {
  pid_t pid, sid, child;

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

  if ((chdir("/home/justfachry/modul2/log/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  FILE * gpid;
  gpid = fopen ("/home/justfachry/modul2/log/pid.txt", "w+");
  fprintf(gpid, "%d",getpid());
  fclose(gpid);

  while(1)
  {
	static int i=0;
	time_t t;
	struct tm *tmp;
	time(&t);
	tmp = localtime(&t);
	char my_time[100], namaFile[100];
	char namaFolder[100];
	char path[100];
	strftime(my_time, sizeof(my_time), "%d:%m:%Y-%H:%M", tmp);

	if(i%30 == 0)
	{
		strcpy(namaFolder,my_time);
		strcpy(path,"/home/justfachry/modul2/log/");
		strcat(path,namaFolder);
		strcat(path, "/");
		mkdir(path, 0777);
	}

	int logno = i+1;
	char newLog[100];
	sprintf(newLog, "log%d", logno);
	strcat(newLog,".log");
	strcpy(namaFile, path);
	strcat(namaFile, newLog);
	
	FILE *slog, *nlog;
	int c;
	slog=fopen("/var/log/syslog", "r");
	nlog=fopen(namaFile, "w");
	while(1){
            c=fgetc(slog);
            if(feof(slog)){
                break;
            }
            fputc(c, nlog);
        }
        fclose(slog);
	fclose(nlog);
 	sleep(60);

	i++;
  }
  exit(EXIT_SUCCESS);
}

```

- Lalu buat file untuk menghentikan file soal5a

```bash
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>

int main(){
	char *argv[] = {"pkill", "-9", "soal5a", NULL};
	execv("/usr/bin/pkill", argv);
}

```
