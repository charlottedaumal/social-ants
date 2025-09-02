/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef ANTWORKER_HPP
#define ANTWORKER_HPP
#pragma once
#include <Environment/Ant.hpp>
#include <Utility/Types.hpp>


/*!
 *@brief Represents a worker ant in the environment
 */


class AntWorker : public Ant
{

public:

    /*!
     *@brief Constructor which initializes the position, the life points and the life expectancy of the new
     *       worker with three parameters
     *
     *@param position position of the new worker
     *@param id_anthill id of the anthill to which the new worker belongs
     */
    AntWorker(ToricPosition const& position, Uid const& id_anthill) ;


    /*!
     *@brief virtual destructor for the current AntWorker
     */
    virtual ~AntWorker() {}


    /*!
     *@brief getter for the food collected
     *
     *@return food collected by the worker
     */
    Quantity getFoodCollected() const ;


    /*!
     *@brief setter for the food collected by the current AntWorker
     *
     *@param food_collected new value for the food collected by the current AntWorker
     */
    void setFoodCollected(Quantity const& food_collected) ;


    /*!
     *@brief draws the current AntWorker
     *
     *@param target window where to draw the current AntWorker
     */
    void drawOn(sf::RenderTarget& target) const override ;


    /*!
     *@brief manages the evolution of the current AntWorker in the environment
     *
     *@param dt time elapsed
     */
    void update(sf::Time dt) override ;


    /*!
     *@brief manages the attack of the current AntWorker towards its enemy
     *      (the enemy is not injured in all cases because the AntWorker has no strength)
     *
     *@param enemy enemy encountered
     *@param dt time elapsed
     */
    void fight(Animal* & enemy, sf::Time dt) override ;

private:

    Quantity _food_collected ;

} ;

#endif // ANTWORKER_HPP
