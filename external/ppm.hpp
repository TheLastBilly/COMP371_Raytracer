#pragma once

#include <fstream>
#include <cstdio>
#include <vector>
#include <string>

#include <errno.h>
#include <cstdio>

#include "exceptions.hpp"

#ifndef uint
#define uint unsigned int
#endif

class ppm
{
    REGISTER_EXCEPTION(file_open_error, "cannot open requested file");

    static void save(const std::string& file_name, const std::vector<double>& buffer, uint dimx, uint dimy)
    {
        std::ofstream ofs(file_name, std::ios_base::out | std::ios_base::binary);
        if(!ofs.is_open())
            THROW_EXCEPTION(file_open_error, "cannot open file \"" + file_name + "\": " + std::string(strerror(errno)));

        ofs << "P6" << std::endl << dimx << ' ' << dimy << std::endl << "255" << std::endl;
    
        for (uint j = 0; j < dimy; ++j)
            for (uint i = 0; i < dimx; ++i)
                ofs << (char) (255.0 * buffer[3*j*dimx+3*i+0]) <<  (char) (255.0 * buffer[3*j*dimx+3*i+1]) << (char) (255.0 * buffer[3*j*dimx+3*i+2]);
    
        ofs.close();
    }
};