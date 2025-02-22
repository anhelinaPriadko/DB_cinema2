#pragma once
#include <iostream>
#include "BinaryController.h"
#include "Halls_data.h"
#include "Index_data.h"
#include "IndexController.h"

class HallTypeController : public BinaryController<HallType, IndexHallType> {
public:
    HallTypeController(IndexController<IndexHallType>& idxCtrl)
        : BinaryController<HallType, IndexHallType>("HallTypes.bin", idxCtrl)
    {
    }

    void get(int id)
    {
        HallType item = BinaryController<HallType, IndexHallType>::get(id);

        /*std::cout << std::left << std::setw(10) << "ID"
            << std::setw(30) << "NAME" << std::endl;*/

        std::cout << std::left << std::setw(10) << item.id
            << std::setw(30) << item.name << std::endl;
    }

    void get_all() override
    {
        BinaryController<HallType, IndexHallType>::get_all();
    }
};
