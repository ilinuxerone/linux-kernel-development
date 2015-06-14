Introduction

The upcall functionality of the Linux kernel allows a kernel module to invoke a function in user space. It is possible to start a program in user space, and give it some command line arguments, as well as setting environment variables.

7.2 Implementation

usermodehelper.c	kernel module that starts a process
callee.c	user space program that will be executed on behalf of the kernel
Our example consists of a kernel module usermodehelper and a user space program callee. Since callee is not started within a shell, we cannot use printf to verify its correct execution, instead we let him run the beep command and let the kernel module specify how many times to beep. The callee gets invoked by the following function prototype: 
int call_usermodehelper(char *path, char **argv, char **envp, enum umh_wait wait)
With the following arguments:

path: The path to the user space program
argv: The arguments for the user space program
envp: A set of environment varialbes
umh_wait: Enum that says whether the kernel module has to wait or whether it can continue with the execution:
UMH_NO_WAIT: don't wait at all
UMH_WAIT_EXEC: wait for the exec, but not the process
UMH_WAIT_PROC: wait for the process to complete
