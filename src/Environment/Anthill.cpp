#include "Anthill.hpp"
#include <Application.hpp>
#include <Random/Random.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <Environment/Food.hpp>
#include <Environment/AntSoldier.hpp>
#include <Environment/AntWorker.hpp>


Anthill::Anthill(ToricPosition const&  position_toric)
    :Positionable (position_toric), _food_stock(0.0), _id(createUid()), _timer(sf::Time::Zero), _size(getAppConfig().anthill_size)
{
    double random (uniform(0,1)) ;
    if((random >= 0) and (random < 0.5)) {
        getAppEnv().addAnimal(new AntWorker(position_toric, _id)) ;
    } else {
        getAppEnv().addAnimal(new AntSoldier(position_toric, _id)) ;
    }
}


Quantity Anthill::getFoodStock() const
{
    return _food_stock ;
}


void Anthill::setFoodStock(Quantity const& food_stock)
{
    _food_stock = food_stock ;
}


Uid Anthill::getId() const
{
    return _id ;
}


sf::Time Anthill::getTimer() const
{
    return _timer ;
}


void Anthill::setTimer(sf::Time const&  new_timer)
{
    _timer = new_timer ;
}


double Anthill::getProbaWorker() const
{
    return getAppConfig().anthill_worker_prob_default ;
}


double Anthill::getSize() const
{
    return _size ;
}


void Anthill::drawOn(sf::RenderTarget& target) const
{
    auto const anthillSprite = buildSprite((getPosition()).toVec2d(), _size, getAppTexture(getAppConfig().anthill_texture)) ;
    target.draw(anthillSprite) ;

    if (isDebugOn()) {
        auto const text1 = buildText(to_nice_string(getFoodStock()), (getPosition()).toVec2d() + Vec2d(0,30), getAppFont(), getAppConfig().text_size, sf::Color::Black) ;
        auto const text2 = buildText(to_nice_string(getId()), (getPosition()).toVec2d() + Vec2d(0,50), getAppFont(), getAppConfig().text_size, sf::Color::Magenta) ;
        target.draw(text1) ;
        target.draw(text2) ;
    }
}


void Anthill::update(sf::Time dt)
{
    _timer += dt ;

    if(_timer >= sf::seconds(getAppConfig().anthill_spawn_delay)) {
        setTimer(sf::Time::Zero) ;
        double theta(uniform(0,1)) ;

        if ((theta >= 0.0) and (theta <= getProbaWorker())) {
            getAppEnv().addAnimal(new AntWorker(getPosition().toVec2d(), getId())) ;
        } else {
            getAppEnv().addAnimal(new AntSoldier(getPosition().toVec2d(), getId())) ;
        }
    }

    if(isContaminated()) {
        _size -= 0.5 ;
    }

}


bool Anthill::isContaminated() const
{
    Insecticide* closest_insecticide(getAppEnv().getClosestInsecticideForEntity(const_cast<Anthill* const>(this))) ;
    return (closest_insecticide != nullptr) ;
}
