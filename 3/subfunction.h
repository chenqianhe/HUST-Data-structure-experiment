#include "def.h"
typedef struct {
    int pos;
    TElemType data;
} myDEF;
void visit(BiTree T);
int creat(BiTree &f,int i,TElemType definition[],int flag);
BiTNode* LocateNode(BiTree T,KeyType e);
BiTree searchfather(BiTree T, KeyType e); 
status CreateBiTree(BiTree &T,TElemType definition[]){
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。*/
    int i,j,flag=0,length=0;
    KeyType e;
    while(definition[length].key != -1){
        length++;
    }
    for(i=0;i< length ;i++){
        e = definition[i].key;
        if (e!=0){
            for(j=i+1;j< length;j++){
                if( e == definition[j].key){
                    flag = 1;
                    break;
                }
            }
            if(flag) break;
        }
    }
    if(flag) return ERROR;
    i = 0;
    BiTree r = (BiTNode*)malloc(sizeof(BiTNode));
    T = r;
    r->data.key = definition[i].key;
    strcpy(r->data.others,definition[i].others);
    i++;
    i = creat(r,i,definition,1);
    i = creat(r,i,definition,2);
    return OK;
}
int creat(BiTree &f,int i,TElemType definition[],int flag){
    if(definition[i].key == 0) {
        if(flag == 1){
            f->lchild = NULL;
        }
        if(flag == 2){
            f->rchild = NULL;
        }
        return i+1;
    }
    if(definition[i].key!=-1){
    	BiTree r = (BiTNode*)malloc(sizeof(BiTNode));
	    r->data.key = definition[i].key;
	    strcpy(r->data.others,definition[i].others);
	    if(flag == 1){
	        f->lchild = r;
	    }
	    if(flag == 2){
	        f->rchild = r;
	    }
	    i++;
	    i = creat(r,i,definition,1);
	    i = creat(r,i,definition,2);
	}

    return i;
}
status ClearBiTree(BiTree &T){
//将二叉树设置成空，并删除所有结点，释放结点空间
    free(T);
    T = NULL;
    return OK;

}
status DestroyBiTree(BiTree &T){
	free(T);
	T = NULL;
	return OK;
} 

