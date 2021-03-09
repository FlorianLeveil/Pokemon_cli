//
// Created by idk on 25/01/2021.
//
#include <iostream>
#include "Pc.h"
#include "../trainers/Trainer.h"
#include "../utils/Utils.h"
#include <unistd.h>


Pc::Pc(int id) : id(id) {
    this->id = id;
    this->pokemons = {};
}

int Pc::getId() const {
    return id;
}

void Pc::setId(int id) {
    Pc::id = id;
}

const std::vector<Pokemon *> &Pc::getPokemons() const {
    return pokemons;
}

void Pc::setPokemons(const std::vector<Pokemon *> &pokemons) {
    Pc::pokemons = pokemons;
}void

Pc::addPokemon(Pokemon *pokemon) {
    Pc::pokemons.push_back(pokemon);
}

void Pc::deletePokemon(const Pokemon * pokemon) {
    Pc::pokemons.erase(std::remove(Pc::pokemons.begin(), Pc::pokemons.end(), pokemon), Pc::pokemons.end());
}

bool Pc::seePokemons() {
    Utils * utils = new Utils();

    system("clear");
    int count = 0;
    if (this->pokemons.empty()) {
        std::cout << "PC: you don't have any pokemons in your pc !" << std::endl;
        sleep(2);
        delete utils;
        return false;
    } else {
        for (auto pokemon : this->pokemons) {
            count += 1;
            std::cout << "| Nb: " << count << " | Name: " << pokemon->getName() << " | Lvl: " << pokemon->getLvl() << std::endl;
        }
        std::cout << "| Choice 1: BACK |"<< std::endl;
        utils->printInputUser(1);
    }
    delete utils;
    return true;
}
bool Pc::putPokemons(Trainer * player) {
    Utils * utils = new Utils();
    int user_choice = 0;
    system("clear");
    std::cout << "PC: which pokemons do you want to put in PC ?" << std::endl;
    std::cout << std::endl;
    int count = 0;
    for (auto pokemon : player->getPokemons()) {
        count += 1;
        std::cout << "| Choice: " <<count << " | Name: " << pokemon->getName() << " | Lvl: " << pokemon->getLvl() << std::endl;
    }
    std::cout << "| Choice: " << count + 1 << " | BACK"<< std::endl;
    user_choice = utils->printInputUser(count + 1);
    if (user_choice == count + 1) {
        std::cout << "PC: Bye" << std::endl;
        sleep(2);
        delete utils;
        return false;
    } else {
        std::cout << "PC: you put: " << player->getPokemons()[user_choice - 1]->getName() << " in your pc !"<< std::endl;
        sleep(3);
        this->addPokemon(player->getPokemons()[user_choice - 1]);
        player->deletePokemon(player->getPokemons()[user_choice - 1]);
        delete utils;
        return true;
    }

}
bool Pc::takePokemons(Trainer * player) {

    system("clear");
    Utils * utils = new Utils();
    int user_choice = 0;
    system("clear");
    std::cout << "PC: which pokemons do you want to take in PC ?" << std::endl;

    int count = 0;
    for (auto pokemon : this->getPokemons()) {
        count += 1;
        std::cout << "| Choice: " <<count << " | Name: " << pokemon->getName() << " | Lvl: " << pokemon->getLvl() << std::endl;
    }
    std::cout << "| Choice: " << count + 1 << " | BACK"<< std::endl;
    user_choice = utils->printInputUser(count + 1);
    if (user_choice == count + 1) {
        std::cout << "PC: Bye" << std::endl;
        sleep(2);
        delete utils;
        return false;
    } else {
        std::cout << "PC: you put: " << this->getPokemons()[user_choice - 1]->getName() << " in your team !"<< std::endl;
        sleep(3);
        player->addPokemon(this->getPokemons()[user_choice - 1]);
        this->deletePokemon(this->getPokemons()[user_choice - 1]);
        delete utils;
        return true;
    }
}