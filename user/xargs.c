#include "kernel/types.h"
#include "user/user.h"

char buf[1024+3], cmd[1024+3];

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("too few arguments for xargs\n");
		exit(1);
	}
	char **cmds = (char**)malloc((argc + 2) * sizeof(char*));
	for(int i = 0; i < argc; ++ i){
		cmds[i] = argv[i];
	}
	read(0, buf, sizeof(buf));
	cmds[argc] = buf;
	cmds[argc + 1] = argv[argc];
	exec(argv[1], cmds + 1);

	free(cmds);
	exit(0);
}
