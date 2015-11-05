//
//  recorder_customer.cpp
//  loaddata
//
//  Created by IreneWu on 15/11/4.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//
#include <string>
#include <iostream>
#include "recorder_customer.h"
#include "Buffer.h"
#include "dbHead.h"
using namespace std;

void readOneRecorder(char * ctmp, char * rec,int size_per_record){
    customer_rel cus;
    const char split[] = "|";
    char * p[MaxColumn];
    
    int i=0;
    int curCol = 0;
        p[curCol] = strtok (ctmp,split);
        cus.custkey = atol(p[curCol++]);
        p[curCol] = strtok(NULL,split);
        strcpy(cus.name,p[curCol++]);
        p[curCol] = strtok(NULL,split);
        strcpy(cus.address,p[curCol++]);
        p[curCol] = strtok(NULL,split);
        cus.nationkey = atol(p[curCol++]);
        p[curCol] = strtok(NULL,split);
        strcpy(cus.phone,p[curCol++]);
        p[curCol] = strtok(NULL,split);
        strcpy(cus.acctbal,p[curCol++]);
        p[curCol] = strtok(NULL,split);
        strcpy(cus.mktsegment,p[curCol++]);
        p[curCol] = strtok(NULL,split);
        strcpy(cus.comment,p[curCol++]);
    char recorder_tmp_[size_per_record];
    /*
    char a[8] = {((char*)&cus.custkey)[0],((char*)&cus.custkey)[1],((char*)&cus.custkey)[2],((char*)&cus.custkey)[3],((char*)&cus.custkey)[4],((char*)&cus.custkey)[5],((char*)&cus.custkey)[6],((char*)&cus.custkey)[7]};
     
    char b[8] = {((char*)&cus.nationkey)[0],((char*)&cus.nationkey)[1],((char*)&cus.nationkey)[2],((char*)&cus.nationkey)[3],((char*)&cus.custkey)[4],((char*)&cus.custkey)[5],((char*)&cus.custkey)[6],((char*)&cus.custkey)[7]};
    */
 //   char * a = (char*)malloc(8*sizeof(char));
 //   cout<<(cus.custkey&0xFF)<<endl;
    /*
    unsigned char a[8];
    a[0]=(cus.custkey>>56);
    a[1]=(cus.custkey&0xFF000000000000)>>48;
    a[2]=(cus.custkey&0xFF0000000000)>>40;
    a[3]=(cus.custkey&0xFF00000000)>>32;
    a[4]=(cus.custkey&0xFF000000)>>24;
    a[5]=(cus.custkey&0xFF0000)>>16;
    a[6]=(cus.custkey&0xFF00)>>8;
    a[7]=(cus.custkey&0xFF);
    */
    long lcuskey=cus.custkey;
    char a[4];
    long * la = &lcuskey;
    int t;
    for(t=0;t<4;t++)
    {
        a[i]=(char)*la;
        la++;
    }
    long lnationkey = cus.nationkey;
    char b[4];
    long * lb = &lnationkey;
    for(t=0;t<4;t++)
    {
        b[i]=(char)*lb;
        lb++;
    }
    
    memcpy(recorder_tmp_, a, 8);
    memcpy(recorder_tmp_+8, cus.name, 64);
    memcpy(recorder_tmp_+72, cus.address, 64);
    memcpy(recorder_tmp_+136, b, 8);
    memcpy(recorder_tmp_+144, cus.phone, 64);
    memcpy(recorder_tmp_+208, cus.acctbal, 64);
    memcpy(recorder_tmp_+272, cus.mktsegment, 64);
    memcpy(recorder_tmp_+336, cus.comment, 128);
//    free(a);
    memcpy(rec, recorder_tmp_, size_per_record);

}
