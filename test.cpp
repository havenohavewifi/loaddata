
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"dbHead.h"
#include "loaddata.h"
#include "cursor.h"
#include "recorder_customer.h"
#include "getaRecordbyCursor.h"

int init_database(struct dbSysHead *head)
{
	initSys(head);
	head->fpdesc = fopen(DBMS_DAT, "rb+");
	isAvail(head->fpdesc, "main", FOPEN);
	return 0;
}

int exit_database(struct dbSysHead *head)
{
	sysUpdate(head);
	fclose(head->fpdesc);
	free(head->bitMap);
	return 0;
}

int main()
{
	struct dbSysHead head;
	long fid1, fid2;

	/*
	初始化，然后打印出当前系统的信息
	*/
	init_database(&head);
	showDesc(&head);
    
/*
	printf("create file1...\n");
    fid1 = creatFileSpace(&head);//为文件一分配空间
	showFileDesc(&head);
	printf("extend 10 pages for file1...\n");
	extendFileSpace(&head, fid1, 10);//扩展十页
	showFileDesc(&head);
*/
 //	printf("extend 10 pages for file1...\n");
//	extendFileSpace(&head, fid1, 10);//再扩展十页
//	showFileDesc(&head);

    loaddata(&head);
    
/*
	printf("create file2...\n");
	fid2 = creatFileSpace(&head);
	showFileDesc(&head);
	printf("extend 10 pages for file2...\n");
	extendFileSpace(&head, fid2, 10);
	showFileDesc(&head);
	printf("extend 10 pages for file2...\n");
	extendFileSpace(&head, fid2, 10);
	showFileDesc(&head);

	printf("delete file1...\n");
	recyFileSpace(&head, fid1);
	showFileDesc(&head);
	printf("delete file2...\n");
	recyFileSpace(&head, fid2);
	showFileDesc(&head);
*/
    
    //test cursor.cpp
    RecordCursor scan(&head, 1, 464);
    char * oneRec = (char *)malloc(sizeof(char)*464);
    customer_rel cus_tmp;
    while (scan.getNextRecord(oneRec)) {
        cus_tmp = getaRecord(oneRec);
    }
	exit_database(&head);
	system("pause");
	return 0;
}

