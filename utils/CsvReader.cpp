//
// Created by idk on 18/01/2021.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "CsvReader.h"

std::vector<std::vector<std::string> > CsvReader::getData()
{
    std::ifstream file(fileName);
    std::vector<std::vector<std::string> > dataList;
    std::string line;
    // Iterate through each line and split the content using delimeter

    while (getline(file, line))
    {
        std::vector<std::string> vec;
        boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
        dataList.push_back(vec);
    }
    // Close the File
    file.close();
    return dataList;
}