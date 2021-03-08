//
// Created by idk on 25/01/2021.
//
#include "Pc.h"

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
