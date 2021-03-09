//
// Created by idk on 18/01/2021.
//
#include "Pokemon.h"
#include "../utils/CsvReader.h"
#include "../utils/Utils.h"
#include <random>
#include <string>
#include <utility>
#include <iostream>
#include <math.h>
#include <unistd.h>
#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define PURPLE "\e[0;35m"
#define BLUE "\e[0;94m"
#define CYN "\e[00;36m"
#define CYN2 "\e[00;96m"
#define YLW "\e[00;93m"




int Pokemon::getId() const {
    return id;
}

void Pokemon::setId(int new_id) {
    Pokemon::id = new_id;
}

int Pokemon::getCode() const {
    return code;
}

void Pokemon::setCode(int new_code) {
    Pokemon::code = new_code;
}

int Pokemon::getSerial() const {
    return serial;
}

void Pokemon::setSerial(int new_serial) {
    Pokemon::serial = new_serial;
}

const std::string &Pokemon::getName() const {
    return name;
}

void Pokemon::setName(std::string &new_name) {
    Pokemon::name = new_name;
}

const std::string &Pokemon::getType1() const {
    return type1;
}

void Pokemon::setType1(std::string &new_type1) {
    Pokemon::type1 = new_type1;
}

const std::string &Pokemon::getType2() const {
    return type2;
}

void Pokemon::setType2(std::string &new_type2) {
    Pokemon::type2 = new_type2;
}

const std::string &Pokemon::getColor() const {
    return color;
}

void Pokemon::setColor(std::string &new_color) {
    Pokemon::color = new_color;
}

const std::string &Pokemon::getAbility1() const {
    return ability1;
}

void Pokemon::setAbility1(std::string &new_ability1) {
    Pokemon::ability1 = new_ability1;
}

const std::string &Pokemon::getAbility2() const {
    return ability2;
}

void Pokemon::setAbility2(std::string &new_ability2) {
    Pokemon::ability2 = new_ability2;
}

const std::string &Pokemon::getAbilityHidden() const {
    return ability_hidden;
}

void Pokemon::setAbilityHidden(std::string &new_abilityHidden) {
    ability_hidden = new_abilityHidden;
}

int Pokemon::getGeneration() const {
    return generation;
}

void Pokemon::setGeneration(int new_generation) {
    Pokemon::generation = new_generation;
}

bool Pokemon::isLegendary() const {
    return legendary;
}

void Pokemon::setLegendary(bool new_legendary) {
    Pokemon::legendary = new_legendary;
}

bool Pokemon::isMegaEvolution() const {
    return mega_evolution;
}

void Pokemon::setMegaEvolution(bool new_megaEvolution) {
    mega_evolution = new_megaEvolution;
}

float Pokemon::getHeight() const {
    return height;
}

void Pokemon::setHeight(float new_height) {
    Pokemon::height = new_height;
}

float Pokemon::getWeight() const {
    return weight;
}

void Pokemon::setWeight(float new_weight) {
    Pokemon::weight = new_weight;
}

int Pokemon::getHp() const {
    return hp;
}

void Pokemon::setHp(int new_hp) {
    Pokemon::hp = new_hp;
}

int Pokemon::getAtk() const {
    return atk;
}

void Pokemon::setAtk(int new_atk) {
    Pokemon::atk = new_atk;
}

int Pokemon::getSpAtk() const {
    return sp_atk;
}

void Pokemon::setSpAtk(int new_spAtk) {
    Pokemon::sp_atk = new_spAtk;
}

int Pokemon::getSpDef() const {
    return sp_def;
}

void Pokemon::setSpDef(int new_spDef) {
    Pokemon::sp_def = new_spDef;
}

int Pokemon::getSpd() const {
    return spd;
}

void Pokemon::setSpd(int new_spd) {
    Pokemon::spd = new_spd;
}

int Pokemon::getTotal() const {
    return total;
}

void Pokemon::setTotal(int new_total) {
    Pokemon::total = new_total;
}


void Pokemon::addMoves(Move* new_moves) {
    Pokemon::moves.push_back(new_moves);
}

