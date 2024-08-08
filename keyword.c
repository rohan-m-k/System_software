#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int iskeyword(char buffer[])
{
    char k[32][10] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", 
    "double", "else", "enum", "extern", "float", "for", "goto", "if", 
    "int", "long", "register", "return", "short", "signed", "sizeof", 
    "static", "struct", "switch", "typedef", "union", "unsigned", 
    "void", "volatile", "while"
};
	int i,flag=0;
	for(i=0;i<32;i++){
		if(strcmp(k[i],buffer)==0){
			flag=1;
			break;
		}
	}
		return flag;
}
int main()
{
	int i=0;
    //int ch;
	char buffer[15];
	FILE*fp;
	fp=fopen("loader.c","r");
	if(fp==NULL){
		printf("while opening error");
		exit(0);
	}
	int ch;
	while((ch=fgetc(fp))!=EOF){
		if(isalpha(ch)){
			buffer[i++]=ch;
		}
		else if(i>0){
			buffer[i]='\0';
			i=0;
			if(iskeyword(buffer)==1)
			{
				printf("%s is keyword\n",buffer);
			}
			buffer[0]='\0';
		}
	}
	fclose(fp);
	return 0;
}
