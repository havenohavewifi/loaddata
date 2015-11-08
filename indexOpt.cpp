
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"dbHead.h"
#include "file.h"
#include "b_plus_tree.h"
#include "loaddata.h"
#include "cursor.h"
#include "getaRecordbyCursor.h"


/**
 * @brief �ڱ��ĳһ�����Ͻ���B+������
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid : long
 * @param [in] column : char*
 * @return  bool
 * 
 * @author weiyu
 * @date 2015/11/8
 **/
bool createIndexOn(struct dbSysHead *head, long fid, char* column){
	printf("create index on %s....\n",column);
	int idx;
	char* index_filename;
	char* indexname = "b_plus_tree_index_";
	char fileID[5] = "";
	sprintf(fileID,"%d",fid);
	Element elem_insert;
	FILE *fp_create;
	FILE *fp;
	int key;
	int location;
	
	index_filename = (char *)malloc( 3*NAMELENGTH );
	*index_filename = '\0';
	index_filename = strcat(index_filename,indexname);
	index_filename = strcat(index_filename,fileID);
	index_filename = strcat(index_filename,column);
	index_filename = strcat(index_filename,".dat");
	printf("%s\n",index_filename);
		
	//��ѯ�����ֵ䣬��ȡ�������
	idx =  queryFileID(head, fid);
	if( idx<0 ) {
		isAvail(NULL,"createIndexOn",ARRAY);
	}
	int i;
	for( i = 0; i <= (head->desc).redef[idx].attributeNum; i++) {
		if( strcmp(column, (head->desc).redef[idx].attribute[i].attributeName) == 0)
			break;
	}	
	//i������ų������Ը���
	if(i > (head->desc).redef[idx].attributeNum){
		printf("No such attribute.\n");
		return false;
	}
		
	//���Բ�������ʱ������������������false
	if( (head->desc).redef[idx].attribute[i].type != 1){
		printf("Not an int attribute.\n");
		return false;
	}

	//�������ļ�
	fp_create = fopen(index_filename,"wb");
	fclose(fp_create);
	fp = fopen(index_filename,"rb+");
	if( fp==NULL){
		printf("fopen error!\n");
		exit(0);
	}
	free(index_filename);
	//�������е�����

    int scanPointer = 0;
	int offset;
    long rec_length = (long)((head->desc).redef[idx].recordLength);
    RecordCursor scanTable(head, fid, rec_length);		
    char * one_Row_ = (char *)malloc(sizeof(char)*rec_length);
    while (true == scanTable.getNextRecord(one_Row_)) { //only scan
		offset = (head->desc).redef[idx].attribute[i].recordDeviation;
		key = *((int *)(one_Row_ + offset));
		location = scanTable.getcLogicLocation();
		printf("key::%d, location::%d\n",key,location);
		elem_insert.key = key;
		elem_insert.pos = location;
		//��һ����¼��Ӧ��elemд�������ļ�
		insert(fp, elem_insert);
		scanPointer ++;
        display(fp);
		printf("\n");
		if(scanPointer > 30)//��ʱֻ����30������
			break;
            //getOneRecord(one_Row_, (head->desc).redef[idx]); //get each attribute value and print
    }
	
	printf("inserted %d records.\n",scanPointer-1);
	//test
/*
	printf("search(fp,-10):%d\n",search(fp,-10));
	printf("search(fp,1):%d\n",search(fp,1));
	printf("search(fp,2):%d\n",search(fp,2));
	printf("search(fp,50):%d\n",search(fp,50));
*/
	fclose(fp);

	return true;
}


/**
 * @brief ɾ����������
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid : long
 * @param [in] column : char*
 * @return  bool
 * 
 * @author weiyu
 * @date 2015/11/6
 **/
bool deleteIndex(struct dbSysHead *head, long fid, char* column){
		//check
	printf("ɾ������....\n");

	char* index_filename;
	char* indexname = "b_plus_tree_index_";
	char fileID[5] = "";
	sprintf(fileID,"%d",fid);
	index_filename = strcat(index_filename,indexname);
	index_filename = strcat(index_filename,fileID);
	index_filename = strcat(index_filename,column);
	index_filename = strcat(index_filename,".dat");
	
	if( remove(index_filename) == 0 ){
    	printf("Removed %s.", index_filename);
		return true;
	}
    else{
    	perror("remove");
		return false;
	}
}


/**
 * @brief ���в���һ������ʱ���ڱ�����������в���һ��element
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid : long
 * @param [in] key : int 
 * @param [in] position : int 
 * @return  bool
 * 
 * @author weiyu
 * @date 2015/11/6
 **/
bool insertInIndex(struct dbSysHead *head, long fid, int key, int position){
	Element elem_insert;
	elem_insert.key = key;
	elem_insert.pos = position;
	FILE *fp;
	int idx;
	char* column;
	char* index_filename;
	char* indexname = "b_plus_tree_index_";
	char fileID[5] = "";
	sprintf(fileID,"%d",fid);
	
	//��ѯ�����ֵ䣬��ȡ�������
	idx =  queryFileID(head, fid);
	if( idx<0 ) {
		isAvail(NULL,"createIndexOn",ARRAY);
	}
	int i;
	for( i = 0; i <= (head->desc).redef[idx].attributeNum; i++) {
		index_filename = (char *)malloc( 3*NAMELENGTH );
		*index_filename = '\0';
		column = (char *)malloc( NAMELENGTH );
		strcpy(column, (head->desc).redef[idx].attribute[i].attributeName);
		index_filename = strcat(index_filename,indexname);
		index_filename = strcat(index_filename,fileID);
		index_filename = strcat(index_filename,column);
		index_filename = strcat(index_filename,".dat");
		fp = fopen(index_filename,"rb+");
		if( fp==NULL){	//no index on current column
			break;
		}
		insert(fp, elem_insert);
		fclose(fp);
		free(index_filename);
		free(column);
	}
	return true;
}


/**
 * @brief ����ɾ��һ������ʱ���ڱ������������ɾ��һ��elem
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid : long 
 * @param [in] key : int 
 * @return  bool 
 * 
 * @author weiyu
 * @date 2015/11/6
 **/
bool deleteInIndex(struct dbSysHead *head, long fid, int key){
	int idx;
	char* column;
	char* index_filename;
	char* indexname = "b_plus_tree_index_";
	char fileID[5] = "";
	sprintf(fileID,"%d",fid);
	
	FILE *fp;
	
	//��ѯ�����ֵ䣬��ȡ�������
	idx =  queryFileID(head, fid);
	if( idx<0 ) {
		isAvail(NULL,"createIndexOn",ARRAY);
	}
	int i;
	//�������ԣ����Ƿ���index
	for( i = 0; i <= (head->desc).redef[idx].attributeNum; i++) {
		//��int������û��index
		if((head->desc).redef[idx].attribute[i].type != 0)
			break;
			
		index_filename = (char *)malloc( 3*NAMELENGTH );
		*index_filename = '\0';
		column = (char *)malloc( NAMELENGTH );
		strcpy(column, (head->desc).redef[idx].attribute[i].attributeName);
		index_filename = strcat(index_filename,indexname);
		index_filename = strcat(index_filename,fileID);
		index_filename = strcat(index_filename,column);
		index_filename = strcat(index_filename,".dat");
		fp = fopen(index_filename,"rb+");
		if( fp==NULL){	//no index on current column
			break;
		}
		del(fp, key);
		fclose(fp);
		free(index_filename);
		free(column);
	}
	return true;
}


