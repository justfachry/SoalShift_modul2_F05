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
    //   printf("%s\n", dir->d_name);
        // int pfile = strlen(dir->d_name)-5;
        // int pnama = strlen(dir->d_name)-4;
        // if(strstr(&dir->d_name[pfile], ".png")){
        //  char nama[100]="";
		    // strncpy(nama, dir->d_name, pnama);
		    // strcat(nama, "_grey.png");
		    // rename(strcat(".", dir->d_name), strcat("home/justfachry/gambar/", nama));
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