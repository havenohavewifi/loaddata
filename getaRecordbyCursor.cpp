//
//  getaRecordbyCursor.cpp
//  loaddata
//
//  Created by IreneWu on 15/11/6.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//
#
#include "getaRecordbyCursor.h"
#include "cursor.h"
#include "recorder_customer.h"

customer_rel getaRecord( char *oneRec){

    customer_rel cus_tmp;
    void * longa = malloc(8);
    memcpy(longa, oneRec, 8);
    char *longach = new char[4];
    longach = (char *)longa;
    char* dd =new char[4];
    for(int i=0;i<4;i++)
    {
        dd=&longach[i];
        dd++;
    }
    long* tt =(long * )dd;
    long ss = *tt;

    
    cus_tmp.custkey = ss;
    memcpy(cus_tmp.name, oneRec+8, 64);
    memcpy(cus_tmp.address, oneRec+72, 64);
    
    memset(longa, 0, 8);
    memcpy(longa, oneRec+136, 8);
    
    longach = (char *)longa;
    dd =new char[4];
    for(int i=0;i<4;i++)
    {
        dd=&longach[i];
        dd++;
    }
    tt =(long * )dd;
    ss = *tt;
    
    cus_tmp.nationkey = ss;
    memcpy(cus_tmp.phone, oneRec+144, 64);
    memcpy(cus_tmp.acctbal, oneRec+208, 64);
    memcpy(cus_tmp.mktsegment, oneRec+272, 64);
    memcpy(cus_tmp.comment, oneRec+336, 128);
//print some atrribute to test
//    cout<<cus_tmp.name<<endl;
//  cout<<cus_tmp.nationkey<<endl;
    free(longa);
    return cus_tmp;
}