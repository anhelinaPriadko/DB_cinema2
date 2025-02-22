#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>

template<typename T>
class IndexController 
{
private:
    std::string file_name;
public:
    std::fstream file;
    const size_t record_size = sizeof(T);

    IndexController(const std::string& filename) : file_name(filename) 
    {
        file.open(file_name, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
        if (!file) {
            std::cerr << "Can`t open the file: " << file_name << std::endl;
        }
    }

    ~IndexController() 
    {
        if (file.is_open()) { file.close(); }
    }

    std::streampos get_position(int id) 
    {
        file.clear();
        file.seekg(0, std::ios::beg);
        T item;
        while (file.read(reinterpret_cast<char*>(&item), record_size)) {
            if (item.id == id)
                return item.position;
        }
        return -1;
    }

    bool check_exist(int id) 
    {
        return get_position(id) != -1;
    }

    void insert(const T& item) 
    {
        file.clear();
        file.seekg(0, std::ios::beg);
        std::streampos pos = -1;

        T temp;
        while (file.read(reinterpret_cast<char*>(&temp), record_size)) {
            if (item.position == temp.position)
            {
                pos = file.tellg() - static_cast<std::streampos>(record_size);
                break;
            }
        }

        if (pos != -1)
        {
            file.seekp(pos, std::ios::beg);
        }
        else
            file.seekp(0, std::ios::end);


        file.write(reinterpret_cast<const char*>(&item), record_size);
        file.flush();
        return;
    }
};
