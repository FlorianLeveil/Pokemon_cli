//
// Created by idk on 01/03/2021.
//
#include <unistd.h>
#include <iostream>
#include <random>
#include "Fight.h"
#include "../pcs/Pc.h"
#include <math.h>
#include <iterator>


#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define PURPLE "\e[0;35m"
#define BLUE "\e[0;94m"
#define CYN "\e[00;36m"
#define CYN2 "\e[00;96m"
#define YLW "\e[00;93m"



Fight::Fight(int id, Trainer *player, Trainer *opponent, Pc*pc) : id(id), player(player), opponent(opponent), pc(pc) {
    Fight::id = id;
    Fight::opponent = opponent;
    Fight::pc = pc;
    this->setPlayer(player);

    this->current_pokemon_opponent = this->opponent->getPokemons().front();
    this->computeLiveDeadPokemon(opponent,&this->opponent_pokemon_dead, &this->opponent_pokemon_live, &this->opponent_pokemon_dead_string , &this->opponent_pokemon_live_string);
}

void Fight::computeLiveDeadPokemon(Trainer *player, std::vector<Pokemon *> *pokemon_dead, std::vector<Pokemon *> *pokemon_live, std::string *pokemon_dead_string, std::string *pokemon_live_string ){
    *pokemon_dead = {};
    *pokemon_live = {};
    *pokemon_dead_string = "";
    *pokemon_live_string = "";
    for (auto &pokemon : player->getPokemons()) {
        if (pokemon->getCurrentHp() == 0) {
            pokemon_dead->push_back(pokemon);
            pokemon_dead_string->push_back('X');
        } else {
            pokemon_live->push_back(pokemon);
            pokemon_live_string->push_back('O');
        }
    }
}

Fight::Fight(int id, Trainer *player, Pc *pc) : id(id), player(player), pc(pc) {
    Fight::id = id;
    Fight::pc = pc;
    std::string pokemon_name = "";
    bool is_good = false;
    this->setPlayer(player);
    Utils * utils = new Utils;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,898);

    while (!is_good) {
        pokemon_name = utils->getPokemonNameWithId(dist6(rng));
        is_good = utils->checkMoves(pokemon_name);
        if (is_good) {
            break;
        }
    }
    this->pokemon = new Pokemon(pokemon_name, 5);
    this->current_pokemon_opponent = this->pokemon;
}

