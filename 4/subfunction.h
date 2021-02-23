#include "def.h" 

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    int num_v = 0,num_vr = 0;
    while(V[num_v++].key!=-1);
    while(VR[num_vr++][0]!=-1);
    num_v--;
    num_vr--;
    if(!num_v||num_v > 20){
        return ERROR;
    }

    G.kind = DN;
    G.vexnum = num_v;
    G.arcnum = num_vr;
    for(int i=0;i<num_v;i++){
        for(int j=0;j<i;j++){
            if(G.vertices[j].data.key==V[i].key){
                return ERROR;
            }
        }
        G.vertices[i].data.key = V[i].key;
        strcpy(G.vertices[i].data.others,V[i].others);
        G.vertices[i].firstarc = NULL;
    }

    for(int i=0,k=0;i<num_vr;k++){
        int j=0;
        for(;j<num_v;j++){
            if(G.vertices[j].data.key==VR[i][0]){
                int k=0,flag=0;
                for(;k<num_v;k++){
                    if(G.vertices[k].data.key==VR[i][1]){
                        flag = k;
                        break;
                    }
                }
                if(k==num_v){
                    return ERROR;
                }
                ArcNode *temp = (ArcNode *)malloc(sizeof(ArcNode));
                temp->adjvex = flag;
                temp->nextarc = G.vertices[j].firstarc;
                G.vertices[j].firstarc = temp;
                break;
            }   
        }
        if(j==num_v){
            return ERROR;
        }

        int temp_vr = VR[i][0];
        VR[i][0] = VR[i][1];
        VR[i][1] = temp_vr;

        if(k%2){
            i++;
        }
    }
    return OK;
}

status DestroyGraph(ALGraph &G)
/*销毁无向图G*/
{
    int i,j;
    if(G.vexnum==0) return OK;
    ArcNode *p1=(ArcNode*)malloc(sizeof(ArcNode));
    for(i=0;i<G.vexnum;i++){
        for(;G.vertices[i].firstarc!=NULL;){
            p1=G.vertices[i].firstarc;
            G.vertices[i].firstarc=G.vertices[i].firstarc->nextarc;
            free(p1);
            p1=NULL;
        }
    }
    G.vexnum=0;
    G.arcnum=0;
    return OK;
}

int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    int i,j;
    if(G.vexnum<1)  return -1;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==u)   return i;
    }
    return -1;
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    if(G.vexnum<1)  return ERROR;
    int i,j,flag=0;
    ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==u){
            G.vertices[i].data.key=value.key;
            strcpy(G.vertices[i].data.others,value.others);
            flag=1;
        }
//        if(G.vertices[i].firstarc){
//            p = G.vertices[i].firstarc;
//            do{
//                if(p->adjvex==u){
//                    p->adjvex = value.key;
//                    break;
//                }
//            }while(p=p->nextarc);
            
//        }

    }
    if(!flag)   return ERROR;
    for(i=0;i<G.vexnum;i++){
        for(j=i+1;j<G.vexnum;j++){
            if(G.vertices[i].data.key==G.vertices[j].data.key)  return ERROR;
        }
    }
    return OK;
}

int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    int i,j;
    if(G.vexnum<1)  return -1;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==u&&G.vertices[i].firstarc!=NULL){
            return G.vertices[i].firstarc->adjvex;
        }
    }
    return -1;
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    int i,index,num;
    index=LocateVex(G,v);
    if(index==-1)    return -1;
    ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
    for(p=G.vertices[index].firstarc;p;p=p->nextarc){
        num=p->adjvex;
        if(G.vertices[num].data.key==w){
            if(p->nextarc!=NULL){
                return G.vertices[index].firstarc->nextarc->adjvex;
            }else{
                return -1;
            }
            
        }
    }
    return -1;
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    if(G.vexnum==MAX_VERTEX_NUM)  return ERROR;
    for(int i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==v.key)   return ERROR;
    }
    G.vertices[G.vexnum].data.key=v.key;
    strcpy(G.vertices[G.vexnum].data.others,v.others);
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}

