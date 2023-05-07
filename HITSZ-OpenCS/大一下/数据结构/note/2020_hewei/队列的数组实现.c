#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0
typedef int ElementType; /* �����������ݶ�Ϊint */
typedef int Position;
struct QNode {
	ElementType *Data;     /* �洢Ԫ�ص�������׵�ַ */
	Position Front, Rear;  /* ���е�ͷ��βָ�� */
	int MaxSize; /* ����������� ��ʵ����ΪMaxsize-1 ����ѭ���������ֿ���*/
};
typedef struct QNode *Queue;

/* ��ʼ������ */
Queue CreateQueue(int MaxSize)
{
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
	Q->Front = Q->Rear = 0;
	Q->MaxSize = MaxSize;
	return Q;
}

/* �ж϶����� ͷβָ�����һ��λ�� ͷָ��ָ�Ŀռ���Զ���� */
int IsFull(Queue Q)
{
	return ((Q->Rear + 1) % Q->MaxSize == Q->Front);
}

/* ��� */
int EnQueue(Queue Q, ElementType x)
{
	if (IsFull(Q)) {
		printf("������");
		return false;
	}
	else {
		Q->Rear = (Q->Rear + 1) % Q->MaxSize;
		Q->Data[Q->Rear] = x;
		return true;
	}
}

/* �ж϶��п� ����ͷβָ���غ� ��ָ��ͬһ�����ÿռ� */
int IsEmpty(Queue Q)
{
	return (Q->Front == Q->Rear);
}

/* ���� */
#define ERROR -999 /* ��־���� */
ElementType DeQueue(Queue Q)
{
	if (IsEmpty(Q)) {
		printf("���п�");
		return ERROR;
	}
	else {
		Q->Front = (Q->Front + 1) % Q->MaxSize; /* �ӿ�ͷ���ָ����һλ�� */
		return  Q->Data[Q->Front]; /* ��ʱ��Frontָ�ľ��ǵ�һ������ */
	}
}