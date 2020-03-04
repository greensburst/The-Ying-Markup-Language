#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "absll.h"

char dest[128] = {0};
char src[128] = {0};

void operateElement(void* str) {
	int i = 0;
	while(*(char*)(str+i) == 32 || *(char*)(str+i) == 9) {
		i++;
	}
	FILE* fp = fopen(dest,"a");
	if(strncmp(str+i,"! ",2) == 0) {
		fprintf(fp,"<h1>%s</h1>\n",str+i+2);
	} else if(strncmp(str+i,"@ ",2) == 0) {
		fprintf(fp,"<h2>%s</h2>\n",str+i+2);
	} else if(strncmp(str+i,"# ",2) == 0) {
		fprintf(fp,"<h3>%s</h3>\n",str+i+2);
	} else {
		fprintf(fp,"<p>%s</p>\n",str);
	}
	fclose(fp);
}

void freeElement(void* str) {
	if(str != NULL) {
		free(str);
		str = NULL; 
	}
}

int main(int argc, char* argv[]) {
	
	if(argv[1] && argv[2]) {
		strcpy(src,argv[1]);
		strcpy(dest,argv[2]);
	} else {
		printf("missing parameters!\n");
		return -1;
	}
	
	FILE* fp = fopen(src,"r"); 
	if(fp == NULL) {
		perror("open note.ing");
		return -1;
	}
	
	PABSLL file = ll_create();
	
	char buf[256] = {0};
	int length = 0;
	while(fgets(buf,sizeof(buf),fp)) {
		
		length = strlen(buf);
		if(buf[length-1] == '\n') {
			buf[strlen(buf)-1] = '\0';
			length--;
		}
		char* line = (char*)malloc(length+1);
		strcpy(line,buf);
		ll_append(file,line);
	}
	
	fp = fopen(dest,"w");
	ll_traverse(file,operateElement);
	
	ll_destroy(file,freeElement);
	fclose(fp);
	return 0;
}
