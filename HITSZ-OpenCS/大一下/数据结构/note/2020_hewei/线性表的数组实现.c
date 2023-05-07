#include<stdio.h>
#define true 1
#define false 0
#define MAXSIZE 100
typedef int ElementType; /* �����������ݶ�Ϊint */
typedef int Position; /* ��������λ�ü����� */
struct LNode {
	ElementType Data[MAXSIZE];
	Position Last;
};
typedef struct LNode *List;

/* ��ʼ�� */
List MakeEmpty()
{
	List L;
	L = (List)malloc(sizeof(struct LNode));
	L->Last = 0; /* ��һ��λ�ò�������� */
	return L;
}

/* �ÿ� */
void Clear(List L)
{
	L->Last = 0;
}

/* ���� */
#define ERROR -1
Position Find(List L, ElementType X)
{
	Position i = 1;
	while (i <= L->Last && L->Data[i] != X)
		i++;
	if (i > L->Last)  return ERROR; /* ���û�ҵ������ش�����Ϣ */
	else  return i;  /* �ҵ��󷵻ص��Ǵ洢λ�� */
}

/* ���� */
int Insert(List L, ElementType X, Position p)
{ /* ��L��ָ��λ��Pǰ����һ����Ԫ��X */
	Position i;
	if (L->Last == MAXSIZE - 1) {
		/* ��ռ����������ܲ��� */
		printf("����");
		return false;
	}
	else if (p<1 || p>L->Last + 1) { /* ������λ�õĺϷ��� */
		printf("λ�ò��Ϸ�");
		return false;
	}
	else {
		for (i = L->Last; i >= p; i--)
			L->Data[i + 1] = L->Data[i]; /* ��λ��P���Ժ��Ԫ��˳������ƶ� */
		L->Data[p] = X;  /* ��Ԫ�ز��� */
		L->Last++;       /* Last����1��ָ�����Ԫ�� */
		return true;
	}
}

/* ɾ�� */
int Delete(List L, Position p)
{ /* ��L��ɾ��ָ��λ��P��Ԫ�� */
	Position i;
	if (p<1 || p>L->Last) { /* ���ձ�ɾ��λ�õĺϷ��� */
		printf("λ��%d������Ԫ��", p);
		return false;
	}
	else {
		L->Last--; /* Last��ָ�����Ԫ�� */
		for (i = p; i <= L->Last; i++)
			L->Data[i] = L->Data[i + 1]; /* ��λ��P+1���Ժ��Ԫ��˳����ǰ�ƶ� */
		return true;
	}
}

/* ȡֵ */
ElementType Retrieve(Position p, List L)
{
	if (p > L->Last) {
		printf("ָ��Ԫ�ز�����");
		return false;
	}
	else {
		return(L->Data[p]);
	}
}

/* ǰ��λ�� */
Position Pre(Position p, List L)
{
	if ((p <= 1) || (p > L->Last)) {
		printf("ǰ��Ԫ�ز�����");
		return false;
	}
	else
		return p - 1;
}

/* ���λ�� */
Position Next(Position p, List L)
{
	if ((p < 1) || (p >= L->Last)) {
		printf("���Ԫ�ز�����");
		return false;
	}
	else
		return p + 1;
}

/* ��ͷλ�� */
Position First(List L)
{
	return 1;
}

/* ����λ�� */
Position End(List L)
{
	return L->Last + 1; /* ���һ��Ԫ�صĺ�һλ */
}

/* �ж���������ͬ */
int Same(ElementType x, ElementType y)
{
	if (x == y) /* ���������͸ı�ʱ��������Ӧ�ıȽϷ��� */
		return true;
	else
		return false;
}

/* ȥ������ֵΪd��Ԫ�� */
void DeleteSame(List L, ElementType d)
{
	Position p;
	p = First(L);
	while (p != End(L)) { /* ����ֱ��pָ�����һ��Ԫ�صĺ�һλ */
		if (Same(Retrieve(p, L), d))
			Delete(p, L);
		else
			p = Next(p, L);
	}
}

/* �����������ϲ�����������ʹ���ǵĺ��������������� */
int FindPair(List L, ElementType x, ElementType *a,ElementType *b)
{
	int length = L->Last;
	if (length < 2) /* ���������ж� */
		return false;
	else if (L->Data[1] >= x) /* ���������ж� */
		return false;
	int i = 1;
	while (i < length) /* ��β�������м�ƽ�ֱ���غ� */
	{
		if (L->Data[i] + L->Data[length] == x)
		{
			*a = L->Data[i];
			*b = L->Data[length];
			return true; /* �ɹ��ҵ� ��ָ���򷵻���������ֵ */
		}
		else if (L->Data[i] + L->Data[length] >x)
			length--;
		else
			i++;
	}
	return false;
}

/* ����͵ط��� */
void Reverse(List L)
{
	int length = L->Last;
	int i;
	ElementType temp;
	for (i = 0; i < length / 2; i++)
	{	/* �������� �ܹ�����length/2�� ����ʱ�м�Ԫ�ز��� */
		temp = L->Data[i + 1];
		L->Data[i + 1] = L->Data[length - i];
		L->Data[length - i] = temp;
	}
}

/* ����[x,y]���־͵ط��� */
void SectionReverse(List L, Position x, Position y)
{
	int i;
	ElementType temp;
	for (i = 0; i < (y - x + 1) / 2; i++)
	{	/* �������� �ܹ�����(y - x + 1)/2�� ����ʱ�м�Ԫ�ز��� */
		temp = L->Data[x + i];
		L->Data[x + i] = L->Data[y - i];
		L->Data[y - i] = temp;
	}
}

/* ����ѭ����λ ������Ԫ������ѭ���ƶ�kλ ʱ�临�Ӷ�O(n) ��������������� */
void Kshift(List L, int k)
{
	int length = L->Last;
	k %= length; /* ȡģ��ֹk�������� */

	SectionReverse(L, 1, length - k);
	SectionReverse(L, length - k + 1, length);
	Reverse(L);
}

/* ��������ϲ� �ұ������� �����µ����� */
List Merge(List La, List Lb)
{
	List Lc = MakeEmpty();
	Position pa = First(La);
	Position pb = First(Lb);
	while (pa <= La->Last && pb <= Lb->Last)
	{	/* ��С�����Ȳ��� */
		if (La->Data[pa] <= Lb->Data[pb])
			Insert(Lc, La->Data[pa++], End(Lc));
		else
			Insert(Lc, Lb->Data[pb++], End(Lc));
	}
	while(pa <= La->Last) /* ����ʣ�ಿ�� */
		Insert(Lc, La->Data[pa++], End(Lc));
	while(pb <= Lb->Last)
		Insert(Lc, Lb->Data[pb++], End(Lc));

	return Lc;
}