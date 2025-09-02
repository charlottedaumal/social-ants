#include "AntSoldier.hpp"
#include <Application.hpp>


AntSoldier::AntSoldier(ToricPosition const& position, Uid const& id_anthill)
    : Ant(ToricPosition(position), id_anthill, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan, 2)
{}


void AntSoldier::drawOn(sf::RenderTarget& target) const
{
    Ant:: drawOn(target, getAppConfig().ant_soldier_texture) ;
}


void AntSoldier::update(sf::Time dt)
{
    if(getStatus() == Idle) {
        Ant::update(dt) ;
        Animal::update(dt, getAttackDelay(), getAppConfig().ant_soldier_strength) ;
        setTimerPeace(getTimerPeace() + dt) ;
    }

    if((getStatus() == Attack) and (getTimerPeace() >= sf::seconds(getAttackDelay()))) {
        Animal::update(dt, getAttackDelay(), getAppConfig().ant_soldier_strength) ;
    }
}


void AntSoldier::fight(Animal* & enemy, sf::Time dt)
{
    if(getAppEnv().getTemperature() == getAppConfig().simulation_usual_temperature) {
        Animal::fight(enemy, dt, getAttackDelay(), getAppConfig().ant_soldier_strength) ;
    } else {
        Animal::fight(enemy, dt, getAttackDelay(), getAppConfig().ant_soldier_strength_high_temperature) ;
    }
}
