#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

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

  if ((chdir("/home/justfachry/modul2")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // main program here
#include <dirent.h> 
#include <stdio.h> 
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
    //   printf("%s\n", dir->d_name);
        int pfile = strlen(dir->d_name)-5;
        if(strstr(&dir->d_name[pfile], ".png")){
         int pnama = strlen(dir->d_name)-4;
         char nama[100]="";
		    strncpy(nama, dir->d_name, pnama);
		    strcat(nama, "_grey.png");
		    rename(strcat(".", dir->d_name), strcat("/gambar", nama));
          
        }
    }
    closedir(d);
}
    sleep(1);
  }
  
  exit(EXIT_SUCCESS);
}