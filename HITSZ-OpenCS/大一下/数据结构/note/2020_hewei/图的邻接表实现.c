/* ͼ���ڽӱ��ʾ�� Ĭ��Ϊ�����Ȩͼnet */
#include<stdio.h>
#include<stdlib.h>

#define MaxVertexNum 100    /* ��󶥵�����Ϊ100 */
typedef int Vertex;         /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;     /* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;      /* ����洢������������Ϊ�ַ��� */

/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode {
	Vertex V1, V2;      /* �����<V1, V2> */
	WeightType Weight;  /* Ȩ�� */
};
typedef PtrToENode Edge;

/* �ڽӵ�Ķ��� */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;         /* �ڽӵ��±� ��ֱ����Data �����޸�ֵ */
	WeightType Weight;   /* ��Ȩ�� */
	PtrToAdjVNode Next;  /* ָ����һ���ڽӵ��ָ�� */
};

/* �����ͷ���Ķ��� */
typedef struct Vnode {
	PtrToAdjVNode FirstEdge;  /* �߱�ͷָ�� �׸��ڽӵ� */
	DataType Data;            /* �涥������� */
							  /* ע�⣺�ܶ�����£����������ݣ���ʱData���Բ��ó��� */
} AdjList;	/* AdjList���ڽӱ����� */

/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;     /* ������ */
	int Ne;     /* ����   */
	AdjList G[MaxVertexNum];  /* �ڽӱ� ����˳��洢 �����±꼴�����±� ��0��ʼ */
};
typedef PtrToGNode LGraph; /* ���ڽӱ�ʽ�洢��ͼ���� */


/* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
LGraph CreateGraph(int VertexNum)
{
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode)); /* ����ͼ */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* ��ʼ���ڽӱ�ͷָ�� */
	/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

/* ���뵥���� ��Ҫ����Edge�ṹ��ָ�� */
void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;

	/* ����� <V1, V2> */
	/* ΪV2�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	/* ��V2���뵽V1�ı�ͷ */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	/* ��������ͼ����Ҫ����� <V2, V1> */
	/* ΪV1�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	/* ��V1���뵽V2�ı�ͷ */
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

/* ����ͼ����ֵ */
LGraph BuildGraph()
{
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	printf("Input the vextex num: ");
	scanf("%d", &Nv);   /* ���붥����� */
	Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */

	printf("Input the edge num: ");
	scanf("%d", &(Graph->Ne));   /* ������� */
	if (Graph->Ne != 0)
	{	/* ����б� */
		E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */
												/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӱ� */
		for (i = 0; i < Graph->Ne; i++) {
			printf("Input an edge as (V1 V2 Weight): ");
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
			InsertEdge(Graph, E);
		}
		free(E); /* �ͷ���ʱ�߽��ռ� */
	}

	/* ������������ݵĻ����������� */
	for (V = 0; V < Graph->Nv; V++)
	{
		printf("Input the vextex data in char: ");
		scanf(" %c", &(Graph->G[V].Data));
	}

	return Graph;
}

/* ����ͼG���붥��V�ڽӵĵ�һ���ڽӵ��±� -1Ϊû���ڽӵ� */
Vertex FirstAdjV(LGraph Graph, Vertex V)
{
	if (Graph->G[V].FirstEdge)
		return Graph->G[V].FirstEdge->AdjV; /* �ҵ� */
	else /* ��һ���ڽӵ����NULL */
		return -1; /* û�ҵ� */
}

/* ����ͼG���붥��V�ڽӵ���W����һ���ڽӵ� -1Ϊ����һ���ڽӵ� */
Vertex NextAdjV(LGraph Graph, Vertex V, Vertex W)
{
	PtrToAdjVNode P;
	P = Graph->G[V].FirstEdge; /* ����ָ��ָ���ڽӱ�ͷ */
	while (P->AdjV != W)
		P = P->Next; /* ��ѭ���ҵ�W���ڵĻ� ��ʱ��Ĭ��W��ȷ */
	if (P->Next) /* ����һ���ڽӵ� */
		return P->Next->AdjV; /* �ҵ� */
	else
		return -1; /* û�ҵ� */

}

/* ������������ݹ麯�� */
void  DFStravel(LGraph Graph, Vertex V, int* visited)
{
	visited[V] = 1; /* ��Ƿ��ʹ� */
	printf("%c ", Graph->G[V].Data);

	Vertex W;
	for (W = FirstAdjV(Graph, V); W != -1; W = NextAdjV(Graph, V, W))
	{	/* �ö���������ڽӵ㶼Ҫ���� */
		if (!visited[W]) /* ������ڽӵ�δ���ʹ� */
			DFStravel(Graph, W, visited); /* ��ݹ���� ����� */
	}
}

