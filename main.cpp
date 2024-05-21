#include <iostream>
#include "TapeController/FileTapeController.h"
#include "Sorter/Sorter.h"
#include <nlohmann/json.hpp>

int main(int argc, char* argv[]) {
    if(argc != 3){
        std::cout << "Wrong number of arguments";
        return 1;
    }
    nlohmann::json j;
    std::fstream config_file("../config.json");
    config_file >> j;
    config_file.close();
    Sorter<FileTapeController> sorter(j["M"], argv[1], "../config.json");
    sorter.sort(argv[2]);
    return 0;
}
