#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxS 1000

int task5_3(int array[],int n){
    //ʵ�ֺ������ܣ��������ٵ��ʵ�Ա������
    int pNumber=0;//һ����_���ʵ�Ա

    return pNumber;
}

int main(){

    int n,i;//����ش���ʵ�Ա��Ŀ
    int *array;
    //�ļ��������
    freopen("5_3_input.in", "r", stdin);
    //freopen("5_3_output.out","w",stdout);
    while(scanf("%d",&n)!=EOF){
        array=(int*)calloc(n,sizeof(int));
        for(i=0;i<n;i++){
            scanf("%d",&array[i]);
        }

        printf("There are at lest %d postmen.\n",task5_3(array,n));

    }
    fclose(stdin);
    //fclose(stdout);



    /*�ն�����
    printf("please enter the number of the answering postman:\n");
    scanf("%d",&n);
    getchar();
    array=(int*)calloc(n,sizeof(int));
    printf("please enter their answers:\n");
    for(i=0;i<n;i++){
        scanf("%d",&array[i]);
    }

    printf("There are at lest %d postmen.\n",task5_3(array,n));
    */
    return 0;
}
