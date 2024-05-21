//
// Created by IvanGan on 20.05.2024.
//

#ifndef YADRO_SORTER_H
#define YADRO_SORTER_H


#include <string>
#include <cmath>
#include <fstream>
#include <algorithm>

template<typename T>
class Sorter {
public:
    Sorter(int M, const std::string& input_file_path);

    Sorter(int M, const std::string& input_file_path, const std::string& config_path);

    void sort(std::string outFilePath);

private:
    int M{};
    T* _output_tape;
    T* _input_tape;
    T* _first_temp_tape;
    T* _second_temp_tape;
    T* _first_trash_tape;
    T* _second_trash_tape;

    void merge_tapes(int size_of_target_tape, int size_of_blocks, T* target_tape);
};

template<typename T>
Sorter<T>::Sorter(int M, const std::string& input_file_path) {
    this->M = M;
    _input_tape = new T(input_file_path);
    std::ofstream file;
    file.open("../temp/tape1.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.open("../temp/tape2.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.open("../temp/tape3.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.open("../temp/tape4.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
    _first_temp_tape = new T("../temp/tape1.txt");
    _second_temp_tape = new T("../temp/tape2.txt");
    _first_trash_tape = new T("../temp/tape3.txt");
    _second_trash_tape = new T("../temp/tape4.txt");
}

template<typename T>
Sorter<T>::Sorter(int M, const std::string& input_file_path, const std::string& config_path) {
    this->M = M;
    _input_tape = new T(input_file_path);
    std::ofstream file;
    file.open("../temp/tape1.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.open("../temp/tape2.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.open("../temp/tape3.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.open("../temp/tape4.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
    _first_temp_tape = new T("../temp/tape1.txt", config_path);
    _second_temp_tape = new T("../temp/tape2.txt", config_path);
    _first_trash_tape = new T("../temp/tape3.txt", config_path);
    _second_trash_tape = new T("../temp/tape4.txt", config_path);
}

template<typename T>
void Sorter<T>::merge_tapes(int size_of_target_tape, int size_of_blocks, T* target_tape) {
    (*_first_temp_tape).reset();
    (*_second_temp_tape).reset();
    for(int i = 0; i < size_of_target_tape / size_of_blocks; i++){

    }
}

template<typename T>
void Sorter<T>::sort(std::string outFilePath) {
    _output_tape = new T(outFilePath);
    int block_size = M;
    int total_blocks = 0;
    std::vector<int> memory(block_size);
    int N = 0;
    while(!(*_input_tape).is_empty()){
        total_blocks++;
        for(int i = 0; i < block_size; i++){
            memory[i] = (*_input_tape).get_number();
            N++;
            (*_input_tape).go_forward();
            if((*_input_tape).is_empty()){
                std::sort(memory.begin(), memory.begin() + i + 1);
                for(int j = 0; j < i + 1; j++){
                    (*_first_temp_tape).set_number(memory[j]);
                    (*_first_temp_tape).go_forward();
                }
                break;
            }
        }
        if((*_input_tape).is_empty()){
            break;
        }
        std::sort(memory.begin(), memory.end());
        for(int i = 0; i < block_size; i++){
            (*_first_temp_tape).set_number(memory[i]);
            (*_first_temp_tape).go_forward();
        }
    }
    (*_first_temp_tape).reset();
    int first_tape_size = (N / block_size / 2 + N / block_size % 2) * block_size;
    int second_tape_size = (N / block_size / 2) * block_size + N % block_size;
    int new_number;
    for(int i = 0; i < first_tape_size; i++){
        (*_first_temp_tape).go_forward();
    }
    while(!(*_first_temp_tape).is_empty()){
        (*_second_temp_tape).set_number((*_first_temp_tape).get_number());
        (*_first_temp_tape).go_forward();
        (*_second_temp_tape).go_forward();
    }

    (*_first_temp_tape).reset();
    (*_second_temp_tape).reset();
    //Раскидал блоки по двум начальным лентам
    int size_of_first_block, size_of_second_block;
    for(int i = 0, c = block_size; i < (int)(log(N / c) / log(c)); i++){
        first_tape_size = (N / block_size / 2 + N / block_size % 2) * block_size;
        second_tape_size = (N / block_size / 2) * block_size + N % block_size;
        for(int j = 0; j < (N / (block_size * 2) / 2 + N / (block_size * 2) % 2) * (block_size * 2);){
            if(first_tape_size == 0){
                size_of_first_block = 0;
            } else {
                size_of_first_block = block_size;
            }
            if(second_tape_size == 0){
                size_of_second_block = 0;
            } else {
                size_of_second_block = block_size;
            }
            while(size_of_first_block > 0 || size_of_second_block > 0){
                if(size_of_second_block == 0){
                    new_number = (*_first_temp_tape).get_number();
                    (*_first_temp_tape).go_forward();
                    size_of_first_block--;
                    first_tape_size--;
                }else if(size_of_first_block == 0){
                    new_number = (*_second_temp_tape).get_number();
                    (*_second_temp_tape).go_forward();
                    size_of_second_block--;
                    second_tape_size--;
                }else if((*_first_temp_tape).get_number() <= (*_second_temp_tape).get_number()){
                    new_number = (*_first_temp_tape).get_number();
                    (*_first_temp_tape).go_forward();
                    size_of_first_block--;
                    first_tape_size--;

                }else{
                    new_number = (*_second_temp_tape).get_number();
                    (*_second_temp_tape).go_forward();
                    size_of_second_block--;
                    second_tape_size--;
                }
                j++;
                (*_first_trash_tape).set_number(new_number);
                (*_first_trash_tape).go_forward();
                if(first_tape_size == 0){
                    size_of_first_block = 0;
                }
                if(second_tape_size == 0){
                    size_of_second_block = 0;
                }
            }
        }
        (*_first_trash_tape).reset();
        for(int j = 0; j < (N / (block_size * 2) / 2) * 2 * block_size + N % (block_size * 2);){
            size_of_first_block = block_size;
            size_of_second_block = block_size;
            if(first_tape_size == 0){
                size_of_first_block = 0;
            }
            if(second_tape_size == 0){
                size_of_second_block = 0;
            }
            while(size_of_first_block > 0 || size_of_second_block > 0){
                if(size_of_second_block == 0){
                    new_number = (*_first_temp_tape).get_number();
                    (*_first_temp_tape).go_forward();
                    first_tape_size--;
                    size_of_first_block--;
                }else if(size_of_first_block == 0){
                    new_number = (*_second_temp_tape).get_number();
                    (*_second_temp_tape).go_forward();
                    second_tape_size--;
                    size_of_second_block--;
                }else if((*_first_temp_tape).get_number() <= (*_second_temp_tape).get_number()){
                    new_number = (*_first_temp_tape).get_number();
                    (*_first_temp_tape).go_forward();
                    first_tape_size--;
                    size_of_first_block--;
                }else{
                    new_number = (*_second_temp_tape).get_number();
                    (*_second_temp_tape).go_forward();
                    second_tape_size--;
                    size_of_second_block--;
                }
                j++;
                (*_second_trash_tape).set_number(new_number);
                (*_second_trash_tape).go_forward();
                if(first_tape_size == 0){
                    size_of_first_block = 0;
                }
                if(second_tape_size == 0){
                    size_of_second_block = 0;
                }
            }
        }
        block_size *= 2;
        (*_second_trash_tape).reset();
        (*_first_temp_tape).reset();
        (*_second_temp_tape).reset();
        std::swap(_first_temp_tape, _first_trash_tape);
        std::swap(_second_temp_tape, _second_trash_tape);
    }
    first_tape_size = (N / block_size / 2 + N / block_size % 2) * block_size;
    second_tape_size = (N / block_size / 2) * block_size + N % block_size;
    size_of_first_block = first_tape_size;
    size_of_second_block = first_tape_size;
    while(size_of_first_block > 0 || size_of_second_block > 0){
        if(size_of_second_block == 0){
            new_number = (*_first_temp_tape).get_number();
            (*_first_temp_tape).go_forward();
            first_tape_size--;
            size_of_first_block--;
        }else if(size_of_first_block == 0){
            new_number = (*_second_temp_tape).get_number();
            (*_second_temp_tape).go_forward();
            second_tape_size--;
            size_of_second_block--;
        }else if((*_first_temp_tape).get_number() <= (*_second_temp_tape).get_number()){
            new_number = (*_first_temp_tape).get_number();
            (*_first_temp_tape).go_forward();
            first_tape_size--;
            size_of_first_block--;
        }else{
            new_number = (*_second_temp_tape).get_number();
            (*_second_temp_tape).go_forward();
            second_tape_size--;
            size_of_second_block--;
        }
        (*_output_tape).set_number(new_number);
        (*_output_tape).go_forward();
        if(first_tape_size == 0){
            size_of_first_block = 0;
        }
        if(second_tape_size == 0){
            size_of_second_block = 0;
        }
    }
    (*_output_tape).reset();
}

#endif //YADRO_SORTER_H
