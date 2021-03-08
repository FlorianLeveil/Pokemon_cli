//
// Created by idk on 25/01/2021.
//

#include <iostream>
#include "Potion.h"
#include "../utils/CsvReader.h"
#define CYN "\e[00;36m"
#define YLW "\e[00;93m"
#define NC "\e[0m"
#include <unistd.h>
#define BLUE "\e[0;94m"






Potion::Potion(int id, std::string &name, int heal) : id(id), name(name), heal(heal) {}

int Potion::getId() const {
    return id;
}

void Potion::setId(int new_id) {
    Potion::id = new_id;
}

const std::string &Potion::getName() const {
    return name;
}

void Potion::setName(const std::string &new_name) {
    Potion::name = new_name;
}

int Potion::getHeal() const {
    return heal;
}

void Potion::setHeal(int new_heal) {
    Potion::heal = new_heal;
}


int Potion::getPrice() const {
    return price;
}

void Potion::setPrice(int new_price) {
    Potion::price = new_price;
}

const std::string &Potion::getDescription() const {
    return description;
}

void Potion::setDescription(const std::string &new_description) {
    Potion::description = new_description;
}

bool Potion::usePotion(Pokemon *pokemon) const {
    std::string white_space_before_text(25, ' ');
    std::cout << white_space_before_text << CYN << "You use " << YLW << this->getName() << CYN << " on "<< BLUE << pokemon->getName() << NC << std::endl;
    sleep(2);
    if (pokemon->getCurrentHp() + this->getHeal() >= pokemon->getCurrentHpMax()) {
        std::cout << white_space_before_text << YLW << this->getName() << CYN << " restore "<< YLW << pokemon->getCurrentHpMax() - pokemon->getCurrentHp() << CYN << " HP on " << YLW << pokemon->getName() << NC << std::endl;
        pokemon->setCurrentHp(pokemon->getCurrentHpMax());
        sleep(2);

    } else {
        pokemon->setCurrentHp(pokemon->getCurrentHp() + this->getHeal());
        std::cout << white_space_before_text << YLW << this->getName() << CYN << " restore "<< YLW << this->getHeal() << CYN << " HP on " << BLUE << pokemon->getName() << NC << std::endl;
        sleep(2);

    }


    return false;
}


Potion::Potion(int id) : id(id) {

    CsvReader reader("/home/idk/Cours/C++/Pokemon_cli/potions/potions.csv");
    std::vector<std::vector<std::string> > dataList = reader.getData();

    int id_potion = id;
    int line = 1;
    for(const std::vector<std::string>& vec : dataList)
    {
        if (line == id_potion) {
            int col = 0;
            for (const std::string &data : vec) {
                if (col == 4) {
                    Potion::setDescription(data);
                };
                if (col == 3) {
                    Potion::setPrice(std::stoi(data));
                    col++;
                };
                if (col == 2) {
                    Potion::setHeal(std::stoi(data));
                    col++;
                };
                if (col == 1) {
                    Potion::setName(data);
                    col++;
                };
                if (col == 0) {
                    Potion::setId(std::stoi(data));
                    col++;
                };
            }
        }
        line++;
    }
}
