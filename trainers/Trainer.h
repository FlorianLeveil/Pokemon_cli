//
// Created by idk on 25/01/2021.
//
#include<ctime>
#ifndef POKEMON_CLI_TRAINER_H
#define POKEMON_CLI_TRAINER_H
#include <string>
#include <vector>
#include "../pokemons/Pokemon.h"
#include "../bags/Bag.h"
#include "../pcs/Pc.h"


class Trainer {
private:
    int id;
    bool is_ia;
    std::string name;
    std::vector<std::string> badges;
    std::vector<Pokemon *> pokemons;
    Trainer * rivals;
    long int time_created;
    long int time_last_save;
    long int time_to_play;
    long int pokedollars;
    int rivals_id;
    int bag_id;
    Bag* bag;
    Pc* pc;

public:
    Trainer();

    Trainer(int id, bool is_ia, std::string name);

    int getRivalsId() const;

    void setRivalsId(int rivalsId);

    int getId() const;

    void setId(int id);

    bool isIa() const;

    void setIsIa(bool isIa);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::vector<std::string> &getBadges() const;

    void setBadges(const std::vector<std::string> &badges);

    const std::vector<Pokemon *> &getPokemons() const;

    void setPokemons(const std::vector<Pokemon *> &pokemons);

    Pc *getPc() const;

    void setPc(Pc *pc);

    void setPokemon(Pokemon &pokemons);

    const long int &getTimeCreated() const;

    void setTimeCreated(long int timeCreated);

    const long int &getTimeLastSave() const;

    void setTimeLastSave(long int timeLastSave);

    long int getTimeToPlay() const;

    void setTimeToPlay(long int timeToPlay);

    const Trainer *getRivals() const;

    void setRivals(Trainer *rivals);

    Bag *getBag() const;

    void setBag(Bag *bag);

    const std::vector<int> getAllPokemonId() const;

    void save();

    long getPokedollars() const;

    void setPokedollars(long pokedollars);

    int getBagId() const;

    void setBagId(int bagId);


    void healAllPokemons();
};


#endif //POKEMON_CLI_TRAINER_H
