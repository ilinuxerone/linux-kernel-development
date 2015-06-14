Introduction

System calls are used when a user space program wants to use some data or some
service provided by the Linux kernel. In current Linux kernel (2.6.23) there
exist 324 system calls. All system calls provide a function which is useful
for many application programs (such as file operations, network operations or
process related operations). There is no point in adding a very specific
system call which can be used only by a specific program.

Usually the system call gets invoked by a wrapper function provided by glibc
(for example open(), socket(), getpid()). Internally each system call is
identified by a unique number.

When a user space process invokes a system call, the CPU switches to kernel
mode and executes the appropriate kernel function.

In order to actually do the switch from user mode to kernel mode there are
some assembly instructions. For x86 architectures there are two possibilities:
"int $0x80", or the newer "sysenter". Both possibilities cause:

the CPU to switch to kernel mode,
the necessary registers to be saved
some validity checks
invoke the system call corresponding to the number provided by the user space
process.
If the system call service routine has finished, the system_call function
checks whether there is some other work to do (such as rescheduling or signal
processing) and it finally restores the user mode process context.

5.2 Implementation

System calls are a low level construct, therefore they are heavily integrated
in the Linux kernel. In order to add a new system call to the Linux kernel,
you have to modify a number of Linux kernel files:

include/asm-i386/unistd.h
This file defines the system call numbers provided by the user space to
identify the system call. Add your system call at the end and increment the
total number of system calls.
         #define __NR_mysyscall          325
        #define NR_syscalls 326
        
include/linux/syscalls.h
This file contains the declaration of all system calls. Add your system call
at the end.
         asmlinkage long sys_mysyscall(char __user *data, int len);
        
arch/i386/kernel/syscall_table.S
This file is a table with all the available system calls. In order to make
your call accessible add the following line at the bottom of this file:
         .long sys_mycall
        
add a new directory mysyscall
Since the system call has to be integrated in the kernel we add a new
directory "mysyscall" for our system call in the top level directory of the
Linux source code.
Makefile
Add the new directory to the variable core-y (search for core-y.*+=) in the
top level Makefile.
Write your new system call function in the file mysyscall/mysyscall.c
This example prints the message provided by the user space to the system log
file and exchanges it with "hello world".
         #include <linux/linkage.h>
        #include <asm/uaccess.h>
        asmlinkage long sys_mysyscall(char __user *buf, int len)
        {
          char msg [200];
          if(strlen_user(buf) > 200)
                   return -EINVAL;
          copy_from_user(msg, buf, strlen_user(buf));
          printk("mysyscall: %s\n", msg);
          copy_to_user(buf, "hello world", strlen("hello world")+1);
          return strlen("hello world")+1;
        }
        

Add a Makefile to your directory with the following line:
         obj-y:= mysyscall.o
        
With this you have completed the kernel implementation. After having compiled
and installed the new kernel, user space applications can make use of the new
system call. The following is an example code which uses the new system call:

         #include <stdio.h>
        #include <string.h>
        #include <unistd.h>
        #include <sys/syscall.h>
        #define MYSYSCALL 325
        int main(){
                char *buf [20];
                memcpy(buf, "hi kernel", strlen("hi kernel") +1);
                syscall(MYSYSCALL, buf, 10);
                printf("kernel said %s\n", buf);
                return 0;
        }