Pokemon::Pokemon(const std::string &name, int new_lvl) : name(name) {

    Utils* utils = new Utils();
    CsvReader reader("/home/idk/Cours/C++/Pokemon_cli/pokemons/Pokemons.csv", ",");
    std::vector<std::vector<std::string> > dataList = reader.getData();

    for (const std::vector<std::string> &vec : dataList) {
        if (vec[3] == name) {
            Pokemon::setId(std::stoi(vec[0]));
            Pokemon::setCode(std::stoi(vec[1]));
            Pokemon::setSerial(std::stoi(vec[2]));
            Pokemon::setName(const_cast<std::string &>(vec[3]));
            Pokemon::setType1(const_cast<std::string &>(vec[4]));
            Pokemon::setType2(const_cast<std::string &>(vec[5]));
            Pokemon::setColor(const_cast<std::string &>(vec[6]));
            Pokemon::setAbility1(const_cast<std::string &>(vec[7]));
            Pokemon::setAbility2(const_cast<std::string &>(vec[8]));
            Pokemon::setAbilityHidden(const_cast<std::string &>(vec[9]));
            Pokemon::setGeneration(std::stoi(vec[10]));
            Pokemon::setLegendary(std::stoi(vec[11]));
            Pokemon::setMegaEvolution(std::stoi(vec[12]));
            Pokemon::setHeight(std::stof(vec[13]));
            Pokemon::setWeight(std::stof(vec[14]));
            Pokemon::setHp(std::stoi(vec[15]));
            Pokemon::setAtk(std::stoi(vec[16]));
            Pokemon::setDef(std::stoi(vec[17]));
            Pokemon::setSpAtk(std::stoi(vec[18]));
            Pokemon::setSpDef(std::stoi(vec[19]));
            Pokemon::setSpd(std::stoi(vec[20]));
            Pokemon::setTotal(std::stoi(vec[21]));
        }
    }

    std::string string_moves = "";
    std::string next_evolution = "";

    CsvReader reader2("/home/idk/Cours/C++/Pokemon_cli/pokemons/pokemon-data.csv", ";");
    std::vector<std::vector<std::string> > dataList2 = reader2.getData();
    for (const std::vector<std::string> &vec : dataList2) {
        if (vec[0] == name) {
            string_moves = vec[11];
            next_evolution = vec[10];
        }
    }
    //LEVELUP
    this->levelUp((int)(pow(new_lvl, 3)), false);



    // CLEAN NEXT EVOLUTION NAME
    next_evolution.erase(std::remove(next_evolution.begin(), next_evolution.end(), '\''), next_evolution.end());
    next_evolution.erase(std::remove(next_evolution.begin(), next_evolution.end(), ']'), next_evolution.end());
    next_evolution.erase(std::remove(next_evolution.begin(), next_evolution.end(), '['), next_evolution.end());
    next_evolution.erase(std::remove(next_evolution.begin(), next_evolution.end(), ' '), next_evolution.end());

    this->setNextEvolutionName(next_evolution);

    // CLEAN MOVES NAME
    string_moves.erase(std::remove(string_moves.begin(), string_moves.end(), '\''), string_moves.end());
    string_moves.erase(std::remove(string_moves.begin(), string_moves.end(), ']'), string_moves.end());
    string_moves.erase(std::remove(string_moves.begin(), string_moves.end(), '['), string_moves.end());
    string_moves.erase(std::remove(string_moves.begin(), string_moves.end(), ' '), string_moves.end());

    std::vector<std::string> string_vector_moves = {};
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token;
    CsvReader reader3("/home/idk/Cours/C++/Pokemon_cli/pokemons/Moves.csv", ",");
    std::vector<std::vector<std::string> > dataList3 = reader3.getData();


    while ((pos = string_moves.find(delimiter)) != std::string::npos) {
        token = string_moves.substr(0, pos);
        string_vector_moves.push_back(token);
        this->addMoves(new Move(token, dataList3));
        string_moves.erase(0, pos + delimiter.length());
    }

    bool i_dont_have_moves = true;
    int size_moves = this->getMoves().size();
    std::vector<Move *> all_moves = this->getMoves();
    while(i_dont_have_moves) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,size_moves);
        int number_random = dist6(rng);
        Move* the_move = all_moves[number_random];
        Move *move_1 = nullptr;
        Move* move_2 = nullptr;
        Move* move_3 = nullptr;

        if (the_move->getCategory() == "Normal" || the_move->getCategory() == "Physical") {
            if (this->getMove1() == nullptr) {
                this->setMove1(the_move);
                move_1 = the_move;
                this->deleteMove(the_move);
                size_moves -= 1;
            } else if (this->getMove2() == nullptr && the_move != move_1) {
                this->setMove2(the_move);
                move_2 = the_move;
                this->deleteMove(the_move);
                size_moves -= 1;
            } else if (this->getMove3() == nullptr && the_move != move_1 && the_move != move_2 ) {
                this->setMove3(the_move);
                move_3 = the_move;
                this->deleteMove(the_move);
                size_moves -= 1;
            } else if (this->getMove4() == nullptr && the_move != move_1 && the_move != move_2 && the_move != move_3 ) {
                this->setMove4(the_move);
                this->deleteMove(the_move);
                size_moves -= 1;
            } else {
                i_dont_have_moves = false;
                break;
            }
        }
    }
}

int Pokemon::getDef() const {
    return def;
}

void Pokemon::setDef(int new_def) {
    Pokemon::def = new_def;
}

Move *Pokemon::getMove1() const {
    return move_1;
}

void Pokemon::setMove1(Move *new_move1) {
    move_1 = new_move1;
}

Move *Pokemon::getMove2() const {
    return move_2;
}

void Pokemon::setMove2(Move *new_move2) {
    move_2 = new_move2;
}

Move *Pokemon::getMove3() const {
    return move_3;
}

void Pokemon::setMove3(Move *new_move3) {
    move_3 = new_move3;
}

