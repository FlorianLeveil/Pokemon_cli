cmake_minimum_required(VERSION 3.17)
project(Pokemon_cli)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pokemon_cli main.cpp pokemons/Pokemon.cpp pokemons/Pokemon.h pokemons/Move.cpp pokemons/Move.h utils/Utils.cpp utils/Utils.h utils/CsvReader.cpp utils/CsvReader.h pokeballs/Pokeball.cpp pokeballs/Pokeball.h trainers/Trainer.cpp trainers/Trainer.h bags/Bag.cpp bags/Bag.h potions/Potion.cpp potions/Potion.h menus/Menu.cpp menus/Menu.h pcs/Pc.cpp pcs/Pc.h fights/Fight.cpp fights/Fight.h)