void Fight::setPlayer(Trainer *new_player){
    Fight::player = new_player;
    for (int i = this->player->getPokemons().size() - 1; i >= 0; i--){
        if (this->player->getPokemons()[i]->getCurrentHp() != 0) {
            this->current_pokemon_player = this->player->getPokemons()[i];
        }
    }
    this->computeLiveDeadPokemon(player,&this->player_pokemon_dead, &this->player_pokemon_live, &this->player_pokemon_dead_string , &this->player_pokemon_live_string);

};
void Fight::printVS() {
    std::string whitespace_for_vs(30,' ');
    std::cout << whitespace_for_vs << CYN <<"    ____   ____   ______"  << std::endl;
    std::cout << whitespace_for_vs <<"   |_  _| |_  _|.' ____ \\  "  << std::endl;
    std::cout << whitespace_for_vs <<"     \\ \\   / /  | (___ \\_|"  << std::endl;
    std::cout << whitespace_for_vs <<"      \\ \\ / /    _.____`."  << std::endl;
    std::cout << whitespace_for_vs <<"       \\ ' /    | \\____) | "  << std::endl;
    std::cout << whitespace_for_vs <<"        \\_/      \\______.'"  << NC << std::endl;
}
void Fight::printPokemonBlock(bool opponent, bool pokemon) {
    std::string PRIMARY_COLOR = (opponent || pokemon) ? (RED) : (BLUE);
    std::string pokemon_name = (opponent || pokemon) ? (this->current_pokemon_opponent->getName()) : (this->current_pokemon_player->getName());
    int pokemon_lvl = (opponent || pokemon) ? (this->current_pokemon_opponent->getLvl()) : (this->current_pokemon_player->getLvl());
    int pokemon_hp = (opponent || pokemon ) ? (this->current_pokemon_opponent->getCurrentHp()) : (this->current_pokemon_player->getCurrentHp());
    int pokemon_hp_max = (opponent || pokemon ) ? (this->current_pokemon_opponent->getCurrentHpMax()) : (this->current_pokemon_player->getCurrentHpMax());
    std::string pipe = "|";
    std::string bar(90, '-');
    std::string one_white_space = " ";
    int pokemon_current_hp_percent = pokemon_hp*100/pokemon_hp_max;
    int progressbar = pokemon_hp*74 / pokemon_hp_max;
    std::string pipe_progressbar(progressbar,'|');
    std::string color_progressbar = (pokemon_current_hp_percent >= 30) ? (GRN) : (RED);


    std::string white_space_pokemon_name( 26 - pokemon_name.size() ,' ');
    std::string white_pace_progressbar(74 - progressbar ,' ');
    std::string white_space_pokemon_lvl( 8 - this->message_lvl.size() - std::to_string(pokemon_lvl).size() ,' ');
    std::string white_space_pokemon_percent_hp( 3 - std::to_string(pokemon_current_hp_percent).size() ,' ');



    std::cout << std::endl;
    std::cout << PRIMARY_COLOR << bar  << std::endl;
    std::cout << PRIMARY_COLOR << pipe << one_white_space  << YLW  << pokemon_name << white_space_pokemon_name;
    std::cout << PRIMARY_COLOR << pipe  << one_white_space << CYN << this->message_lvl << one_white_space << YLW << pokemon_lvl << white_space_pokemon_lvl << PRIMARY_COLOR << pipe << one_white_space << CYN;

    if (opponent) {
        std::string pokemon_missing(6 - this->opponent_pokemon_live_string.size() - this->opponent_pokemon_dead_string.size(), '.');
        std::string white_space_opponent_name( 24 - this->opponent->getName().size() ,' ');
        std::string white_space_opponent_pokemon_list( 15 - this->message_pokemon.size() - this->opponent_pokemon_live_string.size() - this->opponent_pokemon_dead_string.size() - pokemon_missing.size() ,' ');
        std::cout << this->message_name << one_white_space  << YLW << this->opponent->getName() << white_space_opponent_name;
        std::cout << PRIMARY_COLOR << pipe << one_white_space << CYN << this->message_pokemon << one_white_space << GRN << this->opponent_pokemon_live_string << RED << this->opponent_pokemon_dead_string << CYN << pokemon_missing << white_space_opponent_pokemon_list << PRIMARY_COLOR << pipe <<std::endl;


    } else if (pokemon) {
        std::string white_space_pokemon_sauvage( 47 -  this->message_pokemon_sauvage.size() ,' ');
        std::cout << PURPLE << one_white_space  << this->message_pokemon_sauvage << white_space_pokemon_sauvage << PRIMARY_COLOR << pipe <<std::endl;

    } else {
        std::string pokemon_missing(6 - this->player_pokemon_live_string.size() - this->player_pokemon_dead_string.size(), '.');
        std::string white_space_pokemon_exp( 22 - std::to_string(this->current_pokemon_player->getExp()).size() - std::to_string(this->current_pokemon_player->getExpForNextLvl()).size() ,' ');
        std::string white_space_opponent_pokemon_list( 15 - this->message_pokemon.size() - this->player_pokemon_live_string.size() - this->player_pokemon_dead_string.size() - pokemon_missing.size() ,' ');
        std::cout << this->message_pokemon_exp << one_white_space << YLW << this->current_pokemon_player->getExp() << " / " << this->current_pokemon_player->getExpForNextLvl() << white_space_pokemon_exp;
        std::cout << PRIMARY_COLOR << pipe << one_white_space << CYN << this->message_pokemon << one_white_space << GRN << this->player_pokemon_live_string << RED << this->player_pokemon_dead_string << CYN << pokemon_missing << white_space_opponent_pokemon_list << PRIMARY_COLOR << pipe <<std::endl;

    }

    std::cout << PRIMARY_COLOR << bar  << std::endl;

    std::cout << PRIMARY_COLOR << pipe << one_white_space << CYN  << this->message_pokemon_pv << one_white_space << color_progressbar << pokemon_current_hp_percent << "%" << white_space_pokemon_percent_hp;
    std::cout << PRIMARY_COLOR << pipe << CYN << " [" << color_progressbar << pipe_progressbar << CYN << white_pace_progressbar << "] "<< PRIMARY_COLOR << pipe << std::endl;
    std::cout << PRIMARY_COLOR << bar << NC << std::endl;
    std::cout << std::endl;
}

