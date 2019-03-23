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

  if ((chdir("/home/justfachry/Dokumen/makanan")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  int i=1;
  while(1) {
    // main program here
    struct stat lala;
    char dir[] = "/home/justfachry/Dokumen/makanan/makan_enak.txt";
    stat(dir, &lala);

    time_t now = time(NULL);
    time_t op = lala.st_atime;

    if(difftime(now, op)<30){
        char  iter [10];
        sprintf(iter, "%d", i);

        char file[200] = "/home/justfachry/Dokumen/makanan/makan_sehat";
        strcat(file, iter);
        strcat(file, ".txt");
        FILE *fp = fopen(file, "w"); 
fclose(fp);
        i++;
    }
    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}