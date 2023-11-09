#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
	/* Initialize two pointers at the head of the list,
	 * with one being a slow pointer and the other being a fast pointer. */
	node *slow_ptr = head;
	node *fast_ptr = head;

	/* There is no cycle if the list is empty or has one node. */
	while (fast_ptr != NULL && fast_ptr->next != NULL) {
		/* Advance the slow pointer by one node and the fast pointer by two nodes. */
		slow_ptr = slow_ptr->next; 
		fast_ptr = fast_ptr->next->next;
                
		/* If the two pointers are equal, then there is a cycle */
		if (slow_ptr == fast_ptr) {
			return 1;
		}
	}
        /* If we get to the end, then there were no cycles. */
	return 0;
}
