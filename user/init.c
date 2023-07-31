// init: The initial user-level program

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"

char *argv[] = { "sh", 0 };

int
main(void)
{
	int pid, wpid;

	if(getpid() != 1){
		fprintf(2, "init: already running\n");
		exit();
	}

	if(open("/dev/console", O_RDWR) < 0){
		mknod("/dev/console", 1, 1);
		open("/dev/console", O_RDWR);
	}
	dup(0);  // stdout
	dup(0);  // stderr

	for(;;){
		printf("init: starting sh\n");
		pid = fork();


		if(pid < 0){ // nama nebitno ovaj if
			printf("init: fork failed\n");
			exit();
		}


		if(pid == 0){ // ovaj if se desava samo u child procesu
			exec("/bin/sh", argv); //exec
			printf("init: exec sh failed\n");//ova 36 37 se ne desava ako exec prod
			exit();//
		}
		while((wpid=wait()) >= 0 && wpid != pid)
			printf("zombie!\n");

		//wait blokira parenta i ceka da se zavrsi child proces.Kada child proces 			pozove exit perent se odblokira i parent unutura ovog poziva wait cisti child
	}
}
