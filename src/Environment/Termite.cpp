#include "Termite.hpp"
#include <Application.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>


Termite::Termite(ToricPosition const& position)
    : Animal(position, getAppConfig().termite_hp, getAppConfig().termite_lifespan, 3), _attack_delay(getAppConfig().termite_attack_delay)
{}


double Termite::getSpeed() const
{
    if(getAppEnv().getTemperature() == getAppConfig().simulation_usual_temperature) {
        return getAppConfig().termite_speed ;
    } else {
        return getAppConfig().termite_speed_high_temperature ;
    }
}


void Termite::drawOn(sf::RenderTarget& target) const
{
    auto const termiteSprite = buildSprite((getPosition()).toVec2d(), getAppConfig().animal_size, getAppTexture(getAppConfig().termite_texture), getDirection() / DEG_TO_RAD) ;
    target.draw(termiteSprite) ;

    if (isDebugOn()) {
        auto const text = buildText(to_nice_string(getLifePoints()), (getPosition()).toVec2d() + Vec2d(0,30), getAppFont(), getAppConfig().text_size, sf::Color::Black, getDirection() / DEG_TO_RAD) ;
        target.draw(text) ;
        sf::VertexArray ligne(sf::PrimitiveType::Lines, 2) ;
        ligne[0] = { getPosition().toVec2d(), sf::Color::Black } ;
        ligne[1] = { getPosition().toVec2d() + 100 * Vec2d::fromAngle(getDirection()), sf::Color::Blue } ;
        target.draw(ligne) ;
    }
}


bool Termite::isEnemy(Animal const* animal) const
{
    return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this) ;
}


bool Termite::isEnemyDispatch(Termite const* other) const
{
    return false ;
}


bool Termite::isEnemyDispatch(Ant const* other) const
{
    return true ;
}


void Termite::update(sf::Time dt)
{
    if(getStatus() == Idle) {
        Animal::update(dt) ;
        Animal::update(dt, _attack_delay, getAppConfig().termite_strength) ;
        setTimerPeace(getTimerPeace() + dt) ;
    }

    if((getStatus() == Attack) and (getTimerPeace() >= sf::seconds(_attack_delay))) {
        Animal::update(dt, _attack_delay, getAppConfig().termite_strength) ;
    }
}


void Termite::fight(Animal* & enemy, sf::Time dt)
{
    if(getAppEnv().getTemperature() == getAppConfig().simulation_usual_temperature) {
        Animal::fight(enemy, dt, _attack_delay, getAppConfig().termite_strength) ;
    } else {
        Animal::fight(enemy, dt, _attack_delay, getAppConfig().termite_strength_high_temperature) ;
    }
}
