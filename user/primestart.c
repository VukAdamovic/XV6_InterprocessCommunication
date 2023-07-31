#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"


int niz[100000]; // niz

int
main(int argc, char *argv[])
{
	
	int counter = 0 ;
	int komanda = 0;

	for(int i = 0; i < 100000; i++){
		niz[i] = 0;
	}
 	
	//sherujem 3 strukture
	share_mem("niz", niz, sizeof(niz));
	share_mem("komanda", &komanda, sizeof(komanda));
	share_mem("counter", &counter, sizeof(counter));
	
	
	

	//kreiram i pokrecem primecalc i primecom i pozdatini da rade
	int pid1,pid2;
	char *argv2[] ={"/bin/primecalc",0};
	char *argv3[] ={"/bin/ls",0};

	pid1 = fork();

	if(pid1 == 0)
	{
        	exec("/bin/primecalc", argv2);
        }
	else
	{
        	pid2 = fork();
        	if(pid2 == 0)
		{
            		exec("/bin/ls",argv3);
        	}
		wait();
		wait(); 
	}
	exit();	
}
