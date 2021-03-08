//
// Created by idk on 25/01/2021.
//

#ifndef POKEMON_CLI_POTION_H
#define POKEMON_CLI_POTION_H
#include <string>
#include "../pokemons/Pokemon.h"

class Potion {
private:
    int id;
    std::string name;
    int heal;
    int price;
    std::string description;
public:
    Potion(int id, std::string &name, int heal);

    int getId() const;

    void setId(int id);

    const std::string &getName() const;

    void setName(const std::string &name);

    int getHeal() const;

    void setHeal(int heal);

    const std::string &getDescription() const;

    void setDescription(const std::string &description);

    int getPrice() const;

    bool usePotion(Pokemon *pokemon) const;

    void setPrice(int price);

    Potion(int id);


};


#endif //POKEMON_CLI_POTION_H
