#include"parser.h"
#include<fstream>

bool Parser::Print(const std::string& str, const Answer& answer) const {
    std::ofstream fout(str.data());
    if(!fout) {
        return false;
    }
    fout << answer.price << " " << answer.offset << std::endl;
    for(size_t i = 0; i < answer.taken_objects.size(); ++i) {
        fout << answer.taken_objects[i] + 1 << " ";
    } 
    fout.close();
    return true;
}