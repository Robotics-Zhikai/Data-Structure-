#ifndef QUEUE_H
#define QUEUE_H
#define ERROR NULL

typedef struct QueueInfo * QueueInfoAddress;
typedef struct NodeQueue * NodeQueueAddress;

typedef struct TreeNode * TreeNodeAddress;
struct TreeNode
{
	int NumNode; //���ı��
	int left;
	int right;
};
typedef struct ListNode * ListNodeAddress;
struct ListNode
{
	TreeNodeAddress TreeNodeAdd;
	int Root;//������ڵ���
	ListNodeAddress Next;
};
typedef ListNodeAddress ElementTypeQueue;
struct NodeQueue
{
	ElementTypeQueue Data;
	NodeQueueAddress Next;
};

struct QueueInfo
{
	NodeQueueAddress Rear;
	NodeQueueAddress Front;
	NodeQueueAddress HeadNode;
};

QueueInfoAddress CreateQueue(int Maxsize);

int IsQueueEmpty(QueueInfoAddress Queue);

int IsQueuefull(QueueInfoAddress Queue);

QueueInfoAddress QueuePush(QueueInfoAddress Queue, ElementTypeQueue data);

ElementTypeQueue QueuePop(QueueInfoAddress Queue);







#endif