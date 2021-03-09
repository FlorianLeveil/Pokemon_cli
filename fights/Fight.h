//
// Created by idk on 01/03/2021.
//

#ifndef POKEMON_CLI_FIGHT_H
#define POKEMON_CLI_FIGHT_H


#include "../trainers/Trainer.h"
#include "../utils/Utils.h"
#include "../pcs/Pc.h"

class Fight {
private:
    int id;
    Trainer * player = nullptr;
    Trainer * opponent = nullptr;
    Pokemon * pokemon = nullptr;
    Pokemon * current_pokemon_player = nullptr;
    Pokemon * current_pokemon_opponent = nullptr;
    Pc * pc = nullptr;
    std::vector<Pokemon *> player_pokemon_live =  {nullptr};
    std::vector<Pokemon *> player_pokemon_dead = {nullptr};
    std::vector<Pokemon *> opponent_pokemon_live =  {nullptr};
    std::vector<Pokemon *> opponent_pokemon_dead = {nullptr};
    Utils utils = Utils();


    std::string player_pokemon_live_string = "";
    std::string player_pokemon_dead_string = "";


    std::string opponent_pokemon_live_string = "";
    std::string opponent_pokemon_dead_string = "";

    std::string message_lvl = "Lvl:";
    std::string message_name = "Name:";
    std::string message_pokemon = "Pokemon:";
    std::string message_pokemon_exp= "EXP:";
    std::string message_pokemon_pv= "PV:";
    std::string message_pokemon_sauvage = "SAUVAGE";


    std::string select_action_fight = "1: FIGHT";
    std::string select_action_bag = "2: BAG";
    std::string select_action_pokemon = "3: POKEMONS";
    std::string select_action_run = "4: RUN";
public:
    Fight(int id, Trainer *player, Trainer *opponent, Pc * pc);
    Fight(int id, Trainer *player, Pc * pc);

    void viewFightInterface();
    void startFight();
    int selectBag();
    void selectFight();
    bool selectPokemon(bool do_back = false);
    bool selectRun();

    void setPlayer(Trainer *player);

    void printVS();

    void printPokemonBlock(bool opponent, bool pokemon);

    void printPrincipalChoice();

    void computeLiveDeadPokemon(Trainer *player, std::vector<Pokemon *> *pokemon_dead, std::vector<Pokemon *> *pokemon_live, std::string *pokemon_dead_string, std::string *pokemon_live_string);

    int printInputUser(int choice);

    void printAllFightInterface();

    bool doOpponentFight();

    bool doPlayerFight(Move *move);

    int cumpteExpWin(Pokemon *pokemon);

    bool doFight(Move *move, bool just_for_opponent = false);

    void selectPokemonForOpponent();

    virtual ~Fight();

};


#endif //POKEMON_CLI_FIGHT_H
