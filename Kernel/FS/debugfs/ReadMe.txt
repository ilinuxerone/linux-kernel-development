 Debugfs

Description

Debugfs is a simple to use RAM based file system especially designed for debugging purposes. Developers are encouraged to use debugfs instead of procfs in order to obtain some debugging information from their kernel code. Debugfs is quite flexible: it provides the possibility to set or get a single value with the help of just one line of code but the developer is also allowed to write its own read/write functions, and he can use the seq_file interface described in the procfs section.

Implementation

In order to use debugfs it needs to be compiled with the Linux kernel source code. This is done by setting the parameter CONFIG_DEBUG_FS=y.

Before having access to the debugfs it has to be mounted with the following command.
mount -t debugfs none /sys/kernel/debug

debugfs.c	kernel module that implements the "one line" API for a variable of type u8 as well as the API with which you can specify your own read and write functions.
All the "one line" APIs start with debugfs_create_ and are listed in include/linux/debugfs.h

The API with which you can provide your own read and write functions is similar to the one of procfs. In contrast to sysfs, you may create directories and files without having to care about a given hierarchy.

Resources and Further Reading

Kernel source code: include/linux/debugfs.h List of all one line APIs.
http://kerneltrap.org/node/4394 announcement of the debugfs by Greg KH.
http://lwn.net/Articles/115405/ article on lwn about debugfs
