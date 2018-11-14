#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {

	int fd1[2];
	int fd2[2];
	int parent;
	int i=1230;
	// parent = getpid();
	while(i < 1240) {
		pipe(fd1);
		pipe(fd2);
		int pid = fork();
		if(pid == -1)
			perror("-1");
		else if(pid > 0){
			char username[100] = "abcd";
			char pass[100];
			sprintf(pass, "%d", i);
			printf("username %s  password %s\n",username, pass );
			dup2(fd1[1], STDIN_FILENO);
			close(fd1[0]);
			write(fd1[1], username,strlen(username)+1);
			write(fd1[1], pass, strlen(pass)+1);
			close(fd1[1]);


			wait(NULL);
		}
		else { //child
			close(fd1[1]);
			dup2(fd1[0], STDOUT_FILENO);
			close(fd2[0]);
			dup2(fd2[1], STDIN_FILENO);
			execlp("./passwd", "./passwd", "-pa", NULL);
			close(fd1[0]);
			}
		i++;
	}

	return 0;
}
