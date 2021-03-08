//
// Created by idk on 25/01/2021.
//

#ifndef POKEMON_CLI_MENU_H
#define POKEMON_CLI_MENU_H
#include <string>
#include <vector>

class Menu {
private:
    int id;
    std::string type;
    std::string name;
    std::string header;
    std::vector<std::string> choice;
public:
    Menu();

    const std::string &getType() const;

    void setType(const std::string &type);

    const std::string &getName() const;

    void setName(const std::string &name);

    Menu(int id);

    Menu(int id, std::string &header, std::vector<std::string> &choice);

    int getId() const;

    void setId(int id);

    const std::string &getHeader() const;

    void setHeader(const std::string &header);

    const std::vector<std::string> &getChoice() const;

    void setChoice(const std::vector<std::string> &choice);

    Menu createMenu(int id) const;

    virtual ~Menu();

};


#endif //POKEMON_CLI_MENU_H
