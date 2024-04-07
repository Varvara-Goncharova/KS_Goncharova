#pragma once
#include<vector>
#include<cstdint>
#include<string>

class DataBase {
   private:
    std::vector<uint64_t> prices_;
    std::vector<uint64_t> weights_;
    uint64_t max_weight_;
   public:
    bool parse(const std::string& address);
    size_t Size() const;
    uint64_t GetMaxWeight() const; 
    uint64_t GetPrice(size_t index) const;
    uint64_t GetWeight(size_t index) const;
};