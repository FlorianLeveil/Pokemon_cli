#include <iostream>
#include "utils/CsvReader.h"
#include "menus/Menu.h"
#include "trainers/Trainer.h"
#include "fights/Fight.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define PURPLE "\e[0;35m"
#define BLUE "\e[0;94m"
#define CYN "\e[00;36m"
#define CYN2 "\e[00;96m"
#define YLW "\e[00;93m"
#include <random>

int main() {

    auto * first_pokemon_player = new Pokemon("Charmander", 1);
//    auto * first_pokemon_player2 = new Pokemon("Palkia", 4);
//    auto * first_pokemon_player3 = new Pokemon("Dialga", 2);
//    auto * first_pokemon_player4 = new Pokemon("Giratina", 6);
//    auto * first_pokemon_player5 = new Pokemon("Darkrai", 3);
   auto * first_pokemon_player6 = new Pokemon("Arceus", 7);
//
//
//
//    auto * first_pokemon_rivals = new Pokemon("Squirtle", 5);
//
   Trainer * player = new Trainer(1, false, "Florian");
   Trainer * rivals = new Trainer(2, true, "Antoine");
    player->setPokemon(*first_pokemon_player);
    player->setPokemon(*first_pokemon_player6);


    Utils * utils = new Utils();

    std::string user_choice1 = "0";
    Menu* menu1 = new Menu(1);
    user_choice1 = utils->print_menu_func(menu1);
    if (user_choice1 == "0") {
        // Choice name
        std::string user_choice_name = "";
        Menu* menu6 = new Menu(6);
        user_choice_name = utils->print_menu_func(menu6);
        Trainer* player = new Trainer(1, false, user_choice_name);
        delete menu6;

        // Choice Rivals Name
        std::string user_choice_name_rivals = "";
        Menu* menu7 = new Menu(7);
        user_choice_name_rivals = utils->print_menu_func(menu7);
        Trainer* rivals = new Trainer(2, true, user_choice_name_rivals);
        delete menu7;

        // Chen Speak
        Menu* menu8 = new Menu(8);
        user_choice1 = utils->print_menu_func(menu8, rivals);
        delete menu8;

        Menu* menu9 = new Menu(9);
        user_choice1 = utils->print_menu_func(menu9, rivals);
        delete menu9;

        Menu* menu10 = new Menu(10);
        user_choice1 = utils->print_menu_func(menu10, rivals);
        delete menu10;

        std::string user_choice_pokemon = "";
        Menu* menu11 = new Menu(11);
        user_choice_pokemon = utils->print_menu_func(menu11,player,rivals);
        delete menu11;

        Pokemon* first_pokemon_player;
        Pokemon* first_pokemon_rivals;

        if (user_choice_pokemon == "0") {
            first_pokemon_player = new Pokemon("Charmander", 5);
            first_pokemon_rivals = new Pokemon("Squirtle", 5);
            player->setPokemon(*first_pokemon_player);
            rivals->setPokemon(*first_pokemon_rivals);

        } else if (user_choice_pokemon == "1") {
            first_pokemon_player = new Pokemon("Squirtle", 5);
            first_pokemon_rivals = new Pokemon("Bulbasaur", 5);
            player->setPokemon(*first_pokemon_player);
            rivals->setPokemon(*first_pokemon_rivals);

        } else {
            first_pokemon_player = new Pokemon("Bulbasaur", 5);
            first_pokemon_rivals = new Pokemon("Charmander", 5);
            player->setPokemon(*first_pokemon_player);
            rivals->setPokemon(*first_pokemon_rivals);

        }
        Menu* menu19 = new Menu(19);
        user_choice1 = utils->print_menu_func(menu19, first_pokemon_player);
        delete menu19;

        Menu* menu12 = new Menu(12);
        user_choice1 = utils->print_menu_func(menu12, rivals);
        delete menu12;

        Menu* menu13 = new Menu(13);
        user_choice1 = utils->print_menu_func(menu13, rivals);
        delete menu13;

        Menu* menu14 = new Menu(14);
        user_choice1 = utils->print_menu_func(menu14,player,rivals);
        delete menu14;

        Menu* menu15 = new Menu(15);
        user_choice1 = utils->print_menu_func(menu15, rivals);
        delete menu15;

        Menu* menu16= new Menu(16);
        user_choice1 = utils->print_menu_func(menu16, rivals);
        delete menu16;

        Menu* menu17 = new Menu(17);
        user_choice1 = utils->print_menu_func(menu17,player);
        delete menu17;

        Menu* menu18 = new Menu(18);
        user_choice1 = utils->print_menu_func(menu18, rivals, first_pokemon_rivals);
        delete menu18;

        //FIGHT
        Menu* menu20 = new Menu(20);
        user_choice1 = utils->print_menu_func(menu20,player,rivals);
        delete menu20;

        auto* fight1 = new Fight(1,player, rivals);
        fight1->viewFightInterface();
        delete fight1;

    } else if (user_choice1 == "1") {

    } else if (user_choice1 == "2") {

    }
    std::string user_choice = "0";
    Menu *mainMenu = new Menu(2);

    while (true) {
        system("clear");
        user_choice = utils->print_menu_func(mainMenu, player, rivals);

        if (user_choice == "0") {
            Fight * fight_wild_herb = new Fight(0, player);
            fight_wild_herb->viewFightInterface();
            delete fight_wild_herb;
        } else if (user_choice == "1") {

        } else if (user_choice == "2") {
            Menu *pokecenterMenu = new Menu(3);
            std::string user_choice_pokecenter = utils->print_menu_func(pokecenterMenu, player);
            delete pokecenterMenu;

            if (user_choice_pokecenter == "0") {
                player->healAllPokemons();
            }
            utils->pokecenter(user_choice_pokecenter);
        } else if (user_choice == "3") {
            Menu *shopMenu = new Menu(4);
            std::string user_choice_pokeshop = utils->print_menu_func(shopMenu, player);
            delete shopMenu;
            utils->pokeshop(user_choice_pokeshop, player);

        } else if (user_choice == "4") {

        } else if (user_choice == "5") {

        } else if (user_choice == "6") {

        } else if (user_choice == "7") {

        } else if (user_choice == "8") {

        } else if (user_choice == "9") {

        } else if (user_choice == "10") {
            break;
        }
    }
}
