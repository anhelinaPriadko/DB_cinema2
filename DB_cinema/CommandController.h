#pragma once
#include <iostream>
#include "HallController.h"
#include "HallTypeController.h"
#include <sstream>
#include <vector>
#include <string>

class CommandController
{
private:
    IndexController<IndexHallType> indexCtrl; // оголошуємо як член класу
    IndexController<IndexHall> indexHallCtrl;
    HallTypeController halltypecontroller;
    HallController hallcontroller;

public:
    CommandController()
        : indexCtrl("IndexHallType.bin"),               // ініціалізуємо IndexController
        indexHallCtrl("IndexHall.bin"),
        halltypecontroller(indexCtrl),                  // передаємо посилання на indexCtrl
        hallcontroller(halltypecontroller, indexHallCtrl)              // передаємо посилання на halltypecontroller
    {
    }

    ~CommandController() {}

    void format()
    {
        std::cerr << "Error! Invalid format of the argument!\n";
    }

    void invNum()
    {
        std::cerr << "Invalid number of arguments!\n";
    }

    void get_command(const std::string& input)
    {
        std::istringstream iss(input);
        std::vector<std::string> tokens;
        std::string token;

        while (iss >> token) tokens.push_back(token);
        if (tokens.empty()) return;

        std::string command = tokens[0];
        tokens.erase(tokens.begin());

        if (command == "get-m") get_m(tokens);
        else if (command == "get-s") get_s(tokens);
        else if (command == "del-m") del_m(tokens);
        else if (command == "del-s") del_s(tokens);
        else if (command == "update-m") update_m(tokens);
        else if (command == "update-s") update_s(tokens);
        else if (command == "insert-m") insert_m(tokens);
        else if (command == "insert-s") insert_s(tokens);
        else if (command == "calc-m") calculate_m(tokens);
        else if (command == "calc-s") calculate_s(tokens);
        else if (command == "ut-m") ut_m(tokens);
        else if (command == "ut-s") ut_s(tokens);
        else if (command == "calc-s-r") calculate_s_r(tokens);
        else if (command == "get-s-r") get_s_r(tokens);
        else std::cout << "\nError! Invalid command!\n";
    }

    void get_m(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 1)
        {
            invNum();
            return;
        }

        try
        {
            int id = std::stoi(tokens[0]);
            std::cout << std::endl;
            halltypecontroller.get(id);
        }
        catch (const std::exception&)
        {
            format();
        }
    }

    void get_s(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 1)
        {
            invNum();
            return;
        }

        try
        {
            int id = std::stoi(tokens[0]);
            std::cout << std::endl; 
            hallcontroller.get(id);
        }
        catch (const std::exception&)
        {
            format();
        }
    }

    void get_s_r(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 1)
        {
            invNum();
            return;
        }

        try
        {
            int id = std::stoi(tokens[0]);
            hallcontroller.getByType(id);
        }
        catch (const std::exception&)
        {
            format();
        }
    }

    void del_m(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 1)
        {
            invNum();
            return;
        }

        try
        {
            int id = std::stoi(tokens[0]);
            halltypecontroller.remove(id);
            hallcontroller.removeByHallType(id);
        }
        catch (const std::exception&)
        {
            format();
        }
    }

    void del_s(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 1)
        {
            invNum();
            return;
        }

        try
        {
            int id = std::stoi(tokens[0]);
            hallcontroller.remove(id);
        }
        catch (const std::exception&)
        {
            format();
        }
    }

    void update_s(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 6)
        {
            invNum();
            return;
        }

        try
        {
            Hall item(std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]),
                std::stoi(tokens[4]), true, tokens[5].c_str());

            hallcontroller.update(std::stoi(tokens[0]), item);
        }
        catch (const std::exception&)
        {
            format();
        }
    }

    void update_m(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 3)
        {
            invNum();
            return;
        }

        try
        {
            HallType item(std::stoi(tokens[1]), true, tokens[2].c_str());
            halltypecontroller.update(std::stoi(tokens[0]), item);
        }
        catch (const std::exception&)
        {
            format();
        }
    }

    void insert_m(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 2)
        {
            invNum();
            return;
        }

        try
        {
            HallType item(std::stoi(tokens[0]), true, tokens[1].c_str());
            halltypecontroller.insert(item);
        }
        catch (const std::exception&)
        {
            format();
        }
    }

    void insert_s(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 5)
        {
            invNum();
            return;
        }

        try
        {
            Hall item(std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]),
                std::stoi(tokens[3]), true, tokens[4].c_str());

            hallcontroller.insert(item);
        }
        catch (const std::exception&)
        {
            format();
        }
    }

    void calculate_m(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 0)
        {
            invNum();
            return;
        }

        try
        {
            std::cout << "\nNumber of records in master table: "
                << halltypecontroller.calculate() << "\n";
        }
        catch (const std::exception&)
        {
            format();
        }   
    }

    void calculate_s(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 0)
        {
            invNum();
            return;
        }

        try
        {
            std::cout << "\nNumber of records in slave table: "
                << hallcontroller.calculate() << "\n";
        }
        catch (const std::exception&)
        {
            format();
        }
    }

    void calculate_s_r(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 0)
        {
            invNum();
            return;
        }

        try
        {
            int id = std::stoi(tokens[0]);
            std::cout << "\nNumber of records in slave table with type id " << id << ": "
                << hallcontroller.calculateByType(id) << "\n";
        }
        catch (const std::exception&)
        {
            format();
        }
    }

    void ut_m(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 0)
        {
            invNum();
            return;
        }

        try
        {
            std::cout << "\nRecords in master table:\n";
            std::cout << std::left << std::setw(10) << "ID"
                << std::setw(10) << "EXISTS"
                << std::setw(20) << "NEXT FREE POS"
                << std::setw(30) << "NAME" << std::endl;
            halltypecontroller.get_all();
        }
        catch (const std::exception&)
        {
            format();
        }
    }

    void ut_s(const std::vector<std::string>& tokens)
    {
        if (tokens.size() != 0)
        {
            invNum();
            return;
        }

        try
        {
            std::cout << std::left << std::setw(10) << "ID"
                << std::setw(20) << "NUMBER OF ROWS"
                << std::setw(20) << "SEATS IN ROW"
                << std::setw(20) << "TYPE ID"
                << std::setw(10) << "EXISTS"
                << std::setw(20) << "NEXT FREE POS"
                << std::setw(30) << "NAME" << std::endl;

            hallcontroller.get_all();
        }
        catch (const std::exception&)
        {
            format();
        }
    }
};
