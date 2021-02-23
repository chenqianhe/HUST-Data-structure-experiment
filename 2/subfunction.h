#include "def.h"

status InitList(LinkList &L){
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
    if(!L){
        L=(LinkList)malloc(sizeof(LNode));
        L->next=NULL;
        return OK;
    }else{
        return INFEASIBLE;
    }
}
status DestroyList(LinkList &L){
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
    if(L){
        free(L->next);
        L=NULL;
        return OK;
    }else{
        return INFEASIBLE;
    }
}

status ClearList(LinkList &L){
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
    if(L){
        free(L->next);
        L->next=NULL;
        return OK;
    }else{
        return INFEASIBLE;
    }
}
status ListEmpty(LinkList L){
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
    if(L){
        if(L->next==NULL){
            return TRUE;
        }else{
            return FALSE;
        }
    }else{
        return INFEASIBLE;
    }
}
int ListLength(LinkList L){
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
    int length=0;
    LinkList p=L;
    if(L){
        while(p->next!=0){
            length++;
            p=p->next;
        }
        return length;
    }else{
        return INFEASIBLE;
    }
}
status GetElem(LinkList L,int i,ElemType &e){
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if(L){
        int length=0;
        LinkList p=L;
        while(p->next!=0){
            length++;
            p=p->next;
        }
        if(i<1||i>length){
            return ERROR;
        }else{
            p=L;
            for(int j=0;j<i;j++){
                p=p->next;
            }
            e=p->data;
            return OK;
        }
    }else{
        return INFEASIBLE;
    }
}
status LocateElem(LinkList L,ElemType e){
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
    if(L){
        int i=0;
        LinkList p=L;
        while(p->next){
            if(p->data==e){
                return i;
            }
            i++;
            p=p->next;
        }
        if(p->data==e){
            return i;
        }
        return ERROR;
        
    }else{
        return INFEASIBLE;
    }
}
status PriorElem(LinkList L,ElemType e,ElemType &pre){
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if(L){
        LinkList p=L;
        while(p->next){
            if(p->next->data==e&&p!=L){
                pre=p->data;
                return OK;
            }
            p=p->next;
        }
        return ERROR;
    }else{
        return INFEASIBLE;
    }
}
status NextElem(LinkList L,ElemType e,ElemType &next){
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if(L){
        LinkList p=L;
        while(p->next){
            if(p->data==e){
                next=p->next->data;
                return OK;
            }
            p=p->next;
        }
        return ERROR;


    }else{
        return INFEASIBLE;
    }
}
status ListInsert(LinkList &L,int i,ElemType e){
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if(L){
        int t=0;
        LinkList p=L;
        int length=0;
        while(p->next!=0){
            length++;
            p=p->next;
        }
        p=L;
        if(i<1||i>length+1){
            return ERROR;
        }else{
            for(int j=0;j<i-1;j++){
                p=p->next;
            }
            LinkList temp=(LinkList)malloc(sizeof(LNode));
            temp->data=e;
            temp->next=p->next;
            p->next=temp;
            return OK;
        }

    }else{
        return INFEASIBLE;
    }
}
status ListDelete(LinkList &L,int i,ElemType &e){
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if(L){
        int t=0;
        LinkList p=L;
        int length=0;
        while(p->next!=0){
            length++;
            p=p->next;
        }
        p=L;
        if(i<1||i>length+1){
            return ERROR;
        }else{
            for(int j=0;j<i-1;j++){
                p=p->next;
            }
            LinkList temp=p->next->next;
            e=p->next->data;
            free(p->next);
            p->next=temp;
            return OK;
        }

    }else{
        return INFEASIBLE;
    }   
}
status ListTraverse(LinkList L){
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
    if(L){

        LinkList p=L->next;
        if(!(L->next)){
            return OK;
        }
        while(p->next){
            printf("%d ",p->data);
            p=p->next;
        }
        printf("%d",p->data);
        return OK;
    }else{
        return INFEASIBLE;
    }
}
status SaveList(LinkList L,char FileName[]){
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
    FILE  *fp;
    if(!L){
        return INFEASIBLE;
    }else{
        LinkList p=L->next;

        if((fp=fopen(FileName,"wb"))!=NULL){
            while(p->next){
                fputc(p->data,fp);
                p=p->next;
            }
            fputc(p->data,fp);
            fclose(fp);

            return OK;
        }else{
             return INFEASIBLE;
         }
    }
}
status LoadList(LinkList &L,char FileName[]){
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
    FILE  *fp;
    if(L){
        return INFEASIBLE;
    }else{
        
        L=(LinkList)malloc(sizeof(LNode));
        L->next=(LinkList)malloc(sizeof(LNode));
        LinkList p=L->next;

        if ((fp=fopen(FileName,"rb"))!=NULL){
            
            while(1){
                p->data=fgetc(fp);
                if(feof(fp)){
                    p->next=NULL;
                    break;
                }
                p->next=(LinkList)malloc(sizeof(LNode));
                p=p->next;
            }
            p=L;
            while(p->next->next){
                p=p->next;
            }
            p->next=NULL;
            fclose(fp);
            return OK;
        }else{
            return INFEASIBLE;
        }
        
    }
}

