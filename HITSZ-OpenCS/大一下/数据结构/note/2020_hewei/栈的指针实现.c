#include<stdio.h>
#define true 1
#define false 0
typedef int ElementType; /* �����������ݶ�Ϊint */
typedef struct SNode *PtrToSNode;
struct SNode {
	ElementType Data;
	PtrToSNode Next;
};
typedef PtrToSNode Stack; /* רָͷ��� */
/* ָ��ʵ��ջʱ��top��ͷ��㴦������ɾ������Ϊɾ��Ҫ֪����һ���λ�� */

/* ������ջ */
Stack CreateStack()
{/* ����һ����ջ��ͷ��㣬���ظý��ָ�� */
	Stack S;
	S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL; /* ͷ��㲻������� */
	/* ���S->Next->data�Ŵ���׸����� */
	return S;
}

/* �ж϶�ջS�Ƿ�Ϊ�գ����Ƿ���true�����򷵻�false */
int IsEmpty(Stack S)
{
	return (S->Next == NULL); /* ͷ�����һ��ΪNULL��� */
}

/* ѹ��Ԫ�� */
int Push(Stack S, ElementType x)
{ /* ���ÿ���ջ�� */
	PtrToSNode TmpCell; /* �ֲ�������ʱָ��ָ���½�� */
	TmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
	TmpCell->Data = x;
	TmpCell->Next = S->Next;
	S->Next = TmpCell;
	return true;
}

/* ����Ԫ�� */
#define ERROR -999 /*�����ʶ����ElementType����*/
ElementType Pop(Stack S)
{ 
	PtrToSNode FirstCell; /* ָ��ջ��Ԫ�� */
	ElementType TopElem;

	if (IsEmpty(S)) {
		printf("��ջ��");
		return ERROR;
	}
	else {
		FirstCell = S->Next;
		TopElem = FirstCell->Data;
		S->Next = FirstCell->Next;
		free(FirstCell); /* �ͷ�ԭջ��Ԫ�ؿռ� */
		return TopElem;
	}
}

/* ʮ��������ת��Ϊ�˽������ */
void Octal(int n)
{
	Stack S = CreateStack();
	while (n)
	{
		Push(S, n % 8);
		n /= 8;
	}
	while (!IsEmpty(S))
	{
		printf("%d", S->Next->Data);
		Pop(S);
	}
}



/* ������������ */
int main()
{
	int n = 0;
	printf("Input:");
	scanf("%d", &n);
	Octal(n);
	return 0;
}