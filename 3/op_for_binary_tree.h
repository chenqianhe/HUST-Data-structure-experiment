status AddList(LISTS &Lists,char ListName[]){

    Lists.elem[Lists.length].L=NULL;
    strcpy(Lists.elem[Lists.length].name,ListName);
    Lists.length++;
    if(Lists.elem[Lists.length-1].L==NULL){
    	return OK;
	}else{
		return ERROR;
	}

}

status RemoveList(LISTS &Lists,char ListName[]){

    for(int i=0;i<Lists.length;i++){

        if(!strcmp(Lists.elem[i].name,ListName)){

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

    for(int i=0;i<Lists.length;i++){

        if(!strcmp(Lists.elem[i].name,ListName)){

            return i+1;

        }
    }
    return 0;
    
}
