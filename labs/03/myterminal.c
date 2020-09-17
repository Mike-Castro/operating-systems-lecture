#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 1024

int main(){
	char line[BUFFER_LEN];
	char* argv[100];
	char* path = "/bin/";
	char progpath[20];
	int argc;
	int tot=10;
printf("Only 10 entries allowed\n");
for(int i=0; i<tot; i++){
	printf("MikeShell>>");
	if (!fgets(line, BUFFER_LEN, stdin)){
		break;
	}
	size_t length = strlen(line);
	if (line[length-1] == '\n'){
		line[length-1] = '\0';
	}
	if (strcmp(line, "exit")==0){
		break;
	}
	char *tok;
	tok=strtok(line," ");
	int j=0;
	while(tok!=NULL){
		argv[j]=tok;
		tok = strtok(NULL, " ");
		j++;
	}
	argv[j] = NULL;
	argc = j;
	for(int k=0; k < argc; k++){
		printf("%s\n", argv[k]);
	}
	strcpy(progpath, path);
	strcat(progpath, argv[0]);
	
	for(int l=0; l<strlen(progpath); l++){
		if(progpath[l]=='\n'){
			progpath[l]=='\0';
		}
	}
	
	int pid = fork();
	if (pid==0){
		execvp(progpath, argv);
		fprintf(stderr, "Child process could not do execvp\n");
	}else{
		wait(NULL);
		printf("Child exited\n");
	}
}

}