status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    int i,index,num;
    index=LocateVex(G,v);
    if(index==-1)	return ERROR;
    ArcNode *temp=(ArcNode*)malloc(sizeof(ArcNode));
    for(i=0;i<G.vexnum;i++){
        if(i!=index){
            ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
            p=G.vertices[i].firstarc;
            if(p){
                if(p->adjvex==index){
                    G.vertices[i].firstarc=p->nextarc;
                    free(p);
                    continue;
                }
                while(p->nextarc){
                    if(p->nextarc->adjvex==index){
                        temp=p->nextarc;
                        p->nextarc=temp->nextarc;
                        free(temp);
                        break;
                    }
                    else p=p->nextarc;
                }
            }
        }
    }
    for(i=index;i<G.vexnum-1;i++){
        G.vertices[i]=G.vertices[i+1];
    }
    G.vexnum--;
    for(i=0;i<G.vexnum;i++){
        temp=G.vertices[i].firstarc;
        while(temp){
            if(temp->adjvex>index)  temp->adjvex--;
            temp=temp->nextarc;
        }
    }
    return OK;
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    int index_1,index_2;
    index_1=LocateVex(G,v);
    index_2=LocateVex(G,w);
    if(index_1==-1||index_2==-1)   return ERROR;
    int i,j;
    ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
    for(p=G.vertices[index_1].firstarc;p;p=p->nextarc){
        if(p->adjvex==index_2)    return ERROR;
    }
    free(p);
    ArcNode *q=(ArcNode*)malloc(sizeof(ArcNode));
    q->nextarc=G.vertices[index_1].firstarc;
    G.vertices[index_1].firstarc=q;
    q->adjvex=index_2;
    ArcNode *t=(ArcNode*)malloc(sizeof(ArcNode));
    t->nextarc=G.vertices[index_2].firstarc;
    G.vertices[index_2].firstarc=t;
    t->adjvex=index_1;
    return OK;
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
	int index_1,index_2,flag=1;
    index_1=LocateVex(G,v);
    index_2=LocateVex(G,w);
    if(index_1==-1||index_2==-1)   return ERROR;
    int i,j;
    ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
    //判断该边是否存在
    for(p=G.vertices[index_1].firstarc;p;p=p->nextarc){
        if(p->adjvex==index_2)    flag=0;
    }
    if(flag)    return ERROR;
    if(G.vertices[index_1].firstarc->adjvex==index_2){
        p=G.vertices[index_1].firstarc;
        G.vertices[index_1].firstarc=G.vertices[index_1].firstarc->nextarc;
        free(p);
    }else{
    	ArcNode *temp1=(ArcNode*)malloc(sizeof(ArcNode));
	    ArcNode *temp2=(ArcNode*)malloc(sizeof(ArcNode));
	    temp1=G.vertices[index_1].firstarc;
	    for(;temp1->nextarc;temp1=temp1->nextarc){
	        if(temp1->nextarc->adjvex==index_2){
	            temp2=temp1->nextarc;
	            temp1->nextarc=temp1->nextarc->nextarc;
	            free(temp2);
	            break;
	        }
	    }
	}
    if(G.vertices[index_2].firstarc->adjvex==index_1){
        p=G.vertices[index_2].firstarc;
        G.vertices[index_2].firstarc=G.vertices[index_2].firstarc->nextarc;
        free(p);
    }else{
    	ArcNode *temp1=(ArcNode*)malloc(sizeof(ArcNode));
	    ArcNode *temp2=(ArcNode*)malloc(sizeof(ArcNode));
		
		temp1=G.vertices[index_2].firstarc;
	    for(;temp1->nextarc;temp1=temp1->nextarc){
	        if(temp1->nextarc->adjvex==index_1){
	            temp2=temp1->nextarc;
	            temp1->nextarc=temp1->nextarc->nextarc;
	            free(temp2);
	            break;
        	}
   	 	}    	
	}
    return OK;
}

void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

