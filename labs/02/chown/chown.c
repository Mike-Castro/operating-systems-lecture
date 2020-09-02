#include <sys/syscall.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){
	uid_t uid = -1; 
	struct passwd *pwd;
	struct group *grp;

	pwd = getpwnam(argv[2]);
	if(pwd==NULL){
		fprintf(stderr, "Error: User Not Found\n");
		exit(0);
	}else{
		syscall(SYS_chown,argv[1],pwd->pw_uid, -1);
	}

return 0;
}
