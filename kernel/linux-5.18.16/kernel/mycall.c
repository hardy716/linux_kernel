#include<linux/kernel.h>
#include<linux/linkage.h>
#include<linux/syscalls.h>
int value;
SYSCALL_DEFINE1(mycall1, int, x){
	printk("INSERT value: %d", x);
	value = x;
	return 0;
}
SYSCALL_DEFINE0(mycall2){
	printk("Current value: %d", value);
	return value;
}
