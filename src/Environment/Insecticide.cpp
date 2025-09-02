#include "Insecticide.hpp"
#include <Utility/Utility.hpp>
#include <Application.hpp>


Insecticide::Insecticide(Vec2d const& position_toric, Quantity const& quantity)
    : Positionable(position_toric), _quantity(quantity)
{}


Quantity Insecticide::getQuantity() const
{
    return _quantity ;
}


void Insecticide::setQuantity(Quantity const& new_quantity)
{
    _quantity = new_quantity ;
}


void Insecticide::drawOn(sf::RenderTarget& target) const
{
    sf::Color color(sf::Color::Red) ;
    color.a = (255 / getAppConfig().insecticide_max_qty) * _quantity ;
    auto const circle = buildCircle(getPosition().toVec2d(), 10.0, color) ;
    target.draw(circle) ;

    if (isDebugOn()) {
        auto const text = buildText(to_nice_string(getQuantity()), (getPosition()).toVec2d() + Vec2d(0,10), getAppFont(), getAppConfig().text_size, sf::Color::Black) ;
        target.draw(text) ;
    }
}


void Insecticide::update(sf:: Time dt)
{
    if(getAppEnv().getTemperature() <= getAppConfig().simulation_usual_temperature) {
        _quantity -= (dt.asSeconds() * getAppConfig().insecticide_evaporation_rate) ;
    } else {
        _quantity -= (dt.asSeconds() * getAppConfig().insecticide_evaporation_rate_high_temperature) ;
    }
}



