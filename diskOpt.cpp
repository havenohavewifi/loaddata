
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"dbHead.h"


int initTable(struct dbSysHead *head, long fid)
{
	initRelation(head, fid, "customer", "TianzhenWu");
	initAttribute(head, fid, "custkey", 1, 1);
	initAttribute(head, fid, "name", 2, 64);
	initAttribute(head, fid, "address", 2, 64);
	initAttribute(head, fid, "nationkey", 1, 1);
	initAttribute(head, fid, "phone", 2, 64);
	initAttribute(head, fid, "acctbal", 2, 64);
	initAttribute(head, fid, "mktsegment", 2, 64);
	initAttribute(head, fid, "comment", 2, 128);
	return 0;
}

int showTable(struct dbSysHead *head, char* name)
{
	for (int i = 0; i < MAX_FILE_NUM; i++)
	{
		if (strcmp(name, head->desc.redef[i].relationName) == 0)
		{
            printf("dic id: %d\n",i);
			printf("TableName: %s\n", head->desc.redef[i].relationName);
			printf("Constructor: %s\n", head->desc.redef[i].constructor);
			printf("AttributeNum: %d\n", head->desc.redef[i].attributeNum);
			for (int j = 0; j < head->desc.redef[i].attributeNum; j++)
			{
				printf("%d:%s\n", j+1, head->desc.redef[i].attribute[j].attributeName);
			}
            printf("RecordLength: %d\n",head->desc.redef[i].recordLength);
			return 0;
		}
	}
	return -1;
}



/*
* @brief 初始化关系
*
* @param [in] head  : struct dbSysHead *
* @param [in] fid   : long  文件标识
* @param [in] relationName  : char* 关系名
* @param [in] constructorName :char* 建立者名
* @return int
*
* @author mengxi
* @date 2015/11/4
**/
int initRelation(struct dbSysHead *head, long fid, char *relationName, char *constructorName)
{
	int n;

	if (n = queryFileID(head, fid) == -1)
	{
		printf("can't find file!\n");
		return -1;
	}
	(head->desc).redef[n].fileID = fid;
	strcpy((head->desc).redef[n].relationName, relationName);
	strcpy((head->desc).redef[n].constructor, constructorName);
	(head->desc).redef[n].attributeNum = 0;
	(head->desc).redef[n].recordLength = 0;
	changeRecordNum(head, fid, 0);
	return 0;
}

/*
* @brief 更改记录总数
*
* @param [in] head  : struct dbSysHead *
* @param [in] fid   : long  文件标识
* @param [in] num   : int  记录总数
* @return int
*
* @author mengxi
* @date 2015/11/4
**/
int changeRecordNum(struct dbSysHead *head, long fid, int num)
{
	int n;

	if ((n = queryFileID(head, fid)) == -1)
	{
		printf("can't find file!\n");
		return -1;
	}
	(head->desc).redef[n].recordNum = num;
	return 0;
}

