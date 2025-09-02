#include "Loader.hpp"
#include <fstream>
#include "Application.hpp"
#include <Environment/Environment.hpp>
#include <Environment/Termite.hpp>
#include <Utility/Utility.hpp>


void loadMap(std::string const& filepath)
{
    std::vector<std::string> element ;
    std::ifstream file(filepath) ;

    if (file.is_open()) {
        std::string line ;

        while(std::getline(file, line)) {
            element = split(line, ' ') ;

            if((line.substr(0,1) != "#") and (line.substr(0,1) != "\r")) {
                if(line.substr(0,7) == "anthill" ) {
                    getAppEnv().addAnthill(new Anthill(ToricPosition(std::stoi(element[1]), std::stoi(element[2])))) ;
                } else if(line.substr(0,4) == "food") {
                    getAppEnv().addFood(new Food(Vec2d(std::stoi(element[1]), std::stoi(element[2])), std::stoi(element[3]))) ;
                } else if(line.substr(0,7) == "termite") {
                    getAppEnv().addAnimal(new Termite(ToricPosition(std::stoi(element[1]), std::stoi(element[2])))) ;
                } else {
                    std::cerr << "ERROR: incorrect line" << std::endl ;
                }
            }
        }
    }

    file.close() ;
}


void saveMap(std::string const& filepath)
{
    std::ofstream output(filepath.c_str()) ;

    std::vector<ToricPosition> anthills_positions(getAppEnv().getAnthillsPositions()) ;
    std::vector<ToricPosition> food_positions(getAppEnv().getFoodPositions()) ;
    Quantities food_quantities(getAppEnv().getFoodQuantities()) ;
    std::vector<ToricPosition> termites_positions(getAppEnv().getTermitesPositions()) ;

    if(output.is_open()) {

        output << "#anthill posX posY" << std::endl ;
        for(unsigned int i(0) ; i < anthills_positions.size() ; ++i) {
            output << "anthill " << anthills_positions[i] << std::endl ;
        }
        output << std::endl ;

        output << "#food posX posY quantity" << std::endl ;
        for(unsigned int i(0) ; i < food_positions.size() ; ++i) {
            output << "food " << food_positions[i] << " " << food_quantities[i] << std::endl ;
        }
        output << std::endl ;

        output << "#termite posX posY" << std::endl ;
        for(unsigned int i(0) ; i < termites_positions.size() ; ++i) {
            output << "termite " << termites_positions[i] << std::endl ;
        }
        output << std::endl ;

    } else {
        std::cerr << "ERROR: impossible to open the file" ;
    }

    output.close() ;
}
