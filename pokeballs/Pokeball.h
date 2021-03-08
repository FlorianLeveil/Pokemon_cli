//
// Created by idk on 25/01/2021.
//

#ifndef POKEMON_CLI_POKEBALL_H
#define POKEMON_CLI_POKEBALL_H
#include <string>
#include "../pokemons/Pokemon.h"


class Pokeball {
private:
    int id;
    std::string name;
    float catch_value{};
    int price{};
    std::string description;
public:

    int getId() const;

    void setId(int id);

    const std::string &getName() const;

    void setName(const std::string &name);

    float getCatchValue() const;

    void setCatchValue(float catchValue);

    int getPrice() const;

    void setPrice(int price);

    const std::string &getDescription() const;

    void setDescription(const std::string &description);

    Pokeball(int id);

    bool useBall(Pokemon *pokemon) const;
};


#endif //POKEMON_CLI_POKEBALL_H
