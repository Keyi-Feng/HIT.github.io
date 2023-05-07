/* ͼ���ڽӾ����ʾ�� Ĭ��Ϊ�����Ȩͼnet */
#include<stdio.h>
#include<stdlib.h>

#define MaxVertexNum 100    /* ��󶥵�����Ϊ100 */
#define INFINITY 65535      /* ����Ϊ˫�ֽ��޷������������ֵ65535 */
typedef int Vertex;         /* �ö����±��ʾ����,Ϊ���� ��0��ʼ */
typedef int WeightType;     /* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;      /* ����洢������������Ϊ�ַ��� */
							/* ������Ҫ����ö��GraphKindö������ ����������ʡ�� */
/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode {
	Vertex V1, V2;      /* �����<V1, V2> */
	WeightType Weight;  /* Ȩ�� ���и�����Ϣ ��ָ��ָ��info�ṹ�� */
						/* ��Ϊ��Ȩͼ ������ʡ�� �ڽ�Ҳ�ɸĳ�01���� */
};
typedef PtrToENode Edge;

/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;  /* ������ */
	int Ne;  /* ����   */
	WeightType G[MaxVertexNum][MaxVertexNum]; /* �ڽӾ��� */
											  /*��info�ṹ���ͼ�͸ĳ�*info��ά���� */
	DataType Data[MaxVertexNum]; /* �涥������� */
								 /* ע�⣺�ܶ�����£����������ݣ���ʱData[]���Բ��ó��� */
};
typedef PtrToGNode MGraph; /* ���ڽӾ���洢��ͼ���� */


/* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
MGraph CreateGraph(int VertexNum)
{
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode)); /* ����ͼ */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* ��ʼ���ڽӾ��� */
	/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ������Nv - 1��*/
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->G[V][W] = INFINITY; /* ���б߳�ʼֵĬ��Ϊ�� */

	return Graph;
}

/* ���뵥���� ��Ҫ����Edge�ṹ��ָ�� */
void InsertEdge(MGraph Graph, Edge E)
{
	/* ����� <V1, V2> */
	Graph->G[E->V1][E->V2] = E->Weight;
	/* ��������ͼ����Ҫ�����<V2, V1> */
//	Graph->G[E->V2][E->V1] = E->Weight;
}

/* ����ͼ����ֵ */
MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	printf("Input the vextex num: ");
	scanf("%d", &Nv);   /* ���붥����� */
	Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */

	printf("Input the edge num: ");
	scanf("%d", &(Graph->Ne));   /* ������� */
	if (Graph->Ne != 0)
	{	 /* ����б� */
		E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */
												/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
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
		scanf(" %c", &(Graph->Data[V]));
	}

	return Graph;
}

/* ����ͼG���붥��V�ڽӵĵ�һ���ڽӵ��±� -1Ϊû���ڽӵ� */
Vertex FirstAdjV(MGraph Graph, Vertex V)
{
	Vertex W = 0;
	while ((W < Graph->Nv) && (Graph->G[V][W] == INFINITY))
		W++; /* ѭ��ֱ���ҵ���һ�� �� ���������ж��㶼���ڽ� */
	if (W < Graph->Nv)
		return W; /* �ҵ� */
	else
		return -1; /* û�ҵ� */
}

/* ����ͼG���붥��V�ڽӵ���W����һ���ڽӵ� -1Ϊ����һ���ڽӵ� */
Vertex NextAdjV(MGraph Graph, Vertex V, Vertex W)
{
	W = W + 1; /* ��W��һ�������±꿪ʼ�� ��ʱ��Ĭ��W��ȷ */
	while ((W < Graph->Nv) && (Graph->G[V][W] == INFINITY))
		W++; /* ѭ��ֱ���ҵ���һ�� �� ���������ж��㶼���ڽ� */
	if (W < Graph->Nv)
		return W; /* �ҵ� */
	else
		return -1; /* û�ҵ� */
}

/* ������������ݹ麯�� */
void  DFStravel(MGraph Graph, Vertex V, int* visited)
{
	visited[V] = 1; /* ��Ƿ��ʹ� */
	printf("%c ", Graph->Data[V]);

	Vertex W;
	for (W = FirstAdjV(Graph, V); W != -1; W = NextAdjV(Graph, V, W))
	{	/* �ö���������ڽӵ㶼Ҫ���� */
		if (!visited[W]) /* ������ڽӵ�δ���ʹ� */
			DFStravel(Graph, W, visited); /* ��ݹ���� ����� */
	}
}