void Fight::printPrincipalChoice(){
    std::string white_space_before_choice(15,' ');
    std::string bar(60, '-');
    std::string pipe = "|";

    std::cout << white_space_before_choice << CYN2 << bar  << std::endl;
    std::cout << white_space_before_choice << CYN2 << "|"  << utils.create_white_space(29) << pipe << utils.create_white_space(28)  << pipe << std::endl;
    std::cout << white_space_before_choice << CYN2 << "|" << utils.create_white_space(10) << select_action_fight << utils.create_white_space(11)<< pipe <<  utils.create_white_space(11) << select_action_bag << utils.create_white_space(11)<< pipe << std::endl;
    std::cout << white_space_before_choice << CYN2 << "|"  << utils.create_white_space(29) << pipe << utils.create_white_space(28)  << pipe << std::endl;
    std::cout << white_space_before_choice << CYN2 << bar  << std::endl;
    std::cout << white_space_before_choice << CYN2 << "|"  << utils.create_white_space(29) << pipe << utils.create_white_space(28)  << pipe << std::endl;
    std::cout << white_space_before_choice << CYN2 << "|" << utils.create_white_space(10) << select_action_pokemon << utils.create_white_space(8)<< pipe <<  utils.create_white_space(11) << select_action_run << utils.create_white_space(11)<< pipe << std::endl;
    std::cout << white_space_before_choice << CYN2 << "|"  << utils.create_white_space(29) << pipe << utils.create_white_space(28)  << pipe << std::endl;
    std::cout << white_space_before_choice << CYN2 << bar  << std::endl;
}

void Fight::printAllFightInterface() {
    system("clear");
    if (this->opponent) {
        this->printPokemonBlock(true, false);
    } else {
        this->printPokemonBlock(false, true);
    }
    this->printVS();
    this->printPokemonBlock(false, false);
}

void Fight::viewFightInterface(){
    bool total_fight = true;
    bool in_fight = true;
    int pokemon_captured = 0;

    while(total_fight) {
        while (in_fight) {
            this->printAllFightInterface();
            this->printPrincipalChoice();
            int user_choice = this->printInputUser(4);
            if (user_choice == 1) {
                this->printAllFightInterface();
                this->selectFight();
                int user_choice_fight = this->printInputUser(5);
                if (user_choice_fight == 1) {
                    in_fight = this->doFight(current_pokemon_player->getMove1());
                } else if (user_choice_fight == 2) {
                    in_fight = this->doFight(current_pokemon_player->getMove2());

                } else if (user_choice_fight == 3) {
                    in_fight = this->doFight(current_pokemon_player->getMove3());

                } else if (user_choice_fight == 4) {
                    in_fight = this->doFight(current_pokemon_player->getMove4());

                } else {
                    continue;
                }

            } else if (user_choice == 2) {
                this->printAllFightInterface();
                pokemon_captured = this->selectBag();
                if (pokemon_captured == 1) {
                    std::string white_space_before_text(25, ' ');
                    if (this->player->getPokemons().size() >= 6) {
                        this->pc->addPokemon(current_pokemon_opponent);
                        std::cout << white_space_before_text << CYN <<"You cannot have more than 6 Pokemons in your team. So "<< YLW << current_pokemon_opponent->getName() << CYN << " was placed in your PC ! " << NC << std::endl;
                        sleep(2);
                    } else {
                        std::cout << white_space_before_text << YLW << current_pokemon_opponent->getName() << CYN << " was placed in your team." << NC << std::endl;
                        sleep(2);
                        this->player->setPokemon(*current_pokemon_opponent);
                    }
                    in_fight = false;
                    total_fight = false;
                    break;
                } else if (pokemon_captured == 0) {
                    in_fight = this->doFight(current_pokemon_player->getMove1(), true);
                }
            } else if (user_choice == 3) {
                this->printAllFightInterface();
                bool select_pokemon = this->selectPokemon(true);
                if (select_pokemon) {
                    in_fight = this->doFight(current_pokemon_player->getMove1(), true);
                }
            } else {
                in_fight = this->selectRun();
                if (!in_fight) {
                    total_fight = false;
                    break;
                }
            }
        }
        if (!total_fight) {
            break;
        }
        if (this->opponent) {
            this->computeLiveDeadPokemon(opponent,&this->opponent_pokemon_dead, &this->opponent_pokemon_live, &this->opponent_pokemon_dead_string , &this->opponent_pokemon_live_string);
        }
        this->computeLiveDeadPokemon(player,&this->player_pokemon_dead, &this->player_pokemon_live, &this->player_pokemon_dead_string , &this->player_pokemon_live_string);

        std::string white_space_before_text(25, ' ');
        if (this->pokemon) {

            if (this->pokemon->getCurrentHp() == 0) {
                std::cout << white_space_before_text << CYN <<"You got: "<< YLW << "1000" << CYN << " pokedollars !" << NC << std::endl;
                player->setPokedollars(player->getPokedollars() + 1000);
                total_fight = false;
                break;
            } else if (pokemon_captured) {
                total_fight = false;
                break;
            }
        }

        if (this->player_pokemon_live.size() == 0){
            total_fight = false;
            break;
        }

        if (this->opponent_pokemon_live.size() == 0 && this->opponent) {
            total_fight = false;
            std::cout << white_space_before_text << CYN <<"You got: "<< YLW << "2500" << CYN << " pokedollars !" << NC << std::endl;
            player->setPokedollars(player->getPokedollars() + 2500);
            break;
        }

        if (total_fight && current_pokemon_player->getCurrentHp() == 0) {
            this->printAllFightInterface();
            this->selectPokemon();
            in_fight = true;
        }

        if (total_fight && current_pokemon_opponent->getCurrentHp() == 0) {
            this->selectPokemonForOpponent();
            in_fight = true;
        }

    }

}

