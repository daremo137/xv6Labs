#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"


char buf[1024+3], cmd[1024+3];

char *readline(){
	char *p = buf;
	while(read(0, p, 1) && *p != '\n')
		p++;
	*p = '\0';
	if(p == buf)
		return (char*)0;
	return buf;
}

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("too few arguments for xargs\n");
		exit(1);
	}
	char *line;
	char **cmds = (char**)malloc((argc + 2) * sizeof(char*));
	for(int i = 0; i < argc; ++ i){
		cmds[i] = argv[i];
	}
	cmds[argc + 1] = argv[argc];
	while((line = readline())){
		cmds[argc] = line;
		int pid = fork();
		if(pid == 0){
			exec(argv[1], cmds + 1);
		}
		else{
			wait(0);
		}
	}
	free(cmds);
	exit(0);
}
