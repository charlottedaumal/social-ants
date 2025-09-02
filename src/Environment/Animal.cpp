#include "Animal.hpp"
#include <Utility/Constants.hpp>
#include <Random/Random.hpp>
#include <Random/RandomGenerator.hpp>
#include <Application.hpp>


Animal::Animal(ToricPosition const& position, int const& life_points, int const& life_expectancy, unsigned int id_type)
    : Positionable(position), _direction(uniform(0.0,TAU)), _life_points(life_points), _life_expectancy(life_expectancy), _timer(sf::Time::Zero), _status(Idle), _timer_fight(sf::Time::Zero), _timer_peace(sf::seconds(getAppConfig().termite_attack_delay)), _id_type(id_type)
{}


Animal::Animal(ToricPosition const& position)
    : Animal(position, 1, getAppConfig().animal_default_lifespan)
{}


Angle Animal::getDirection() const
{
    return _direction ;
}


int Animal::getLifeExpectancy() const
{
    return _life_expectancy ;
}


int Animal::getLifePoints() const
{
    return _life_points ;
}


sf::Time Animal::getTimer() const
{
    return _timer ;
}


Status Animal::getStatus() const
{
    return _status ;
}


sf::Time Animal::getTimerPeace() const
{
    return _timer_peace ;
}


unsigned int Animal::getIdType() const
{
    return _id_type ;
}


void Animal::setDirection(Angle const& angle)
{
    _direction = angle ;
}


void Animal::setLifeExpectancy(int const& life_expectancy)
{
    _life_expectancy = life_expectancy ;
}


void Animal::setTimer(sf::Time const& timer)
{
    _timer = timer ;
}


void Animal::setLifePoints(int const& life_points)
{
    _life_points = life_points ;
}


void Animal::setStatus(Status const& status)
{
    _status = status ;
}


void Animal::setTimerPeace(sf::Time const& timer_peace)
{
    _timer_peace = timer_peace ;
}


bool Animal::isDead() const
{
    return ((_life_points <= 0.0) or (_life_expectancy <= 0)) ;
}


void Animal::move(sf::Time dt)
{
    auto dx = getSpeed() * Vec2d::fromAngle(_direction).Vec2d::normalised() * dt.asSeconds() ;
    setPosition(getPosition().toVec2d() + dx) ;
    turn() ;
}


void Animal::turn()
{
    if(_timer >= sf::seconds(getAppConfig().animal_next_rotation_delay)) {
        RotationProbs data(computeRotationProbs()) ;
        std::piecewise_linear_distribution<> dist(data.first.begin(), data.first.end(), data.second.begin()) ;
        double gamma(dist(getRandomGenerator()) * DEG_TO_RAD) ;
        setDirection(_direction + gamma) ;
        setTimer(sf::Time::Zero) ;
    }
}


//life update for all animals
void Animal::update(sf::Time dt)
{
    _timer += dt ;
    _life_expectancy -= 1 ;

    if((getAppEnv().getDayCycle() == Day) or (getAppEnv().getTemperature() == getAppConfig().simulation_usual_temperature) or (getAppEnv().getTemperature() == getAppConfig().simulation_high_temperature)) {
        move(dt) ;
    }

    if((getAppEnv().getTemperature() == getAppConfig().simulation_low_temperature) or(getAppEnv().getTemperature() == getAppConfig().simulation_high_temperature)) {
        _life_expectancy -= 1 ;
    }

    Insecticide* closest_insecticide(getAppEnv().getClosestInsecticideForAnimal(this)) ;
    if(closest_insecticide != nullptr) {
        _life_points = 0 ;
    }
    closest_insecticide = nullptr ;
}


//fight update for predators
void Animal::update(sf::Time dt, double const& delay, int const& strength)
{
    if(getAppEnv().getDayCycle() == Day) {
        Animal* enemy (getAppEnv().getClosestEnemy(this)) ;
        if(enemy != nullptr) {
            if (_timer_fight <= sf::seconds(delay)) {
                _status = Attack ;
                enemy->setStatus(Attack) ;
            }

            fight(enemy, dt, delay, strength) ;

            if(_timer_fight == sf::Time::Zero) {
                _status = Idle ;
            }
        } else {
            _status = Idle ;
        }
    }
}


const RotationProbs Animal::computeRotationProbs() const
{
    return RotationProbs ({ -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180},
    {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000}) ;
}


void Animal::fight(Animal* & enemy, sf::Time dt, double const& delay, int const& strength)
{
    if((_timer_fight <= sf::seconds(delay)) and (enemy!=nullptr)) {
        enemy->setLifePoints(enemy->getLifePoints() - strength) ;
        _timer_fight += dt ;
    }

    if((_timer_fight >= sf::seconds(delay)) or (isDead() or (enemy->isDead()))) {
        _timer_fight = sf::Time::Zero ;
        _timer_peace = sf::Time::Zero ;
    }
}
