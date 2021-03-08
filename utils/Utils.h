//
// Created by idk on 18/01/2021.
//

#ifndef POKEMON_CLI_UTILS_H
#define POKEMON_CLI_UTILS_H
#include <string>
#include <vector>
#include "../menus/Menu.h"
#include "../trainers/Trainer.h"


class Utils {
public:
    Utils();

    std::string create_white_space(int nb_white_space);
    std::string print_menu_func(Menu *menu);
    std::string print_menu_func(Menu *menu, Trainer *rivals);
    static bool replace(std::string &str, const std::string &from, const std::string &to);
    long int get_current_timestamp_to_int();
    long int timestamp_to_int(auto value);

    static void _pokemon_print_menu_func(Menu *menu, Pokemon *pokemon);

    std::string print_menu_func(Menu *menu, Trainer *trainer, Pokemon *pokemon);

    std::string print_menu_func(Menu *menu, Pokemon *pokemon);

    std::string print_menu_func(Menu *menu, Trainer *trainer, Trainer *rivals);

    void pokecenter(std::string);
    std::string getPokemonNameWithId(int pokemon_id);

    bool checkMoves(std::string pokemon_name);

    int printInputUser(int choice);

    bool pokeshop(std::string anwser, Trainer *player);
};


#endif //POKEMON_CLI_UTILS_H