int Fight::printInputUser(int choice) {
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
            if (user_choice_int > 0 && user_choice_int <= choice) {
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
void Fight::startFight(){}

void Fight::selectFight(){

    //MOVE
    std::string move1 = this->current_pokemon_player->getMove1()->getName();
    std::string move2 = this->current_pokemon_player->getMove2()->getName();
    std::string move3 = this->current_pokemon_player->getMove3()->getName();
    std::string move4 = this->current_pokemon_player->getMove4()->getName();

    //MOVE WHITESPACE
    std::string white_space_before_choice(15,' ');
    std::string white_space_move1_L((25 - move1.size()) / 2,' ');
    std::string white_space_move1_R(25 - white_space_move1_L.size() - move1.size(),' ');
    std::string white_space_move2_L((26 - move2.size()) / 2,' ');
    std::string white_space_move2_R(26 - white_space_move2_L.size() - move2.size(),' ');
    std::string white_space_move3_L((25 - move3.size()) / 2,' ');
    std::string white_space_move3_R(25 - white_space_move3_L.size() - move3.size(),' ');
    std::string white_space_move4_L((26 - move4.size()) / 2,' ');
    std::string white_space_move4_R(26 - white_space_move4_L.size() - move4.size(),' ');

    //POWER
    int power1 = this->current_pokemon_player->getMove1()->getPower();
    int power2 = this->current_pokemon_player->getMove2()->getPower();
    int power3 = this->current_pokemon_player->getMove3()->getPower();
    int power4 = this->current_pokemon_player->getMove4()->getPower();

    //CATEGORY
    std::string category1 = this->current_pokemon_player->getMove1()->getCategory();
    std::string category2 = this->current_pokemon_player->getMove2()->getCategory();
    std::string category3 = this->current_pokemon_player->getMove3()->getCategory();
    std::string category4 = this->current_pokemon_player->getMove4()->getCategory();


    //CATEGORY AND POWER WHITE SPACE

    std::string white_space_cat_power1_L((16 - category1.size() - std::to_string(power1).size()) / 3,' ');
    std::string white_space_cat_power1_R(16 - (white_space_cat_power1_L.size()*2) - category1.size() - std::to_string(power1).size(),' ');

    std::string white_space_cat_power2_L((17 - category2.size() - std::to_string(power2).size()) / 3,' ');
    std::string white_space_cat_power2_R(17 - (white_space_cat_power2_L.size()*2) - category2.size() - std::to_string(power2).size(),' ');

    std::string white_space_cat_power3_L((16 - category3.size() - std::to_string(power3).size()) / 3,' ');
    std::string white_space_cat_power3_R(16 - (white_space_cat_power3_L.size()*2) - category3.size() - std::to_string(power3).size(),' ');

    std::string white_space_cat_power4_L((17 - category4.size() - std::to_string(power4).size()) / 3,' ');
    std::string white_space_cat_power4_R(17 - (white_space_cat_power4_L.size()*2) - category4.size() - std::to_string(power4).size(),' ');

    //TYPE
    std::string type1 = this->current_pokemon_player->getMove1()->getType();
    std::string type2 = this->current_pokemon_player->getMove2()->getType();
    std::string type3 = this->current_pokemon_player->getMove3()->getType();
    std::string type4 = this->current_pokemon_player->getMove4()->getType();

    //PP
    int pp1 = this->current_pokemon_player->getMove1()->getPp();
    int pp2 = this->current_pokemon_player->getMove2()->getPp();
    int pp3 = this->current_pokemon_player->getMove3()->getPp();
    int pp4 = this->current_pokemon_player->getMove4()->getPp();

    //CURRENT_PP
    int current_pp1 = this->current_pokemon_player->getMove1()->getCurrentPp();
    int current_pp2 = this->current_pokemon_player->getMove2()->getCurrentPp();
    int current_pp3 = this->current_pokemon_player->getMove3()->getCurrentPp();
    int current_pp4 = this->current_pokemon_player->getMove4()->getCurrentPp();

    //PP AND CURRENT PP
    std::string pp_currentpp1 = std::to_string(current_pp1) + " / " + std::to_string(pp1);
    std::string pp_currentpp2 = std::to_string(current_pp2) + " / " + std::to_string(pp2);
    std::string pp_currentpp3 = std::to_string(current_pp3) + " / " + std::to_string(pp3);
    std::string pp_currentpp4 = std::to_string(current_pp4) + " / " + std::to_string(pp4);


    //TYPE AND PP

    std::string white_space_type_pp1_L((18 - type1.size() - pp_currentpp1.size()) / 3,' ');
    std::string white_space_type_pp1_R(18 - (white_space_type_pp1_L.size()*2) - type1.size() - pp_currentpp1.size(),' ');

    std::string white_space_type_pp2_L((19 - type2.size() - pp_currentpp2.size()) / 3,' ');
    std::string white_space_type_pp2_R(19 - (white_space_type_pp2_L.size()*2) - type2.size() - pp_currentpp2.size(),' ');

    std::string white_space_type_pp3_L((18 - type3.size() - pp_currentpp3.size()) / 3,' ');
    std::string white_space_type_pp3_R(18 - (white_space_type_pp3_L.size()*2) - type3.size() - pp_currentpp3.size(),' ');

    std::string white_space_type_pp4_L((19 - type4.size() - pp_currentpp4.size()) / 3,' ');
    std::string white_space_type_pp4_R(19 - (white_space_type_pp4_L.size()*2) - type4.size() - pp_currentpp4.size(),' ');


    std::string bar(60, '-');
    std::string pipe = "|";
    std::string white_space_before_back(34, ' ');

    std::cout << white_space_before_choice << CYN2 << bar  << std::endl;
    std::cout << white_space_before_choice << CYN2 << "|" << white_space_move1_L << "1: " << RED << move1 << CYN2 << white_space_move1_R << "|" <<  white_space_move2_L << "2: " << RED <<move2 << CYN2 << white_space_move2_R << "|" << std::endl;
    std::cout << white_space_before_choice << CYN2 << "|" << white_space_cat_power1_L << "Ctg: " << YLW << category1 << white_space_cat_power1_L << CYN2 << "Power: " << YLW << std::to_string(power1) << white_space_cat_power1_R << CYN2 << pipe << white_space_cat_power2_L << "Ctg: " << YLW << category2 << CYN2 << white_space_cat_power2_L << "Power: " << YLW << std::to_string(power2) << white_space_cat_power2_R << CYN2 << pipe << std::endl;
    std::cout << white_space_before_choice << CYN2 << "|" << white_space_type_pp1_L << "Type: " << YLW << type1 << white_space_type_pp1_L << CYN2 << "PP: " << YLW << pp_currentpp1 << white_space_type_pp1_R << CYN2 << pipe << white_space_type_pp2_L << "Type: " << YLW << type2 << CYN2 << white_space_type_pp2_L << "PP: " << YLW << pp_currentpp2 << white_space_type_pp2_R << CYN2 << pipe << std::endl;
    std::cout << white_space_before_choice << CYN2 << bar  << std::endl;
    std::cout << white_space_before_choice << CYN2 << "|" << white_space_move3_L << "3: " << RED << move3 << CYN2 << white_space_move3_R << "|" <<  white_space_move4_L << "4: " << RED <<move4 << CYN2 << white_space_move4_R << "|" << std::endl;
    std::cout << white_space_before_choice << CYN2 << "|" << white_space_cat_power3_L << "Ctg: " << YLW << category3 << white_space_cat_power3_L << CYN2 << "Power: " << YLW << std::to_string(power3) << white_space_cat_power3_R << CYN2 << pipe << white_space_cat_power4_L << "Ctg: " << YLW << category4 << CYN2 << white_space_cat_power4_L << "Power: " << YLW << std::to_string(power4) << white_space_cat_power4_R << CYN2 << pipe << std::endl;
    std::cout << white_space_before_choice << CYN2 << "|" << white_space_type_pp3_L << "Type: " << YLW << type3 << white_space_type_pp3_L << CYN2 << "PP: " << YLW << pp_currentpp3 << white_space_type_pp3_R << CYN2 << pipe << white_space_type_pp4_L << "Type: " << YLW << type4 << CYN2 << white_space_type_pp4_L << "PP: " << YLW << pp_currentpp4 << white_space_type_pp4_R << CYN2 << pipe << std::endl;
    std::cout << white_space_before_choice << CYN2 << bar  << std::endl;
    std::cout << white_space_before_back << CYN2 << "|" << "     5: BACK     " << "|" << NC << std::endl;
    std::cout << white_space_before_back << CYN2 << "-------------------" << NC << std::endl;

}

void Fight::selectPokemonForOpponent() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,this->opponent_pokemon_live.size());
    this->current_pokemon_opponent = this->opponent_pokemon_live[dist6(rng) -1];
}

