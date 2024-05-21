#include <iostream>
#include "TapeController/FileTapeController.h"
#include "Sorter/Sorter.h"
#include <nlohmann/json.hpp>

int main() {
    Sorter<FileTapeController> sorter(3, "../temp/testTape.txt", "../config.json");
    sorter.sort("../output.txt");
    return 0;
}
