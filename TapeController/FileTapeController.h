//
// Created by IvanGan on 20.05.2024.
//

#ifndef YADRO_FILETAPECONTROLLER_H
#define YADRO_FILETAPECONTROLLER_H


#include <vector>
#include <fstream>

class FileTapeController{
public:

    FileTapeController(const std::string& file_path, const std::string& config_path);

    FileTapeController(const std::string& file_path);

    void go_forward();

    int get_number();

    bool is_empty();

    void set_number(int value);

    void reset();

private:
    bool _is_empty;
    std::vector<int> _newNumbers;
    std::fstream _file;
    int _currentNumber{};
    std::string _filePath;
};


#endif //YADRO_FILETAPECONTROLLER_H
