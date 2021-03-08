//
// Created by idk on 18/01/2021.
//

#ifndef POKEMON_CLI_CSVREADER_H
#define POKEMON_CLI_CSVREADER_H
#include <utility>
#include <vector>
#include <string>


class CsvReader {

    std::string fileName;
    std::string delimeter;
public:

    CsvReader(std::string filename, std::string delimeter = "|") :
            fileName(std::move(filename)), delimeter(std::move(delimeter))
    { }

    std::vector<std::vector<std::string> > getData();
};

#endif //POKEMON_CLI_CSVREADER_H
