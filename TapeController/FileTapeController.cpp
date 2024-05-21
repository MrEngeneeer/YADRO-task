//
// Created by IvanGan on 20.05.2024.
//

#include <iostream>
#include "FileTapeController.h"
#include "windows.h"
#include <nlohmann/json.hpp>

FileTapeController::FileTapeController(std::string const& file_path, std::string const& config_path) {
    _file.open(file_path, std::ios::in);
    if (!_file) {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }
    _is_empty=false;
    _filePath = file_path;
    _newNumbers.clear();
    _file >> _currentNumber;
    nlohmann::json config_json;
    std::fstream config_file(config_path);
    config_file >> config_json;
    config_file.close();
    _read_time = config_json["read time"];
    _write_time = config_json["write time"];
    _shift_time = config_json["shift time"];
    _reset_time = config_json["reset time"];
}

FileTapeController::FileTapeController(std::string const& file_path) {
    _file.open(file_path, std::ios::in);
    if (!_file) {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }
    _is_empty=false;
    _filePath = file_path;
    _newNumbers.clear();
    _file >> _currentNumber;
    _read_time = 0;
    _write_time = 0;
    _shift_time = 0;
    _reset_time = 0;
}

int FileTapeController::get_number() {
    Sleep(_read_time);
    return _currentNumber;
}

void FileTapeController::go_forward(){
    Sleep(_shift_time);
    _newNumbers.push_back(_currentNumber);
    _file >> _currentNumber;
    if(!_file){
        _is_empty = true;
    }
}

void FileTapeController::set_number(int value) {
    Sleep(_write_time);
    _currentNumber = value;
    _is_empty = true;
}

void FileTapeController::reset() {
    Sleep(_reset_time);
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
