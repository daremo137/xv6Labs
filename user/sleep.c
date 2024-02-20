#include "kernel/types.h"
//#include "kernel/stat.h"
//#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int seconds;

  if(argc <= 1){
    printf("please input the seconds\n");
    exit(1);
  }
	seconds = atoi(argv[1]);
	sleep(seconds);	
	//exit(0);
	return 0;
}