/*
* @brief 初始化一个属性表
*
* @param [in] head  : struct dbSysHead *
* @param [in] fid   : long  文件标识
* @param [in] name  : char* 属性名
* @param [in] type  : int  属性类型
* @param [in] length: int  属性长度
* @return int
*
* @author mengxi
* @date 2015/11/4
**/
int initAttribute(struct dbSysHead *head, long fid, char *name, int type, int length)
{
<<<<<<< Updated upstream
	int n;
	int pos;

	if (n = queryFileID(head, fid) == -1)
	{
		printf("can't find file!\n");
		return -1;
	}
	if ((head->desc).redef[n].attributeNum == ATTRIBUTENUM)
	{
		printf("too many attributes!\n");
		return -1;
	}
	pos = (head->desc).redef[n].attributeNum;
	strcpy((head->desc).redef[n].attribute[pos].attributeName, name);
	(head->desc).redef[n].attribute[pos].type = type;
	(head->desc).redef[n].attribute[pos].length = length;
	if (pos == 0)
	{
		(head->desc).redef[n].attribute[pos].recordDeviation = 0;
		switch ((head->desc).redef[n].attribute[pos].type)
		{
		case 1:(head->desc).redef[n].recordLength += sizeof(int);  break;
		case 2:(head->desc).redef[n].recordLength += length*sizeof(char); break;
		case 3:(head->desc).redef[n].recordLength += sizeof(date); break;
		}
	}
	else
	{
		switch ((head->desc).redef[n].attribute[pos].type)
		{
		case 1:(head->desc).redef[n].attribute[pos].recordDeviation = (head->desc).redef[n].recordLength;
			(head->desc).redef[n].recordLength += sizeof(int);  break;
		case 2:(head->desc).redef[n].attribute[pos].recordDeviation = (head->desc).redef[n].recordLength;
			(head->desc).redef[n].recordLength += length*sizeof(char); break;
		case 3:(head->desc).redef[n].attribute[pos].recordDeviation = (head->desc).redef[n].recordLength;
			(head->desc).redef[n].recordLength += sizeof(date); break;
		}	
	}
	(head->desc).redef[n].attributeNum++;
	return 0;
=======
    int n;
    int pos;
    
    if (n = queryFileID(head, fid) == -1)
    {
        printf("can't find file!\n");
        return -1;
    }
    if ((head->desc).redef[n].attributeNum == ATTRIBUTENUM)
    {
        printf("too many attributes!\n");
        return -1;
    }
    pos = (head->desc).redef[n].attributeNum;
    strcpy((head->desc).redef[n].attribute[pos].attributeName, name);
    (head->desc).redef[n].attribute[pos].type = type;
    (head->desc).redef[n].attribute[pos].length = length;
    if (pos == 0)
    {
        (head->desc).redef[n].attribute[pos].recordDeviation = 0;
        switch ((head->desc).redef[n].attribute[pos].type)
        {
            case 1:(head->desc).redef[n].recordLength += sizeof(int);  break;
            case 2:(head->desc).redef[n].recordLength += length*sizeof(char); break;
            case 3:(head->desc).redef[n].recordLength += sizeof(date); break;
        }
    }
    else
    {
        switch ((head->desc).redef[n].attribute[pos].type)
        {
            case 1:(head->desc).redef[n].attribute[pos].recordDeviation = (head->desc).redef[n].recordLength;
                (head->desc).redef[n].recordLength += sizeof(int);  break;
            case 2:(head->desc).redef[n].attribute[pos].recordDeviation = (head->desc).redef[n].recordLength;
                (head->desc).redef[n].recordLength += length*sizeof(char); break;
            case 3:(head->desc).redef[n].attribute[pos].recordDeviation = (head->desc).redef[n].recordLength;
                (head->desc).redef[n].recordLength += sizeof(date); break;
        }	
    }
    (head->desc).redef[n].attributeNum++;
    return 0;
>>>>>>> Stashed changes
}
/*
* @brief 删除一个属性表
*
* @param [in] head  : struct dbSysHead *
* @param [in] fid   : long  文件标识
* @param [in] name  : char* 属性名
* @return int
*
* @author mengxi
* @date 2015/11/4
**/
/*
int deleteAttribute(struct dbSysHead *head, long fid, char *name)
{
	int n;
	int num;

	if (n = queryFileID(head, fid) == -1)
	{
		printf("can't find file!\n");
		return -1;
	}
	num = (head->desc).fileDesc[n].relationDef.attributeNum;
	for (int i = 0; i < num; i++)
	{
		if (strcmp(name, (head->desc).fileDesc[n].relationDef.attribute[i].attributeName) == 0)
		{
			switch ((head->desc).fileDesc[n].relationDef.attribute[i].type)
			{
			case 1:changeRecordLength(head, fid, (head->desc).fileDesc[n].relationDef.attribute[i].length - sizeof(int)); break;
			case 2:changeRecordLength(head, fid, (head->desc).fileDesc[n].relationDef.attribute[i].length - sizeof(char)); break;
			case 3:changeRecordLength(head, fid, (head->desc).fileDesc[n].relationDef.attribute[i].length - sizeof(date)); break;
			default:
				break;
			}
			(head->desc).fileDesc[n].relationDef.attributeNum--;
			for (int j = i; j < num-1; j++)
			{
				strcpy((head->desc).fileDesc[n].relationDef.attribute[j].attributeName, (head->desc).fileDesc[n].relationDef.attribute[j+1].attributeName);
				(head->desc).fileDesc[n].relationDef.attribute[j].length = (head->desc).fileDesc[n].relationDef.attribute[j+1].length;
				(head->desc).fileDesc[n].relationDef.attribute[j].type = (head->desc).fileDesc[n].relationDef.attribute[j+1].type;
				(head->desc).fileDesc[n].relationDef.attribute[j].recordDeviation = (head->desc).fileDesc[n].relationDef.attribute[j+1].recordDeviation;
			}
			break;
		}
	}
}

*/

