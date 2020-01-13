#include <stdio.h>
#include <signal.h>

#define INPUTLEN 100


void inthandler(int s){
	printf("Received signal %d..wariting\n",s);
	sleep(2);
	printf("Leaving inthandler\n");
}

void quithandler(int s){
	printf("Received signal %d..wariting\n",s);
	sleep(3);
	printf("Leaving quithandler\n");
}

int main(int ac,char *av[]){
	char input[INPUTLEN];
	int nchars;
	signal(SIGINT,inthandler);
	signal(SIGQUIT,quithandler);

	do{
		printf("Type a message\n");
		nchars=read(0,input,(INPUTLEN-1));
		if(nchars==-1){
			perror("read error");
		}else{
			input[nchars]='\0';
			printf("you typed:%s\n",input);
		}

	}while(strncmp(input,"quit",4)!=0);

}
