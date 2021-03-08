//
// Created by idk on 18/01/2021.
//

#include "Utils.h"
#include "../trainers/Trainer.h"
#include "CsvReader.h"
#include <iostream>
#include <cstdlib>
#include <chrono>

#define NC "\e[0m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define RED "\e[41m"
#define YLW "\e[00;93m"

#include <unistd.h>



Utils::Utils() {}

std::string Utils::getPokemonNameWithId(int pokemon_id){
    CsvReader reader("/home/idk/Cours/C++/Pokemon_cli/pokemons/Pokemons.csv", ",");
    std::vector<std::vector<std::string> > dataList = reader.getData();

    for (const std::vector<std::string> &vec : dataList) {
        if (vec[0] == std::to_string(pokemon_id)) {
            return vec[3];
        }
    }
}

bool Utils::checkMoves(std::string pokemon_name) {
    bool is_good = false;

    CsvReader reader2("/home/idk/Cours/C++/Pokemon_cli/pokemons/pokemon-data.csv", ";");
    std::vector<std::vector<std::string> > dataList2 = reader2.getData();
    for (const std::vector<std::string> &vec : dataList2) {
        if (vec[0] == pokemon_name) {
            is_good = true;
            break;
        }
    }

    return is_good;
}

void Utils::pokecenter(std::string do_heal) {
    system("clear");

    if (do_heal == "1") {
        std::cout << GRN<<"Nurse Joelle:"<< NC <<"No worries I don't heal your pokemons." << std::endl;
        sleep(2);
    } else {
        std::cout << GRN<<"Nurse Joelle:"<< NC <<"Alright give me your pokemons please." << std::endl;
        sleep(2);
        std::cout << GRN<<"Nurse Joelle:"<< NC <<"It's good your pokemons are in great shape ! Bye." << std::endl;
        sleep(2);

    }
}

int Utils::printInputUser(int choice) {
    bool not_valid = true;
    std::string user_choice = "0";
    int user_choice_int = 0;

    while (not_valid) {
        std::cout << std::endl;
        std::cout << "Your choice: ";
        std::cin >> user_choice;

        if (std::cin.fail()) {
            std::cout << "Your input is not valid !" << std::endl;
            std::cin.clear();
            std::cin.ignore(80, '\n');

        } else {
            user_choice_int = std::stoi(user_choice);
            if (user_choice_int >= 0 && user_choice_int <= choice) {
                std::cin.clear();
                std::cin.ignore(80, '\n');
                not_valid = false;
            } else {
                std::cout << "Your input is not valid !" << std::endl;
                std::cin.clear();
                std::cin.ignore(80, '\n');
            }
        }
    }
    return user_choice_int;
}