/* ��������������㷨 */
void DFS(MGraph Graph)
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
void BFS(MGraph Graph)
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
			printf("%c ", Graph->Data[V]);
			VexQ[rear++] = V; /* ��� */
			while (front != rear)
			{	/* ���׺Ͷ�βָ���غϱ�ʾ���п� */
				for (W = FirstAdjV(Graph, V); W != -1; W = NextAdjV(Graph, V, W))
				{	/* ����V����ÿ���ڽӵ� */
					if (!visited[W])
					{	/* ������ڽӵ�δ���ʹ� */
						visited[W] = 1; /* ��Ƿ��ʹ� */
						printf("%c ", Graph->Data[W]);
						VexQ[rear++] = W; /* ��� */
					}
				}
				front++; /* ����Ԫ�س��� */
			}
		}
	}
	free(VexQ); /* �ͷŶ�̬�ռ� */
}

/* ��С������ Prim�㷨 */
void Prim(MGraph Graph)
{
	int i, j, k;
	WeightType minCost; /* ������ ������lowCost����������Сֵ */
	WeightType lowCost[MaxVertexNum]; /* �洢��������ж������̾��� */
	Vertex closeV[MaxVertexNum]; /* ��̾����Ӧ�������� */

	lowCost[0] = -1; /* �Ƚ��±�Ϊ0�Ķ������� */
	for (i = 1; i < Graph->Nv; i++)
	{	/* ��ʼ�� */
		lowCost[i] = Graph->G[0][i]; /* ����һ��Ȩ�ش��� */
		closeV[i] = 0; /* �����㶼��Ϊ�±�0�Ľ�� */
	}

	printf("MST by Prim: ");
	for (i = 1; i < Graph->Nv; i++)
	{	/* ����(Nv - 1)�α��� �����Ӧ������ */
		minCost = INFINITY; /* ����̾����ֵ��Ϊ�� */
		for (j = 1; j < Graph->Nv; j++)
		{	/* ����̾��� */
			if (lowCost[j] < minCost && lowCost[j] != -1)
			{	/* ����̾���ʱӦ�ų��Ѿ�����Ķ��� */
				minCost = lowCost[j];
				k = j; /* ���Ϊk �±�k��Ϊ��ǰ�ɴ�������ⶥ�� */
			}
		}
		printf("(%d,%d)%d ", closeV[k], k, lowCost[k]);
		lowCost[k] = -1; /* ��k���� */
		for (j = 1; j < Graph->Nv; j++)
		{	/* ������̾��� */
			if (Graph->G[k][j] < lowCost[j])
			{	/* �Ѿ�����Ķ�����Ϊ-1 ��˲��ᱻ���� */
				lowCost[j] = Graph->G[k][j];
				closeV[j] = k;
			}
		}
	}
}

/* ����ͼ��Դ���·�� Dijkstra�㷨 Ĭ�Ͽ��Ա��� */
void Dijkstra(MGraph Graph)
{
	int i, j, k;
	int sum; /* �洢�½��������ܴ�����·������ */
	int inVex[MaxVertexNum]; /* ���ÿ�������Ƿ��Ѿ���·���� ȡ0/1 */
	WeightType Di[MaxVertexNum]; /* ��ǰ�ɴ�·�� */
	WeightType minDi; /* ��ǰ�ɴ�·���е����·�� */

	inVex[0] = 1; /* �Ƚ��±�Ϊ0�Ķ������� */
	for (i = 1; i < Graph->Nv; i++)
	{	/* ��ʼ�� */
		Di[i] = Graph->G[0][i]; /* ����һ��Ȩ�ش��� */
		inVex[i] = 0; /* ����·���еĽ�㶼���Ϊ0 */
	}

	for (i = 1; i < Graph->Nv; i++)
	{	/* ����(Nv - 1)��ѭ�� ÿ������һ������ */
		minDi = INFINITY; /* ����̿ɴ�·����ֵ��Ϊ�� */
		for (j = 1; j < Graph->Nv; j++)
		{	/* �ҵ���̿ɴ�·�� */
			if (!inVex[j] && Di[j] < minDi)
			{	/* ����̿ɴ����ʱӦ�ų��Ѿ�����Ķ��� */
				minDi = Di[j];
				k = j; /* ���Ϊk �±�k��Ϊ��ǰ�ɴ�������ⶥ�� */
			}
		}
		/* ���ͼ����ȫ��ͨ ����ʱ���Ҳ���k k�ͻ�ȡ��һ�ε�ֵ �������л���65535 */
		/* �������һ�ζ�û�� ��2����0�� ���bug ���Ĭ�Ͽɱ��� */
		inVex[k] = 1; /* ��k���� */
		for (j = 1; j < Graph->Nv; j++)
		{	/* ���µ�ǰ�ɴ�·�� */
			if (!inVex[j])
			{	/* ������Ķ��㲻���� */
				sum = Di[k] + Graph->G[k][j]; /* ��k·�����ⶥ�������·�� */
				if (sum < Di[j])
				{	/* ����·������ ����Ϊ�¿ɴ�·�� */
					Di[j] = sum;
				}
			}
		}
	}
	printf("Shortest path from v0 by Dijkstra: ");
	for (i = 1; i < Graph->Nv; i++)
	{	/* ���������Ŀɴ�·�� ��ʱÿ���㶼�����Ž� */
		printf("%d ", Di[i]);
	}
}