Move *Pokemon::getMove4() const {
    return move_4;
}

void Pokemon::setMove4(Move *new_move4) {
    move_4 = new_move4;
}

const std::vector<int> &Pokemon::getNewMoveByLvl() const {
    return new_move_by_lvl;
}

void Pokemon::setNewMoveByLvl(const std::vector<int> &newMoveByLvl) {
    new_move_by_lvl = newMoveByLvl;
}

const std::vector<Move *> &Pokemon::getMoves() const {
    return moves;
}


void Pokemon::setMoves(const std::vector<Move *> &moves) {
    Pokemon::moves = moves;
}

void Pokemon::deleteMove(const Move * moves) {
    Pokemon::moves.erase(std::remove(Pokemon::moves.begin(), Pokemon::moves.end(), moves), Pokemon::moves.end());
}


Pokemon::~Pokemon() {
    delete this->move_1;
    delete this->move_2;
    delete this->move_3;
    delete this->move_4;
}

const std::string &Pokemon::getNextEvolutionName() const {
    return next_evolution_name;
}

void Pokemon::setNextEvolutionName(const std::string &new_nextEvolutionName) {
    next_evolution_name = new_nextEvolutionName;
}

int Pokemon::getCurrentHp() const {
    return current_hp;
}

void Pokemon::setCurrentHp(int new_currentHp) {
    current_hp = new_currentHp;
}

int Pokemon::getLvl() const {
    return lvl;
}

void Pokemon::levelUp(int new_exp, bool do_log) {
    bool lvl_up = false;
    bool compute = true;
    int new_expv2 = new_exp;
    this->setTotalExp(this->getTotalExp() + new_exp);
    while (compute) {
        if (this->getExp() + new_exp >= this->getExpForNextLvl()) {
            lvl_up = true;
            Pokemon::setLvl(this->getLvl() + 1);
            Pokemon::setCurrentHpMax();
            Pokemon::setExp(this->getExp() + new_exp - this->getExpForNextLvl());
            Pokemon::setExpForNextLvl((int)pow((this->getLvl() + 1), 3));
            Pokemon::setCurrentHp(this->getCurrentHpMax());
            Pokemon::setCurrentAtk(setAllStats(this->getAtk()));
            Pokemon::setCurrentSpAtk(setAllStats(this->getSpAtk()));
            Pokemon::setCurrentDef(setAllStats(this->getDef()));
            Pokemon::setCurrentSpDef(setAllStats(this->getSpDef()));
            Pokemon::setCurrentSpd(setAllStats(this->getSpd()));
            new_exp = new_expv2 - this->getExp();
            if (do_log) {
                std::string white_space_before_text(25, ' ');
                std::cout << white_space_before_text << CYN << "Great congrulation, " <<BLUE << this->getName() << CYN << " level up ! New lvl: "<< YLW << this->getLvl() << NC << std::endl;
                sleep(2);
            }
        } else if (!lvl_up){
            this->setExp(this->getExp() + new_exp);
            compute = false;
        } else {
            compute = false;
        }
    }

}

void Pokemon::setLvl(int lvl) {
    Pokemon::lvl = lvl;
}

int Pokemon::getExp() const {
    return exp;
}

void Pokemon::setExp(int new_exp) {
    Pokemon::exp = new_exp;
}

int Pokemon::getCurrentHpMax() const {
    return current_hp_max;
}

void Pokemon::setCurrentHpMax() {
    float current_hp_max_1 = (((this->getHp() + 15 + 31)/50)* this->getLvl()) + 10;
    Pokemon::current_hp_max = (static_cast<int>(current_hp_max_1));
}

int Pokemon::setAllStats(int base_stat) {
    return static_cast<int>(((base_stat + 15 + 31)/50)*this->getLvl()+5);
}

int Pokemon::getExpForNextLvl() const {
    return exp_for_next_lvl;
}

void Pokemon::setExpForNextLvl(int expForNextLvl) {
    exp_for_next_lvl = expForNextLvl;
}

int Pokemon::getTotalExp() const {
    return total_exp;
}

void Pokemon::setTotalExp(int totalExp) {
    total_exp = totalExp;
}

int Pokemon::getCurrentAtk() const {
    return current_atk;
}

void Pokemon::setCurrentAtk(int currentAtk) {
    current_atk = currentAtk;
}

int Pokemon::getCurrentDef() const {
    return current_def;
}

void Pokemon::setCurrentDef(int currentDef) {
    current_def = currentDef;
}

int Pokemon::getCurrentSpAtk() const {
    return current_sp_atk;
}

void Pokemon::setCurrentSpAtk(int currentSpAtk) {
    current_sp_atk = currentSpAtk;
}

int Pokemon::getCurrentSpDef() const {
    return current_sp_def;
}

void Pokemon::setCurrentSpDef(int currentSpDef) {
    current_sp_def = currentSpDef;
}

int Pokemon::getCurrentSpd() const {
    return current_spd;
}

void Pokemon::setCurrentSpd(int currentSpd) {
    current_spd = currentSpd;
}

