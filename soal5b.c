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
