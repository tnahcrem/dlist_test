#ifndef _DBLIST_H_
#define _DBLIST_H_




typedef struct dblist_node_t {
	struct dblist_node_t *next, *prev;
} dblist_node_t;

#define DBLIST_NODE_INIT(name) { &(name), &(name) }

#define DBLIST_NODE(name) \
	struct dblist_node_t name = DBLIST_NODE_INIT(name)

#define INIT_DBLIST_NODE(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
void __dblist_add(struct dblist_node_t * _new,
	struct dblist_node_t * prev,
	struct dblist_node_t * next);

/**
 * dblist_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static  __inline void dblist_add(struct dblist_node_t *_new, struct dblist_node_t *head)
{
	__dblist_add(_new, head, head->next);
}

/**
 * dblist_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static __inline void dblist_add_tail(struct dblist_node_t *_new, struct dblist_node_t *head)
{
	__dblist_add(_new, head->prev, head);
}

/**
 * dblist_del - deletes entry from list.
 * @entry: the element to delete from the list.
 */
void dblist_del(struct dblist_node_t *entry);

/**
 * dblist_empty - tests whether a list is empty
 * @head: the list to test.
 */
int dblist_empty(struct dblist_node_t *head);

/**
 * dblist_entry - get the struct for this entry
 * @ptr:	the &struct dblist_node_t pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the dblist_node_t within the struct.
 */
#define dblist_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

/**
 * dblist_for_each	-	iterate over a list
 * @pos:	the &struct dblist_node_t to use as a loop counter.
 * @head:	the head for your list.
 */
#define dblist_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * dblist_for_each_safe	-	iterate over a list safe against removal of list entry
 * @pos:	the &struct dblist_node_t to use as a loop counter.
 * @n:		another &struct dblist_node_t to use as temporary storage
 * @head:	the head for your list.
 */
#define dblist_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

/**
 * list_for_each_prev	-	iterate over a list in reverse order
 * @pos:	the &struct dblist_node_t to use as a loop counter.
 * @head:	the head for your list.
 */
#define dblist_for_each_prev(pos, head) \
	for (pos = (head)->prev; pos != (head); \
        	pos = pos->prev)

/**
 * dblist_for_each_prev_safe  -   iterate over a list safe in reverse
         order against removal of list entry
 * @pos:    the &struct dblist_node_t to use as a loop counter.
 * @n:      another &struct dblist_node_t to use as temporary storage
 * @head:   the head for your list.
 */
#define dblist_for_each_prev_safe(pos, n, head) \
    for (pos = (head)->prev, n = pos->prev; pos != (head); \
        pos = n, n = pos->prev)

/**
 * dblist_count - get the number of items
 * @head: the list to test.
 */
static __inline int dblist_count(struct dblist_node_t *head)
{
    struct dblist_node_t* pos;
    int i = 0;
    dblist_for_each(pos, head)
        i ++;
    return i;
}


#endif // end of #ifndef _DBLIST_H_
