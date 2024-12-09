#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/spinlock.h>
#include <linux/slab.h>

#include "metrics.h"

DEFINE_SPINLOCK(iterator_lock);

struct metrics_info metrics_vector[MAX_METRICS];

int iterator_metrics = 0;

u64 memcached_phys_addr; // remove lator

SYSCALL_DEFINE3(register_metrics, u32, port, u64, phys_addr, u32, size)
{
	spin_lock(&iterator_lock);

	if (iterator_metrics >= MAX_METRICS) {
		pr_warn("register_metrics: metrics_vector is full\n");
		spin_unlock(&iterator_lock);
		return -ENOMEM;
	}

	metrics_vector[iterator_metrics].port = port;
	metrics_vector[iterator_metrics].phys_addr = phys_addr;
	metrics_vector[iterator_metrics].size = size;

	pr_info("register_metrics: Added metric at iterator %d: port=%u, phys_addr=0x%llx, size=%u\n",
		iterator_metrics, port, phys_addr, size);

	iterator_metrics++;

	spin_unlock(&iterator_lock);

	return 0;
}

// SYSCALL_DEFINE0(reset_metrics_vector)
// {
// 	spin_lock(&iterator_lock);
//
// 	memset(metrics_vector, 0, sizeof(metrics_vector));
//
// 	iterator = 0;
//
// 	spin_unlock(&iterator_lock);
//
// 	pr_info("reset_metrics_vector: metrics_vector has been reset\n");
//
// 	return 0;
// }

// #include <linux/gfp.h>
// #include <linux/kernel.h>
// #include <linux/syscalls.h>
// #include <linux/spinlock.h>
// #include <linux/slab.h>
//
// static DEFINE_SPINLOCK(iterator_lock);
//
// u64 memcached_phys_addr; // remove lator
//
// struct metrics_info {
// 	u32 port;
// 	u64 phys_addr;
// 	u32 size;
// 	struct metrics_info *ptr;
// };
//
// struct metrics_info *head_to_metrics_list = NULL;
// struct metrics_info *tail_to_metrics_list = NULL;
//
// SYSCALL_DEFINE3(register_metrics, u32, port, u64, phys_addr, u32, size)
// {
// 	struct metrics_info *p;
//
// 	p = (struct metrics_info *)kmalloc(sizeof(struct metrics_info),
// 					   GFP_KERNEL);
// 	if (!p) {
// 		pr_err("register_metrics: Failed to allocate memory\n");
// 		return -ENOMEM;
// 	}
//
// 	p->port = port;
// 	p->phys_addr = phys_addr;
// 	p->size = size;
// 	p->ptr = NULL;
//
// 	spin_lock(&iterator_lock);
//
// 	if (!head_to_metrics_list) {
// 		head_to_metrics_list = p;
// 		tail_to_metrics_list = p;
// 	} else {
// 		tail_to_metrics_list->ptr = p;
// 		tail_to_metrics_list = p;
// 	}
//
// 	spin_unlock(&iterator_lock);
//
// 	pr_info("register_metrics: Added metric - port: %u, phys_addr: %llx, size: %u\n",
// 		port, phys_addr, size);
//
// 	return 0;
// }
//
