//
// Created by idk on 25/01/2021.
//

#ifndef POKEMON_CLI_BAG_H
#define POKEMON_CLI_BAG_H
#include <vector>
#include "../pokeballs/Pokeball.h"
#include "../potions/Potion.h"
#include "../pokemons/Pokemon.h"


class Bag {
private:
    int id;
    std::vector<Pokeball *> pokeballs;
    std::vector<Potion *> potions;
public:
    Bag(int id, std::vector<Pokeball *> &pokeballs, std::vector<Potion *> &potions);

    int getId() const;

    void setId(int id);

    const std::vector<Pokeball *> &getPokeballs() const;

    void setPokeballs(const std::vector<Pokeball *> &pokeballs);

    void addPokeball(Pokeball &pokeball);

    const std::vector<Potion *> &getPotions() const;

    void setPotion(const std::vector<Potion *> &potion);

    Bag(int id);

    void addPotion(Potion &new_potion);

    void save();

    const std::vector<int> getAllPotionId() const;

    const std::vector<int> getAllPokeballsId() const;

    bool useItemByName(std::string item_name, Pokemon * pokemon_opponent, Pokemon * pokemon_player);
};


#endif //POKEMON_CLI_BAG_H
