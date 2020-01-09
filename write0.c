#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int ac,char *av[]){
	if(ac!=2){
		fprintf(stderr,"usage:write0 ttyname\n");
		exit(1);
	}
	int fd;
	char buf[BUFSIZ];
    printf("%s\n",av[1]);
	fd=open(av[1],O_WRONLY);
	printf("%d\n",fd);
	while(fgets(buf,BUFSIZ,stdin)!=NULL){
		if(write(fd,buf,strlen(buf))==-1)
				break;
	}
	close(fd);
}
