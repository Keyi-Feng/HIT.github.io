#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define true 1
#define false 0
typedef char ElementType; /* �����������ݶ�Ϊchar */
typedef struct TNode *BinTree;
struct TNode { /* ����㶨�� */
	ElementType Data; /* ������� */
	BinTree Left;     /* ָ�������� */
	BinTree Right;    /* ָ�������� */
};

/* ��ʼ������ �����Ǹ���Ҳ���������� ���ڵ�ռ�ɴ������ */
BinTree MakeBT(ElementType data)
{
	BinTree BT;
	BT = (BinTree)malloc(sizeof(struct TNode));
	BT->Data = data; /* ֱ�Ӵ����� ����ݹ���� */
	BT->Left = NULL;
	BT->Right = NULL;
	return BT;
}

/* �ж����� */
int IsEmpty(BinTree BT)
{	/* ֱ�Ӷ�BT�����ж� ����ݹ���� */
	if (BT == NULL) 
		return 1;
	else
		return 0;
}

/* ��������ͷ��������ռ� */
void DestroyBT(BinTree BT)
{	/* ֻ�к���������������ͷŵ�ȫ���ռ� ������ʧ */
	if (BT) {
		DestroyBT(BT->Left);
		DestroyBT(BT->Right);
		free(BT);
	}
}

/* �ݹ�������� */
void InorderTraversal(BinTree BT)
{
	if (BT) {
		InorderTraversal(BT->Left);
		/* �˴������BT���ķ��ʾ��Ǵ�ӡ���� */
		printf("%c ", BT->Data); /* ��������Ϊ�ַ��� */
		InorderTraversal(BT->Right);
	}
}

