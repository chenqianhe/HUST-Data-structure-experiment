#include "subfunction.h"

int e = 0;
int i = -1;
int j=0; 
int flag1=0;
int pre = -1; 
int next=-1;

status InitList(LinkList &L);
status DestroyList(LinkList &L);
status ClearList(LinkList&L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
status LocateElem(LinkList L,ElemType e); //简化过
status PriorElem(LinkList L,ElemType e,ElemType &pre);
status NextElem(LinkList L,ElemType cur,ElemType& next_e);
status ListInsert(LinkList& L,int i,ElemType e);
status ListDelete(LinkList& L,int i,ElemType& e);
status ListTraverse(LinkList L);  //简化过
status SaveList(LinkList L,char FileName[]);
status LoadList(LinkList &L,char FileName[]);

void menu(LinkList& L,char FileName[]){
	if(!L)	flag1=0;
	else flag1=1;
	char name[30];
	strcpy(name,FileName);
	int op=1;
	while(op){
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Linked Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList       8. PriorElem\n");
		printf("    	  2. DestroyList    9. NextElem \n");
		printf("    	  3. ClearList      10. ListInsert\n");
		printf("    	  4. ListEmpty      11. ListDelete\n");
		printf("    	  5. ListLength     12. ListTrabverse\n");
		printf("    	  6. GetElem        13. Write File\n");
		printf("    	  7. LocateElem     14. Read In File\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~14]:");
		scanf("%d",&op);
	    switch(op){
		   	case 1:
			 	if (!flag1)
					{ 
					j=InitList(L);
			 		if (L==NULL) printf("可能没有正确分配表头节点空间");
					if (L->next!=NULL) printf("表头节点可能没有正确初始化");
				    if (j==OK) {
				               printf("线性表初始化成功");
				               flag1=1;
				               }
				    }
				else
				    {
				 	j=InitList(L);
				    if (j==INFEASIBLE){
				     	printf("INFEASIBLE");
				     	printf("可能会对已经存在的线性表初始化");
					} 
				    }
			 	getchar();getchar();
			 	break;
		   	case 2:
			    j=DestroyList(L);
				if (!flag1)
				{
					printf("不能对不存在的线性表进行销毁操作！\n");	
				}
				else
			    { 
			        if(j==OK){
			            	printf("线性表销毁成功！\n");
			            	flag1=0;	
					}else printf("INFEASIBLE");
			    } 
			 	getchar();getchar();
			 	break;
		   	case 3:
			    if (!flag1) { 
			    	printf("可能会对不存在的线性表清空");
			    }
				else {
					j=ClearList(L);
					if (j==OK) printf("线性表清空成功！\n");
					else if(j==INFEASIBLE)	printf("INFEASIBLE");
					if(L->next)	printf("表头节点后继节点指针未置为NULL");
			    }
				getchar();getchar();
				break;
		   	case 4:
		   		if(!flag1){
		   			printf("可能会对不存在的线性表判空");
				}else if(ListEmpty(L)==OK) printf("线性表为空！\n");
			    else printf("线性表不为空！\n");   
				getchar();getchar();
				break;
		   	case 5:
				if(!flag1){
		   			printf("可能会对不存在的线性表求表长\n");
				}else printf("线性表长为 %d\n",ListLength(L));     
			 	getchar();getchar();
			 	break;
		   	case 6:
		   		if(!flag1){
		   			printf("可能会对不存在的线性表查找元素\n");
				}else{
					printf("请输入要获取第几个元素\n");
					scanf("%d",&i);
	
			   		if(GetElem(L,i,e)==OK){
			   			printf("第%d个元素为%d\n",i,e);
					}else{
						printf("不存在第%d个元素\n",i); 
					}
				}
			 	getchar();getchar();
				break;
		   	case 7:
		   		if(!flag1){
		   			printf("可能会对不存在的线性表进行元素查询\n");
				}else{
					printf("请输入要查询的元素\n");
					scanf("%d",&i);
					if((e=LocateElem(L,i))){
						printf("您输入的元素是第%d个\n",e);
					}else{
						printf("您输入的元素不存在\n");
					} 
				} 
			 	getchar();getchar();
			 	break;
		   	case 8:
		   		if(!flag1){
		   			printf("可能会对不存在的线性表进行前驱元素查询\n");
				}else{
					printf("请输入要查询前驱元素的元素\n");
					scanf("%d",&i);
					if(PriorElem(L,i,pre)){
						printf("您输入的元素的前驱元素是%d\n",pre);
					}else{
						printf("您输入的元素不存在前驱元素\n");
					} 
				}    
			 	getchar();getchar();
			 	break;
		   	case 9:
		   		if(!flag1){
		   			printf("可能会对不存在的线性表进行后驱元素查询\n");
				}else{
					printf("请输入要查询后驱元素的元素\n");
					scanf("%d",&i);
					if(NextElem(L,i,next)){
						printf("您输入的元素的后驱元素是%d\n",next);
					}else{
						printf("您输入的元素不存在后驱元素\n");
					} 
				}    
			 	getchar();getchar();
			 	break;
		   	case 10:
		   		if(!flag1){
		   			printf("可能会对不存在的线性表进行插入\n");
				}else{
					printf("请输入要插入的位置\n");
					scanf("%d",&i);
					printf("请输入要插入的元素\n");
					scanf("%d",&e);
					j=ListInsert(L,i,e);
					if(j==OK){
						printf("插入元素成功\n");
					}else if(j==ERROR){
						printf("插入位置错误\n");
					} 
				} 
   
			 	getchar();getchar();
			 	break;
		   	case 11:
		   		if(!flag1){
		   			printf("可能会对不存在的线性表进行删除\n");
				}else{
					printf("请输入要删除第几个元素：\n");
					scanf("%d",&i);
					j=ListDelete(L,i,e); 
					if(j==OK){
						printf("删除成功\n");
						
					}else if(j==ERROR){
						printf("删除位置错误\n");
					}
				} 
			 	getchar();getchar();
			 	break;
		   	case 12:
				if(!flag1){
		   			printf("可能会对不存在的线性表进行遍历\n");
				}else if(ListEmpty(L)){
					printf("线性表为空\n");
				}else{
					ListTraverse(L); 
				}    
			 	getchar();getchar();
			 	break;
			case 13:{
				if(!flag1){
		   			printf("可能会对不存在的线性表进行存储\n");
				}else{
					j=SaveList(L,name);
					if(j==OK){
						printf("保存成功！\n"); 
					}
				} 
				getchar();getchar();
				break;
			}
			case 14:{
				if(flag1){
					printf("不能对已存在的线性表进行读文件操作！");
				}else{
					j=LoadList(L,name);
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



