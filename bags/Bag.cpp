//
// Created by idk on 25/01/2021.
//

#include <fstream>
#include <utility>
#include "Bag.h"
#include "../utils/CsvReader.h"
#include "../utils/Utils.h"

Bag::Bag(int id, std::vector<Pokeball *> &pokeballs, std::vector<Potion *> &potions) : id(id),
                                                                                      pokeballs(pokeballs),
                                                                                      potions(potions) {
    Bag::setId(id);
    Bag::setPokeballs(pokeballs);
    Bag::setPotion(potions);
}

int Bag::getId() const {
    return id;
}

void Bag::setId(int new_id) {
    Bag::id = new_id;
}

bool Bag::useItemByName(std::string item_name, Pokemon* pokemon_opponent, Pokemon* pokemon_player) {
    bool is_pokeball = true;
    bool result = false;
    int i = 0;

    for (auto potion : this->potions) {
        if (item_name == potion->getName()) {
            result = potion->usePotion(pokemon_player);
            is_pokeball = false;
            break;
        }
        i = i + 1;
    };
    if (!is_pokeball) {
        this->potions.erase(this->potions.begin() + i);
    }
    i = 0;
    if (is_pokeball) {
        for (auto pokeball : this->pokeballs) {
            if (item_name == pokeball->getName()) {
                result = pokeball->useBall(pokemon_opponent);
                break;
            }
            i = i + 1;
        }
        this->pokeballs.erase(this->pokeballs.begin() + i);
    }

    return result;
}

const std::vector<Pokeball *> &Bag::getPokeballs() const {
    return pokeballs;
}

void Bag::setPokeballs(const std::vector<Pokeball *> &new_pokeballs) {
    Bag::pokeballs = new_pokeballs;
}

void Bag::addPokeball(Pokeball &new_pokeball) {
    Bag::pokeballs.push_back(&new_pokeball);
}

const std::vector<int> Bag::getAllPokeballsId() const {
    std::vector<Pokeball *> all_pokeballs = Bag::getPokeballs();
    std::vector<int> result;
    for (int i = 0; i < all_pokeballs.size(); i++) {
        int pokeball_id = all_pokeballs[i]->getId();
        result.push_back(pokeball_id);
    };

    return result;
}

const std::vector<Potion *> &Bag::getPotions() const {
    return potions;
}

void Bag::setPotion(const std::vector<Potion *> &new_potion) {
    Bag::potions = new_potion;
}

void Bag::addPotion(Potion &new_potion) {
    Bag::potions.push_back(&new_potion);
}



const std::vector<int> Bag::getAllPotionId() const {
    std::vector<Potion *> all_potions = Bag::getPotions();
    std::vector<int> result;
    for (int i = 0; i < all_potions.size(); i++) {
        int potion_id = all_potions[i]->getId();
        result.push_back(potion_id);
    };

    return result;
}


Bag::Bag(int id) : id(id) {
    CsvReader reader("/home/idk/Cours/C++/Pokemon_cli/pokeballs/pokeballs.csv");
    std::vector<std::vector<std::string> > dataList = reader.getData();
    int id_bag = id;
    Bag::setId(id_bag);
    int line = 1;
    for(const std::vector<std::string>& vec : dataList)
    {
        if (line == id_bag) {
            int col = 0;
            for (const std::string &data : vec) {
                if (col > 0) {
                    Pokeball pokeball = Pokeball(std::stoi(data));
                    Bag::addPokeball(pokeball);
                };
            }
        }
        if (line == id_bag + 1) {
            int col = 0;
            for (const std::string &data : vec) {
                if (col > 0) {
                    Potion potion = Potion(std::stoi(data));
                    Bag::addPotion(potion);
                };
            }
        }
        line++;
    }
}

void Bag::save() {
    Utils utils = Utils();
    std::vector<int> all_potions_id = Bag::getAllPotionId();
    std::vector<int> all_pokeballs_id = Bag::getAllPokeballsId();
    std::ofstream myFile("./save_bags.csv");
    myFile << Bag::getId() <<"|";
    for( const int & str : all_potions_id ) {
        myFile << str << "|";
    }
    myFile << std::endl;
    myFile << Bag::getId() <<"|";

    for( const int & str2 : all_pokeballs_id ) {
        myFile << str2 << "|";
    }
    myFile << std::endl;
    myFile.close();
}

