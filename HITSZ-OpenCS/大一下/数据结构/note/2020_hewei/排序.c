#include<stdio.h>
#include<stdlib.h>

/* �����������򶼰����� */
/* �����ݶ�Ϊ���� �±�0������� �ܹ�n�� ��nλ������ */
typedef int ElementType;

/* �򵥲������� O(n^2) �ȶ� */
void InsertSort(ElementType A[], int n)
{
	int p, i;
	ElementType tmp;

	for (p = 1; p < n; p++)
	{	/* �±�0��Ԫ�ص���������� */
		tmp = A[p]; /* ȡ��δ���������еĵ�һ��Ԫ�� ���ٽ��������� */
		for (i = p; i > 0 && A[i - 1] > tmp; i--)/* ��ʱ����ѭ�� ���ٲ���ʱ����Ҫ��̽�� */
			A[i] = A[i - 1]; /*������������������Ԫ�رȽϲ����� */
		A[i] = tmp; /* �Ž����ʵ�λ�� */
	}
}

/* �������� */
void Swap(ElementType *x, ElementType *y)
{
	ElementType temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

/* ��ð������ O(n^2) �ȶ� */
void BubbleSort(ElementType A[], int n)
{
	int i;
	int flag = 1; /* ����Ƿ�����˽��� */
	while (flag)
	{
		flag = 0; /* ����û�н��� */
		for (i = 1; i < n; i++)
		{	/* ���±�1��ʼ ÿ������ǰ���Ƚ� */
			if (A[i] < A[i - 1])
			{
				Swap(&A[i], &A[i - 1]);
				flag = 1; /* �����˽��� ˵������û���� */
			}
		}
	}
}

/* ��ѡ������ O(n^2) ���ȶ� */
void SelectSort(ElementType A[], int n)
{
	int i, j;
	int index; /* ���δ���������е���С��λ�� */
	for (i = 0; i < n - 1; i++)
	{	/* ���һ�����±�n-2���±�n-1���� */
		index = i;
		for (j = i + 1; j < n; j++)
		{
			if (A[j] < A[index])
			{
				index = j;
			}
		}
		Swap(&A[i], &A[index]);
	}
}

/* ԭʼϣ������ ���ȶ� �ü������� */
void OriShellSort(ElementType A[], int n)
{
	int  D, P, i;
	ElementType tmp;

	for (D = n / 2; D > 0; D /= 2)
	{
		for (P = D; P < n; P++)
		{ /* �������� ���±�D�Ŀ�ʼ �൱����ͨ���±�1��ʼ */
			tmp = A[P];
			for (i = P; i >= D && A[i - D] > tmp; i -= D)
				A[i] = A[i - D];
			A[i] = tmp;
		}
	}
}

/* ����ϣ������ O(n^1.3) ���ȶ� ��Sedgewick�������� */
void ShellSort(ElementType A[], int n)
{
	int Si, D, P, i;
	ElementType tmp;
	/* ����ֻ�г�һС�������� */
	int Sedgewick[] = { 929, 505, 209, 109, 41, 19, 5, 1, 0 };

	for (Si = 0; Sedgewick[Si] >= n; Si++);
	/* ��ʼ������Sedgewick[Si]���ܳ����������г��� */

	for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si])
	{
		for (P = D; P < n; P++)
		{ /* �������� ���±�D�Ŀ�ʼ �൱����ͨ���±�1��ʼ */
			tmp = A[P];
			for (i = P; i >= D && A[i - D] > tmp; i -= D)
				A[i] = A[i - D];
			A[i] = tmp;
		}
	}
}

/* ������ O(nlogn) ���ȶ� */

