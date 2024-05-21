//
// Created by IvanGan on 20.05.2024.
//

#include <iostream>
#include "FileTapeController.h"

FileTapeController::FileTapeController(std::string const& file_path, std::string const& config_path) {
    _file.open(file_path, std::ios::in);
    if (!_file) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }
    _is_empty=false;
    _filePath = file_path;
    _newNumbers.clear();
    _file >> _currentNumber;

    std::ifstream config_file("config.json");
}

FileTapeController::FileTapeController(std::string const& file_path) {
    _file.open(file_path, std::ios::in);
    if (!_file) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }
    _is_empty=false;
    _filePath = file_path;
    _newNumbers.clear();
    _file >> _currentNumber;

    std::ifstream config_file("config.json");
}

int FileTapeController::get_number() {
    return _currentNumber;
}

void FileTapeController::go_forward(){
    _newNumbers.push_back(_currentNumber);
    _file >> _currentNumber;
    if(!_file){
        _is_empty = true;
    }
}

void FileTapeController::set_number(int value) {
    _currentNumber = value;
    _is_empty = true;
}

void FileTapeController::reset() {
    if(!_is_empty) {
        _newNumbers.push_back(_currentNumber);
    }

    _is_empty = false;

    while (_file >> _currentNumber) {
        _newNumbers.push_back(_currentNumber);
    }
    _file.close();
    std::ofstream _newFile(_filePath);

    for (int i : _newNumbers) {
        _newFile << i << std::endl;
    }
    _newFile.close();
    _file.open(_filePath);
    _file >> _currentNumber;
    _newNumbers.clear();
}

bool FileTapeController::is_empty() {
    return _is_empty;
}
