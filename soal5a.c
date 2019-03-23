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
