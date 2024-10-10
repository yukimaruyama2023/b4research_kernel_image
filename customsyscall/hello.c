#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(hello)
{
	pr_info("Hello! I'm hello syscall\n");
	return 0;
}
