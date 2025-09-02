#include "Generator.hpp"
#include <Random/Random.hpp>
#include <Application.hpp>


Generator::Generator()
    : _timer(sf::Time::Zero)
{}


void Generator::update_entity(sf::Time dt,  double const& delta, double const& min_qty, double const& max_qty, Vec2d& new_coordinates, Quantity& new_quantity)
{
    _timer += dt ;

    if(_timer > sf::seconds(delta)) {
        _timer = sf::Time::Zero ;
        new_coordinates = Vec2d (normal(getAppConfig().simulation_size/2, getAppConfig().simulation_size/4*getAppConfig().simulation_size/4), normal(getAppConfig().simulation_size/2, getAppConfig().simulation_size/4*getAppConfig().simulation_size/4)) ;
        new_quantity = Quantity (uniform(min_qty, max_qty)) ;
    }
}
