#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXINTEGER 2147483647
#define MININTEGER 0

#define MAX(a,b) ((a>b) ? a : b)
#define MIN(a,b) ((a<b) ? a : b)

//�������ܣ����ؿ��Ա���������������ֵ
//����˵��������nums�洢���Ա���䣬numsSize������Ա����
int maximumGap(int* nums, int numsSize){
    //����ɴ˺����Ĺ���
    return 0;
}
int main()
{
    int numsSize;  //���Ա����
    int count = 0; //�����������
    int maxdiff;   //���������������ֵ
    freopen("5_2_input.in", "r", stdin);

    while(scanf("%d",&numsSize)!=EOF){
        count++;
        int nums[numsSize];  //���Ա��������
        for(int i = 0;i < numsSize;i++){
            scanf("%d",&nums[i]);
        }
        printf("====Case %d====\n",count);
        maxdiff = maximumGap(nums,numsSize);
        printf("%d\n", maxdiff);

    }
    fclose(stdin);
    //�ն�����ķ�ʽ
    /*while(scanf("%d",&numsSize)!=EOF){
        count++;
        int nums[numsSize];
        for(int i = 0;i < numsSize;i++){
            scanf("%d",&nums[i]);
        }
        printf("====Case %d====\n",count);
        maxdiff = maximumGap(nums,numsSize);
        printf("%d\n", maxdiff);
    }*/

    return 0;
    /*�������������ʽ��
    ���룺
    4
    1 3 5 10
    �����
    5
    */
}
