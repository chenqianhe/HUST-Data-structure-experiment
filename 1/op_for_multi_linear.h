

status AddList(LISTS &Lists,char ListName[]){
// 只需要在Lists中增加一个名称为ListName的空线性表

//    Lists.elem[Lists.length].L.elem=(ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    Lists.elem[Lists.length].L.elem=NULL;
    Lists.elem[Lists.length].L.length=0;
    Lists.elem[Lists.length].L.listsize=LIST_INIT_SIZE;
    strcpy(Lists.elem[Lists.length].name,ListName);
    Lists.length++;
    if(Lists.elem[Lists.length-1].L.elem==NULL){
    	return OK;
	}else{
		return ERROR;
	}

}

status RemoveList(LISTS &Lists,char ListName[]){
// Lists中删除一个名称为ListName的线性表

    for(int i=0;i<Lists.length;i++){

        if(!strcmp(Lists.elem[i].name,ListName)){
            // free(Lists.elem[i]);

            for(int j=i;j<Lists.length-1;j++){
                Lists.elem[j]=Lists.elem[j+1];
            }
            Lists.length--;
            return OK;

        }
    }
    return ERROR;

}

int LocateList(LISTS Lists,char ListName[]){
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0

    for(int i=0;i<Lists.length;i++){

        if(!strcmp(Lists.elem[i].name,ListName)){

            return i+1;

        }
    }
    return 0;
    
}
