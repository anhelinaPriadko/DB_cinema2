#pragma once
#include <iostream>
#include <iomanip>
#include <cstring>

struct Hall {
    int id;
    int number_of_rows;
    int seats_in_row;
    int type_id; // посилання на тип залу
    long next_free_pos;
    bool exists;
    char name[30];

    Hall(int id = 0, int n_rows = 0, int s_row = 0, int t_id = 0, bool e = true, const char* _name = "")
        : id(id), number_of_rows(n_rows), seats_in_row(s_row), type_id(t_id),
        next_free_pos(-1), exists(e)
    {
        strncpy_s(name, _name, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }

    friend std::ostream& operator<<(std::ostream& os, const Hall& hall) {
        os << std::left << std::setw(10) << hall.id
            << std::setw(20) << hall.number_of_rows
            << std::setw(20) << hall.seats_in_row
            << std::setw(20) << hall.type_id
            << std::setw(10) << hall.exists
            << std::setw(20) << hall.next_free_pos
            << std::setw(30) << hall.name << std::endl;
        return os;
    }
};

struct HallType {
    int id;  // ID типу залу
    long next_free_pos;
    bool exists;
    char name[30];

    HallType(int id = 0, bool e = true, const char* _name = "")
        : id(id), next_free_pos(-1), exists(e)
    {
        strncpy_s(name, _name, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }

    friend std::ostream& operator<<(std::ostream& os, const HallType& ht) {
        os << std::left << std::setw(10) << ht.id
            << std::setw(10) << ht.exists
            << std::setw(20) << ht.next_free_pos
            << std::setw(30) << ht.name << std::endl;
        return os;
    }
};
