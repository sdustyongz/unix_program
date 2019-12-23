#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24 
#define LINELEN 512 
void do_more(FILE*in);
int showMore(FILE* );
int main(int cnt,char * avgs[]){
	if(cnt==1){
		do_more(stdin);
	}else if(cnt>1){
		while(--cnt){
			FILE * fp;
			if((fp=fopen(*++avgs,"r"))!=NULL){
				do_more(fp);
				fclose(fp);
			}
		}
	}

}



void do_more(FILE * fp){
	char line[LINELEN];
	int line_num=0;
	FILE * fp_tty;
	fp_tty=fopen("/dev/tty","r");
	while(fgets(line,LINELEN,fp)!=NULL){
		fputs(line,stdout);
		if((++line_num)==PAGELEN){
			if(showMore(fp_tty)){
				line_num=0;
			}else{
				exit(0);
			}
			
		}
		

	}
}

int showMore(FILE * cmd){
	printf("more?\n");
	char ch;
	while((ch=getc(cmd))!=EOF){
		if(ch=='q'){
			return 0;
		}
		if(ch==' '){
			return 1;
		}
	}
}
