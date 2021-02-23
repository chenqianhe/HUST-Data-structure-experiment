#include "subfunction.h"

int e = 0;
int i = -1;
int j=0; 
int flag1=0;
int pre = -1; 
int next=-1;

int CreateBiTree(BiTree &T,TElemType definition[]);
status DestroyBiTree(BiTree &L);
status ClearBiTree(BiTree&L);
status BiTreeEmpty(BiTree L);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T,KeyType e); 
status Assign(BiTree &T,KeyType e,TElemType value); 
BiTNode* GetSibling(BiTree T,KeyType e); 
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
status DeleteNode(BiTree &T,KeyType e);
void visit(BiTree T);
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);
void visit(BiTree T);
void visual(BiTree &T);

void menu(BiTree& L,char FileName[]){
	if(!L)	flag1=0;
	else flag1=1;
	char name[30];
	strcpy(name,FileName);
	int op=1;
	while(op){
		system("cls");	printf("\n\n");
		printf("      Menu for Binary Tree On Linked Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. CreateBiTree    9. InsertNode\n");
		printf("    	  2. DestroyBiTree  10. DeleteNode \n");
		printf("    	  3. ClearBiTree    11. PreOrderTraverse\n");
		printf("    	  4. BiTreeEmpty    12. InOrderTraverse\n");
		printf("    	  5. BiTreeDepth    13. PostOrderTraverse\n");
		printf("    	  6. LocateNode     14. LevelOrderTraverse\n");
		printf("    	  7. Assign         15. Save In File\n");
		printf("    	  8. GetSibling     16. Read In File\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~16]:");
		scanf("%d",&op);
	    switch(op){
		   	case 1:
			 	if (!flag1){
				 	L = (BiTree)malloc(sizeof(BiTNode)); 
					TElemType definition[100];
					int ans,i=0;
					do {
						scanf("%d%s",&definition[i].key,definition[i].others);
					} while (definition[i++].key!=-1);
										
					j=CreateBiTree(L->lchild,definition);
					
					if (j==OK)
					{
						flag1 = 1; 
					    PreOrderTraverse(L->lchild,visit);
					    printf("\n");
					    InOrderTraverse(L->lchild,visit);
					    visual(L);
					}else printf("关键字不唯一");
				}else{
			     	printf("可能会对已经存在的二叉树初始化");
				} 
			 	getchar();getchar();
			 	break;
		   	case 2:
				if (!flag1)
				{
					printf("不能对不存在的二叉树进行销毁操作！\n");	
				}
				else
			    { 
			    	j = DestroyBiTree(L); 
			        if(j==OK){
		            	printf("二叉树销毁成功！\n");
		            	flag1=0;	
					}else printf("未正确清空二叉树");
			    } 
			 	getchar();getchar();
			 	break;
		   	case 3:
			    if (!flag1) { 
			    	printf("可能会对不存在的二叉树清空");
			    }
				else {
					j=ClearBiTree(L->lchild);
					if (j==OK) printf("二叉树清空成功！\n");
					else if(L->lchild)	printf("表头节点后继节点指针未置为NULL");
			    }
				getchar();getchar();
				break;
		   	case 4:
		   		if(!flag1){
		   			printf("可能会对不存在的二叉树判空");
				}else if(BiTreeEmpty(L)==OK) printf("二叉树为空！\n");
			    else printf("二叉树不为空！\n");   
				getchar();getchar();
				break;
		   	case 5:
				if(!flag1){
		   			printf("可能会对不存在的二叉树求深度\n");
				}else printf("二叉树深度为 %d\n",BiTreeDepth(L->lchild));     
				visual(L);
			 	getchar();getchar();
			 	break;
		   	case 6:
		   		if(!flag1){
		   			printf("可能会对不存在的二叉树进行元素查询\n");
				}else{
					printf("请输入要查询的关键字\n");
					scanf("%d",&i);
					BiTNode* n = LocateNode(L->lchild,i);
					if(n){
						printf("您查询的节点内容为：%d,%s",n->data.key,n->data.others);
					}else{
						printf("您查询的节点不存在");
					}
					visual(L);
				} 
			 	getchar();getchar();
				break;
		   	case 7:
		   		if(!flag1){
		   			printf("可能会对不存在的二叉树进行节点赋值\n");
				}else{
					printf("请输入要赋值的节点关键字：\n");
					scanf("%d",&i);
					TElemType value;
					printf("请输入赋值结点的新内容：");
					scanf("%d%s",&value.key,&value.others); 
					j = Assign(L->lchild,i,value);
					if(j==OK){
						printf("赋值成功");
					}else{
						printf("您要赋值的节点不存在");
					}
					visual(L);
				} 
			 	getchar();getchar();
			 	break;
		   	case 8:
		   		if(!flag1){
		   			printf("可能会对不存在的二叉树进行兄弟节点查询\n");
				}else{
					printf("请输入要查询的关键字\n");
					scanf("%d",&i);
					BiTNode* n = GetSibling(L->lchild,i);
					if(n){
						printf("您查询的节点的兄弟节点为%d%s",n->data.key,n->data.others);
					}else{
						printf("无兄弟结点");
					}
					visual(L);
				}    
			 	getchar();getchar();
			 	break;
		   	case 9:
		   		if(!flag1){
		   			printf("可能会对不存在的二叉树进行插入\n");
				}else{
					int LR;
					printf("请输入要插入的位置的关键字和位置（-1根节点，0左节点，1右节点）\n");
					scanf("%d%d",&i,&LR);
					TElemType c;
					
					printf("请输入要插入的元素内容\n");
					scanf("%d%s",&c.key,&c.others);
					j=InsertNode(L,i,LR,c);
					if(j==OK){
						printf("插入成功\n");
					}else{
						printf("插入位置错误\n");
					} 
					visual(L);
				} 
			 	getchar();getchar();
			 	break;
		   	case 10:
		   		if(!flag1){
		   			printf("可能会对不存在的二叉树进行删除\n");
				}else{
					printf("请输入要删除的元素关键字：\n");
					scanf("%d",&i);
					j=DeleteNode(L->lchild,i); 
					if(j==OK){
						printf("删除成功\n");
						
					}else{
						printf("删除位置错误\n");
					}
					visual(L);
				} 
			 	getchar();getchar();
			 	break;
		   	case 11:
				if(!flag1){
		   			printf("可能会对不存在的二叉树进行遍历\n");
				}else if(BiTreeEmpty(L)){
					printf("二叉树为空\n");
				}else{
					PreOrderTraverse(L->lchild,visit); 
					visual(L);
				}    
			 	getchar();getchar();
			 	break;
		 	case 12:
				if(!flag1){
		   			printf("可能会对不存在的二叉树进行遍历\n");
				}else if(BiTreeEmpty(L)){
					printf("二叉树为空\n");
				}else{
					InOrderTraverse(L->lchild,visit); 
					visual(L);
				}    
			 	getchar();getchar();
			 	break;
			case 13:
				if(!flag1){
		   			printf("可能会对不存在的二叉树进行遍历\n");
				}else if(BiTreeEmpty(L)){
					printf("二叉树为空\n");
				}else{
					PostOrderTraverse(L->lchild,visit); 
					visual(L);
				}    
			 	getchar();getchar();
			 	break;	 	
			case 14:
				if(!flag1){
		   			printf("可能会对不存在的二叉树进行遍历\n");
				}else if(BiTreeEmpty(L)){
					printf("二叉树为空\n");
				}else{
					LevelOrderTraverse(L->lchild,visit); 
					visual(L);
				}    
			 	getchar();getchar();
			 	break;	
			case 15:{
				if(!flag1){
		   			printf("可能会对不存在的二叉树进行存储\n");
				}else{
					j=SaveBiTree(L->lchild,name);
					if(j==OK){
						printf("保存成功！\n"); 
					}
				} 
				getchar();getchar();
				break;
			}
			case 16:{
				if(flag1){
					printf("不能对已存在的二叉树进行读文件操作！");
				}else{
					L = (BiTree)malloc(sizeof(BiTNode)); 
					j=LoadBiTree(L->lchild,name);
					if(j==OK){
						flag1=1;
						printf("读取成功！\n");
						visual(L);
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



