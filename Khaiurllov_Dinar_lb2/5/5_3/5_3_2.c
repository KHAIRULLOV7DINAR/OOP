#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>
#include <sys/resource.h>

int main()
{
    const int lowest_prio = sched_get_priority_min(SCHED_FIFO);
    const int highest_prio = sched_get_priority_max(SCHED_FIFO);
    
    fprintf(stdout, "Min priority level: %d\nMax priority level: %d\n", lowest_prio, highest_prio);
    
    return EXIT_SUCCESS;
}
