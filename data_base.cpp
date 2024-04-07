#include "data_base.h"
#include<fstream>
#include<utility>

size_t DataBase::Size() const {
    return weights_.size();
}

uint64_t DataBase::GetPrice(size_t index) const {
    return prices_[index];
}

uint64_t DataBase::GetWeight(size_t index) const {
    return weights_[index];
}

bool DataBase::parse(const std::string& address) {
    std::ifstream fin(address.data());
    if(!fin) {
        return false;
    }
    size_t size;
    size_t max_weight;
    fin >> size >> max_weight;
    std::vector<uint64_t> prices;
    std::vector<uint64_t> weights;
    for(size_t i = 0; i < size; ++i) {
        uint64_t price;
        uint64_t weight;
        fin >> price >> weight;
        prices.push_back(price);
        weights.push_back(weight);
    }
    fin.close();
    max_weight_ = max_weight;
    prices_ = std::move(prices);
    weights_ = std::move(weights);
    return true;
}

uint64_t DataBase::GetMaxWeight() const {
    return max_weight_;
}