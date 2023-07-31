#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"



int prost(int broj){

	int prost = 1;
	for( int i = 2; i <= broj/2; i++){
		prost = 1;
		if( broj / i == 0){
			prost = 0;
			break;
		}
	}

	if(prost == 1)
		return 1;
	else
		return 0;
}

int
main(int argc, char *argv[])
{
	void *komanda;
	void *niz;
	void *counter;
	int i = 2;


	get_shared("niz", &niz);
	get_shared("komanda", &komanda);
	get_shared("counter", &counter);
	
	
	

	for(;;){
		if(*(int*) counter == 99999){
			break;
		}
			
		//if()
			if(prost(i) == 1){ // ako je prost ubaci u niz roditelja i povecaj cout
				//*(((int*)niz + (*((int*)counter)))) = i;
				*(int*)counter = *(int*)counter + 1;
			}
			i++;
		//}

	}

	exit();
}
