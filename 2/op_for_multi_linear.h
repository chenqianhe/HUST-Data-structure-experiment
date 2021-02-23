

status AddList(LISTS &Lists,char ListName[]){
// 鍙渶瑕佸湪Lists涓鍔犱竴涓悕绉颁负ListName鐨勭┖绾挎€ц〃

//    Lists.elem[Lists.length].L.elem=(ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
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
// Lists涓垹闄や竴涓悕绉颁负ListName鐨勭嚎鎬ц〃

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
// 鍦↙ists涓煡鎵句竴涓悕绉颁负ListName鐨勭嚎鎬ц〃锛屾垚鍔熻繑鍥為€昏緫搴忓彿锛屽惁鍒欒繑鍥?

    for(int i=0;i<Lists.length;i++){

        if(!strcmp(Lists.elem[i].name,ListName)){

            return i+1;

        }
    }
    return 0;
    
}