int Fight::selectBag(){
    std::string bar(202, '-');
    std::string bar_2(13, '-');
    int choice = 0;


    std::vector<int> pokeballs_count_by_id = {0,0,0,0 };
    std::vector<int> potions_count_by_id = {0,0,0,0 };
    std::vector<std::string> id_items = {};




    for (auto &pokeball : this->player->getBag()->getPokeballs()) {
        pokeballs_count_by_id[pokeball->getId() - 1] = pokeballs_count_by_id[pokeball->getId() - 1] + 1;
    }
    for (auto &potion : this->player->getBag()->getPotions()) {
        potions_count_by_id[potion->getId() - 1] = potions_count_by_id[potion->getId() - 1] + 1;
    }

    int count_ball = 0;
    int count_for = 0;
    for ( int pokeball : pokeballs_count_by_id) {
        if (pokeball) {
            count_ball += pokeball;
            std::string white_space_after_item(17  -  this->player->getBag()->getPokeballs()[count_ball - 1]->getName().size(),' ');
            std::string white_space_after_description(134  -  this->player->getBag()->getPokeballs()[count_ball - 1]->getDescription().size(),' ');
            std::string white_space_after_count(5  -  std::to_string(pokeball).size(),' ');


            std::cout << CYN2 << bar << std::endl;
            choice = choice + 1 ;
            std::cout << CYN2 << "|" << " Choice: " << choice << " |"<< " Item: " << YLW << this->player->getBag()->getPokeballs()[count_ball - 1]->getName() << white_space_after_item << CYN2 << " |" << " Description:  " << YLW << this->player->getBag()->getPokeballs()[count_ball -1]->getDescription() << white_space_after_description<< CYN2 << " |" << " Count: " << YLW << pokeball << CYN2 << white_space_after_count << "|" << std::endl;
            id_items.push_back(this->player->getBag()->getPokeballs()[count_ball -1]->getName());
        }
        count_for = count_for + 1;
    }

    int count_potion = 0;
    int count_for_2 = 0;
    for ( int potion : potions_count_by_id) {
        if (potion) {
            count_potion += potion;
            std::string white_space_after_item_2(16  -  this->player->getBag()->getPotions()[count_potion - 1]->getName().size(),' ');
            std::string white_space_after_description_2(133  -  this->player->getBag()->getPotions()[count_potion - 1]->getDescription().size(),' ');
            std::string white_space_after_count2(5  -  std::to_string(potion).size(),' ');
            choice = choice + 1 ;
            std::cout << CYN2 << bar  << std::endl;
            std::cout << CYN2 << "|" << " Choice: " << choice << " |"<< " Item: " << YLW << this->player->getBag()->getPotions()[count_potion - 1]->getName() << white_space_after_item_2 << CYN2 << " |" << " Description:  " << YLW << this->player->getBag()->getPotions()[count_potion - 1]->getDescription()<< white_space_after_description_2 << CYN2 << " |" << " Count: " << YLW << potion << CYN2 << white_space_after_count2 << "|" << std::endl;
            id_items.push_back(this->player->getBag()->getPotions()[count_potion - 1]->getName());
        }
        count_for_2 = count_for_2 + 1;
    }
    std::cout << CYN2 << bar  << std::endl;
    std::cout << CYN2 << "|" << " Back: " << choice + 1 << "   |"<< std::endl;
    std::cout << CYN2 << bar_2  << std::endl;

    int user_choice = this->printInputUser(choice + 1);

    if (user_choice == choice + 1){
        return 2;
    }
    bool result = this->player->getBag()->useItemByName(id_items[user_choice - 1], current_pokemon_opponent, current_pokemon_player);
    if (result) {
        return 1;
    } else {
        return 0;
    }
}