/* ��������������㷨 */
void DFS(LGraph Graph)
{
	Vertex V;
	int *visited = (int *)malloc(Graph->Nv * sizeof(int)); /* ��̬���������� */
	/* �˴�����������count�������ż����� */
	/* �ڵݹ�ʱ���������� dnf[V]=count ��¼ÿ��������ʵĴ��� */

	printf("DFS: ");
	for (V = 0; V < Graph->Nv; V++)
	{	/* ��������ʼ�� Ҳ����memset */
		visited[V] = 0;
	}
	for (V = 0; V < Graph->Nv; V++)
	{	/* ���±�Ϊ0�Ķ��㿪ʼ���� ÿ��ѭ���߹��ı�Ϊһ�������� */
		if (!visited[V]) /* ѭ����ʵ�ʴ���Ϊͼ����ͨ������ */
			DFStravel(Graph, V, visited); /* ���õݹ麯�� */
	}

	free(visited); /* �ͷŶ�̬�ռ� */
}

/* ��������������㷨 ���ö��� */
void BFS(LGraph Graph)
{
	Vertex V;
	int *visited = (int *)malloc(Graph->Nv*sizeof(int)); /* ��̬���������� */
	for (V = 0; V < Graph->Nv; V++)
	{	/* ��������ʼ�� Ҳ����memset */
		visited[V] = 0;
	}

	printf("BFS: ");
	Vertex *VexQ = (Vertex *)malloc(Graph->Nv * sizeof(Vertex));
	int front = 0, rear = 0; /* ����ͷβλ�ñ�ʶ�غ� */
	/* ע�� ��ʱ�Ķ��в���ѭ������ ��������ͬ��С�ռ���������н�� */
	/* �����еĽ��˳����󻹿����ڼ�¼ ÿ��������ʵĴ��� */

	Vertex W;
	for (V = 0; V < Graph->Nv; V++)
	{	/* ���±�Ϊ0�Ķ��㿪ʼ���� ÿ��ѭ���߹��ı�Ϊһ���ȹ��� */
		if (!visited[V])
		{	/* ����ö���δ���ʹ� */
			visited[V] = 1; /* ��Ƿ��ʹ� */
			printf("%c ", Graph->G[V].Data);
			VexQ[rear++] = V; /* ��� */
			while (front != rear)
			{	/* ���׺Ͷ�βָ���غϱ�ʾ���п� */
				for (W = FirstAdjV(Graph, V); W != -1; W = NextAdjV(Graph, V, W))
				{	/* ����V����ÿ���ڽӵ� */
					if (!visited[W])
					{	/* ������ڽӵ�δ���ʹ� */
						visited[W] = 1; /* ��Ƿ��ʹ� */
						printf("%c ", Graph->G[V].Data);
						VexQ[rear++] = W; /* ��� */
					}
				}
				front++; /* ����Ԫ�س��� */
			}
		}
	}
	free(VexQ); /* �ͷŶ�̬�ռ� */
}

/* �ڽӱ�洢 - ���������㷨 */

int TopSort(LGraph Graph, Vertex TopOrder[])
{ /* ��Graph������������,  TopOrder[]˳��洢�����Ķ����±� */
	int Indegree[MaxVertexNum], cnt;
	Vertex V;
	Vertex *VexQ = (Vertex *)malloc(Graph->Nv * sizeof(Vertex));
	int front = 0, rear = 0; /* ����ͷβλ�ñ�ʶ�غ� */
	/* ע�� ��ʱ�Ķ��в���ѭ������ ��������ͬ��С�ռ���������н�� */

	/* ��ʼ��Indegree[] */
	for (V = 0; V < Graph->Nv; V++)
		Indegree[V] = 0;

	/* ����ͼ���õ�Indegree[] */
	Vertex W;
	for (V = 0; V < Graph->Nv; V++)
		for (W = FirstAdjV(Graph, V); W != -1; W = NextAdjV(Graph, V, W))
			Indegree[W]++; /* �������<V, W->AdjV>�ۼ��յ����� */

	/* ���������Ϊ0�Ķ������� */
	for (V = 0; V < Graph->Nv; V++)
		if (Indegree[V] == 0)
		{
			VexQ[rear++] = V; /* ��� */
		}

	/* ��������������� */
	cnt = 0;
	while (front != rear)
	{
		V = VexQ[front];
		TopOrder[cnt++] = V; /* ��֮��Ϊ������е���һ��Ԫ�� */
		front++; /* ����һ�����Ϊ0�Ķ��� */
		/* ��V��ÿ���ڽӵ�Wɾȥһ����� */
		for (W = FirstAdjV(Graph, V); W != -1; W = NextAdjV(Graph, V, W))
			if (--Indegree[W] == 0)/* ��ɾ��Vʹ��W->AdjV���Ϊ0 */
				VexQ[rear++] = W;  /* ��ö������� */
	}

	if (cnt != Graph->Nv)
		return 0; /* ˵��ͼ���л�·, ���ز��ɹ���־ */
	else
		return 1;
}


int main()
{
	LGraph G = BuildGraph();
	DFS(G);
	printf("\n");
	BFS(G);
	return 0;
}