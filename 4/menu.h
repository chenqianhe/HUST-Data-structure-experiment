#include "subfunction.h"

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u); 
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v); 
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
void visit(VertexType v);
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);

int e = 0;
//int i = -1;
int j=0; 
int flag1=0;
int pre = -1; 
int next=-1;


void menu(ALGraph& L,char FileName[]){
	flag1 = 0; 
//	if(!L)	flag1=0;
//	else flag1=1;
	char name[30];
	strcpy(name,FileName);
	int op=1;
	while(op){
		system("cls");	printf("\n\n");
		printf("      Menu for Graph On Linked Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. CreatGraph    8. DeleteVex\n");
		printf("    	  2. DestroyGraph  9. InsertArc \n");
		printf("    	  3. LocateVex     10. DeleteArc\n");
		printf("    	  4. PutVex        11. DFSTraverse\n");
		printf("    	  5. FirstAdjVex   12. BFSTraverse\n");
		printf("    	  6. NextAdjVex    13. SaveGraph\n");
		printf("    	  7. InsertVex     14. LoadGraph\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~14]:");
		scanf("%d",&op);
	    switch(op){
		   	case 1:
			 	if (!flag1){
				 	
					VertexType V[30];
					KeyType VR[100][2];
					int i=0;
					do {
					    scanf("%d%s",&V[i].key,V[i].others);
					} while(V[i++].key!=-1);
					i=0;
					do {
					    scanf("%d%d",&VR[i][0],&VR[i][1]);
					   } while(VR[i++][0]!=-1);
					if (CreateCraph(L,V,VR)==ERROR) printf("输入数据错，无法创建");
					else {
						for(int i=0;i<L.vexnum;i++)
						{
					     ArcNode *p=L.vertices[i].firstarc;
					     printf("%d %s",L.vertices[i].data.key,L.vertices[i].data.others);
					     while (p)
					     {
					         printf(" %d",p->adjvex);
					         p=p->nextarc;
					     }
					     printf("\n");
						}
						flag1 = 1;
					}
				}else{
			     	printf("可能会对已经存在的图初始化");
				} 
			 	getchar();getchar();
			 	break;
		   	case 2:
				if (!flag1)
				{
					printf("不能对不存在的图进行销毁操作！\n");	
				}
				else
			    { 
			    	j = DestroyGraph(L); 
			        if(j==OK){
		            	printf("图销毁成功！\n");
		            	flag1=0;	
					}else printf("未正确销毁图");
			    } 
			 	getchar();getchar();
			 	break;
		   	case 3:
			    if (!flag1) { 
			    	printf("图未创建");
			    }
				else {
					KeyType u;
					printf("请输入要查找的顶点：\n");
					scanf("%d",&u);  
					j=LocateVex(L,u);
					if (j!=-1) printf("查找顶点的位序为%d\n",j);
					else	printf("节点不存在\n");
			    }
				getchar();getchar();
				break;
		   	case 4:
		   		if(!flag1){
		   			printf("可能会修改不存在的图");
				}else {
					KeyType u;
					VertexType value;
					printf("请输入要修改的顶点：\n");
					scanf("%d",&u);  
					printf("请输入修改值：\n");
					scanf("%d%s",&value.key,value.others);
					j = PutVex(L,u,value);
					if(j)	printf("修改成功\n");
					else	printf("操作失败\n"); 
				}   
				getchar();getchar();
				break;
		   	case 5:
				if(!flag1){
		   			printf("图未创建\n");
				}else{
					KeyType u;
					printf("请输入要查找的顶点：\n");
					scanf("%d",&u); 
					j = FirstAdjVex(L,u);
					if (j!=-1)
						printf("%d %s",L.vertices[j].data.key,L.vertices[j].data.others);
					else
						printf("查找失败");
				}     
			 	getchar();getchar();
			 	break;
		   	case 6:
		   		if(!flag1){
		   			printf("可能会对不存在的图进行查询\n");
				}else{
					int v,w;
					printf("请输入v和w"); 
					scanf("%d%d",&v,&w);
					j = NextAdjVex(L,v,w);
					if (j!=-1)
						printf("%d %s",L.vertices[j].data.key,L.vertices[j].data.others);
					else
						printf("无下一邻接顶点");
				} 
			 	getchar();getchar();
				break;
		   	case 7:
		   		if(!flag1){
		   			printf("可能会对不存在的图进行顶点插入\n");
				}else{
					VertexType v;
					printf("请输入要插入的顶点的信息\n");
					scanf("%d%s",&v.key,v.others);
					j = InsertVex(L,v);
					if (j==OK)
						for(int i=0;i<L.vexnum;i++)
						{
					     ArcNode *p=L.vertices[i].firstarc;
					     printf("%d %s",L.vertices[i].data.key,L.vertices[i].data.others);
					     while (p)
					     {
					         printf(" %d",p->adjvex);
					         p=p->nextarc;
					     }
					     printf("\n");
						}
					else printf("插入操作失败");
				} 
			 	getchar();getchar();
			 	break;
		   	case 8:
		   		if(!flag1){
		   			printf("可能会对不存在的图进行节点删除\n");
				}else{
					KeyType v;
					printf("请输入要删除的顶点:\n"); 
					scanf("%d",&v);
					
					j = DeleteVex(L,v);
					if (j==OK) {
						for(int i=0;i<L.vexnum;i++)
						{
					     ArcNode *p=L.vertices[i].firstarc;
					     printf("%d %s",L.vertices[i].data.key,L.vertices[i].data.others);
					     while (p)
					     {
					         printf(" %d",p->adjvex);
					         p=p->nextarc;
					     }
					     printf("\n");
						}
					}
					else printf("删除顶点操作失败");
				}    
			 	getchar();getchar();
			 	break;
		   	case 9:
		   		if(!flag1){
		   			printf("可能会对不存在的图进行插入\n");
				}else{
					KeyType v,w;
					printf("请输入要插入的弧的两个顶点：\n");
					scanf("%d%d",&v,&w);
					j=InsertArc(L,v,w);
					if (j==OK) {
						for(int i=0;i<L.vexnum;i++)
						{
					     ArcNode *p=L.vertices[i].firstarc;
					     printf("%d %s",L.vertices[i].data.key,L.vertices[i].data.others);
					     while (p)
					     {
					        printf(" %d",p->adjvex);
					        p=p->nextarc;
					     }
					     printf("\n");
						}
					}
					else printf("插入弧操作失败");
				} 
			 	getchar();getchar();
			 	break;
		   	case 10:
		   		if(!flag1){
		   			printf("可能会对不存在的图进行边删除\n");
				}else{
					KeyType v,w;
					printf("请输入要删除的弧的两个顶点：\n");
					scanf("%d%d",&v,&w);
					j = DeleteArc(L,v,w);
					if (j==OK) {
						for(int i=0;i<L.vexnum;i++)
						{
					     ArcNode *p=L.vertices[i].firstarc;
					     printf("%d %s",L.vertices[i].data.key,L.vertices[i].data.others);
					     while (p)
					     {
					        printf(" %d",p->adjvex);
					        p=p->nextarc;
					     }
					     printf("\n");
						}
					}
					else printf("删除弧操作失败");
				} 
			 	getchar();getchar();
			 	break;
		   	case 11:
				if(!flag1){
		   			printf("可能会对不存在的图进行遍历\n");
				}else{
					DFSTraverse(L,visit);
				}
			 	getchar();getchar();
			 	break;
		 	case 12:
				if(!flag1){
		   			printf("可能会对不存在的图进行遍历\n");
				}else{
					BFSTraverse(L,visit);
				}    
			 	getchar();getchar();
			 	break;
			case 13:{
				if(!flag1){
		   			printf("可能会对不存在的图进行存储\n");
				}else{
					j=SaveGraph(L, name);
					if(j==OK){
						printf("保存成功！\n"); 
					}
				} 
				getchar();getchar();
				break;
			}
			case 14:{
				if(flag1){
					printf("不能对已存在的图进行读文件操作！");
				}else{
//					L = (ALGraph*)malloc(sizeof(ALGraph));  
					j=LoadGraph(L, name);
					if(j==OK){
						flag1=1;
						printf("读取成功！\n");
					}else{
						printf("文件地址错误");
					}
				}
				getchar();getchar();
				break;
			}
			case 0:
	         	break;
			}//end of switch
	  }//end of while
	
}//end of menu



