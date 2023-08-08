#pragma once

#include <fstream>
#include <iostream>
#include <ctime>


class log
{
    private:

    std::string time_stamp();
    std::string path();
    void flush();

    public:

    log();
    ~log();
};


