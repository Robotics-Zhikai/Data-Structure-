#ifndef LINEAR_H
#define LINEAR_H




typedef int ElementType;
typedef struct Node * PtrToNode;
struct Node {
	ElementType Data;
	PtrToNode   Next;
};
typedef PtrToNode List;

void Print(List L); /* 细节在此不表；空链表将输出NULL */
ElementType FindKth(int K, List L);
int Find(ElementType X, List L);
List Insert(ElementType X, int i, List L);
void Delete(int i, List * L);
int Length(List L);
List GetLocation(ElementType i, List L);
void CopyL(List * L11, List * L33); //复制L3到L1


#endif