#include "kernel/types.h"
#include "user/user.h"

char buf[1024+3], cmd[1024+3];


int main(int argc, char *args[]){
	int i, j;
	char *p;

	printf("this process has %d arg, the first arg is %s\n", argc, args[0]);
	printf("all args below:\n");
	for(i = 0; i < argc; ++ i){
		printf("%s ", args[i]);
	}
	printf("\n");
	if(argc < 2){
		printf("too few arguments for xargs\n");
		exit(1);
	}
	char **cmds = (char**)malloc((argc + 2) * sizeof(char*));
	for(int i = 0; i < argc; ++ i){
		
	}
	//fgets(buf, sizeof(buf), 0);
	read(0, buf, sizeof(buf));
	p = cmd;
	//printf("received string is %s\n", buf);
	for(i = 2; i < argc; ++ i){
		//strcat(cmd, args[i]);
		for(j = 0; args[i][j] != '\0'; ++ j){
			*p++ = args[i][j];
		}
		*p++ = ' ';
	}
	//strcat(cmd, buf);
	for(i = 0; buf[i] != '\0'; ++ i){
		*p++ = buf[i];
	}
	*p = '\0';
	printf("whole cmd is %s\n", cmd);
	exec(args[1], cmds + 1);

	exit(0);
}
