//
// Created by idk on 18/01/2021.
//

#ifndef POKEMON_CLI_MOVE_H
#define POKEMON_CLI_MOVE_H
#include <string>
#include <vector>


class Move {
private:

    int id;
    std::string name;
    std::string type;
    std::string category;
    std::string contest;
    int pp;
    int current_pp = pp;
    int power;
    int accuracy;
    int generation;
public:

    Move(const std::string &name, std::vector<std::vector<std::string>> dataList3);

    Move(const std::string &name);

    Move(int id, std::string name, std::string type, std::string category,
         std::string contest, int pp, int power, int accuracy, int generation);

    int getId() const;

    int getCurrentPp() const;

    void setCurrentPp(int currentPp);

    void setId(int id);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getType() const;

    void setType(const std::string &type);

    const std::string &getCategory() const;

    void setCategory(const std::string &category);

    const std::string &getContest() const;

    void setContest(const std::string &contest);

    int getPp() const;

    void setPp(int pp);

    int getPower() const;

    void setPower(int power);

    int getAccuracy() const;

    void setAccuracy(int accuracy);

    int getGeneration() const;

    void setGeneration(int generation);
};


#endif //POKEMON_CLI_MOVE_H
