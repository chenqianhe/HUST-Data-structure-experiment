
#include "menu.h"
#include "op_for_multi_linear.h"


status RemoveList(LISTS &Lists,char ListName[]); 
int LocateList(LISTS Lists,char ListName[]); 
void menu(SqList& L,char FileName[]);



char initname[]= "_list.dat";
char FileName[30];

int main(){
	int op=1;
	LISTS Lists;
	Lists.length=0;
	Lists.listsize=10;
	while(op){
		system("cls");	printf("\n\n");
		printf("      Menu for Multi Linear Table Management System \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. Insert     \n");
		printf("    	  2. Delete     \n");
		printf("    	  3. Lookup  \n");
		printf("    	  4. Operating linear table  \n");
		printf("    	  5. Overview \n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~5]:");
		scanf("%d",&op);
		switch(op){
			case 1:{
				if(Lists.length==10){
					printf("多线性表管理系统为空，无法插入\n");
				}else{
					printf("请输入新线性表名称：");
					char name[30];
					scanf("%s",name);
					j=AddList(Lists,name);
					if(j){
						printf("插入成功！\n");
					}else{
						printf("ERROR！\n");
					}
				}
				getchar();getchar();
				break;
			}
			case 2:{
				if(Lists.length==0){
					printf("多线性表管理系统为空，无法删除\n");
				}else{
					printf("请输入要删除的线性表名称：");
					char name[30];
					scanf("%s",name);
					j=RemoveList(Lists,name);
					if(j){
						printf("删除成功！\n");
					}else{
						printf("ERROR！\n");
					}					
				}
				getchar();getchar();
				break;
			}
			case 3:{
				if(Lists.length==0){
					printf("多线性表管理系统为空，无法查找\n");
				}else{
					printf("请输入要查找的线性表名称：");
					char name[30];
					scanf("%s",name);
					j=LocateList(Lists,name);
					if(j){
						printf("您所查找的是第%d个线性表\n",j);
					}else{
						printf("该线性表不存在！\n");
					}					
				}
				getchar();getchar();
				break;
			}
			case 4:{
				if(Lists.length==0){
					printf("多线性表管理系统为空，无法操作\n");
				}else{
					printf("请输入要操作的线性表名称：");
					char name[30];
					scanf("%s",name);
					j=LocateList(Lists,name);
					if(j){
						printf("您要操作的是第%d个线性表\n",j);
						strcpy(FileName,strcat(name,initname));

						menu(Lists.elem[j-1].L,FileName);
						printf("操作完成");
						
					}else{
						printf("该线性表不存在！\n");
					}					
				}
				getchar();getchar();
				break;
			}
			case 5:{
				printf("线性表管理系统目前共有%d个线性表\n",Lists.length);
				for(int i=0;i<Lists.length;i++){
					printf("第%d个线性表，名称为%s,长度为%d\n",i+1,Lists.elem[i].name,Lists.elem[i].L.length);
				}
				getchar();getchar();
				break;
			}
			
			case 0:{
				break;
			}
		
		}
		
	}
	printf("欢迎下次再使用本系统！\n");
	return 0;
	
}

	
	
