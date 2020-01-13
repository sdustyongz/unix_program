#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>

void countdown();
int set_ticker(int);
int main(){
	signal(SIGALRM,countdown);
	if(set_ticker(500)==-1){
		perror("set_ticker");
	}else{
		while(1)
			pause();
	}
	return 0;

}
void countdown(){
	static int num=10;
	printf("%d..",num--);
	fflush(stdout);
	if(num<0){
		printf("DONE!\n");
		exit(0);
	}

}

int set_ticker(int msecs){
	struct itimerval new_timeset;
	long n_sec,n_usecs;

	n_sec=msecs/1000;
	n_usecs=(msecs%1000)*1000L;
	new_timeset.it_interval.tv_sec=n_sec;
	new_timeset.it_interval.tv_usec=n_usecs;
	new_timeset.it_value.tv_usec=n_usecs;
	new_timeset.it_value.tv_sec=n_sec;
	return setitimer(ITIMER_REAL,&new_timeset,NULL);

}
