#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void find(char *path, char *filename){
	int fd;
	char buf[512], buf2[512], *p, *p2;
	struct dirent de;
	struct stat st;
	
	if((fd = open(path, O_RDONLY)) < 0){
		fprintf(2, "find: cannot open %s\n", path);
		return;
	}
	if(fstat(fd, &st) < 0){
		fprintf(2, "find: cannot stat %s\n", path);
		return;
	}

	switch(st.type){
		case T_DIR:
			if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
				printf("find: path too long\n");
				break;
			}
			strcpy(buf, path);
			p = buf + strlen(buf);
			*p++ = '/';
			while(read(fd, &de, sizeof(de)) == sizeof(de)){

				if(de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
					continue;

				strcpy(buf2, buf);
				p2 = buf2 + strlen(buf2);
				memmove(p2, de.name, DIRSIZ);
			   	p2[DIRSIZ] = 0;	
				if(stat(buf2, &st) < 0){
					printf("find: cannot stat2 %s\n", buf);
					continue;
				}

				if(st.type == T_DIR){
					strcpy(buf2, buf);
					p2 = buf2 + strlen(buf2);
					memmove(p2, de.name, DIRSIZ);
				   	p2[DIRSIZ] = 0;	
					find(buf2, filename);
					continue;
				}
				if(strcmp(de.name, filename) == 0){
					printf("%s%s\n", buf, filename);
				}

			}
			break;
	}
	close(fd);
}

int main(int argc, char *argv[]){
	
	if(argc < 3){
		printf("failed to find\n");
		exit(1);
	}
	
	find(argv[1], argv[2]);

	exit(0);
}