bool Utils::pokeshop(std::string anwser, Trainer * player) {
    system("clear");
    bool is_potion = false;
    bool is_pokeball = false;
    int user_choice = 0;
    Potion * item_potion = nullptr;
    Pokeball * item_pokeball = nullptr;

    if (anwser == "1") {
        is_potion = true;
        std::vector<Potion *> all_potions = {new Potion(1), new Potion(2), new Potion(3), new Potion(4)};
        std::cout << GRN <<"Saleswoman:" << NC << " which pokeballs do you want ?" << std::endl;
        std::cout << std::endl;
        int choice = 0;
        for (auto potion : all_potions) {
            choice = choice + 1;
            std::cout << choice <<": " << GRN << potion->getName() << NC <<" | Description: " << potion->getDescription()<< " | price: " << potion->getPrice() << std::endl;
        }
        std::cout << choice +1  <<":" << " BACK;";

        user_choice = this->printInputUser(choice +1);
        if (user_choice == choice +1) {
            std::cout << GRN <<"Saleswoman:" << NC << " bye !" << std::endl;
            sleep(2);
            system("clear");
            return false;
        }
        system("clear");
        item_potion  = all_potions[user_choice - 1];


    } else {
        is_pokeball = true;
        std::vector<Pokeball *> all_pokeballs = {new Pokeball(1), new Pokeball(2), new Pokeball(3), new Pokeball(4)};
        std::cout << GRN <<"Saleswoman:" << NC << " which potions do you want ?" << std::endl;
        std::cout << std::endl;
        int choice = 0;
        for (auto pokeball : all_pokeballs) {
            choice = choice + 1;
            std::cout << choice <<": " << GRN << pokeball->getName() << NC <<" | Description: " << pokeball->getDescription()<< " | price: " << pokeball->getPrice() << std::endl;
        }
        std::cout << choice +1  <<": " << "BACK;";
        user_choice = this->printInputUser(choice +1);

        if (user_choice == choice +1) {
            std::cout << GRN <<"Saleswoman:" << NC << " bye !" << std::endl;
            sleep(2);
            system("clear");

            return false;
        }
        system("clear");
        item_pokeball = all_pokeballs[user_choice - 1];
    }

    if (is_potion){
        std::cout << GRN <<"Saleswoman:" << NC << " you selected "<< YLW <<item_potion->getName()<< NC << ". The price is at: "<< YLW  <<item_potion->getPrice() << NC << " pokedollars. You have: "<< YLW <<player->getPokedollars()<< NC << std::endl;
        std::cout << GRN <<"Saleswoman:" << NC << " how many "<< YLW << item_potion->getName()<< NC << " do you want ?" << std::endl;
    } else {
        std::cout << GRN <<"Saleswoman:" << NC << " you selected "<< YLW <<item_pokeball->getName()<< NC << ". The price is at: "<< YLW  <<item_pokeball->getPrice() << NC << " pokedollars. You have: "<< YLW <<player->getPokedollars()<< NC << std::endl;
        std::cout << GRN <<"Saleswoman:" << NC << " how many "<< YLW << item_pokeball->getName()<< NC << " do you want ?" << std::endl;
    }


    std::cout << std::endl;
    user_choice = this->printInputUser(99999999);

    if (user_choice == 0) {
        std::cout << GRN <<"Saleswoman:" << NC << " bye !" << std::endl;
        sleep(2);
        return false;
    }
    if (is_potion){
        if (user_choice * item_potion->getPrice() > player->getPokedollars()) {
            std::cout << GRN <<"Saleswoman:" << NC << " you don't have: "<< YLW <<user_choice * item_potion->getPrice() << NC << " pokedollars, bye !" << std::endl;
            sleep(2);
            return false;
        }
    } else {
        if (user_choice * item_pokeball->getPrice() > player->getPokedollars()) {
            std::cout << GRN <<"Saleswoman:" << NC << " you don't have: "<< YLW <<user_choice * item_pokeball->getPrice() << NC << " pokedollars, bye !" << std::endl;
            sleep(2);
            return false;
        }
    }

    if (is_pokeball){
        std::cout << GRN <<"Saleswoman:" << NC << " you got "<< YLW << user_choice << NC << "x "<< YLW <<item_pokeball->getName() << NC << " for " << YLW <<user_choice * item_pokeball->getPrice() << NC << "pokedollars, bye !" << std::endl;
        player->setPokedollars(player->getPokedollars() - (item_pokeball->getPrice() * user_choice));
        for (int i = 0; i < user_choice; i++)
        {
            player->getBag()->addPokeball(*item_pokeball);
        }

    } else {
        std::cout << GRN <<"Saleswoman:" << NC << " you got "<< YLW << user_choice << NC << "x "<< YLW <<item_potion->getName() << NC << " for " << YLW <<user_choice * item_potion->getPrice() << NC << "pokedollars, bye !" << std::endl;
        player->setPokedollars(player->getPokedollars() - (item_potion->getPrice() * user_choice));
        for (int i = 0; i < user_choice; i++){
            player->getBag()->addPotion(*item_potion);
        }
    }
    sleep(3);
    return true;






}

bool Utils::replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

std::string Utils::create_white_space(int nb_white_space) {
    return std::string(nb_white_space, ' ');
}


std::string Utils::print_menu_func(Menu *menu, Trainer *trainer, Pokemon *pokemon) {
    _pokemon_print_menu_func(menu, pokemon);
    return this->print_menu_func(menu, trainer);
}