void PercDown(ElementType A[], int p, int N)
{ /* ���˺��� ��N��Ԫ�ص���������A[p]Ϊ�����Ӷѵ���Ϊ���� */
	int Parent, Child;
	ElementType X;

	X = A[p]; /* ȡ��������ŵ�ֵ */
	for (Parent = p; (Parent * 2 + 1) < N; Parent = Child)
	{ /* ��Ϊͷ����±���0 ����2 * N + 1��ʾ������ */
		Child = Parent * 2 + 1;
		if ((Child != N - 1) && (A[Child] < A[Child + 1]))
		{	/* ����������һ��Child ������Child�Ҹ��� */
			Child++;  /* Childָ�������ӽ��Ľϴ��� */
		}
		if (X >= A[Child])
			break; /* �ҵ��˺���λ�� */
		else  /* ����X */
			A[Parent] = A[Child];
	}
	A[Parent] = X;
}

void HeapSort(ElementType A[], int N)
{ /* ������ N�ǽ������ �±�N����� */
	int i;

	for (i = N / 2 - 1; i >= 0; i--)
	{	/* �������� �����һ����Ҷ�ӽ�㿪ʼ */
		PercDown(A, i, N);
	}

	for (i = N - 1; i > 0; i--)
	{	/* ɾ�����Ѷ� */
		Swap(&A[0], &A[i]); /* ���Ѷ���������ĩ */
		PercDown(A, 0, i); /* ʣ���Ԫ���齨�¶� */
	}
}

/* �鲢���� - �ݹ�ʵ�� �ŵ㣺�ȶ� ȱ�㣺����ռ� */

