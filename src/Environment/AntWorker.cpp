#include "AntWorker.hpp"
#include <Application.hpp>
#include <Utility/Utility.hpp>


AntWorker::AntWorker(ToricPosition const& position, Uid const& id_anthill)
    : Ant(position, id_anthill, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan, 1), _food_collected(0.0)
{}


Quantity AntWorker::getFoodCollected () const
{
    return _food_collected ;
}


void AntWorker::setFoodCollected(Quantity const& food_collected)
{
    _food_collected = food_collected ;
}


void AntWorker::drawOn(sf::RenderTarget& target) const
{
    Ant::drawOn(target, getAppConfig().ant_worker_texture) ;

    if (isDebugOn()) {
        auto const text = buildText(to_nice_string(getFoodCollected()), (getPosition()).toVec2d() + Vec2d(0,60), getAppFont(), getAppConfig().text_size, sf::Color::Red, getDirection() / DEG_TO_RAD) ;
        target.draw(text) ;
    }
}


void AntWorker::update(sf::Time dt)
{
    if(getStatus() == Idle) {
        Ant::update(dt) ;

        Food* closest_food(getAppEnv().getClosestFoodForAnt(getPosition())) ;
        Anthill* anthill_for_ant(getAppEnv().getAnthillForAnt(getPosition(), getIdAnthill())) ;

        //checking if the food is contaminated with some insecticide
        if((closest_food != nullptr) and (closest_food->isContaminated())) {
            setLifePoints(0) ;
        }

        //checking if the worker ant meets a source of food and can take some
        if((closest_food != nullptr) and (getFoodCollected() == 0.0) and (getLifePoints() > 0)) {
            if((closest_food->getQuantity() >= getAppConfig().ant_max_food)) {
                setFoodCollected (getAppConfig().ant_max_food) ;
                closest_food->setQuantity(closest_food->getQuantity() - getAppConfig().ant_max_food) ;
            } else {
                setFoodCollected(closest_food->getQuantity()) ;
                closest_food->setQuantity(0.0) ;
            }
            if(anthill_for_ant == nullptr) {
                setDirection(getDirection() + PI) ;
            }
        }

        // checking if the worker ant meets its anthill and put the food it collected in its anthill
        if((anthill_for_ant != nullptr) and (getFoodCollected() != 0.0) and (getLifePoints() > 0)) {
            anthill_for_ant->setFoodStock(anthill_for_ant->getFoodStock() + getFoodCollected()) ;
            setFoodCollected(0.0) ;
            setDirection(getDirection() + PI) ;
        }

        anthill_for_ant = nullptr ;
        closest_food = nullptr ;
    }
}


void AntWorker::fight(Animal* & enemy, sf::Time dt)
{
    if(getAppEnv().getTemperature() == getAppConfig().simulation_usual_temperature) {
        Animal::fight(enemy, dt, getAttackDelay(), getAppConfig().ant_worker_strength) ;
    } else {
        Animal::fight(enemy, dt, getAttackDelay(), getAppConfig().ant_worker_strength_high_temperature) ;
    }
}