/**
* @brief 查询一个文件是否存在
*
* @param [in] head  : struct dbSysHead *
* @param [in] fid : long     文件标识
* @return  int
*
* @author mengxi
* @date 2015/10/20
**/
int queryFileID(struct dbSysHead *head, long fid)
{
	int i;

	for (i = 0; i<MAX_FILE_NUM; i++) {
		if ((head->desc).fileDesc[i].fileID == fid){
			break;
		}
	}
	if (MAX_FILE_NUM == i)
		return -1;
	else
		return i;
}


/**
* @brief 初始化一个Segment
*
* @param [in] head  : struct dbSysHead *
* @param [in] startPage : long     为该Segment分配的连续的页面的第一个页面的页号
* @return  int
*
* @author mengxi
* @date 2015/10/20
**/
int initSegment(struct Segment *newSegment, long startPage, long pageNum, long fd, long preAddr, long nextAddr)
{
	long i;

	for (i = 0; i<pageNum; i++){
		(*newSegment).pageNo[i] = startPage + i;
	}
	(*newSegment).count = pageNum;
	(*newSegment).fid = fd;
	(*newSegment).preAddr = preAddr;
	(*newSegment).nextAddr = nextAddr;
	return 0;
}



/**
* @brief 获得一个Segment的值
*
* @param [in] head  : struct dbSysHead *
* @param [in] SegmentAddr : long     该Segment在存储文件中的位置
* @param [out] newSegment :struct Segment *    用于接受相应的Segment
* @return  int
*
* @author mengxi
* @date 2015/10/20
**/
int getSegmentValue(struct dbSysHead *head, long segmentAddr, struct Segment *newSegment)
{
	rewind(head->fpdesc);
	fseek(head->fpdesc, segmentAddr, SEEK_SET);
	fread(newSegment, sizeof(struct Segment), 1, head->fpdesc);
	return 0;
}



/**
* @brief 把一个Segment的信息写入存储文件
*
* @param [in] head  : struct dbSysHead *
* @param [in] SegmentAddr : long     该Segment在存储文件中的位置
* @param [out] newSegment :struct Segment *    要写入的Segment内容
* @return  int
*
* @author mengxi
* @date 2015/10/20
**/
int writeSegmentValue(struct dbSysHead *head, long segmentAddr, struct Segment *newSegment)
{
	rewind(head->fpdesc);
	fseek(head->fpdesc, segmentAddr, SEEK_SET);
	fwrite(newSegment, sizeof(struct Segment), 1, head->fpdesc);
	return 0;
}



/**
* @brief 获得一个文件的最后一个Segment在存储文件中的位置
*
* @param [in] head  : struct dbSysHead *
* @param [in] fid : long     文件标识
* @return  long
* @retval  存储文件的位置
*
* @author mengxi
* @date 2015/10/20
**/
long getLastSegmentAddr(struct dbSysHead *head, long fid)
{
	struct Segment newSegment;
	int descNo;
	long segmentAddr;
	long curAddr;

	descNo = queryFileID(head, fid);
	if (descNo<0) {
		return descNo;
	}
	segmentAddr = (head->desc).fileDesc[descNo].fileAddr;
	while (segmentAddr>0) {
		getSegmentValue(head, segmentAddr, &newSegment);
		curAddr = segmentAddr;
		segmentAddr = newSegment.nextAddr;
	}
	return curAddr;
}



