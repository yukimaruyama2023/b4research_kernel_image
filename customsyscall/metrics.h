#ifndef METRICS_H
#define METRICS_H

#include <linux/types.h>
#include <linux/spinlock.h>

#define MAX_METRICS 200

struct metrics_info {
	u32 port;
	u64 phys_addr;
	u32 size;
};

extern struct metrics_info metrics_vector[MAX_METRICS];
extern int iterator_metrics;
extern spinlock_t iterator_lock;

#endif
