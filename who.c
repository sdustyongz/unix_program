#include <stdio.h>
#include <utmp.h>
#include <stdlib.h>

#define SHOWHOST

void show(struct utmp *);

int main(){
	struct utmp current_record;
	FILE * utmpfd;
	int reclen=sizeof(current_record);
	if((utmpfd=fopen(UTMP_FILE,"r"))==NULL){
		exit(1);
	}
	while(fread(&current_record,reclen,1,utmpfd)==1){
		show(&current_record);
	}	
}

void show(struct utmp * recard){
	if(recard->ut_type!=USER_PROCESS)
		return;
	printf("%-8.8s",recard->ut_name);
	printf("  ");
	printf("%8.8s",recard->ut_line);

	printf("  ");
	printf("%10ld",recard->ut_time);

	printf("  ");
	#ifdef SHOWHOST
		printf("(% s)",recard->ut_host);
	#endif 
	printf("\n");
}
