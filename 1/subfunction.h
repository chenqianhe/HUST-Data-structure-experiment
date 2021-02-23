#include "def.h"

//typedef int status; 
//typedef int ElemType; //数据元素类型定义





status InitList(SqList& L){
	// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
    if(!L.elem){
	    L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
		L.length=0;
		L.listsize=LIST_INIT_SIZE;
		return OK;
    }else{
        return INFEASIBLE;
    }
}
status DestroyList(SqList& L){
	// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
	    if(L.elem!=NULL){
		free(L.elem);
		L.elem = NULL;
		L.length = 0;
		L.listsize = 0;
		return OK;
	}
	return INFEASIBLE;
}
status ClearList(SqList&L){
	// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
    if(L.elem==NULL){
		return INFEASIBLE;
	}else{
		L.length = 0;
		return OK;
	}
}
status ListEmpty(SqList L){
	// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
    if(!L.elem){
        return INFEASIBLE;
    }else if(L.length==0){
		return TRUE;
	}else{
		return FALSE;
	}
} 
status ListLength(SqList L){
	// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
	if(L.elem){
        return L.length;
    }
    return INFEASIBLE;
} 
status GetElem(SqList L,int i,ElemType& e){
	// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
	if(!L.elem){
        return INFEASIBLE;
    }else if(i<1||i>L.length){
		return ERROR;
	}else{
		e = L.elem[i-1];
		return OK;
	}
}
status LocateElem(SqList L,ElemType e){
	// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回OK；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
    if(!L.elem){
        return INFEASIBLE;
    }else{
        for(int i=0;i<L.length;i++){
			if(e==L.elem[i]){
				return i+1;
			}
		}
    }
    return ERROR;
}
status PriorElem(SqList L,ElemType e,ElemType &pre){
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。

    if(!L.elem){
        return INFEASIBLE;
    }else{
        for(int i=0;i<L.length;i++){
			if(e==L.elem[i]&&i!=0){
                pre = L.elem[i-1];
				return OK;
			}
        }
    }
    return ERROR;
}
status NextElem(SqList L,ElemType e,ElemType &next){
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。

    if(!L.elem){
        return INFEASIBLE;
    }else{
        for(int i=0;i<L.length;i++){
			if(e==L.elem[i]&&i!=L.length-1){
                next = L.elem[i+1];
				return OK;
			}
        }
    }
    return ERROR;

}
status ListInsert(SqList &L,int i,ElemType e){
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if(!L.elem){
        return INFEASIBLE;
    }else if(i<1||i>(L.length+1)){
		return ERROR;
	}else{
        if(L.length>=L.listsize){
            int *p=(ElemType *)realloc(L.elem,(L.length+LIST_INIT_SIZE)*sizeof(ElemType));
            L.elem=p;
            L.listsize+=LIST_INIT_SIZE;
        }

            for(int j=L.length;j>i-1;j--){
                L.elem[j]=L.elem[j-1];
            }
        
        L.elem[i-1]=e;
        L.length++;
        // printf("%d",L.elem[i-1]);
        return OK;
	}

}
status ListDelete(SqList &L,int i,ElemType &e){
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。

    if(!L.elem){
        return INFEASIBLE;
    }else if(i<=0||i>(L.length+1)||L.length==0){
		return ERROR;
	}else{
        e=L.elem[i-1];
        for(int j=i-1;j<L.length-1;j++){
            L.elem[j]=L.elem[j+1];
        }
        
        
        L.length--;
        // printf("%d",L.elem[i-1]);
        return OK;
	}

}
status ListTraverse(SqList L){
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。

    if(!L.elem){
        return INFEASIBLE;
    }else if(L.length!=0){
        for(int i=0;i<L.length-1;i++){
            printf("%d ",L.elem[i]);
            
        }
        printf("%d",L.elem[L.length-1]);
        return OK;
    }

}
status  SaveList(SqList L,char FileName[]){
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。

    FILE  *fp;
    if(!L.elem){
        return INFEASIBLE;
    }else{

        if((fp=fopen(FileName,"wb"))!=NULL){
             fwrite(L.elem,sizeof(ElemType),L.length,fp);
             fclose(fp);

             return OK;
        }else{
             return INFEASIBLE;
         }
        
    }
}
status  LoadList(SqList &L,char FileName[]){
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。

    FILE  *fp;

    if(L.elem){
        return INFEASIBLE;
    }else{
        
        L.elem=(ElemType *) malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        L.length=0;
        if ((fp=fopen(FileName,"rb"))!=NULL){
            
            while(fread(&L.elem[L.length++],sizeof(ElemType),1,fp));
                // printf("%d",L.elem[L.length-1]);
            fclose(fp);
			L.length--;
			L.listsize=LIST_INIT_SIZE;
            return OK;
        }else{
            return ERROR;
        }
        
    }

}
 
