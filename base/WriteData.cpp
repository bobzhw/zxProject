//
// Created by zhouwei on 19-4-1.
//

#include "WriteData.h"


DataWriter::DataWriter(const std::string& filepath)
{
    ofs_.open(filepath,ios::out|ios::binary);

}

void DataWriter::write(const std::string& line)
{
    ofs_ << line;
//    ofs_.flush();
}

void DataWriter::writeLine(const std::string &line)
{
    ofs_ << line << endl;
//    ofs_.flush();
}

void DataWriter::close()
{
    ofs_.flush();
    ofs_.close();
}