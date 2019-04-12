//
// Created by zhouwei on 19-3-24.
//

#ifndef HWPROJECT_READDATA_H
#define HWPROJECT_READDATA_H
#include<fstream>
#include<iostream>
#include<string>
#include<vector>

class DataReader{
private:
    std::ifstream ifs_;
public:
    DataReader(std::string filepath);
    ~DataReader();
    std::vector<std::string> readLines();
    void close();
};


#endif //HWPROJECT_READDATA_H
