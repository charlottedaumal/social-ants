#include "Food.hpp"
#include <Utility/Utility.hpp>
#include <Application.hpp>


Food::Food(Vec2d const& position_toric, Quantity const& quantity)
    : Positionable(position_toric), _quantity(quantity)
{}


Quantity Food::getQuantity() const
{
    return _quantity ;
}


void Food::setQuantity(Quantity const& new_quantity)
{
    _quantity = new_quantity ;
}


Quantity Food::takeQuantity(Quantity const& quantity_to_collect)
{
    Quantity quantity_collected ;

    if(quantity_to_collect >= getQuantity()) {
        quantity_collected = getQuantity() ;
    } else {
        quantity_collected = quantity_to_collect ;
    }

    setQuantity(getQuantity() - quantity_collected) ;
    return quantity_collected ;
}


void Food::drawOn(sf::RenderTarget& target) const
{
    std::string food_texture(getAppConfig().food_texture);
    if(_quantity < ((getAppConfig().food_min_qty)+(getAppConfig().food_max_qty))/2) {
        food_texture = getAppConfig().food_deshydrated_texture ;
    }

    auto const foodSprite = buildSprite((getPosition()).toVec2d(), getQuantity(), getAppTexture(food_texture)) ;
    target.draw(foodSprite) ;

    if (isDebugOn()) {
        auto const text = buildText(to_nice_string(getQuantity()), (getPosition()).toVec2d() + Vec2d(0,10), getAppFont(), getAppConfig().text_size, sf::Color::Black) ;
        target.draw(text) ;
    }
}


void Food::update(sf::Time dt)
{
    _quantity -= (dt.asSeconds() * getAppConfig().food_evaporation_rate) ;
}


bool Food::isContaminated() const
{
    Insecticide* closest_insecticide(getAppEnv().getClosestInsecticideForEntity(const_cast<Food* const>(this))) ;
    return (closest_insecticide != nullptr) ;
}