/* �ݹ�������� */
void PreorderTraversal(BinTree BT)
{
	if (BT) {
		printf("%c ", BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}

/* �ݹ������� */
void PostorderTraversal(BinTree BT)
{
	if (BT) {
		PostorderTraversal(BT->Left);
		PostorderTraversal(BT->Right);
		printf("%c ", BT->Data);
	}
}

/* �ݹ�˫����� �ȷ��ʽ�� ��˫����������� �ٷ���һ�� ��˫����������� */
void DoubleorderTraversal(BinTree BT)
{
	if (BT) {
		printf("%c ", BT->Data);
		DoubleorderTraversal(BT->Left);
		printf("%c ", BT->Data);
		DoubleorderTraversal(BT->Right);
	}
}

/** ������� ���ö��� **/

struct QNode {
	BinTree *Data;     /* �洢�����ָ���������׵�ַ */
	int Front, Rear;  /* ���е�ͷ��βָ�� */
	int MaxSize; /* ����������� ��ʵ����ΪMaxsize-1 ����ѭ���������ֿ���*/
};
typedef struct QNode *Queue;

Queue CreateQueue(int MaxSize)
{   /* ��ʼ������ */
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Data = (BinTree *)malloc(MaxSize * sizeof(BinTree));
	Q->Front = Q->Rear = 0;
	Q->MaxSize = MaxSize;
	return Q;
}

int IsQueueEmpty(Queue Q)
{   /* �ж϶��п� ����ͷβָ���غ� ��ָ��ͬһ�����ÿռ� */
	return (Q->Front == Q->Rear);
}

BinTree DeQueue(Queue Q)
{   /* ���� �����ж϶��п� ��Ϊѭ�������Ѿ����� */
	Q->Front = (Q->Front + 1) % Q->MaxSize;
	return  Q->Data[Q->Front];
}

int EnQueue(Queue Q, BinTree x)
{	/* ��� ��Ҫ���Ƕ����� */
	if ((Q->Rear + 1) % Q->MaxSize == Q->Front) {
		printf("������"); /* ��ʾ��������ռ䲻�� */
		return 0;
	}
	else {
		Q->Rear = (Q->Rear + 1) % Q->MaxSize;
		Q->Data[Q->Rear] = x;
		return 1;
	}
}

void LevelorderTraversal(BinTree BT)
{
	Queue Q;
	BinTree T;

	if (!BT) return; /* ���ǿ�����ֱ�ӷ��� */

	Q = CreateQueue(100); /* �����ն���Q */
	EnQueue(Q, BT);
	while (!IsQueueEmpty(Q)) {
		T = DeQueue(Q);
		printf("%c ", T->Data); /* ����ȡ�����еĽ�� */
		if (T->Left)   EnQueue(Q, T->Left);
		if (T->Right)  EnQueue(Q, T->Right);
	}
}	
/*  �������ò������ ��һά�����Ϊ�ṹ������ 
	���ɴ洢ÿ��������ڵĲ��� ��һ������Ϊ1 EnQueue����ʱ��1 
	���ɴ洢ÿ������˫�� EnQueue����ʱ˳���¼˫�׽�� 
	���ɴ洢ÿ�����ĳ��� �ɹ�EnQueueһ�ξ���1 ���2 
	�����������飨�����Ѿ������еĽṹ�壩�����ҵ������� �������
	����ʱ����level[i]++ �������ÿһ��Ŀ��	
*/

/** �ǵݹ�������� ����ջ **/

struct SNode {
	BinTree *Data; /* �洢�����ָ���������׵�ַ Data��ָ�� */
	int Top;      /* ջ����ʶ�� */
	int MaxSize;  /* ��ջ�ܳ� ����[0]����� ʵ������ΪMaxSize-1 */
};
typedef struct SNode *Stack;

Stack CreateStack(int MaxSize)
{	/* ������ջ */
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (BinTree *)malloc(MaxSize * sizeof(BinTree));
	S->Top = 0;
	S->MaxSize = MaxSize;
	return S;
}

int Push(Stack S, BinTree x)
{	/* ѹ��Ԫ�� ��Ҫ����ջ�� */
	if (S->Top == S->MaxSize - 1) {
		printf("��ջ��"); /* ��ʾջ����ռ䲻�� */
		return 0;
	}
	else {
		S->Data[++(S->Top)] = x;
		return 1;
	}
}

BinTree Pop(Stack S)
{	/* ��ջ �����ж�ջ�� ��Ϊѭ�������Ѿ����� */
	return (S->Data[(S->Top)--]);
}

void InOrderStackTraversal(BinTree BT)
{
	Stack S;
	BinTree T = BT;

	if (!BT) return; /* ���ǿ�����ֱ�ӷ��� */

	S = CreateStack(100); /* ������ջS */
	do{
		while (T != NULL)
		{	/* һֱ��ȡ������ֱ�������½�NULL */
			Push(S, T);
			T = T->Left;
		}
		if (S->Top != 0)
		{	/* ��ջ�л��н�� */
			T = Pop(S); /* �������������һ��㵯�� */
			printf("%c ", T->Data); /* ��� */
			T = T->Right; /* �ٿ������� */
		}
	} while ((S->Top != 0) || (T != NULL));
}

/** �ǵݹ�������� ����ջ **/
void  PreOrderStackTraversal(BinTree BT)
{
	Stack S;
	BinTree T = BT;

	if (!BT) return; /* ���ǿ�����ֱ�ӷ��� */

	S = CreateStack(100); /* ������ջS */
	do{
		while (T != NULL)
		{
			printf("%c ", T->Data); /* ��� */
			Push(S, T);
			T = T->Left; /* һֱ��ȡ������ֱ�������½�NULL */
		}
		if (S->Top != 0)
		{
			T = Pop(S); /* �������������һ��㵯�� */
			T = T->Right; /* �ٿ������� */
		}
	} while ((S->Top != 0) || (T != NULL));
}

/** �ǵݹ������� ����ջ **/
void  PostOrderStackTraversal(BinTree BT)    //����������ǵݹ�
{
	Stack S;
	BinTree T = BT;

	if (!BT) return; /* ���ǿ�����ֱ�ӷ��� */

	BinTree p;
	int b;
	S = CreateStack(100); /* ������ջS */
	do {
		while (T != NULL)
		{
			Push(S, T);
			T = T->Left; /* һֱ��ȡ������ֱ�������½�NULL */
		}
		p = NULL;
		b = 1; /* ���������������� */
		while ((S->Top != 0) && b)
		{	/* ��ջ�л���Ԫ�� ��ջ��ָ�������������ڻ��ѷ��� */
			T = S->Data[S->Top];
			if (T->Right == p) 
			{	/* pһ��ʼ��NULL ��ʾ��̽���������ֲ����� */
				printf("%c ", T->Data); /*������������ �������� */
				Pop(S); /* �����Ѿ����ʹ��ĸ���� */
				p = T; /* �������Ѿ����ʹ� ��p��� �����´���̽ */
			}
			else
			{	/* ������δ̽�� �� �������Ѿ���ȫ̽���� */
				T = T->Right; /* �ٿ������� */
				b = 0; /* ����������δ̽���� �����µ�����ѭ�� */
			}
		}
	} while (S->Top != 0);
}

/* ��֪��#���գ����������� ���������� */
BinTree PreCreate()
{
	BinTree BT;
	ElementType ch;
	while (getchar() != '\n');
	scanf("%c", &ch);
	if (ch == '#')
		BT = NULL; /* ֱ���ÿ� ��Ϊ�����ÿ�ͷ��� ��һ������Ҫ������� */
	else
	{
		BT = MakeBT(ch);
		if (!BT) exit(0); /* ���벻���ռ� ֱ�ӽ������� */
		BT->Left = PreCreate();
		BT->Right = PreCreate(); /* �ݹ���ú��� ������������ */
	}
	return BT;
}

/* �������Ľ����ʴ��� */
BinTree QACreate(int flag)
{	
	BinTree BT = NULL;
	ElementType ch;
	if (flag == 0)
	{	/* ���ε��ú���ʱ �������Ϊ0 �����Ӧ��ʾ */
		printf("����㣺");
	}
	scanf(" %c", &ch);
	while (getchar() != '\n');
	if (ch != '#')
	{	/* �ǿ� �ݹ���� */
		BT = MakeBT(ch);
		printf("%c�������ǣ�", BT->Data);
		BT->Left = QACreate(1);
		printf("%c���Һ����ǣ�", BT->Data);
		BT->Right = QACreate(1);
	}
	return BT;
}

/* �ݹ����������������� ���ò������ */
int Depth(BinTree BT)
{
	int ldepth, rdepth; /* ����Ҫ����ֵ */
	if (BT == NULL)
		return 0; /* �����������ݹ鵽Ҷ�ӽ���NULL���� */
	else
	{	/* �ǿ� */
		ldepth = Depth(BT->Left);
		rdepth = Depth(BT->Right); /* �ݹ�������������� */
		if (ldepth > rdepth) /* ȡ�����+1 Ϊ�Լ������������ */
			return ldepth + 1;
		else
			return rdepth + 1;
	}
}

/* �ж����Ŷ������Ƿ�ȼ� */
int Equal(BinTree BT1, BinTree BT2)
{
	int x = 0; 
	if (IsEmpty(BT1) && IsEmpty(BT2))
	{	/* ����������� �ض���� */
		x = 1;
	}
	else if (!IsEmpty(BT1) && !IsEmpty(BT2))
	{	/* �ų���һ��һ�е���� �������ǿ�ʱ */
		if (BT1->Data == BT2->Data)
		{	/* ���ж�������� */
			if (Equal(BT1->Left, BT2->Left))
			{	/* �������ȼ� ������ж�����Ų����ֵ�� �򻯴��� */
				x = Equal(BT1->Right, BT2->Right);
			}
		}
	}
	return x;
}

/* ��֪����+���� ���������� */
BinTree PreInOrderCreate(ElementType a[], ElementType b[], int r1, int l1, int r2, int l2)
{	//�ĸ������ֱ�Ϊ�������������ʼλ�úͽ���λ�ú������������ʼλ�úͽ���λ��
	int i;
	if (r1 > l1)//����Ѿ�����Ҷ�ӣ�����
		return NULL;
	
	for (i = r2; b[i] != a[r1]; ++i);//�ҵ����ڵ�����������е�λ��
	BinTree BT = MakeBT(a[r1]);
	BT->Left = PreInOrderCreate(a, b, r1 + 1, l1 - l2 + i, r2, i - 1);//�ݹ����������ĺ��������r1+1��ָ�Ѹ�ȥ��֮���λ��
	BT->Right = PreInOrderCreate(a, b, l1 - l2 + i + 1, l1, i + 1, l2);//�ݹ����������ĺ������
	return BT;
}
/* ��֪����+���� ���������� */

/* ��֪��#�������� ���������� */
/* �ж�һ������������Ƿ�Ϊ�������� */
int isFull(BinTree BT)
{
	struct Node
	{
		BinTree bt;
		int level;     
	} Q[100]; /* ͨ������ʵ�ּ򵥶��� ��������ѭ������ ����ᶪʧ���� */ 
     
	if (BT == NULL)
		return true;

	int rear = 0, front = 0; /* ��0�����Ҳ������� �غ�ʱ��ʾ��һ��Ԫ�� */
	Q[rear].bt = BT;
	Q[rear].level = 1;
	int tot = 1; /* �ܽ���� �Ѿ������˸���� */

	while (rear >= front) /* ֻ�е�front����rear�Ž��� */
	{
		if (Q[front].bt->Left)
		{
			tot++;
			Q[++rear].bt = Q[front].bt->Left;
			Q[rear].level = Q[front].level + 1;
		}
		if (Q[front].bt->Right)
		{
			tot++;
			Q[++rear].bt = Q[front].bt->Right;
			Q[rear].level = Q[front].level + 1;
		}
		front++;  /* ���� */
	}
	int deep = Q[rear].level;; /* ����� rear��Ϊ���һ���ĳ����� */
	printf("\ndeep=%d, tot=%d\n", deep, tot);
	return 1 << deep == tot + 1; /* λ����ʵ��2^n */
}

/* �ж�һ������������Ƿ�Ϊ��ȫ������ Ҳ�ǲ������ ������NULL �������ȫ��������NULL�ض��������� */
/* ����������������Ƚ�㣨�����ý���·����*/
/* ��������洢�Ķ�����ת����������ȫ�������洢�������� #�ű�ʾ�ս�� */
/* ���������� */
int main()
{
	int i;
	char a[30];
	char b[30];
	BinTree BT;
	scanf("%s %s", a, b);
	int l = strlen(a);
	BT = PreInOrderCreate(a, b, 0, l - 1, 0, l - 1);
	PostorderTraversal(BT);
	return 0;
}
/* �����������Ľ����������ɾ�� */
/* �������Ӧ�� */