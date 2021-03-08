//
// Created by idk on 25/01/2021.
//

#include "Pokeball.h"
#include "../utils/CsvReader.h"
#include <math.h>
#define CYN "\e[00;36m"
#define YLW "\e[00;93m"
#define NC "\e[0m"
#include <unistd.h>
#include <iostream>
#include <random>

#define BLUE "\e[0;94m"



const std::string &Pokeball::getName() const {
    return name;
}

void Pokeball::setName(const std::string &new_name) {
    Pokeball::name = new_name;
}

float Pokeball::getCatchValue() const {
    return catch_value;
}

void Pokeball::setCatchValue(float new_catchValue) {
    catch_value = new_catchValue;
}

int Pokeball::getPrice() const {
    return price;
}

void Pokeball::setPrice(int new_price) {
    Pokeball::price = new_price;
}

const std::string &Pokeball::getDescription() const {
    return description;
}

void Pokeball::setDescription(const std::string &new_description) {
    Pokeball::description = new_description;
}

int Pokeball::getId() const {
    return id;
}

bool Pokeball::useBall(Pokemon * pokemon) const {
    std::string white_space_before_text(25, ' ');
    float percent = (((1 +  ((float(pokemon->getCurrentHpMax()) *3) - (float(pokemon->getCurrentHp()) * 2))) * 200 * this->getCatchValue() * 1) / (float(pokemon->getCurrentHpMax()) *3)) / 256;
    int percent_100 = (int)(float(100) * percent);
    std::cout << white_space_before_text << CYN << "You use " << YLW << this->getName() << CYN << " on "<< BLUE << pokemon->getName() << NC << std::endl;
    sleep(2);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,100);
    if (percent_100 >= dist6(rng)) {
        std::cout << white_space_before_text << CYN << "Great congrulation, you got " <<YLW << pokemon->getName() << CYN << " !"<< NC << std::endl;
        sleep(2);
        return true;
    } else {
        std::cout << white_space_before_text << CYN << "The capture of " <<YLW << pokemon->getName() << CYN << " failed !"<< NC << std::endl;
        sleep(2);
        return false;
    }
}

void Pokeball::setId(int new_id) {
    Pokeball::id = new_id;
}

Pokeball::Pokeball(int id): id(id){

    CsvReader reader("/home/idk/Cours/C++/Pokemon_cli/pokeballs/pokeballs.csv");
    std::vector<std::vector<std::string> > dataList = reader.getData();

    int id_ball = id;
    int line = 1;
    for(const std::vector<std::string>& vec : dataList)
    {
        if (line == id_ball) {
            int col = 0;
            for (const std::string &data : vec) {
                if (col == 4) {
                    Pokeball::setDescription(data);
                };
                if (col == 3) {
                    Pokeball::setPrice(std::stoi(data));
                    col++;
                };
                if (col == 2) {
                    Pokeball::setCatchValue(std::stof(data));
                    col++;
                };
                if (col == 1) {
                    Pokeball::setName(data);
                    col++;
                };
                if (col == 0) {
                    Pokeball::setId(std::stoi(data));
                    col++;
                };
            }
        }
        line++;
    }
}