status BiTreeEmpty(BiTree L){
	if(L->lchild){
		return FALSE;
	}else{
		return TRUE;
	}
}
int BiTreeDepth(BiTree T){
//求二叉树T的深度
    if(T==NULL){
        return 0;
    }else{
        int left = BiTreeDepth(T->lchild);
        int right = BiTreeDepth(T->rchild);
        return left>right?(left+1):(right+1);
    }
}
BiTNode* LocateNode(BiTree T,KeyType e){
//查找结点
    if(T->data.key == e){
        return T;
    }
    if(T->lchild!=NULL){
        BiTree left = LocateNode(T->lchild,e);
        if(left){
            return left;
        }
    }
    if(T->rchild!=NULL){
        BiTree right = LocateNode(T->rchild,e);
        if(right){
            return right;
        }   
    }

    return NULL;

}
status Assign(BiTree &T,KeyType e,TElemType value){
//实现结点赋值。
    if(value.key != e){
        BiTree p = LocateNode(T,value.key);
        if(p){
            return ERROR;
        }
    }
    BiTree p = LocateNode(T,e);
    if(p){
        p->data.key = value.key;
        strcpy(p->data.others,value.others);
        return OK;
    }else{
        return ERROR;
    }
}
BiTNode* GetSibling(BiTree T,KeyType e){
//实现获得兄弟结点
    if(T->lchild!=NULL&&T->rchild!=NULL){
        if(T->lchild->data.key == e){
            return T->rchild;
        }else if(T->rchild->data.key == e){
            return T->lchild;
        }
    }
    BiTree p =NULL;
    if(T->lchild!=NULL){
        p = GetSibling(T->lchild, e);
    }
    if(T->rchild!=NULL&&!p){
        p = GetSibling(T->rchild,e);
    }
    return p;
}
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c){
//插入结点。
    BiTree p = NULL;
    p = LocateNode(T->lchild,e);
    BiTree t = NULL;
    if((t=LocateNode(T->lchild,c.key))){
        return ERROR;
    }
    if(p){
        BiTree newnode = (BiTree)malloc(sizeof(BiTNode));
        newnode->data.key = c.key;
        strcpy(newnode->data.others,c.others);
        newnode->lchild = NULL;
        newnode->rchild = NULL;
        if(LR==0){
            newnode->rchild = p->lchild;
            p->lchild = newnode;
        }else if(LR==1){
            newnode->rchild = p->rchild;
            p->rchild = newnode;
        }else if(LR==-1){
            newnode->rchild = T->lchild;
            T->lchild = newnode;
        }
        return OK;
    }else{
        return ERROR;
    }
}
status DeleteNode(BiTree &T,KeyType e){
//删除结点。此题允许通过增加其它函数辅助实现本关任务
    BiTree father = NULL;
    BiTree p = NULL;
    if(!(p=LocateNode(T,e))){
        return ERROR;
    }else{
        father = searchfather(T,e);
    }
    if(!father){
        BiTree right=T->lchild;

        while(right->rchild!=NULL){
            right=right->rchild;
        }
        right->rchild=p->rchild;
        free(T);
        T=p->lchild;
    }else{
        if(p->lchild==NULL&&p->rchild==NULL){
            if(father->lchild==p){
                father->lchild=NULL;
            }else{
                father->rchild=NULL;
            }
        }else if(p->lchild!=NULL&&p->rchild==NULL){
            if(father->lchild==p){
                father->lchild=p->lchild;
            }else{
                father->rchild=p->lchild;
            }
        }else if(p->lchild==NULL&&p->rchild!=NULL){
            if(father->lchild==p){
                father->lchild=p->rchild;
            }else{
                father->rchild=p->rchild;
            }
        }else{
            BiTree right=p->lchild;
            while(right->rchild!=NULL){
                right=right->rchild;
            }
            right->rchild=p->rchild;
            if(father->lchild==p){
                father->lchild=p->lchild;
            }else{
                father->rchild=p->lchild;
            }
            
        }
        free(p);
    }
    
    return OK;
}
BiTree searchfather(BiTree T, KeyType e){
    if(T->lchild!=NULL){
        if(T->lchild->data.key == e){
            return T;
        }else{
            BiTree left = searchfather(T->lchild,e);
            if(left){
                return left;
            }
        }

    }
    if(T->rchild!=NULL){
        if(T->rchild->data.key == e){
            return T;
        }else{
            BiTree right = searchfather(T->rchild,e);
            if(right){
                return right;
            }
        } 
    }

}
void visit(BiTree T){
    printf(" %d,%s",T->data.key,T->data.others);
}
status PreOrderTraverse(BiTree T,void (*visit)(BiTree)){
//先序遍历二叉树T
    BiTree node[100]={0};
    node[0] = T;

    int i=0;
    int t=0;


    do{
        visit(node[i]);
        if(node[i]->lchild!=NULL&&node[i]->rchild==NULL){
            for(int j=t;j>i;j--){
                node[j+1] = node[j];
            }
            node[i+1] = node[i]->lchild;
            t++;
        }else if(node[i]->lchild==NULL&&node[i]->rchild!=NULL){
            for(int j=t;j>i;j--){
                node[j+1] = node[j];
            }
            node[i+1] = node[i]->rchild;
            t++;
        }else if(node[i]->lchild!=NULL&&node[i]->rchild!=NULL){
            for(int j=t;j>i;j--){
                node[j+2] = node[j];
            }
            node[i+1] = node[i]->lchild;
            node[i+2] = node[i]->rchild;
            t+=2;
        }
        i++;
    }while(i<=t);
}
status InOrderTraverse(BiTree T,void (*visit)(BiTree)){
//中序遍历二叉树T
    if(T->lchild!=NULL){
        InOrderTraverse(T->lchild,visit);
    }
    visit(T);
    if(T->rchild!=NULL){
        InOrderTraverse(T->rchild,visit);
    }
}
status PostOrderTraverse(BiTree T,void (*visit)(BiTree)){
//后序遍历二叉树T
    if(T->lchild!=NULL){
        PostOrderTraverse(T->lchild,visit);
    }
    
    if(T->rchild!=NULL){
        PostOrderTraverse(T->rchild,visit);
    }
    visit(T);
}
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree)){
//按层遍历二叉树T
    BiTree node[100]={0};
    node[0] = T;

    int i=0;
    int t=1;


    do{
        visit(node[i]);
        if(node[i]->lchild!=NULL){
            node[t++] = node[i]->lchild;
        }
        if(node[i]->rchild!=NULL){
            node[t++] = node[i]->rchild;
        }
        i++;
    }while(i<t);
}
status SaveBiTree(BiTree T, char FileName[]){
//将二叉树的结点数据写入到文件FileName中

    FILE  *fp;
    BiTree node[101]={0,};
    myDEF definition[100];
    node[1] = T;
    int i = 1;
    if((fp=fopen(FileName,"wb"))!=NULL){
        while(i<101){
            if(node[i]!=NULL){
                fprintf(fp,"%d %d %s ",i,node[i]->data.key,node[i]->data.others);
                if(node[i]->lchild!=NULL){
                    node[2*i]=node[i]->lchild;
                }
                if(node[i]->rchild!=NULL){
                    node[2*i+1]=node[i]->rchild;
                }
            }
            i++;
        }
    }
    fclose(fp);
    return OK;
}
status LoadBiTree(BiTree &T, char FileName[]){
//读入文件FileName的结点数据，创建二叉树
    BiTree location[100];
    for (int i = 0; i < 100; ++i)
        location[i] = NULL;
    FILE *fp;
    fp = fopen(FileName, "r");
    int a, b;
    char string[20];
    while (fscanf(fp, "%d %d %s ", &a, &b, string) != EOF)
    {
        location[a] = (BiTree) malloc(sizeof(BiTNode));
        location[a]->data.key = b;
        strcpy(location[a]->data.others, string);
        location[a]->rchild = NULL;
        location[a]->lchild = NULL;
    }
    for (int i = 2; i < 100; ++i)
    {
        if (location[i / 2] != NULL)
        {
            if (i % 2 == 1)
                location[i / 2]->rchild = location[i];
            else
                location[i / 2]->lchild = location[i];
        }
    }
    T = location[1];
    fclose(fp);
    return OK;
}
void visual(BiTree &T){
	int h = BiTreeDepth(T->lchild);
	int l = (int)pow(2,h)-1;
	
	BiTree node[101]={0,};
    node[1] = T->lchild;
    
    int i=1;
    int t=0;
    printf("\n"); 
    while(i<l+1){
    	if(node[i]!=NULL){
    		printf(" %d,%s\t",node[i]->data.key,node[i]->data.others);
	        if(node[i]->lchild!=NULL){
	            node[2*i]=node[i]->lchild;
	        }
	        if(node[i]->rchild!=NULL){
	            node[2*i+1]=node[i]->rchild;
	        }
    	}else{
    		printf(" 0,#\t");
		}
		if(i%(int)pow(2,t)==(int)pow(2,t)-1){
			printf("\n");
			t++;
		}
    	i++;
	}

	
}


