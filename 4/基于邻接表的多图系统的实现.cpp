#include "menu.h"
#include "op_for_graph.h"
#include <cstdlib>
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]); 
int LocateList(LISTS Lists,char ListName[]); 
void menu(ALGraph& L,char FileName[]);



char initname[]= "_list.dat";
char FileName[30];

int main(){
	int op=1;
	LISTS Lists;
	Lists.length=0;
	Lists.listsize=10;
	while(op){
		system("cls");	printf("\n\n");
		printf("      Menu for Multi Graph Management System \n");
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
					printf("图管理系统已满，无法插入\n");
				}else{
					printf("请输入图的名称：");
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
					printf("图管理系统为空，无法删除\n");
				}else{
					printf("请输入要删除的图的名称：");
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
					printf("图管理系统为空，无法查找\n");
				}else{
					printf("请输入要查找的图的名称：");
					char name[30];
					scanf("%s",name);
					j=LocateList(Lists,name);
					if(j){
						printf("您所查找的是第%d个图\n",j);
					}else{
						printf("该图不存在！\n");
					}					
				}
				getchar();getchar();
				break;
			}
			case 4:{
				if(Lists.length==0){
					printf("图管理系统为空，无法操作\n");
				}else{
					printf("请输入要操作的图的名称：");
					char name[30];
					scanf("%s",name);
					j=LocateList(Lists,name);
					if(j){
						printf("您要操作的是第%d个图\n",j);
						strcpy(FileName,strcat(name,initname));

						menu(Lists.elem[j-1].L,FileName);
						printf("操作完成");
						
					}else{
						printf("该图不存在！\n");
					}					
				}
				getchar();getchar();
				break;
			}
			case 5:{
				printf("图管理系统目前共有%d个图\n",Lists.length);
				for(int i=0;i<Lists.length;i++){
					printf("第%d个图，名称为%s\n",i+1,Lists.elem[i].name);
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

	
	
