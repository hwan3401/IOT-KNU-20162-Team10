#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct word{

	char b[20];
	int index;
	struct word *link;
};
void search(struct word *first_ptr, char searchword[20],int count);
void save_word(struct word *ptr ,char now_ch,int ch_order);
void save_index(struct word *ptr ,int count);
struct word* word_init(struct word *before_ptr);
int main(){
	
	int i;
	struct word *ptr,*before_ptr,*first_ptr;
	int count=1;
	int ch_order=0;
	char ch;
	char now_ch='a',before_ch='A',searchword[20]={NULL};
	FILE *fp;
	fp=fopen("C:\\project\\ttt.txt","r");
	if (fp==NULL)
	{
		printf("file open error\n");
		exit(1);
	}
	ptr=(struct word*)malloc(sizeof(struct word));
	ptr->index=count;
	before_ptr=ptr;
	first_ptr=ptr;
	printf("txt 내용: ");
	while((int)(now_ch=fgetc(fp))!=EOF){
	
		printf("%c",now_ch);
			if ((int)now_ch!=32 &&(int)before_ch==32 ) 
			{
				count++;
				
				ptr=(struct word*)malloc(sizeof(struct word));
				before_ptr->link=ptr;
				before_ptr=ptr;

				ch_order=0;
				save_index(&*ptr,count);
				save_word(&*ptr,now_ch,&ch_order,&count);
			}
			else if ((int)now_ch!=32 &&(int)before_ch!=32 ) 
			{
				save_word(&*ptr,now_ch,&ch_order,&count);
		}
		before_ch=now_ch;	
	}	
	ptr->link=first_ptr;
	ptr=first_ptr;
	printf("\n");
	for(i=0;i<count;i++){	
		word_init(&*ptr);
		ptr=ptr->link;
	}
	printf("검색할 단어를 입력하세요 : ");
	scanf("%s",searchword);
	search(&*first_ptr,searchword,count);
	fclose(fp);
}
void search(struct word *first_ptr, char searchword[20],int count){
	int i,num=0;
	printf("검색 단어: [%s], 검색 단어 길이: %d \n",searchword,strlen(searchword));	
			for (i=0;i<count;i++){
				printf("%d번방에 저장된 단어:%s \n",first_ptr->index,first_ptr->b);
				if(strcmp(first_ptr->b,searchword)==0){
					printf("[[[%d번방에서 같은단어[%s]검출]]]\n",first_ptr->index,first_ptr->b);
					num++;}
					first_ptr=(first_ptr->link);
			}
			if (num==0) {printf("[[[같은 단어가 없습니다]]]");}
			else {
				printf("============================\n");
				printf("=> 총 %d 개의 같은 단어 검출\n",num);}
}



struct word* word_init(struct word *ptr){
	int i;
	for(i=0;i<20;i++){
		if ((int)(ptr->b[i]<65) || (int)(ptr->b[i])>122)
			ptr->b[i]='\0';
	}
	return ptr;//이 가리키고 있는 값을 반환한다.(반환형은 word형.)
}
void save_word(struct word *ptr ,char now_ch,int* ch_order,int* count){
	
		ptr->b[*ch_order]=now_ch;
		(*ch_order)++;
}
void save_index(struct word *ptr ,int count){
	ptr->index=count;//생성된 방에 번호 부여
}
