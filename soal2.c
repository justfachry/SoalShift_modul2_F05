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