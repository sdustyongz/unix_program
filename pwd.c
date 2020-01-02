#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 256

ino_t get_inode(char * fname){
	struct stat info;
	if(stat(fname,&info)==-1){
		fprintf(stderr,"cannot stat");
		perror(fname);
		exit(1);
	}
	return info.st_ino;
}

void inum_to_name(ino_t inde_to_find,char * namebuf,int buflen){
	DIR * dir_ptr;
	struct dirent * direntp;
	dir_ptr = opendir(".");
	if(dir_ptr==NULL){
		perror(".");
		exit(1);
	}
	while((direntp=readdir(dir_ptr))!=NULL){
		if(direntp->d_ino==inde_to_find){
			strncpy(namebuf,direntp->d_name,buflen);
			namebuf[buflen-1]='\0';
			closedir(dir_ptr);
			return;
		}
	}
	fprintf(stderr,"error looking for inum %d\n",inde_to_find);
	exit(1);
}

void printpathto(ino_t this_inode){
	ino_t my_inode;
	char its_name[BUFFSIZE];
	if(get_inode("..")!=this_inode){
		chdir("..");
		inum_to_name(this_inode,its_name,BUFFSIZE);
		my_inode=get_inode(".");
		printpathto(my_inode);
		printf("/%s",its_name);
	}
}

int main(){
	printpathto(get_inode("."));
	putchar('\n');
	return 0;
}
