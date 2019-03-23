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
