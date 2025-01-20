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
//
// SYSCALL_DEFINE0(reset_metrics_vector_2)
// {
// 	spin_lock(&iterator_lock_2);
// 	memset(metrics_vector_2, 0, sizeof(metrics_vector_2));
// 	iterator_metrics_2 = 0;
// 	spin_unlock(&iterator_lock_2);
// 	pr_info("reset_metrics_vector_2: metrics_vector_2 has been reset\n");
//
// 	return 0;
// }
