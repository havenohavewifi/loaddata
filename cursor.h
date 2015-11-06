//
//  cursor.h
//  loaddata
//
//  Created by IreneWu on 15/11/6.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#ifndef __loaddata__cursor__
#define __loaddata__cursor__

#include <stdio.h>
/*
extern "C" {
    // #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbHead.h"
};
extern "C" {
    extern int reqPage(struct  dbSysHead *head, long query);
    extern long mapPage(struct dbSysHead *head, long fid, long num);
}
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "dbHead.h"
using namespace std;

class RecordCursor
{
public:
    // construct function
    RecordCursor(struct dbSysHead *head, long fid, long recordLength) {
        int idx = queryFileID(head, fid);
        if(idx < 0) {
            cout << fid << "file doesn't exist!" << endl;
            exit(0);
        }
        this->head = head;
        this->fid = fid;
        this->recordLength = recordLength;
        this->cLogicPage = -1;
        this->cBufferPage = 0;
        this->bufferOffset = 0;
        this->start = true;
        this->filePageNum = head->desc.fileDesc[idx].filePageNum;
    }
    
    bool getNextRecord(void *des);
    
private:
    struct dbSysHead *head;
    long fid;
    long cLogicPage;
    long filePageNum;
    long cBufferPage;
    long bufferOffset;
    long recordLength;
    bool start;
};




// int getNextPage(struct dbSysHead *head, long fid, long num) {

// 	int pageIdInDisk = mapPage(head, fid, num+1);

// 	return reqPage(head, pageIdInDisk);
// }

// int getNextRecord(struct dbSysHead *head, long mapNo, long offset, long recordLen) {

// 	return head->buff.data[mapNo][offset:offset+recordLen]
// }
#endif /* defined(__loaddata__cursor__) */
