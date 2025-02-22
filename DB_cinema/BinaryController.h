#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>
#include "IndexController.h"
#include "Halls_data.h"
#include "Index_data.h"

template<typename T, typename IndexT>
class BinaryController {
protected:
    const size_t record_size = sizeof(T);
    std::string file_name;
    std::fstream file;
    IndexController<IndexT>& indexController; // посилання на об'єкт індекс контролера
    long first_free_pos;

    //////// Допоміжна функція для отримання ID запису
    //////int getId(const T& item) {
    //////    if constexpr (std::is_same<T, Hall>::value)
    //////        return item.id;
    //////    else if constexpr (std::is_same<T, HallType>::value)
    //////        return item.id;
    //////    return 0;
    //////}
    // Створення індексного запису із даного запису та позиції
    IndexT createIndex(const T& item, long pos) {
        if constexpr (std::is_same<T, Hall>::value)
            return IndexHall(item.id, pos, item.type_id);
        else if constexpr (std::is_same<T, HallType>::value)
            return IndexHallType(item.id, pos);
        return IndexT{};
    }

    std::streampos find_position(int id) {
        return indexController.get_position(id);
    }
public:
    BinaryController(const std::string& filename, IndexController<IndexT>& idxCtrl)
        : file_name(filename), indexController(idxCtrl), first_free_pos(-1)
    {
        file.open(file_name, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
        if (!file) {
            std::cerr << "Can`t open the file: " << file_name << std::endl;
        }
    }

    virtual ~BinaryController() {
        if (file.is_open())
            file.close();
    }

    virtual void write(std::streampos pos, T& item)
    {
        file.clear();
        file.seekp(pos, std::ios::beg);
        file.write(reinterpret_cast<const char*>(&item), record_size);

        IndexT t = IndexT(item.id, pos);

        //indexController.insert(t);

        indexController.file.seekp(0, std::ios::beg);
        indexController.file.write(reinterpret_cast<const char*>(&t), sizeof(IndexT));
    }

    virtual void insert(T& item) 
    {
        if (!file.is_open()) 
            return;
        file.clear();

        std::streampos pos = find_position(item.id);
        if (pos != -1)
        {
            T temp;
            file.seekg(pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&temp), record_size);

            if (temp.exists)
            {
                std::cerr << "Item with this ID already exists!\n";
                return;
            }
        }

        if (first_free_pos != -1)
        {
            T t;
            file.clear();
            file.seekg(first_free_pos, std::ios::beg);
            file.read(reinterpret_cast<char*>(&t), record_size);
            pos = first_free_pos;
            first_free_pos = t.next_free_pos;
        }
        else 
        {
            file.seekp(0, std::ios::end);
            pos = file.tellp();
        }

        write(pos, item);
    }

    virtual void remove(int id) 
    {
        std::streampos pos = find_position(id);
        if (pos == -1) 
        {
            std::cerr << "There is no record with this ID!" << std::endl;
            return;
        }

        file.seekg(pos, std::ios::beg);
        T item;
        file.read(reinterpret_cast<char*>(&item), record_size);

        if (!item.exists)
            return;

        item.exists = false;

        item.next_free_pos = first_free_pos;
        first_free_pos = pos;

        file.seekp(pos, std::ios::beg);
        file.write(reinterpret_cast<const char*>(&item), record_size);
        file.flush();
    }

    T get(int id) 
    {
        std::streampos pos = find_position(id);
        if (pos == -1) {
            std::cerr << "There is no record with this ID!" << std::endl;
            return T();
        }

        file.seekg(pos, std::ios::beg);
        T item;
        file.read(reinterpret_cast<char*>(&item), record_size);

        if (!item.exists)
            return T();

        return item;
    }
    
    virtual void update(int old_id, const T& item) 
    {
        std::streampos pos = find_position(old_id);

        if (pos == -1) 
        {
            std::cerr << "There is no record with this ID to update" << std::endl;
            return;
        }

        if (old_id != item.id) 
        {
            if (find_position(item.id) != -1) 
            {
                std::cerr << "The ID in updated data is already used!" << std::endl;
                return;
            }
        }

        file.seekp(pos, std::ios::beg);
        file.write(reinterpret_cast<const char*>(&item), record_size);
        file.flush();
        indexController.insert(createIndex(item, pos));
    }

    virtual void get_all() 
    {
        if (!file.is_open()) return;

        file.clear();
        file.seekg(0, std::ios::beg);
        T item;
        while (file.read(reinterpret_cast<char*>(&item), record_size))
            std::cout << item << std::endl;
    }

    virtual int calculate(bool countAll = true) 
    {
        int count = 0;
        file.clear();
        file.seekg(0, std::ios::beg);
        T item;
        
        while (file.read(reinterpret_cast<char*>(&item), record_size)) 
        {
            ++count;
        }
        
        return count;
    }
};
