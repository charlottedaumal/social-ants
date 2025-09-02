#include "Pheromone.hpp"
#include <Application.hpp>
#include <Utility/Utility.hpp>


Pheromone::Pheromone(Vec2d const& position, double const& quantity)
    : Positionable (ToricPosition(position)), _quantity(quantity)
{}


double Pheromone::getQuantity() const
{
    return _quantity ;
}


void Pheromone::setQuantity(double const& quantity)
{
    _quantity = quantity ;
}


void Pheromone::drawOn(sf::RenderTarget& target) const
{
    sf::Color color(sf::Color::Green) ;
    color.a = (255 / getAppConfig().ant_pheromone_energy) * _quantity ;
    auto const circle = buildCircle(getPosition().toVec2d(), 5.0, color) ;
    target.draw(circle) ;
}


void Pheromone::update(sf:: Time dt)
{
    if(getAppEnv().getTemperature() <= getAppConfig().simulation_usual_temperature) {
        _quantity -= (dt.asSeconds() * getAppConfig().pheromone_evaporation_rate) ;
    } else {
        _quantity -= (dt.asSeconds() * getAppConfig().pheromone_evaporation_rate_high_temperature) ;
    }
}


bool Pheromone::isNegligible() const
{
    return (_quantity <= getAppConfig().pheromone_threshold) ;
}