std::string Utils::print_menu_func(Menu *menu, Pokemon *pokemon) {
    _pokemon_print_menu_func(menu, pokemon);
    return this->print_menu_func(menu);
}

void Utils::_pokemon_print_menu_func(Menu *menu, Pokemon *pokemon) {
    std::string user_choice = "0";
    const std::string& name = menu->getName();
    const std::string& header = menu->getHeader();
    replace(const_cast<std::string &>(header), "*POKEMON*", pokemon->getName());
    menu->setHeader(header);

    if (name == "*POKEMON*") {
        menu->setName(pokemon->getName());
    }
}
std::string Utils::print_menu_func(Menu *menu, Trainer *trainer, Trainer *rivals) {
    const std::string& name = menu->getName();
    const std::string& header = menu->getHeader();
    replace(const_cast<std::string &>(header), "*RIVALS*", rivals->getName());
    replace(const_cast<std::string &>(header), "*PLAYER*", trainer->getName());
    menu->setHeader(header);

    if (name == "*RIVALS*") {
        menu->setName(rivals->getName());
    }
    return this->print_menu_func(menu);
}


std::string Utils::print_menu_func(Menu *menu, Trainer *trainer) {
    const std::string& name = menu->getName();
    const std::string& header = menu->getHeader();
    replace(const_cast<std::string &>(header), "*RIVALS*", trainer->getName());
    replace(const_cast<std::string &>(header), "*PLAYER*", trainer->getName());
    menu->setHeader(header);

    if (name == "*RIVALS*") {
        menu->setName(trainer->getName());
    }
    return this->print_menu_func(menu);
}
std::string Utils::print_menu_func(Menu * menu) {

    const std::string &type = menu->getType();
    const std::string &name = menu->getName();
    const std::string &header = menu->getHeader();
    const std::vector<std::string> &multi_choice = menu->getChoice();


    system("clear");
    bool valid = false;
    std::string user_choice = "0";
    int user_choice_int = 0;
    int need_validation = 0;
    std::string type_question_answer = "QA";
    std::string type_answer = "A";
    std::string type_nothing = "N";


    do {
        std::cout << "\n";
        std::cout << GRN << name << NC <<": " << header << std::endl;
        std::cout << "\n";
        int choice = 0;

        if (type == type_question_answer) {
            need_validation = 1;
            for (auto it = std::begin(multi_choice); it != std::end(multi_choice); ++it) {
                std::cout << choice << ": " << *it << std::endl;
                choice++;
            };
            std::cout << "\n";
            std::cout << "Your choice: ";
            std::cin >> user_choice;
        } else if (type == type_answer) {
            std::cout << "Enter value: ";
            std::cin >> user_choice;
            std::cin.clear();
            std::cin.ignore(80, '\n');
            break;
            // TODO check if user choice name existed
            // TODO create fill
        } else if (type == type_nothing) {
            std::cout << "Press "<< CYN << "ENTER" << NC;
            if (std::cin.get() == '\n') {
                std::cin.clear();
                user_choice = "0";
                break;
            };

        };
        if (need_validation == 1) {
            if (std::cin.fail()) {
                std::cout << "Your input is not valid !" << std::endl;
                std::cin.clear();
                std::cin.ignore(80, '\n');

            } else {
                user_choice_int = std::stoi(user_choice);
                if (user_choice_int >= 0 && user_choice_int <= choice - 1) {
                    valid = true;
                    std::cin.clear();
                    std::cin.ignore(80, '\n');
                } else {
                    std::cout << "Your input is not valid !" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(80, '\n');
                }

            }
        };
    } while (!valid);
    return user_choice;
}


long int Utils::get_current_timestamp_to_int() {
    const auto p1 = std::chrono::system_clock::now();
    long int result = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
    return result;
};

long int Utils::timestamp_to_int(auto value) {
    long int result = std::chrono::duration_cast<std::chrono::seconds>(value.time_since_epoch()).count();
    return result;
}

