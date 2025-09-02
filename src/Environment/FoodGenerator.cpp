#include "FoodGenerator.hpp"
#include <Application.hpp>
#include <Environment/Food.hpp>


FoodGenerator::FoodGenerator()
    : Generator()
{}


void FoodGenerator::update(sf::Time dt)
{
    if((getAppEnv().getTemperature() == getAppConfig().simulation_usual_temperature) or (getAppEnv().getDayCycle() == Night)) {
        Quantity new_quantity(0) ;
        Vec2d new_coordinates ;
        Generator::update_entity(dt, getAppConfig().food_generator_delta, getAppConfig().food_min_qty, getAppConfig().food_max_qty, new_coordinates, new_quantity) ;
        getAppEnv().addFood(new Food(new_coordinates, new_quantity)) ;
    }
}