/**
* @brief 扩展一个文件的空间
*
* @param [in/out] head  : struct dbSysHead *
* @param [in] fid : long     文件标识
* @param [in] extendPage : long    要扩展的页数
* @return  int
*
* @author mengxi
* @date 2015/10/20
**/
int extendFileSpace(struct dbSysHead *head, long fid, int extendPage)
{
	long segmentAddr;
	struct Segment newSegment;
	struct Segment lastSegment;
	int allocStaPage;
	int i;
	int count;
	int nPage;
	int numPage;
	int idx;

	numPage = extendPage;
	allocStaPage = allocatePage(head, numPage);
	if (allocStaPage < 0) {
		printf("extendFileSpace error:out of disk space.");
		exit(0);
	}
	segmentAddr = getLastSegmentAddr(head, fid);
	getSegmentValue(head, segmentAddr, &lastSegment);
	if (lastSegment.count < PAGE_PER_SEGMENT) {
		nPage = (numPage < (PAGE_PER_SEGMENT - lastSegment.count)) ? numPage : (PAGE_PER_SEGMENT - lastSegment.count);
		count = lastSegment.count;
		for (i = 0; i<nPage; i++) {
			lastSegment.pageNo[count + i] = allocStaPage;
			allocStaPage++;
		}
		lastSegment.count += nPage;
		writeSegmentValue(head, segmentAddr, &lastSegment);
		numPage -= nPage;
	}
	if (numPage > 0) {
		while (numPage > 0) {
			nPage = (numPage < PAGE_PER_SEGMENT) ? numPage : PAGE_PER_SEGMENT;
			initSegment(&newSegment, allocStaPage, nPage, fid, segmentAddr, -1);
			allocStaPage += nPage;

			lastSegment.nextAddr = (head->desc).segmentAddr + (head->desc).segmentCur * sizeof(struct Segment);
			newSegment.preAddr = segmentAddr;
			writeSegmentValue(head, segmentAddr, &lastSegment);
			segmentAddr = lastSegment.nextAddr;
			(head->desc).segmentCur++;
			(head->desc).segmentNum++;

			lastSegment.count = newSegment.count;
			lastSegment.nextAddr = newSegment.nextAddr;
			lastSegment.preAddr = newSegment.preAddr;
			for (i = 0; i<newSegment.count; i++) {
				lastSegment.pageNo[i] = newSegment.pageNo[i];
			}
			numPage -= nPage;
		}
		writeSegmentValue(head, segmentAddr, &newSegment);
	}
	idx = queryFileID(head, fid);
	head->desc.fileDesc[idx].filePageNum += extendPage;
	return 0;
}



/**
* @brief 创建一个文件，为它分配空间
*
* @param [in/out] head  : struct dbSysHead *
* @return  int
* @retval  返回文件的标识号，即fid
*
* @author mengxi
* @date 2015/10/20
**/
long creatFileSpace(struct dbSysHead *head)
{
	struct Segment newSegment;
	long segmentAddr;
	long alloStaPage;
	int i;

	if ((head->desc).curFileNum >= MAX_FILE_NUM) {
		printf("creatFile Space error:total files cannot be more than %d.\n", (head->desc).curFileNum);
		return -1;
	}
	segmentAddr = (head->desc).segmentAddr + sizeof(struct Segment) * (head->desc).segmentCur;
	alloStaPage = allocatePage(head, PAGE_PER_SEGMENT);
	if (alloStaPage >= 0) {
		for (i = 0; i<MAX_FILE_NUM; i++) {
			if ((head->desc).fileDesc[i].fileID <= 0) {
				break;
			}
		}
		(head->desc).fileDesc[i].fileID = (head->desc).curfid;
		(head->desc).fileDesc[i].fileAddr = segmentAddr;
		(head->desc).fileDesc[i].filePageNum = PAGE_PER_SEGMENT;
		(head->desc).curFileNum++;
		initSegment(&newSegment, alloStaPage, PAGE_PER_SEGMENT, (head->desc).fileDesc[i].fileID, -1, -1);
		rewind(head->fpdesc);
		fseek(head->fpdesc, (head->desc).fileDesc[i].fileAddr, SEEK_SET);
		fwrite(&newSegment, sizeof(struct Segment), 1, head->fpdesc);
		(head->desc).segmentNum++;
		(head->desc).segmentCur++;
		(head->desc).curfid++;
	}
	else {
		printf("creatFileSpace error:creat error");
		exit(0);
	}
	return (head->desc).fileDesc[i].fileID;
}



