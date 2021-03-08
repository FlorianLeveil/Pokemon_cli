//
// Created by idk on 25/01/2021.
//

#include "Menu.h"
#include "../utils/Utils.h"
#include "../utils/CsvReader.h"

Menu::Menu(int id, std::string &header, std::vector<std::string> &choice) : id(id), header(header),
                                                                                        choice(choice) {}

int Menu::getId() const {
    return id;
}

void Menu::setId(int new_id) {
    Menu::id = new_id;
}

const std::string &Menu::getHeader() const {
    return header;
}

void Menu::setHeader(const std::string &new_header) {
    Menu::header = new_header;
}

const std::string &Menu::getType() const {
    return type;
}

void Menu::setType(const std::string &new_type) {
    Menu::type = new_type;
}

const std::vector<std::string> &Menu::getChoice() const {
    return choice;
}

void Menu::setChoice(const std::vector<std::string> &new_choice) {
    Menu::choice = new_choice;
}
const std::string &Menu::getName() const {
    return name;
}

void Menu::setName(const std::string &new_name) {
    Menu::name = new_name;
}

Menu::Menu() {}

Menu::Menu(int id) : id(id) {
    std::vector<std::string> choices {};

    CsvReader reader("/home/idk/Cours/C++/Pokemon_cli/menus/text.csv");
    std::vector<std::vector<std::string> > dataList = reader.getData();

    int id_menu = id;
    int line = 1;
    for(const std::vector<std::string>& vec : dataList)
    {
        if (line == id_menu) {

            int col = 0;
            for (const std::string &data : vec) {
                if (col == 4) {
                    choices.push_back(data);
                };
                if (col == 3) {
                    Menu::setHeader(data);
                    col++;
                };
                if (col == 2) {
                    Menu::setName(data);
                    col++;
                };
                if (col == 1) {
                    Menu::setType(data);
                    col++;
                };
                if (col == 0) {
                    Menu::setId(std::stoi(data));
                    col++;
                };
            }
        }
        line++;
    }
    Menu::setChoice(choices);
}

Menu::~Menu() {
}
