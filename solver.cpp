#include"solver.h"
#include<set>
#include<random>
#include<queue>

const size_t STEPS_AMOUNT = 1000;
const size_t GENERATION_MAX_SIZE = 100;
const size_t GENERATION_CREATION_MAX_ITERATIONS = 10000;

struct Generation{
    uint64_t weight;
    uint64_t price;
    std::vector<bool> objects;
};

bool operator<(const Generation& first, const Generation& second) {
    return first.weight < second.weight || 
        (first.weight == second.weight && first.price < second.price);
}

Answer GenerationsAlgorithm(const DataBase& data) {
    std::random_device rd;
    std::set<Generation> generations;
    size_t max_amount = 1;
    for(size_t i = 0; i < data.Size(); ++i) {
        max_amount *= 2;
    }
    max_amount = std::min(max_amount, GENERATION_MAX_SIZE);
    size_t i = 0;
    while(generations.size() < max_amount && i < GENERATION_CREATION_MAX_ITERATIONS) {
        std::vector<bool> current(data.Size(), false);
        uint64_t weight = 0;
        uint64_t price = 0;
        for(size_t i = rd() % data.Size(); i < current.size(); ++i) {
            if(weight + data.GetWeight(i) <= data.GetMaxWeight()) {
                size_t random_value = rd() % 2;
                if(random_value == 1) {
                    current[i] = true;
                    weight += data.GetWeight(i);
                    price += data.GetPrice(i);
                }
            }
        }
        generations.insert({weight, price, current});
        ++i;
    }
    for(size_t i = 0; i < STEPS_AMOUNT && generations.size() * 4 > max_amount; ++i) {
        std::priority_queue<Generation> queue;
        for(auto it = generations.begin(); it != generations.end(); ++it) {
            auto next = it;
            ++next;
            for(; next != generations.end(); ++next) {
                std::vector<bool> current(data.Size(), false);
                uint64_t weight = 0;
                uint64_t price = 0;
                for(size_t i = 0; i < data.Size(); ++i) {
                    if(weight + data.GetWeight(i) <= data.GetMaxWeight()) {
                        size_t random_value = rd() % 2;
                        if(random_value == 1) {
                            if(it->objects[i]) { 
                                current[i] = true;
                                weight += data.GetWeight(i);
                                price += data.GetPrice(i);
                            }
                        } else {
                            if(next->objects[i]) { 
                                current[i] = true;
                                weight += data.GetWeight(i);
                                price += data.GetPrice(i);
                            }
                        }
                    }
                }
                queue.push({weight, price, current});
            }
        }
        generations.clear();
        while(generations.size() < max_amount && !queue.empty()) {
            generations.insert(queue.top());
            queue.pop();
        }
    }
    Generation best = *generations.begin();
    for(const auto& generation : generations) {
        if(best.price < generation.price) {
            best = generation;
        }
    }
    std::vector<size_t> taken_objects;
    for(size_t i = 0; i < data.Size(); ++i) {
        if(best.objects[i]) {
            taken_objects.push_back(i);
        }
    }
    return {taken_objects, best.price, data.GetMaxWeight() - best.weight};
}