/**
* @brief 为一个文件分配连续的空间，如果没有足够的连续空间，则不分配
*
* @param [in/out] head  : struct dbSysHead *
* @param [in] reqPageNum : int    请求分配的页数
* @return  long
* @retval  如果分配成功，则返回该连续空间的第一个页面的页号
*
* @author mengxi
* @date 2015/10/20
**/
long allocatePage(struct dbSysHead *head, int reqPageNum)
{
	long totalPage;
	int i, j;
	int page, pos;
	int count;
	int alloStaPage;

	totalPage = head->desc.totalPage;
	for (i = 0; i<totalPage; i++) {
		page = i / (8 * sizeof(long));
		pos = i - 8 * sizeof(long)*page + 1;
		count = 0;
		if (getBit(*(head->bitMap + page), pos) == P_AVAI) {
			for (j = i; count<reqPageNum && j<totalPage; j++) {
				page = j / (8 * sizeof(long));
				pos = j - 8 * sizeof(long)*page + 1;
				if (getBit(*(head->bitMap + page), pos) == P_AVAI) {
					count++;
				}
				else {
					break;
				}
			}
		}
		if (count == reqPageNum) {
			break;
		}
		else {
			i = i + count;
		}
	}
	if (count != reqPageNum) {
		return ALLO_FAIL;
	}
	else {
		alloStaPage = i;
		for (j = 0; j<reqPageNum; j++) {
			page = (i + j) / (8 * sizeof(long));
			pos = (i + j) - 8 * sizeof(long)*page + 1;
			setBit(head->bitMap + page, pos, P_UNAVAI);
		}
		(head->desc).pageAvai -= reqPageNum;
	}
	return alloStaPage;
}



/**
* @brief 回收一个页
*
* @param [in/out] head  : struct dbSysHead *
* @param [in] pageNo : int    要回收的页号
* @return  int
*
* @author mengxi
* @date 2015/10/20
**/
int recyOnePage(struct dbSysHead *head, long pageNo)
{
	int page, pos;

	page = pageNo / (sizeof(long) * 8);
	pos = pageNo - page * 8 * sizeof(long) + 1;
	setBit(head->bitMap + page, pos, P_AVAI);
	return 0;
}



/**
* @brief 回收分配给一个文件的所有页
*
* @param [in] head  : struct dbSysHead *
* @param [in] SegmentAddr : long    该文件的第一个Segment在存储文件的首地址
* @return  int
*
* @author mengxi
* @date 2015/10/20
**/
int recyPage(struct dbSysHead *head, long segmentAddr)
{
	struct Segment newSegment;
	int i;

	getSegmentValue(head, segmentAddr, &newSegment);
	for (i = 0; i<newSegment.count; i++) {
		recyOnePage(head, *(newSegment.pageNo + i));
	}
	(head->desc).segmentNum--;
	while (newSegment.nextAddr > 0) {
		getSegmentValue(head, newSegment.nextAddr, &newSegment);
		for (i = 0; i<newSegment.count; i++) {
			recyOnePage(head, *(newSegment.pageNo + i));
		}
		(head->desc).segmentNum--;
	}
	return 0;
}



/**
* @brief 删除一个文件
*
* @param [in/out] head  : struct dbSysHead *
* @param [in] fid : long    要回收的文件的标识
* @return  int
*
* @author mengxi
* @date 2015/10/20
**/
int recyFileSpace(struct dbSysHead *head, long fid)
{
	int i;

	i = queryFileID(head, fid);
	if (i < 0) {
		return i;
	}
	recyPage(head, (head->desc).fileDesc[i].fileAddr);
	(head->desc).pageAvai += (head->desc).fileDesc[i].filePageNum;
	(head->desc).fileDesc[i].fileAddr = 0;
	(head->desc).fileDesc[i].fileID = 0;
	(head->desc).fileDesc[i].filePageNum = 0;
	(head->desc).curFileNum--;
	return 0;
}