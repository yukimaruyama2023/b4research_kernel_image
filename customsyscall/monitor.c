#include <linux/kernel.h>
#include <linux/syscalls.h>

u64 memcached_phys_addr;

SYSCALL_DEFINE1(monitor, u64, phys_addr)
{
	pr_info("Hello! I'm monitor syscall\n");
	memcached_phys_addr = phys_addr;
	pr_info("memcached_phys_addr is %lx\n", memcached_phys_addr);
	return 0;
}
