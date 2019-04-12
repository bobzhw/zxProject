//
// Created by zhouwei on 19-4-1.
//

#ifndef MATHNLP_WRITEDATA_H
#define MATHNLP_WRITEDATA_H

#include<fstream>
#include<string>

using namespace std;


class DataWriter {
public:
    DataWriter(const std::string& filepath);
    void write(const std::string& line);
    void write(int line)
    {
        ofs_ << line;
    }
    void writeLine(const std::string& line);
    void writeLine(int line)
    {
        ofs_ << line << "\n";
    }
    void close();
private:
    fstream ofs_;
};


#endif //MATHNLP_WRITEDATA_H
