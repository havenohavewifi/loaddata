//
//  main.cpp
//  loaddata
//
//  Created by IreneWu on 15/11/3.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "loaddata.h"
#include "Buffer.h"
#include "dbHead.h"
#include "recorder_customer.h"

using namespace std;
string src="/Users/irene/Desktop/customer.tbl";

void loaddata(struct dbSysHead * head)
{
    
    ifstream infile;
    infile.open(src.c_str());
    if(!infile)
    {
        cout<<"open file failure"<<endl;
    }
    else{
        int size_per_record = sizeof(customer_rel);
        char oneRec[size_per_record];
        string tmp;
        Buffer t(head);
        int k=0;
        unsigned long len;
        long pageNum = 0;
        //get one line from customer.tbl
        while (getline(infile,tmp)) {
            int tmp_len = tmp.length();
            char * oneRow = new char[tmp_len+1];
            memcpy(oneRow, tmp.c_str(), tmp_len);
            //split this line and get one recorder
            readOneRecorder(oneRow, oneRec, size_per_record);
            //if more than one page, write to file and reset Buffer t
            if(false == t.AppendBuffer(oneRec, size_per_record))
            {
                t.writeBuffer(t.filehead, t.data_, t.current_size_);
                t.pageID++;
                memset(t.data_, 0, SIZE_PER_PAGE);
                memcpy(t.data_, oneRec, size_per_record);
                t.pointer_ = t.data_+size_per_record;
                t.current_size_ = size_per_record;
            }
            k++;
            if(k>40) break;
        }
        //write remainder
        t.writeBuffer(head, t.data_, t.current_size_);
        
//打印几个字符串检查一下
        void * readcontent = malloc(60);
        rdFile(head, 1, 8, 64, readcontent);
        char *rec = (char *)readcontent;
        cout<<rec<<endl;
        
        rdFile(head, 1, 136, 8, readcontent);
        rec = (char *)readcontent;
        cout<<rec<<endl;
        
        void * intcontent = malloc(8);
        rdFile(head, 1, 0, 8, intcontent);
        
        //        long * readtoint = (long *)readint;
        //        long readvalue = *readtoint;
        
        long readvalue = (long)intcontent;
        cout<<readvalue<<endl;
        rec = (char *)readcontent;
         
        free(readcontent);
    }


}

