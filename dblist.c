#include "dblist.h"

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
void __dblist_add(dblist_node_t * _new,
	dblist_node_t * prev,
	dblist_node_t * next)
{
	next->prev = _new;
	_new->next = next;
	_new->prev = prev;
	prev->next = _new;
}

/**
 * dblist_del - deletes entry from list.
 * @entry: the element to delete from the list.
 */
void dblist_del(dblist_node_t *entry)
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
}

/**
 * dblist_empty - tests whether a list is empty
 * @head: the list to test.
 */
int dblist_empty(dblist_node_t *head)
{
	return head->next == head;
}


