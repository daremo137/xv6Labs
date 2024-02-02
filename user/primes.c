#include "kernel/types.h"
#include "user/user.h"
const int MAXN = 35;

void prime(int fd){
	
	int pr, x;
	if(read(fd, &pr, sizeof(int)) == 0)
		exit(0);
	printf("prime %d\n", pr);
	
	int p[2];
	pipe(p);
	int pid = fork();
	if(pid != 0){
		close(p[0]);
		while(read(fd, &x, sizeof(int)) != 0){
			if(x % pr != 0)
				write(p[1], &x, sizeof(int));
			
		}
		close(p[1]);
	}else{
		close(p[1]);
		prime(p[0]);	
	}
	wait(0);
}

void solve(){
	int i, p[2];
	pipe(p);
	for(i = 2; i <= MAXN; ++ i){
		write(p[1], &i, sizeof(i));
	}
	close(p[1]);
	prime(p[0]);
	close(p[0]);
}

int main(int argc, char *argv[]){

	solve();
	wait(0);
	exit(0);
}
