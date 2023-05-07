#include<stdio.h>
#define true 1
#define false 0
typedef char ElementType; /* �����������ݶ�Ϊchar */
typedef int Position;
struct SNode {
	ElementType *Data; /* �洢Ԫ�ص����� Data��ָ�� */
	Position Top;      /* ջ����ʶ�� */
	int MaxSize;       /* ��ջ�ܳ� ����[0]����� ʵ������ΪMaxSize-1 */
};
typedef struct SNode *Stack;

/* ������ջ */
Stack CreateStack(int MaxSize)
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
	S->Top = 0;
	S->MaxSize = MaxSize;
	return S;
}

/* ��ԭ��ջ */
void MakeNull(Stack S)
{
	S->Top = 0;
}

/* ����Ƿ�ջ�� */
int IsFull(Stack S)
{
	return (S->Top == S->MaxSize - 1); /* �ﵽʵ������ */
}

/* ѹ��Ԫ�� */
int Push(Stack S, ElementType x)
{
	if (IsFull(S)) {
		printf("��ջ��");
		return false;
	}
	else {
		S->Data[++(S->Top)] = x;
		return true;
	}
}

/* ����Ƿ�ջ�� */
int IsEmpty(Stack S)
{
	return (S->Top == 0);
}

/* ����Ԫ�� */
#define ERROR -999 /* �����־����ElementType���� */
ElementType Pop(Stack S)
{
	if (IsEmpty(S)) {
		printf("��ջ��");
		return ERROR; /* ERROR��ElementType������ֵ����־���� */
	}
	else
		return (S->Data[(S->Top)--]);
}

/* ����׺���ʽת��Ϊ��׺���ʽ */
void Change(char str[],Stack S)
{
	int i;
	ElementType e;
	for (i = 0; str[i] != '\0'; i++)  /* ������׺���ʽ�е��ַ� */
	{
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
		{   /* ���Ϊ��ĸ����ֱ����� */
			printf("%c", str[i]);
		}
		if (str[i] == "(")
		{	/* ����������ֱ����ջ */
			Push(S, str[i]);
		}
		if (str[i] == ")")
		{	/* ���������Ŵ����ֹ�����ڵ�һ������ */
			while (S->Data[S->Top] != "(")
			{
				e = Pop(S);
				printf("%c", e);
			}
			Pop(S); /* ����ٰ������ŵ��� */
		}
		if (str[i] == '+' || str[i] == '-')  
		{   /*���Ϊ�ӺŻ���ţ����ж�ջ��Ԫ���Ƿ�Ϊ�˳� */
			while (S->Data[S->Top] == '*' || S->Data[S->Top] == '/')
			{   /* ����ʱջ��Ϊ�˳��������ջ��Ԫ�� */
				e = Pop(S);   
				printf("%c", e);  
			}
			Push(S, str[i]);
		}
		if (str[i] == '*' || str[i] == '/') 
		{   /* ���Ϊ�˳�����ֱ����ջ */
			Push(S, str[i]);
		}
	}
	while (S->Top != 0)    //��ջ��Ϊ�գ���ջ�е�Ԫ��ȫ�����
	{
		e = Pop(S);
		printf("%c", e);
	}
}

/* ������������ */
int main()
{
	char str[100];
	Stack S = CreateStack(100);
	scanf("%s", str);
	Change(str, S);
	return 0;
}