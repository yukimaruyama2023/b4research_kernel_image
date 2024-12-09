#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/spinlock.h>
#include <linux/slab.h>

#include "metrics.h"

SYSCALL_DEFINE0(reset_metrics_vector)
{
	spin_lock(&iterator_lock);
	memset(metrics_vector, 0, sizeof(metrics_vector));
	iterator_metrics = 0;
	spin_unlock(&iterator_lock);
	pr_info("reset_metrics_vector: metrics_vector has been reset\n");

	return 0;
}
