/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#pragma once
#include <Utility/Types.hpp>
#include <Environment/Positionable.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>


class Ant ;
class Termite ;


enum Status {

    Attack, Idle, Escaping

} ;


/*!
 *@brief Represents an animal in the environment
 */


class Animal : public Positionable, public Drawable, public Updatable
{

public:

    /*!
     *@brief Constructor which initializes the position, the life points and the life expectancy
     *       with two parameters
     *
     *@param position position of the new Animal
     *@param life_points life points of the new Animal
     *@param life_expectancy life expectancy of the new Animal
     */
    Animal(ToricPosition const& position, int const& life_points, int const& life_expectancy, unsigned int id_type = 0) ;


    /*!
     *@brief Constructor which initializes the position with a parameter
     *
     *@param position position of the new Animal
     */
    Animal(ToricPosition const& position) ;


    /*!
     *@brief virtual destructor for the current Animal
     */
    virtual ~Animal() {}


    /*!
     *@brief getter for the speed of the current animal
     *
     *@return speed of the current Animal
     */
    virtual double getSpeed() const = 0 ;


    /*!
     *@brief getter for the direction
     *
     *@return direction of the current Animal
     */
    Angle getDirection() const ;


    /*!
     *@brief getter for the life expectancy
     *
     *@return life expectancy of the current Animal
     */
    int getLifeExpectancy() const ;


    /*!
     *@brief getter for the life points
     *
     *@return life points of the current Animal
     */
    int getLifePoints() const ;


    /*!
     *@brief getter for the timer
     *
     *@return timer of the current Animal
     */
    sf::Time getTimer() const ;


    /*!
     *@brief getter for the status
     *
     *@return status of the current Animal
     */
    Status getStatus() const ;


    /*!
     *@brief getter for the timer which measures the time that must be spent after the end of a fight to begin a new one
     *
     *@return value of _timer_peace of the current Animal
     */
    sf::Time getTimerPeace() const ;


    /*!
     *@brief getter for the type id of the current Animal
     *
     *@return type id of the current Animal
     */
    unsigned int getIdType() const ;


    /*!
     *@brief tells if the animal is dead or alive
     *
     *@return true if the animal is dead
     */
    bool isDead() const ;


    /*!
     *@brief update the position and the speed of the current Animal after an elapsed time
     *
     *@param dt time elapsed
     */
    void move(sf::Time dt) ;


    /*!
     *@brief attempt of the current Animal to turn
     */
    virtual void turn() ;


    /*!
     *@brief manages the evolution of Animal's instances in the environment
     *
     *@param dt time elapsed
     */
    virtual void update(sf::Time dt) override ;


    /*!
     *@brief manages the evolution of the status, the search for a enemy and a potential fight for the predators
     *
     *@param dt time elapsed
     *@param delay attack delay which measures the duration of a fight for the current Animal
     *@param strength strength of the current Animal
     */
    void update(sf::Time dt, double const& delay, int const& strength) ;


    /*!
     *@brief getter for a set of angles and probabilities
     *
     *@return set of angles each one associated to a probability
     */
    virtual const RotationProbs computeRotationProbs() const ;


    /*!
     *@brief tells if an animal encountered is an enemy or not
     *
     *@param entity animal encountered
     *
     *@return true if the current Animal is an enemy of the animal encountered and if both animals are alive
     */
    virtual bool isEnemy(Animal const* entity) const = 0 ;


    /*!
     *@brief tells if a termite is an enemy of the current Animal
     *
     *@param other a termite
     *
     *@return true if a termite is an enemy of the current Animal
     */
    virtual bool isEnemyDispatch(Termite const* other) const = 0 ;


    /*!
     *@brief tells if an ant is an enemy of the current Animal
     *
     *@param other an ant
     *
     *@return true if an ant is an enemy of the current Animal
     */
    virtual bool isEnemyDispatch(Ant const* other) const = 0 ;


    /*!
     *@brief manages the attack of the current Animal towards its enemy
     *
     *@param enemy enemy to attack
     *@param dt time elapsed
     *@param delay duration of the fight for the current Animal
     *@param strength strength of the current Animal
     */
    virtual void fight(Animal* & enemy, sf::Time dt, double const& delay, int const& strength) ;


    /*!
     *@brief manages the attack the current Animals towards its enemy with two parameters
     *
     *@param enemy enemy to attack
     *@param dt time elapsed
     */
    virtual void fight(Animal* & enemy, sf::Time dt) = 0 ;


protected:

    /*!
     *@brief setter for the direction
     *
     *@param angle new angle for the direction of the current Animal
     */
    void setDirection(Angle const& angle) ;


    /*!
     *@brief setter for the life expectancy
     *
     *@param life_expectancy new value for the life expectancy of the current Animal
     */
    void setLifeExpectancy(int const& life_expectancy) ;


    /*!
     *@brief setter for the timer
     *
     *@param new_timer new value for the timer of the current Animal
     */
    void setTimer(sf::Time const& new_timer) ;


    /*!
     *@brief setter for the life points
     *
     *@param life_points new value for the life points of the current Animal
     */
    void setLifePoints(int const& life_points) ;


    /*!
     *@brief setter for the status
     *
     *@param status new value for the status of the current Animal
     */
    void setStatus(Status const& status) ;


    /*!
     *@brief setter for the _timer_peace
     *
     *@param timer_peace new value for _timer_peace of the current Animal
     */
    void setTimerPeace(sf::Time const& timer_peace) ;

private:

    Angle _direction ;
    int _life_points ;
    int _life_expectancy ;
    sf::Time _timer ;
    //status of the Animal which can be either Attack or Idle
    Status _status ;
    // time during which the animal is allowed to fight
    sf::Time _timer_fight ;
    // time during which the animal has to rest after a fight
    sf::Time _timer_peace ;
    //id which allows us to distinguish the different types of animals for the graph (termites, soldiers, workers)
    unsigned int _id_type ;

} ;

#endif // ANIMAL_HPP