void DFS(AdjList verx,int index,int visited[100],void (*visit)(VertexType))
{
    ArcNode *p=verx[index].firstarc;
    if(visited[index])  return;
    visited[index]=1;
    visit(verx[index].data);
    while(p){
        if(!visited[p->adjvex]) DFS(verx,p->adjvex,visited,visit);
        p=p->nextarc;
    }
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    int visited[100]={0};
    for(int i=0;i<G.vexnum;i++){
        if(!visited[i]){
            DFS(G.vertices,i,visited,visit);
        }
    }
    return OK;
}

typedef struct Qnode{       //链队结点的类型
   int data;
   struct Qnode *next;
}Qnode,*QueuePtr;
typedef struct{        //链队指针类型
   QueuePtr front;
   QueuePtr rear;
}LinkQueue;
void InitQueue(LinkQueue &Q){
    Q.front=Q.rear=(QueuePtr)malloc(sizeof(Qnode));
    Q.front->next=NULL;
}
void EnQueue(LinkQueue &Q,int e){
    QueuePtr p=(QueuePtr)malloc(sizeof(Qnode));
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
}
int QueueEmpty(LinkQueue &Q){
    return (Q.rear==Q.front?1:0);
}
void DeQueue(LinkQueue &Q,int &e){
    QueuePtr p;
    if(QueueEmpty(Q))   return;
    p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    if(Q.front->next==NULL) Q.rear=Q.front;
    free(p);
}
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    LinkQueue Q;
    int visited[100]={0};
    InitQueue(Q);
    for(int i=0;i<G.vexnum;i++){
        if(!visited[i]){
            visited[i]=1;
            visit(G.vertices[i].data);
            EnQueue(Q,i);
            while(!QueueEmpty(Q)){
                DeQueue(Q,i);
                ArcNode *q=G.vertices[i].firstarc;
                for(;q!=NULL;q=q->nextarc){
                    if(!visited[q->adjvex]){
                        EnQueue(Q,q->adjvex);
                        visited[q->adjvex]=1;
                        visit(G.vertices[q->adjvex].data);
                    }
                }
            }
        }
    }
    return OK;
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    FILE *fp = fopen(FileName, "w");
    fprintf(fp, "%d %d", G.vexnum, G.arcnum);
    fputc('\n', fp);
    for (int i = 0; i < G.vexnum; ++i)
    {
        fprintf(fp, "%d %s", G.vertices[i].data.key, G.vertices[i].data.others);
        for (ArcNode *p = G.vertices[i].firstarc; p != NULL; p = p->nextarc)
            fprintf(fp, " %d", p->adjvex);
        fputc('\n', fp);
    }
    fclose(fp);
    for(int i=0;i<G.vexnum;i++)
    {
        if (G.vertices[i].firstarc!=NULL)
        {
            free(G.vertices[i].firstarc);
            G.vertices[i].firstarc=NULL;
        }
    }
    G.vexnum=0;
    G.arcnum=0;
    return OK;
}

status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    FILE *fp = fopen(FileName, "r");
    fscanf(fp, "%d %d", &G.vexnum, &G.arcnum);
    fgetc(fp);
    int a = 0;
    for (int i = 0; i < G.vexnum; ++i)
    {
        fscanf(fp, "%d %s", &G.vertices[i].data.key, G.vertices[i].data.others);
        G.vertices[i].firstarc = NULL;
        if (fgetc(fp)!='\n')
        {
            fscanf(fp,"%d",&a);
            G.vertices[i].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
            G.vertices[i].firstarc->adjvex=a;
            G.vertices[i].firstarc->nextarc=NULL;
        }
        ArcNode *p = G.vertices[i].firstarc;
        while (fgetc(fp)!='\n')
        {
            fscanf(fp,"%d",&a);
            p->nextarc = (ArcNode *) malloc(sizeof(ArcNode));
            p->nextarc->adjvex = a;
            p->nextarc->nextarc = NULL;
            p = p->nextarc;
        }
    }
    fclose(fp);
    return OK;
}