bool Fight::selectPokemon(bool do_back) {
    int pokemon_list_size = this->player->getPokemons().size();
    int number_choice = 0;
    bool not_valid = true;

    std::string white_space_before_choice(15,' ');
    std::string white_space_before_number_choice(29,' ');
    std::string white_space_after_number_choice(28,' ');
    std::string bar(60, '-');

    std::string white_space_pokemon_name_L((22 - this->current_pokemon_player->getName().size()) / 2,' ');
    std::string white_space_pokemon_name_R(23 - white_space_pokemon_name_L.size() - this->current_pokemon_player->getName().size(),' ');

    std::string white_space_pokemon_lvl_L((26 - std::to_string(this->current_pokemon_player->getLvl()).size()) / 2,' ');
    std::string white_space_pokemon_lvl_R(26 - white_space_pokemon_lvl_L.size() - std::to_string(this->current_pokemon_player->getLvl()).size(),' ');





    for (auto &pokemon : this->player->getPokemons()) {
        number_choice = number_choice + 1;
        int pokemon_current_hp_percent = pokemon->getCurrentHp()*100/pokemon->getCurrentHpMax();
        int progressbar = pokemon->getCurrentHp()*45 / pokemon->getCurrentHpMax();
        std::string pipe_progressbar(progressbar,'|');
        std::string color_progressbar = (pokemon_current_hp_percent >= 30) ? (GRN) : (RED);
        std::string white_space_for_hp(3 - std::to_string(pokemon_current_hp_percent).size(), ' ');
        std::string white_pace_progressbar(45 - progressbar ,' ');


        std::string white_space_pokemon_name_L((22 - pokemon->getName().size()) / 2,' ');
        std::string white_space_pokemon_name_R(23 - white_space_pokemon_name_L.size() - pokemon->getName().size(),' ');

        std::string white_space_pokemon_lvl_L((23 - std::to_string(pokemon->getLvl()).size()) / 2,' ');
        std::string white_space_pokemon_lvl_R(23 - white_space_pokemon_lvl_L.size() - std::to_string(pokemon->getLvl()).size(),' ');

        std::cout << white_space_before_choice << CYN2 << bar  << std::endl;

        std::cout << white_space_before_choice << CYN2 << "|" << white_space_before_number_choice << YLW << number_choice << white_space_after_number_choice << CYN2 << "|" << std::endl;
        std::cout << white_space_before_choice << CYN2 << "|" << white_space_pokemon_name_L << "Name: " << YLW << pokemon->getName() << CYN2 << white_space_pokemon_name_R << "|" <<  white_space_pokemon_lvl_L << "Lvl: " << YLW << pokemon->getLvl() << CYN2 << white_space_pokemon_lvl_R << "|" << std::endl;
        std::cout << white_space_before_choice << CYN2 << "|" << " Hp: " << YLW << pokemon_current_hp_percent <<"%" << white_space_for_hp << CYN << " [" << color_progressbar << pipe_progressbar << CYN2 << white_pace_progressbar << "] "<<  "|" << std::endl;

        if (pokemon_list_size == 1) {
            std::cout << white_space_before_choice << CYN2 << bar  << std::endl;
        }

        pokemon_list_size = pokemon_list_size -1;
    }
    if (do_back) {
        std::string white_space_before_back(34, ' ');
        std::cout << white_space_before_back << CYN2 << "|" << "     " << number_choice + 1 << ": BACK     " << "|" << NC << std::endl;
        std::cout << white_space_before_back << CYN2 << "-------------------" << NC << std::endl;
    }

    std::string white_space_before_choice_2(25, ' ');
    int user_input = 0;
    while(not_valid){
        if (do_back) {
            user_input = this->printInputUser(number_choice + 1);
            if (user_input == number_choice + 1) {
                return false;
            }
        } else {
            user_input = this->printInputUser(number_choice);
        }
        if (this->player->getPokemons()[user_input -1]->getCurrentHp() == 0) {
            std::cout << white_space_before_choice_2 << YLW << this->player->getPokemons()[user_input -1]->getName() << RED << " is dead ! Choice an other Pokemon." << NC << std::endl;
        } else {
            this->current_pokemon_player = this->player->getPokemons()[user_input -1];
            std::cout << white_space_before_choice_2 << BLUE << this->current_pokemon_player->getName() << CYN << " go to the fight !" << NC << std::endl;
            sleep(2);
            not_valid = false;
            break;
        }
    }
    return true;


}
bool Fight::selectRun(){
    std::string white_space_before_choice(35,' ');
    std::cout << std::endl;
    if (this->opponent) {
        this->printAllFightInterface();
        std::cout << white_space_before_choice << RED << "You can't run away !" << NC << std::endl;
        sleep(3);
        return true;
    } else {
        this->printAllFightInterface();
        std::cout << white_space_before_choice << YLW << "You take flight !" << NC << std::endl;
        sleep(3);
        return false;
    }
}
bool Fight::doPlayerFight(Move * move){
    std::string white_space_before_text(25, ' ');
    std::cout << white_space_before_text << BLUE << this->current_pokemon_player->getName() << CYN << " attack " << BLUE << move->getName() << CYN << " !" << NC << std::endl;

    int hp_damage = (int)(((this->current_pokemon_player->getLvl() * 0.4 + 2) * this->current_pokemon_player->getCurrentAtk() * move->getPower()) / (this->current_pokemon_opponent->getCurrentDef() * 50) + 2);
    move->setCurrentPp(move->getCurrentPp() - 1);
    sleep(2);
    if (this->current_pokemon_opponent->getCurrentHp() - hp_damage <= 0) {
        this->current_pokemon_opponent->setCurrentHp(0);
        std::cout << white_space_before_text << RED << this->current_pokemon_opponent->getName() << CYN << " is dead ! " << NC << std::endl;
        sleep(2);
        return true;
    } else {
        this->current_pokemon_opponent->setCurrentHp(this->current_pokemon_opponent->getCurrentHp() - hp_damage);
        std::cout << white_space_before_text << RED << this->current_pokemon_opponent->getName() << CYN << " is still alive." << NC << std::endl;
        sleep(2);
        return false;
    }
}
bool Fight::doOpponentFight(){
    std::string white_space_before_text(25, ' ');
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,3);
    int random_attack = dist6(rng);
    std::string move_name = "";
    int move_power = 0;
    if (random_attack == 0) {
        move_name = this->current_pokemon_opponent->getMove1()->getName();
        move_power = this->current_pokemon_opponent->getMove1()->getPower();
    } else if (random_attack == 1) {
        move_name = this->current_pokemon_opponent->getMove2()->getName();
        move_power = this->current_pokemon_opponent->getMove2()->getPower();

    } else if (random_attack == 2) {
        move_name = this->current_pokemon_opponent->getMove3()->getName();
        move_power = this->current_pokemon_opponent->getMove3()->getPower();

    } else {
        move_name = this->current_pokemon_opponent->getMove4()->getName();
        move_power = this->current_pokemon_opponent->getMove4()->getPower();

    }
    std::cout << white_space_before_text << RED << this->current_pokemon_opponent->getName() << CYN << " attack " << RED << move_name << CYN << " !" << NC << std::endl;

    int hp_damage = (int)(((this->current_pokemon_opponent->getLvl() * 0.4 + 2) * this->current_pokemon_opponent->getCurrentAtk() * move_power) / (this->current_pokemon_player->getCurrentDef() * 50) + 2);

    sleep(2);
    if (this->current_pokemon_player->getCurrentHp() - hp_damage <= 0) {
        this->current_pokemon_player->setCurrentHp(0);
        std::cout << white_space_before_text << BLUE << this->current_pokemon_player->getName() << CYN << " is dead !" << NC << std::endl;
        sleep(2);
        return true;
    } else {
        this->current_pokemon_player->setCurrentHp(this->current_pokemon_player->getCurrentHp() - hp_damage);
        std::cout << white_space_before_text << BLUE << this->current_pokemon_player->getName() << CYN << " is still alive." << NC << std::endl;
        sleep(2);
        return false;
    }
}

