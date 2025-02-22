#pragma once
#include <iostream>
#include "BinaryController.h"
#include "HallTypeController.h"

class HallController : public BinaryController<Hall, IndexHall> {
private:
    HallTypeController& hallTypeController;
public:
    HallController(HallTypeController& typeController, IndexController<IndexHall>& idxCtrl)
        : BinaryController<Hall, IndexHall>("Halls.bin", idxCtrl),
        hallTypeController(typeController) {}

    void insert(Hall& hall) override 
    {
        HallType ht = hallTypeController.BinaryController<HallType, IndexHallType>::get(hall.type_id);
        if (!ht.exists) 
        {
            std::cerr << "There is no hall type with this id!" << std::endl;
            return;
        }
        if (indexController.check_exist(hall.id)) {
            std::cerr << "There is already a record with this id!" << std::endl;
            return;
        }
        BinaryController<Hall, IndexHall>::insert(hall);
    }

    void update(int old_id, const Hall& hall) override 
    {
        if (!indexController.check_exist(old_id)) 
        {
            std::cerr << "There is no record with this id to update!" << std::endl;
            return;
        }

        HallType ht = hallTypeController.BinaryController<HallType, IndexHallType>::get(hall.type_id);
        if (!ht.exists) 
        {
            std::cerr << "There is no hall type with this id!" << std::endl;
            return;
        }
        BinaryController<Hall, IndexHall>::update(old_id, hall);
    }

    void removeByHallType(int hall_type_id) 
    {
        file.clear();
        file.seekg(0, std::ios::beg);
        IndexHall temp;

        while (BinaryController<Hall, IndexHall>::indexController.file.read(reinterpret_cast<char*>(&temp),
            BinaryController<Hall, IndexHall>::indexController.record_size)) 
        {
            if (temp.type_id == hall_type_id)
                remove(temp.id);
        }
    }

    void getByType(int id)
    {
        file.clear();
        file.seekg(0, std::ios::beg);

        std::cout << std::left << std::setw(10) << "ID"
            << std::setw(20) << "NUMBER OF ROWS"
            << std::setw(20) << "SEATS IN ROW"
            << std::setw(20) << "TYPE ID"
            << std::setw(30) << "NAME" << std::endl;

        IndexHall temp;
        while (BinaryController<Hall, IndexHall>::indexController.file.read(reinterpret_cast<char*>(&temp),
            BinaryController<Hall, IndexHall>::indexController.record_size))
        {
            if (temp.type_id == id)
                get(temp.id);
        }
   
    }

    int calculateByType(int id)
    {
        file.clear();
        file.seekg(0, std::ios::beg);

        IndexHall temp;
        int counter = 0;
        while (BinaryController<Hall, IndexHall>::indexController.file.read(reinterpret_cast<char*>(&temp),
            BinaryController<Hall, IndexHall>::indexController.record_size))
        {
            if (temp.type_id == id)
                ++counter;
        }

        return counter;
    }

    void get(int id)
    {
        Hall item = BinaryController<Hall, IndexHall>::get(id);

        /*std::cout << std::left << std::setw(10) << "ID"
            << std::setw(20) << "NUMBER OF ROWS"
            << std::setw(20) << "SEATS IN ROW"
            << std::setw(20) << "TYPE ID"
            << std::setw(30) << "NAME" << std::endl;*/

        std::cout << std::left << std::setw(10) << item.id
            << std::setw(20) << item.number_of_rows
            << std::setw(20) << item.seats_in_row
            << std::setw(20) << item.type_id
            << std::setw(30) << item.name << std::endl;
    }

    void get_all() override
    {
        BinaryController<Hall, IndexHall>::get_all();
    }
};
