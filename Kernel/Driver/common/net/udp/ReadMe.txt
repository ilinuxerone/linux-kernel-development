Introduction

Beside the file system based mechanism described in the last section, there are mechanisms based on the socket interface. Sockets allow the Linux kernel to send notifications to a user space application. This is in contrast to the file system mechanisms, where the kernel can alter a file, but the user program does not know of any change until it choses to access that file. The socket based mechanisms allow the applications to listen on a socket, and the kernel can send them messages at any time. This leads to a communication mechanism in which user space and kernel space are equal partners.

There are different socket families which can be used to achieve this goal:

AF_INET
designed for network communication, but UDP sockets can also be used for the communication between a kernel module and the user space. The use of UDP sockets for node local communication involves a lot of overhead.

AF_PACKET
allows the user to define all packet headers.

AF_NETLINK (netlink sockets)
They are especially designed for the communication between the kernel space and the user space. There are different netlink socket types currently implemented in the kernel, all of which deal with a specific subset of the networking part of the Linux kernel.

In this section we briefly cover UDP sockets, as they are the most flexible communication mechanism. Afterwards we look at netlink sockets, with a special focus on "generic netlink sockets".

3.2 UDP Sockets

Description

We briefly describe UDP sockets, since their usage in user space is well known and they provide a lot of flexibility. With UDP sockets it is possible to have communication between a kernel module on one system and a user space application on an other machine.

Implementation

udpRecvCallback.c	kernel module that provides a callback function to receive messages on port number 5555.
udpUser.c	user space program that sends a message to the kernel which sends the message back.
The user space program sends the string "hello world" to the kernel, which listens on port 5555. The module prints the payload to the system log file and sends it back to the application. The application receives the message and prints the payload to stdout.

The user space code does not need any explanation, since a lot of documentation is available for socket programming. The module implementation requires some understanding of the Linux kernel. The module_init function performs three actions:

Create a socket to receive UDP packets. As is well known from user space, we first create the socket and then we bind it. In addition we specify a callback function, which is executed every time a packet is received on that socket. This callback function is executed in "interrupt context". This implies that only a restricted set of operations can be performed in that function, and it is not allowed to send any messages.
Therefore we define a work_queue with which we can delay the sending of the answer until we have left interrupt context.
Finally, we create a socket to send the answer back to the application.
Each time the module receives a packet, the callback function cb_data() is executed. The only thing this callback function does is to submit the send_answer() function to the work_queue. If the kernel decides that there is no better work to do, it executes the send_answer function. The send_answer() function receives the packets, by dequeuing them from the sockets-receive-queue, with skb_dequeue. Since more than one packet can be received by the socket between two consecutive executions of send_answer(), this function may need to dequeue multiple messages. The number of messages in the socket queue can be obtained with a call to skb_queue_len(). After having dequeued the packet the message is printed to the system log and a message is send back to the application with the sock_sendmsg() function. Since this function assumes to be executed from user space, we have to adjust the boundaries for the allowed memory region with the help of the set_fs macro.
