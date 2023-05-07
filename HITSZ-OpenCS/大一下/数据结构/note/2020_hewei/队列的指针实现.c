#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0
typedef int ElementType; /* �����������ݶ�Ϊint */
typedef struct Node *PtrToNode;
struct Node { /* �����еĽ�� */
	ElementType Data;
	PtrToNode Next;
};
typedef PtrToNode Position;

struct QNode { /* ���б��� */
	Position Front, Rear;  /* ���е�ͷ��βָ�� */
};
typedef struct QNode *Queue;

/* ��ʼ������ */
Queue MakeNull()
{
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Front = (Position)malloc(sizeof(struct Node));
	Q->Front->Next = NULL;
	Q->Rear = Q->Front; /* �ն��е�ͷ��βָ��ָ��ͬһ�������ݵĽ�� �ý�㲻�� */
	return Q;
}

/* �жϿն��� */
int IsEmpty(Queue Q)
{
	return (Q->Front == Q->Rear);
}

/* ���ض��������� */
ElementType GetFront(Queue Q)
{
	return Q->Front->Next->Data; /* �������ײ��õĽ�� */
}

/* ���� */
#define ERROR -999 /* ��־���� */
ElementType DeQueue(Queue Q)
{
	Position tmp;
	ElementType FrontElem;

	if (IsEmpty(Q)) {
		printf("���п�");
		return ERROR;
	}
	else {
		FrontElem = GetFront(Q);
		tmp = Q->Front->Next;
		Q->Front->Next = tmp->Next;
		free(tmp);  /* �ͷű�ɾ�����ռ�  */
		if (Q->Front->Next == NULL) /* �����б�ֻ��һ��Ԫ�أ����Ӻ�Rearû��Ŀ�� */
			Q->Rear = Q->Front; /* ��ͷβָ���غϣ�������п� */
		return  FrontElem;
	}
}

/* ��� */
void EnQueue(ElementType x, Queue Q)
{
	Q->Rear->Next = (Position)malloc(sizeof(struct Node));
	Q->Rear = Q->Rear->Next; /* βָ����� */
	Q->Rear->Data = x;
	Q->Rear->Next = NULL;
}