# loaddata
customer.tbl是源数据文件 
Buffer.h Buffer.cpp是写文件的缓存类
recorder_customer.h recorder_customer.cpp是记录关系customer.tbl的类
loaddata.h loaddata.cpp 是把customer.tbl解析并写入file的方法
为了调试方便，我在file.h里修改里SIZE_DATA_SPACE的大小，test.cpp也做了一些修改
注意 fileID是从1开始编号