/* L = �����ʼλ��, R = �ұ���ʼλ��, RightEnd = �ұ��յ�λ��*/
void Merge(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{ /* �������A[L]~A[R-1]��A[R]~A[RightEnd]�鲢��һ���������� */
	int LeftEnd, NumElements, Tmp;
	int i;

	LeftEnd = R - 1; /* ����յ�λ�� */
	Tmp = L;         /* �������е���ʼλ�� */
	NumElements = RightEnd - L + 1;

	while (L <= LeftEnd && R <= RightEnd)
	{
		if (A[L] <= A[R])
			TmpA[Tmp++] = A[L++]; /* �����Ԫ�ظ��Ƶ�TmpA */
		else
			TmpA[Tmp++] = A[R++]; /* ���ұ�Ԫ�ظ��Ƶ�TmpA */
	}

	while (L <= LeftEnd)
		TmpA[Tmp++] = A[L++]; /* ֱ�Ӹ������ʣ�µ� */
	while (R <= RightEnd)
		TmpA[Tmp++] = A[R++]; /* ֱ�Ӹ����ұ�ʣ�µ� */

	for (i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpA[RightEnd]; /* �������TmpA[]���ƻ�A[] */
}

void Msort(ElementType A[], ElementType TmpA[], int L, int RightEnd)
{ /* ���ĵݹ������� */
	int Center;

	if (L < RightEnd) {
		Center = (L + RightEnd) / 2;
		Msort(A, TmpA, L, Center);              /* �ݹ������ */
		Msort(A, TmpA, Center + 1, RightEnd);     /* �ݹ����ұ� */
		Merge(A, TmpA, L, Center + 1, RightEnd);  /* �ϲ������������� */
	}
}

void MergeSort(ElementType A[], int N)
{ /* �鲢���� */
	ElementType *TmpA;
	TmpA = (ElementType *)malloc(N*sizeof(ElementType));

	if (TmpA != NULL) {
		Msort(A, TmpA, 0, N - 1);
		free(TmpA);
	}
	else printf("�ռ䲻��");
}

/* �鲢���� - ѭ��ʵ�� */
/* ����Merge�����ڵݹ�汾�и��� */

/* length = ��ǰ�������еĳ���*/
void Merge_pass(ElementType A[], ElementType TmpA[], int N, int length)
{ /* �����鲢������������ */
	int i, j;

	for (i = 0; i <= N - 2 * length; i += 2 * length)
		Merge(A, TmpA, i, i + length, i + 2 * length - 1);
	if (i + length < N) /* ʣ�����1�� ������2�� ���й鲢 */
		Merge(A, TmpA, i, i + length, N - 1);
	else /* ���ֻʣ1������ */
		for (j = i; j < N; j++) TmpA[j] = A[j];
}

void Merge_Sort(ElementType A[], int N)
{
	int length;
	ElementType *TmpA;

	length = 1; /* ��ʼ�������г��� */
	TmpA = (ElementType *)malloc(N * sizeof(ElementType));
	if (TmpA != NULL) {
		while (length < N)
		{
			Merge_pass(A, TmpA, N, length);
			length *= 2;
			/* ���Merge�����и��ƹ��� ���´���Ͳ��� */
			/* �����������´�����Ա�֤������ż����Merge_pass ���������A���� */
			Merge_pass(TmpA, A, N, length);
			length *= 2;
		}
		free(TmpA);
	}
	else printf("�ռ䲻��");
}

/* �������� */

ElementType Median3(ElementType A[], int Left, int Right)
{ /* �����С�����ѡȡ��λ�������� */
	int Center = (Left + Right) / 2;
	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);
	/* ��ʱA[Left] <= A[Center] <= A[Right] */
	Swap(&A[Center], &A[Right - 1]); /* ����׼Pivot�ص��ұ�*/
									 /* ֻ��Ҫ����A[Left+1] �� A[Right-2] */
	return  A[Right - 1];  /* ���ػ�׼Pivot */
}

void Qsort(ElementType A[], int Left, int Right)
{ /* ���ĵݹ麯�� */
	int Pivot, Low, High;
	int Cutoff = 100; /* ��ֵ */

	if (Cutoff <= Right - Left) { /* �������Ԫ�س�ֶ࣬������� */
		Pivot = Median3(A, Left, Right); /* ѡ��׼ */
		Low = Left; High = Right - 1;
		while (1)
		{ /*�������бȻ�׼С���Ƶ���׼��ߣ�����Ƶ��ұ�*/
			while (A[++Low] < Pivot);
			while (A[--High] > Pivot);
			/* ע��˴����ҲҪͣ�»� ���������ͣ ����ȫ������ �ͻ�ʹ����һֱ���Ҷ� O(n^2) */
			if (Low < High) Swap(&A[Low], &A[High]);
			else break; /* Low����/����High ��ʾָ���Ѿ�Խλ */
		}
		Swap(&A[Low], &A[Right - 1]);   /* ����׼������ȷ��λ�� */
		Qsort(A, Left, Low - 1);    /* �ݹ������ */
		Qsort(A, Low + 1, Right);   /* �ݹ����ұ� */
	}
	else InsertSort(A + Left, Right - Left + 1); /* Ԫ��̫�٣��ü����� ����ݹ�ռ�� */
}

void QuickSort(ElementType A[], int N)
{ /* ͳһ�ӿ� */
	Qsort(A, 0, N - 1);
}

/* �������� */

/* ����Ԫ�������MaxDigit���ؼ��֣�����ȫ��ͬ����Radix */
#define MaxDigit 4
#define Radix 10

/* ͰԪ�ؽ�� */
typedef struct Node *PtrToNode;
struct Node {
	int key;
	PtrToNode next;
};

/* Ͱͷ��� */
struct HeadNode {
	PtrToNode head, tail;
};
typedef struct HeadNode Bucket[Radix];

int GetDigit(int X, int D)
{ /* Ĭ�ϴ�λD=1, ��λD<=MaxDigit */
	int d, i;

	for (i = 1; i <= D; i++) {
		d = X % Radix;
		X /= Radix;
	}
	return d;
}

void LSDRadixSort(ElementType A[], int N)
{	/* �������� - ��λ���� */
	/* ��λ�����Ҫ��λ ���Ŵ�λ�� ֻ���ٶ��������� �����ڲ��� */
	int D, Di, i;
	Bucket B;
	PtrToNode tmp, p, List = NULL;

	for (i = 0; i < Radix; i++) /* ��ʼ��ÿ��ͰΪ������ */
		B[i].head = B[i].tail = NULL;
	for (i = 0; i < N; i++)
	{	/* ��ԭʼ������������ʼ����List ���˳������ν */
		tmp = (PtrToNode)malloc(sizeof(struct Node));
		tmp->key = A[i];
		tmp->next = List;
		List = tmp; /* ��tmp����List���������м� */
	}
	/* ���濪ʼ���� */
	for (D = 1; D <= MaxDigit; D++)
	{ /* �����ݵ�ÿһλѭ������ */
		/* �����Ƿ���Ĺ��� */
		p = List;
		while (p) {
			Di = GetDigit(p->key, D); /* ��õ�ǰԪ�صĵ�ǰλ���� */
			tmp = p; p = p->next; /* ��List��ժ�� */
			/* ����B[Di]��Ͱβ �����Ԫ����tail */
			tmp->next = NULL;
			if (B[Di].head == NULL)
				B[Di].head = B[Di].tail = tmp;
			else {
				B[Di].tail->next = tmp;
				B[Di].tail = tmp;
			}
		}
		/* �������ռ��Ĺ��� */
		List = NULL;
		for (Di = Radix - 1; Di >= 0; Di--)
		{	/* ��ÿ��Ͱ��Ԫ��˳���ռ���List һ��Ҫ�ȷ������� */
			if (B[Di].head)
			{	/* ���Ͱ��Ϊ�� */
				/* ��Ͱ����List��ͷ */
				B[Di].tail->next = List;
				List = B[Di].head;
				B[Di].head = B[Di].tail = NULL; /* ���Ͱ */
			}
		}
	}
	/* ��List����A[]���ͷſռ� */
	for (i = 0; i < N; i++) {
		tmp = List;
		List = List->next;
		A[i] = tmp->key;
		free(tmp);
	}
}

void MSD(ElementType A[], int L, int R, int D)
{ /* ���ĵݹ麯��: ��A[L]...A[R]�ĵ�Dλ���������� */
	int Di, i, j;
	Bucket B;
	PtrToNode tmp, p, List = NULL;
	if (D == 0) return; /* �ݹ���ֹ���� */

	for (i = 0; i < Radix; i++) /* ��ʼ��ÿ��ͰΪ������ */
		B[i].head = B[i].tail = NULL;
	for (i = L; i <= R; i++) 
	{ /* ��ԭʼ������������ʼ����List */
		tmp = (PtrToNode)malloc(sizeof(struct Node));
		tmp->key = A[i];
		tmp->next = List;
		List = tmp;
	}
	/* �����Ƿ���Ĺ��� */
	p = List;
	while (p) {
		Di = GetDigit(p->key, D); /* ��õ�ǰԪ�صĵ�ǰλ���� */
		tmp = p; p = p->next; /* ��List��ժ�� */
		/* ����B[Di]��Ͱͷ �����Ԫ����head */
		if (B[Di].head == NULL) B[Di].tail = tmp;
		tmp->next = B[Di].head;
		B[Di].head = tmp;
	}
	/* �������ռ��Ĺ��� */
	i = j = L; /* i, j��¼��ǰҪ�����A[]�����Ҷ��±� */
	for (Di = 0; Di < Radix; Di++)
	{ /* ����ÿ��Ͱ */
		if (B[Di].head)
		{ /* ���ǿյ�Ͱ��Ͱ����A[], �ݹ����� */
			p = B[Di].head;
			while (p) {
				tmp = p;
				p = p->next;
				A[j++] = tmp->key;
				free(tmp);
			}
			/* �ݹ�Ը�Ͱ����������, λ����1 */
			MSD(A, i, j - 1, D - 1);
			i = j; /* Ϊ��һ��Ͱ��Ӧ��A[]��� */
		}
	}
}

void MSDRadixSort(ElementType A[], int N)
{	/* �������� - ��λ����   ͳһ�ӿ� */
	/* ��λ������Ҫ��λ ��λ�������� ���ڲ����� ����ض����� */
	MSD(A, 0, N - 1, MaxDigit); /* ���DҪ�����λ */
}