/* ����ͼ��Դ���·�� Dijkstra�㷨 ���������·���ټ� */
void DisplayPath(Vertex *path, Vertex v)
{
	if (path[v] != 0)
	{	/* ��·���л��������ټ� �ݹ���ú��� */
		DisplayPath(path, path[v]);
		printf("v%d->", path[v]);
	}
}

void DijkstraWithPath(MGraph Graph)
{
	int i, j, k;
	int sum;
	int inVex[MaxVertexNum];
	WeightType Di[MaxVertexNum];
	WeightType minDi;
	Vertex path[MaxVertexNum]; /* �洢����ý���·���ټ� */

	inVex[0] = 1;
	for (i = 1; i < Graph->Nv; i++)
	{	/* ��ʼ�� */
		Di[i] = Graph->G[0][i];
		inVex[i] = 0;
		path[i] = 0; /* Ĭ��·���ټ����±�Ϊ0�Ķ������ */
	}

	for (i = 1; i < Graph->Nv; i++)
	{	/* ����(Nv - 1)��ѭ�� ÿ������һ������ */
		minDi = INFINITY;
		for (j = 1; j < Graph->Nv; j++)
		{
			if (!inVex[j] && Di[j] < minDi)
			{
				minDi = Di[j];
				k = j;
			}
		}
		inVex[k] = 1;
		for (j = 1; j < Graph->Nv; j++)
		{	/* ���µ�ǰ�ɴ�·�� */
			if (!inVex[j])
			{
				sum = Di[k] + Graph->G[k][j];
				if (sum < Di[j])
				{
					Di[j] = sum;
					path[j] = k; /* ����j���ټ�����Ϊ����k���ټ� ����·����k,j) */
				}
			}
		}
	}
	printf("Shortest path from v0 by Dijkstra: \n");
	for (i = 1; i < Graph->Nv; i++)
	{	/* ���������Ŀɴ�·�� ��ʱÿ���㶼�����Ž� */
		printf("To v%d :", i);
		DisplayPath(path, i);
		printf("v%d ", i); /* ���·���ټ� */
		printf("Sum:%d\n", Di[i]); /* ���·������ */
	}
}

/* ��Դ���·�㷨 Floyd�㷨 O(V^3) �Գ���ͼ�Ѻ� */
int Floyd(MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum])
{
	Vertex i, j, k;

	/* ��ʼ�� ֱ�Ӵ���Ȩ�ؾ��� */
	for (i = 0; i < Graph->Nv; i++)
		for (j = 0; j < Graph->Nv; j++) {
			D[i][j] = Graph->G[i][j];
			path[i][j] = -1;
		}

	for (k = 0; k < Graph->Nv; k++)
		for (i = 0; i < Graph->Nv; i++)
			for (j = 0; j < Graph->Nv; j++)
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
					if (i == j && D[i][j] < 0) /* �����ָ�ֵȦ */
						return 0; /* ������ȷ��������ش����� */
					/* �и�Ȩ�߿��� �������и�Ȩ�� */
					path[i][j] = k; /* ���·��ʱ�ݹ���ü��� Ϊ-1ʱ��ʾֱ�� */
				}
	return 1; /* �㷨ִ����ϣ�������ȷ��� */
}

int main()
{
	MGraph G = BuildGraph();
	Dijkstra(G);
	printf("\n");

	return 0;
}