
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"b_plus_tree.h"

char * index_filename = "b_plus_tree_index.dat";

int main()
{
	FILE *fp;
	int key_num=100000;
	Element element_insert;

	fp = fopen(index_filename,"rb+");
	if( fp == NULL ){
		printf("索引文件不存在，重新建立索引....\n");
		FILE *fp_create;
		fp_create = fopen(index_filename,"wb");
		fclose(fp_create);
		fp = fopen(index_filename,"rb+");
		if( fp==NULL){
			printf("fopen error!\n");
			exit(0);
		}
	}
	
	for(int i=0; i<20; i++){
		// key
		element_insert.key = i;
		// value
		element_insert.pos = i+1 ;
		insert(fp,element_insert);
	}
	
	printf("%d\n",search(fp,-10));
	printf("%d\n",search(fp,1));
	printf("%d\n",search(fp,5000));
	printf("%d\n",search(fp,99999));
	printf("%d\n",search(fp,100000));
	printf("%d\n",search(fp,100001));
	display(fp);
	fclose(fp);

	return 0;
}