/*
 ============================================================================
 Name        : hello.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "dblist.h"

// dummy message struct
typedef struct
{
    dblist_node_t    node;
    uint           msg1;
    uint           msg2;
} TEST_MSG_t;

// global messages list
dblist_node_t        msgList;

/*
 * Name: void procMsgs(void)
 * Abstract: Extract each message in the global
 * message list and print of data from it.
 */
void procMsgs(void)
{
	uint count;
	TEST_MSG_t*  pMsg;
	count = dblist_count(&msgList);
	printf("\n the count is %d",count);

	while(count--)
	{
        pMsg = dblist_entry(msgList.next, TEST_MSG_t, node);
        dblist_del(&pMsg->node);
        printf("\n msg1 is %d AND msg2 is %d",pMsg->msg1,pMsg->msg2);
	}
}
int main(void) {

	TEST_MSG_t* m1 = (TEST_MSG_t*)malloc(sizeof(TEST_MSG_t));
	TEST_MSG_t* m2 = (TEST_MSG_t*)malloc(sizeof(TEST_MSG_t));
	TEST_MSG_t* m3 = (TEST_MSG_t*)malloc(sizeof(TEST_MSG_t));
	INIT_DBLIST_NODE(&msgList);
	m1->msg1 = 1;
	m1->msg2 = 2;
	m2->msg1 = 3;
	m2->msg2 = 4;
	m3->msg1 = 5;
	m3->msg2 = 6;
	// Add it like a stack
	dblist_add(&m1->node, &msgList);
	dblist_add(&m2->node, &msgList);
	dblist_add(&m3->node, &msgList);
	procMsgs();

	// Add it like a queue
	dblist_add_tail(&m1->node, &msgList);
	dblist_add_tail(&m2->node, &msgList);
	dblist_add_tail(&m3->node, &msgList);
	procMsgs();

	return 0;
}