int Fight::cumpteExpWin(Pokemon* pokemon) {
    float expwin = float(pokemon->getTotal()) * (float(pokemon->getLvl()) / 7);
    std::string white_space_before_text(25, ' ');
    std::cout << white_space_before_text << BLUE << this->current_pokemon_player->getName() << CYN << " win " << YLW << (int)(expwin) << CYN << " exp!" << NC << std::endl;
    sleep(2);
    return (int)(expwin);
}


bool Fight::doFight(Move * move, bool just_for_opponent) {
    bool pokemon_dead;
    this->printAllFightInterface();
    if (just_for_opponent) {
        pokemon_dead = this->doOpponentFight();
        if (pokemon_dead) {
            return false;
        } else {
            return true;
        }
    }
    if (this->current_pokemon_opponent->getCurrentSpd() > this->current_pokemon_opponent->getCurrentSpd()) {
        pokemon_dead = this->doOpponentFight();
        if (pokemon_dead) {
            return false;
        }
        pokemon_dead = this->doPlayerFight(move);
        if (pokemon_dead) {
            this->current_pokemon_player->levelUp(this->cumpteExpWin(this->current_pokemon_opponent), true);
            return false;
        }
    } else {
        pokemon_dead = this->doPlayerFight(move);
        if (pokemon_dead) {
            this->current_pokemon_player->levelUp(this->cumpteExpWin(this->current_pokemon_opponent),true);
            return false;
        }
        pokemon_dead = this->doOpponentFight();
        if (pokemon_dead) {
            return false;
        }
    }
    return true;
}

Fight::~Fight() {}





