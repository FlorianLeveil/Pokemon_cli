//
// Created by idk on 18/01/2021.
//

#ifndef POKEMON_CLI_POKEMON_H
#define POKEMON_CLI_POKEMON_H
#include <string>
#include <vector>
#include <memory>
#include "Move.h"

class Pokemon {
private:
    int id;
    int code;
    int serial;
    std::string next_evolution_name;
    std::string name;
    std::string type1;
    std::string type2;
    std::string color;
    std::string ability1;
    std::string ability2;
    std::string ability_hidden;
    int generation;
    bool legendary;
    bool mega_evolution;
    float height;
    float weight;
    int hp;
    int lvl = 1;
    int exp = 0;
    int exp_for_next_lvl = 0;
    int total_exp = 0;
    int current_hp;
    int current_hp_max;
    int atk;
    int def;
    int sp_atk;
    int sp_def;
    int current_atk;
    int current_def;
    int current_sp_atk;
    int current_sp_def;
    int spd;
    int current_spd;
    int total;
    std::vector<Move *> moves;
    Move* move_1 = nullptr;
    Move* move_2 = nullptr;
    Move* move_3 = nullptr;
    Move* move_4 = nullptr;
    std::vector<int> new_move_by_lvl;

public:
    Pokemon(const std::string &name, int new_lvl);

    int getCurrentSpd() const;

    void setCurrentSpd(int currentSpd);

    int getCurrentAtk() const;

    void setCurrentAtk(int currentAtk);

    int getCurrentDef() const;

    void setCurrentDef(int currentDef);

    int getCurrentSpAtk() const;

    void setCurrentSpAtk(int currentSpAtk);

    int getCurrentSpDef() const;

    void setCurrentSpDef(int currentSpDef);

    int getExpForNextLvl() const;

    void setExpForNextLvl(int expForNextLvl);

    int getTotalExp() const;

    void setTotalExp(int totalExp);

    int getCurrentHpMax() const;

    void  setCurrentHpMax();

    int getLvl() const;

    void setLvl(int lvl);

    int getExp() const;

    void setExp(int exp);

    int getCurrentHp() const;

    void setCurrentHp(int currentHp);

    const std::string &getNextEvolutionName() const;

    void setNextEvolutionName(const std::string &nextEvolutionName);

    const std::vector<Move *> &getMoves() const;

    void setMoves(const std::vector<Move *> &moves);

    Move *getMove1() const;

    void setMove1(Move *move1);

    Move *getMove2() const;

    void setMove2(Move *move2);

    Move *getMove3() const;

    void setMove3(Move *move3);

    Move *getMove4() const;

    void setMove4(Move *move4);

    const std::vector<int> &getNewMoveByLvl() const;

    void setNewMoveByLvl(const std::vector<int> &newMoveByLvl);

    int getDef() const;

    void setDef(int def);


    int getId() const;

    void setId(int id);

    int getCode() const;

    void setCode(int code);

    int getSerial() const;

    void setSerial(int serial);

    const std::string &getName() const;

    void setName( std::string &name);

    const std::string &getType1() const;

    void setType1( std::string &type1);

    const std::string &getType2() const;

    void setType2( std::string &type2);

    const std::string &getColor() const;

    void setColor( std::string &color);

    const std::string &getAbility1() const;

    void setAbility1( std::string &ability1);

    const std::string &getAbility2() const;

    void setAbility2(std::string &ability2);

    const std::string &getAbilityHidden() const;

    void setAbilityHidden( std::string &abilityHidden);

    int getGeneration() const;

    void setGeneration(int generation);

    bool isLegendary() const;

    void setLegendary(bool legendary);

    bool isMegaEvolution() const;

    void setMegaEvolution(bool megaEvolution);

    float getHeight() const;

    void setHeight(float height);

    float getWeight() const;

    void setWeight(float weight);

    int getHp() const;

    void setHp(int hp);

    int getAtk() const;

    void setAtk(int atk);

    int getSpAtk() const;

    void setSpAtk(int spAtk);

    int getSpDef() const;

    void setSpDef(int spDef);

    int getSpd() const;

    void setSpd(int spd);

    int getTotal() const;

    void setTotal(int total);

    void addMoves(Move* new_moves);

    virtual ~Pokemon();

    void deleteMove(const Move *moves);

    int setAllStats(int base_stat);

    void levelUp(int new_exp, bool do_log);
};


#endif //POKEMON_CLI_POKEMON_H