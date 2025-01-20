#ifndef METRICS_H
#define METRICS_H

#include <linux/types.h>
#include <linux/spinlock.h>

#define MAX_METRICS 200

struct metrics_info {
	u32 port;
	int struct_id;
	u32 size;
	u64 phys_addr;
};
// struct metrics_info_2 {
// 	u32 port;
// 	int struct_identifier;
// 	u64 phys_addr;
// };

extern struct metrics_info metrics_vector[MAX_METRICS];
// extern struct metrics_info_2 metrics_vector_2[MAX_METRICS];
extern int iterator_metrics;
// extern int iterator_metrics_2;
extern spinlock_t iterator_lock;
// extern spinlock_t iterator_lock_2;

#endif
