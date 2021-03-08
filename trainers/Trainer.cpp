//
// Created by idk on 25/01/2021.
//

#include <fstream>
#include <numeric>
#include <chrono>
#include <iostream>
#include "Trainer.h"
#include "../utils/Utils.h"


bool Trainer::isIa() const {
    return is_ia;
}

void Trainer::setIsIa(bool new_isIa) {
    is_ia = new_isIa;
}

int Trainer::getId() const {
    return id;
}

void Trainer::setId(int new_Id) {
    Trainer::id = new_Id;
}

const std::string &Trainer::getName() const {
    return name;
}

void Trainer::setName(const std::string &new_name) {
    Trainer::name = new_name;
}

const std::vector<std::string> &Trainer::getBadges() const {
    return badges;
}

void Trainer::setBadges(const std::vector<std::string> &new_badges) {
    Trainer::badges = new_badges;
}

const std::vector<Pokemon *> &Trainer::getPokemons() const {
    return pokemons;
}

void Trainer::setPokemons(const std::vector<Pokemon *> &new_pokemons) {
    Trainer::pokemons = new_pokemons;
}

void Trainer::setPokemon(Pokemon &new_pokemon) {
    Trainer::pokemons.push_back(&new_pokemon);
}

long int Trainer::getTimeToPlay() const {
    return time_to_play;
}

void Trainer::setTimeToPlay(long int new_timeToPlay) {
    time_to_play = new_timeToPlay;
}

const Trainer *Trainer::getRivals() const {
    return rivals;
}

void Trainer::healAllPokemons(){
    for (auto pokemon : this->getPokemons()) {
        pokemon->setCurrentHp(pokemon->getCurrentHpMax());
    }
};

void Trainer::setRivals(Trainer *new_rivals) {
    Trainer::rivals = new_rivals;
}
Bag* Trainer::getBag() const {
    return bag;
}

void Trainer::setBag(Bag *new_bag) {
    Trainer::bag = new_bag;
}

Trainer::Trainer(int id, bool is_ia, std::string name) {
    Utils utils = Utils();
    std::vector<std::string> badges = {""};

    Pokeball* pokeball = new Pokeball(1);
    std::vector<Pokeball *> pokeballs = {pokeball, pokeball, pokeball};

    Potion* potion = new Potion(1);
    std::vector<Potion *> potions = {potion, potion, potion};

    Bag* bag = new Bag(id, pokeballs, potions);
    Pc* pc = new Pc(id);
    Trainer::setId(id);
    Trainer::setIsIa(is_ia);
    Trainer::setName(name);
    Trainer::setBadges(badges);
    Trainer::setTimeLastSave(utils.get_current_timestamp_to_int());
    Trainer::setTimeCreated(utils.get_current_timestamp_to_int());
    Trainer::setTimeToPlay(0);
    Trainer::setPokedollars(5000);
    Trainer::setBagId(id);
    Trainer::setBag(bag);
    Trainer::setPc(pc);

    if (!is_ia) {
        Trainer::setRivalsId(id + 1);
    }

}


const long int &Trainer::getTimeCreated() const {
    return time_created;
}

void Trainer::setTimeCreated(long int new_timeCreated) {
    time_created = new_timeCreated;
}

const long int &Trainer::getTimeLastSave() const {
    return time_last_save;
}

void Trainer::setTimeLastSave(long int new_timeLastSave) {
    time_last_save = new_timeLastSave;
}

const std::vector<int> Trainer::getAllPokemonId() const {
    std::vector<Pokemon *> all_pokemons = Trainer::getPokemons();
    std::vector<int> result;
    for (int i = 0; i < all_pokemons.size(); i++) {
        int pokemon_id = all_pokemons[i]->getId();
        result.push_back(pokemon_id);
    };

    return result;
}

void Trainer::save() {
    Utils utils = Utils();
    std::ofstream myFile;
    long int time_to_play = Trainer::getTimeToPlay() + (utils.get_current_timestamp_to_int() - Trainer::getTimeLastSave());
    std::vector<int> all_pokemon_id = Trainer::getAllPokemonId();
    std::string file_name = "./";


    if (Trainer::isIa()){
        file_name.append("save_RIVALS_");
    } else {
        file_name.append("save_PLAYER_");
    }
    file_name.append(std::to_string(Trainer::getId()));
    file_name.append(".csv");


    myFile.open(file_name.c_str());
    myFile << "id:" << Trainer::getId()<< std::endl;
    myFile << "is_ia:"<< Trainer::isIa() << std::endl;
    myFile << "name:" <<Trainer::getName() << std::endl;
    myFile << "badges:";
    for( const std::string & str : Trainer::getBadges() ) {
        myFile << str << " ";
    }
    myFile << std::endl;
    myFile << "pokemons:";
    for( const int & pokemon_id : all_pokemon_id) {
        myFile << std::to_string(pokemon_id) << " ";
    }
    myFile << std::endl;
    myFile <<"time_created:" << Trainer::getTimeCreated() << std::endl;
    myFile <<"time_last_save:" << utils.get_current_timestamp_to_int() << std::endl;
    myFile <<"time_to_play:" << time_to_play << std::endl;
    myFile <<"pokedollars:" << Trainer::getPokedollars() << std::endl;
    myFile <<"rivals_id:" << Trainer::getRivalsId() << std::endl;
    myFile <<"bag_id:" << Trainer::getBagId() << std::endl;

    // Close the file
    myFile.close();

}

long Trainer::getPokedollars() const {
    return pokedollars;
}

void Trainer::setPokedollars(long new_pokedollars) {
    Trainer::pokedollars = new_pokedollars;
}

int Trainer::getBagId() const {
    return bag_id;
}

void Trainer::setBagId(int new_bagId) {
    bag_id = new_bagId;
}

int Trainer::getRivalsId() const {
    return rivals_id;
}

void Trainer::setRivalsId(int new_rivalsId) {
    rivals_id = new_rivalsId;
}

Trainer::Trainer() {

}

Pc *Trainer::getPc() const {
    return pc;
}

void Trainer::setPc(Pc *pc) {
    Trainer::pc = pc;
}



