#pragma once

#include"data_base.h"
#include<vector>
#include<cstddef>
#include<cstdint>


struct Answer {
    std::vector<size_t> taken_objects;
    uint64_t price;
    uint64_t offset;
};

Answer GenerationsAlgorithm(const DataBase& data);