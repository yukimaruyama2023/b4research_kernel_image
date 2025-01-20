#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/spinlock.h>
#include <linux/slab.h>

#include "metrics.h"

DEFINE_SPINLOCK(iterator_lock);
// DEFINE_SPINLOCK(iterator_lock_2);

struct metrics_info metrics_vector[MAX_METRICS];

int iterator_metrics = 0;

u64 memcached_phys_addr; // remove lator

// this syscall is called per application server
SYSCALL_DEFINE4(register_metrics, u32, port, int, struct_id, u32, size, u64,
		phys_addr)
{
	spin_lock(&iterator_lock);

	if (iterator_metrics >= MAX_METRICS) {
		pr_warn("register_metrics: metrics_vector is full\n");
		spin_unlock(&iterator_lock);
		return -ENOMEM;
	}

	metrics_vector[iterator_metrics].port = port;
	metrics_vector[iterator_metrics].struct_id = struct_id;
	metrics_vector[iterator_metrics].size = size;
	metrics_vector[iterator_metrics].phys_addr = phys_addr;

	pr_info("register_metrics: Added metric at iterator %d: port=%u, struct_id=%d, size=%u, phys_addr=0x%llx\n",
		iterator_metrics, port, struct_id, size, phys_addr);

	iterator_metrics++;

	spin_unlock(&iterator_lock);

	return 0;
}

/*// this syscall is callced per struct*/
/*SYSCALL_DEFINE3(register_metrics_2, u32, port, int, struct_identifier, u64,*/
/*		phys_addr)*/
/*{*/
/*	spin_lock(&iterator_lock_2);*/
/**/
/*	if (iterator_metrics_2 >= MAX_METRICS) {*/
/*		pr_warn("register_metrics_2: metrics_vector is full\n");*/
/*		spin_unlock(&iterator_lock_2);*/
/*		return -ENOMEM;*/
/*	}*/
/**/
/*	metrics_vector_2[iterator_metrics_2].port = port;*/
/*	metrics_vector_2[iterator_metrics_2].struct_identifier =*/
/*		struct_identifier;*/
/*	metrics_vector_2[iterator_metrics_2].phys_addr = phys_addr;*/
/**/
/*	pr_info("register_metrics_2: Added metric at iterator %d: port=%u, struct_identifier=%d, phys_addr=0x%llx\n",*/
/*		iterator_metrics_2, port, struct_identifier, phys_addr);*/
/**/
/*	iterator_metrics_2++;*/
/**/
/*	spin_unlock(&iterator_lock_2);*/
/**/
/*	return 0;*/
/*}*/
