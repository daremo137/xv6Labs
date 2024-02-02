#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"


void solve(){
	int p[2];
	pipe(p);
	char buf[10];
	int pid = fork();
	if(pid < 0){
		write(2, "error\n", strlen("error\n"));
		exit(1);
	}
	else if(pid == 0){ //the current process is the child process
		read(p[0], buf, 5); 
		printf("%d: received %s\n", getpid(), buf);
		write(p[1], "pong", 5);
		//close(p[0]);
		//close(p[1]);
	
	}
	else{
		write(p[1], "ping", 5);
		wait(0);
		read(p[0], buf, 5);
		printf("%d: received %s\n", getpid(), buf);
		//close(p[1]);
		//close(p[0]);
	}

	//pipe(p);
	//printf("%d: received ping\n", p[0]);
	//close(p[0]);
	//printf("%d: received pong\n", p[1]);
	//close(p[1]);
	
	return;
}

int main(int argc, char *argv[]){
	
	solve();

	exit(0);
}
