//
// Created by zhouwei on 19-3-24.
//

#include "ReadData.h"
DataReader::DataReader(std::string filepath)
{

    ifs_.open(filepath,std::ios::out | std::ios::binary);
}

std::vector<std::string> DataReader::readLines()
{
    std::string line;
    std::vector<std::string> vec;
    while(getline(ifs_,line))
    {
//        std::cout << line << std::endl;
        vec.push_back(line);
    }
    return vec;
}

DataReader::~DataReader()
{
    ifs_.close();
}

void DataReader::close()
{
    ifs_.close();
}