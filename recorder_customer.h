//
//  recorder_customer.h
//  loaddata
//
//  Created by IreneWu on 15/11/4.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#ifndef __loaddata__recorder_customer__
#define __loaddata__recorder_customer__

#include <stdio.h>

#define MaxChar 64
#define LongMaxChar 128
#define MaxLine 256
#define MaxColumn 16
#include "dbHead.h"

//a record length :464
struct customer_rel{
    long custkey;
    char name[MaxChar];
    char address[MaxChar];
    long nationkey;
    char phone[MaxChar];
    char acctbal[MaxChar];
    char mktsegment[MaxChar];
    char comment[LongMaxChar];
};
void readOneRecorder(char * row, char *rec, int size_per_record);
#endif /* defined(__loaddata__recorder_customer__) */
