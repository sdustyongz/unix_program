#include <stdio.h>
#include <termios.h>
#include<string.h>
#include<fcntl.h>


#define QUESTION "do you want annother transaction"
#define TRIES 3
#define SLEEPTIME 2
#define BEEP putchar('\a');

int get_response(char *,int);

void set_crmode();
void  tty_mode(int);
int get_ok_char();
void set_nodelay_mode();
int main(void){
	tty_mode(0);
	set_crmode();
	set_nodelay_mode();
	get_response(QUESTION,3);	
	tty_mode(1);
	return 0;
}

int get_response(char *  qus,int maxtries){
	printf("%s (y/n)",qus);
	fflush(stdout);
	int input;
	while(1){
		sleep(SLEEPTIME);
		input=tolower(get_ok_char());
		if(input=='y')
			return 0;
		if(input=='n')
			return 1;
		if(maxtries--==0)
				return 2;
		BEEP;
		}
}


int get_ok_char(){
	int c;
	while((c=getchar())!=EOF&&strchr("yYnN",c)==NULL)
			;
	return c;
	
}
void set_crmode(){
	struct termios ttystate;
	tcgetattr(0,&ttystate);
	ttystate.c_lflag &=~ICANON;
	ttystate.c_lflag &=~ECHO;
	ttystate.c_cc[VMIN]=1;
	tcsetattr(0,TCSANOW,&ttystate);

}	

void set_nodelay_mode(){
	int termflags;
	termflags=fcntl(0,F_GETFL);
	termflags |=O_NDELAY;
	fcntl(0,F_SETFL,termflags);
}


void tty_mode(int how){
	static struct termios original_mode;
	static int original_flags;
	if(how==0){
		 tcgetattr(0,&original_mode);
		original_flags=fcntl(0,F_GETFL);
	}else{
		 tcsetattr(0,TCSANOW,&original_mode);
		 fcntl(0,F_SETFL,original_flags);
	}
}
