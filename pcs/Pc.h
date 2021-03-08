//
// Created by idk on 25/01/2021.
//

#ifndef POKEMON_CLI_PC_H
#define POKEMON_CLI_PC_H


#include <string>
#include <vector>
#include "../pokemons/Pokemon.h"

class Pc {


private:
    int id;
    std::vector<Pokemon *> pokemons = {};
public:
    Pc(int id);

    int getId() const;

    void setId(int id);

    const std::vector<Pokemon *> &getPokemons() const;

    void setPokemons(const std::vector<Pokemon *> &pokemons);

    void addPokemon(Pokemon *pokemon);
};



#endif //POKEMON_CLI_PC_H
