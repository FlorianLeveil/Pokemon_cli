//
// Created by idk on 18/01/2021.
//

#include "Move.h"
#include "../utils/CsvReader.h"

#include <utility>

Move::Move(int id, std::string name, std::string type, std::string category,
           std::string contest, int pp, int power, int accuracy, int generation) : id(id), name(std::move(name)),
                                                                                            type(std::move(type)),
                                                                                            category(std::move(category)),
                                                                                            contest(std::move(contest)), pp(pp),
                                                                                            power(power),
                                                                                            accuracy(accuracy),
                                                                                            generation(generation) {}

int Move::getId() const {
    return id;
}

void Move::setId(int new_id) {
    Move::id = new_id;
}

const std::string &Move::getName() const {
    return name;
}

void Move::setName(const std::string &new_name) {
    Move::name = new_name;
}

const std::string &Move::getType() const {
    return type;
}

void Move::setType(const std::string &new_type) {
    Move::type = new_type;
}

const std::string &Move::getCategory() const {
    return category;
}

void Move::setCategory(const std::string &new_category) {
    Move::category = new_category;
}

const std::string &Move::getContest() const {
    return contest;
}

void Move::setContest(const std::string &new_contest) {
    Move::contest = new_contest;
}

int Move::getPp() const {
    return pp;
}

void Move::setPp(int new_pp) {
    Move::pp = new_pp;
}

int Move::getPower() const {
    return power;
}

void Move::setPower(int new_power) {
    Move::power = new_power;
}

int Move::getAccuracy() const {
    return accuracy;
}

void Move::setAccuracy(int new_accuracy) {
    Move::accuracy = new_accuracy;
}

int Move::getGeneration() const {
    return generation;
}

void Move::setGeneration(int new_generation) {
    Move::generation = new_generation;
}

Move::Move(const std::string &name, std::vector<std::vector<std::string> > dataList3 ) : name(name) {
    for(std::vector<std::string>& vec : dataList3)
    {
        if (vec[1] == name ) {
           this->setId(std::stoi(vec[0]));
           this->setName(const_cast<std::string &>(vec[1]));
           this->setType(const_cast<std::string &>(vec[2]));
           this->setCategory(const_cast<std::string &>(vec[3]));
           this->setContest(const_cast<std::string &>(vec[4]));
           this->setPp(std::stoi(vec[5]));
           this->setCurrentPp(std::stoi(vec[5]));
           this->setPower(std::stoi(vec[6]));
           this->setAccuracy(std::stoi(vec[7]));
           this->setGeneration(std::stoi(vec[8]));
           break;
        }
    }
}

int Move::getCurrentPp() const {
    return current_pp;
}

void Move::setCurrentPp(int currentPp) {
    current_pp = currentPp;
}
