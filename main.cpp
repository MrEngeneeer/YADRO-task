#include <iostream>
#include "TapeController/FileTapeController.h"
#include "Sorter/Sorter.h"

int main() {
    Sorter<FileTapeController> sorter(3, "../temp/testTape.txt");
    sorter.sort("../output.txt");
    return 0;
}
