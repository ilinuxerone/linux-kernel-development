读函数的原型：
	int read_proc(char *page, char **start, off_t off,int count, int *eof, void *data);
	当我们通过诸如“cat”之类的命令来读取/proc目录下的文件内容时，内核会分配给proc读取程序一页大小的内存空间，即PAGE_SIZE大小，proc的驱动程序会自动将这块内存中的数据复制到用户空间，最终待访问的proc文件的read_proc回调函数会被调用，其中：
	page：将需要传递给用户的数据复制到这个缓冲区地址里。这个缓冲区是内核空间的，不需要用户调用copy_to_user()之类的函数，系统会自动将page中的数据复制给用户。
	start：在page所指向的缓冲区中需要复制给用户数据的起始地址。一般不使用。
	off：用户打算读取文件时的偏移地址，即从这个地址开始读取。类似用户空间lseek移动文件指针的作用。
	count：用户要求读取的字节数。
	eof：如果读到文件结尾，当驱动程序的数据发送完毕时将这个值置为1，发送给用户，我们可以通过该值判断是否读取到文件末尾。
	data：私有数据指针，一般不用。

	写函数的原型：
	int write_proc(struct file *file, const char __user *buffer,unsigned long count, void *data);
	file：内核中一个打开的文件结构，通常忽略。
	buffer：用户空间传递过来的数据指针，用户待写入文件的数据就存储在这个值所指向的地址区域中。而这家伙实际上是一个用户空间地址，内核中不能直接拿来用，需要调用诸如copy_from_user()之类的函数来讲用户空间的数据复制到内核空间来。
	count：用户待写入文件的字节数。
	data：一般不用。
	删除proc文件比较简单，调用：
	void remove_proc_entry(const char *name, struct proc_dir_entry *parent)
	即可，参数同上，其中name是要删除的proc文件的名称。

在上面的例子中我们看到read_proc的回调函数中我们确实没有调用copy_to_user()函数，结果还是正确误区地返回给用户。procfs既然属于一种特殊的文件系统，那我们我们是否可以像操作普通文件那样，对其进行扩充呢？答案是肯定，我们对上面的例子稍加改造，使用内核提供的文件系统的机制来实现对proc文件的读写操作.见proc_ext.c实例。
