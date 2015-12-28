#include<stdlib.h>
#include<stdio.h>
int num;
int network[100][100];  //�ڽӾ���
int Path[100];      //������ɹ���
int dist[100];      //����������ľ���
int S[100];         //����S
int isgen;          //�Ƿ��Ѿ���������
int isdijk;         //�Ƿ��Ѿ�������dijkstra�㷨
int start;          //���

void gen();
int dijk();

void gen()      //�����ڽӾ���
{
    int i,j;
    srand((int)time(0));
    puts("input the number of routers");
    scanf("%d",&num);
    if(num > 100 || num <= 0)
        return 0;
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < num; j++)
        {
            network[i][j] = rand()%10 + 1;
            if(i == j)          //Ϊ����ڵ�
                network[i][j] = 0;
            else if(i > j)      //����ͼֱ�Ӹ�ֵ
                network[i][j] = network[j][i];
            else
                network[i][j] = rand()%10 + 1;  //ʹ��rand������������
            printf("%-3d", network[i][j]);
        }
        puts("");
    }
    isgen = 1;
    isdijk = 0;
}
int dijk()      //�Ͻ�˹�����㷨
{
    int next;
    int i,j;
    int c = 0;  //Ϊ��Path����
    if(!isgen)      //�ж��Ƿ�Ϸ�
    {
        puts("generate network first");
        return 0;
    }
    puts("input start point");
    scanf("%d",&start);
    if(start > num || start < 0)
    {
        puts("invalid number");
        return;
    }
    printf("start is %d\n", start);
    for(i = 0; i < num; i++)        //��ʼ������
    {
        dist[i] = network[start][i];
        S[i] = 0;
    }
    S[start] = 1;
    for(i = 1; i < num; i++)
    {
        int Min = 11;
        for(j = 0; j < num; j++)        //choose one point
        {
            if(S[j] == 0)
            {
                if(dist[j] < Min)
                {
                    next = j;
                    Min = dist[j];
                }
            }
        }
        S[next] = 1;
        for(j = 0; j < num; j++)
        {
            if( S[j] == 0 && (dist[j] > Min + network[next][j]))    //�¼ӵıߵĳ��ȼ��ϵ�������ĳ��Ⱥ�С��ֱ�ӵ������ĳ���
            {
                dist[j] = Min + network[next][j];
            }
        }
        printf("next one is : %d\n",next);
        Path[c] = next;
        c++;
    }
    puts("done");
    isdijk = 1;
}
void print_matrix()     //��ӡ�ڽӾ���
{
    int i,j;
    if(!isgen)
    {
        puts("generate network first");
        return 0;
    }
    if(!isdijk)
    {
        puts("run Dijkstra Algorithm first");
        return 0;
    }
    puts("Adjacency Matrix:");
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < num; j++)
        {
            printf("%-3d", network[i][j]);
        }
        puts("");
    }
}
void print_all()        //  ��ӡ���е�·��
{
    int i,j;
    int c = 0;
    if(!isgen)
    {
        puts("generate network first");
        return 0;
    }
    if(!isdijk)
    {
        puts("run Dijkstra Algorithm first");
        return 0;
    }
    printf("start point: %d\n", start);
    for(j = 0; j < num; j++)
    {
        if(j == start)
            continue;
        printf("%d -> ", start);
        for(i = 0; i < num; i++)
        {
            if(Path[i] == j)
            {
                printf("%d", Path[i]);
                break;
            }
            printf("%d -> ", Path[i]);
        }
        printf("    distance: %d\n", dist[j]);
    }
}
void print_one()        //��ӡĳһ��·��
{
    int i,e;
    if(!isgen)
    {
        puts("generate network first");
        return 0;
    }
    if(!isdijk)
    {
        puts("run Dijkstra Algorithm first");
        return 0;
    }
    puts("input end point");
    scanf("%d",&e);
    if(e >= num || e < 0)
    {
        puts("invalid number");
        return;
    }
    if(start  == e)
    {
        puts("start shouldn't be equal to end");
        return ;
    }
    printf("%d -> ", start);
    for(i = 0; i < num; i++)
    {
        if(Path[i] == e)
        {
            printf("%d\n", Path[i]);
            break;
        }
        printf("%d -> ", Path[i]);
    }
    printf("distance: %d", dist[e]);
}
void menu()     //�˵�
{
    puts("\n1.generate network");
    puts("2.run Dijkstra algorithm");
    puts("3.print Adjacency Matrix");
    puts("4.print all path");
    puts("5.print epecified path");
    puts("6.quit");
}
void welcome()
{
    puts("welcome to Dijkstra's Algorithm");
}
int main()
{
    int opt;
    isdijk = 0;
    isgen = 0;
    welcome();
    while(1)        //whileѭ������ѯ���û��Ĳ���
    {
        menu();
        scanf("%d",&opt);
        switch(opt)
        {
        case 1:
            gen();
            break;
        case 2:
            dijk();
            break;
        case 3:
            print_matrix();
            break;
        case 4:
            print_all();
            break;
        case 5:
            print_one();
            break;
        case 6:
            return 0;
        default:
            puts("input invalid,try again");
        }
    }
    return 0;
}
