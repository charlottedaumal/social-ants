#include "InsecticideGenerator.hpp"
#include <Application.hpp>
#include <Environment/Insecticide.hpp>


InsecticideGenerator::InsecticideGenerator()
    :  Generator()
{}


void InsecticideGenerator::update(sf::Time dt)
{
    if(getAppEnv().getTemperature() == getAppConfig().simulation_usual_temperature) {
        Quantity new_quantity(0) ;
        Vec2d new_coordinates ;
        Generator::update_entity(dt, getAppConfig().insecticide_generator_delta, getAppConfig().insecticide_min_qty, getAppConfig().insecticide_max_qty, new_coordinates, new_quantity) ;
        getAppEnv().addInsecticide(new Insecticide (new_coordinates, new_quantity)) ;
    }
}



