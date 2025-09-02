/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef TERMITE_HPP
#define TERMITE_HPP
#pragma once
#include <Environment/Ant.hpp>


/*!
 *@brief Represents a termite in the environment
 */


class Termite : public Animal
{

public:

    /*!
     *@brief Constructor which initializes the position of the termite with a ToricPosition
     *
     *@param position position of the new termite
     */
    Termite(ToricPosition const& position) ;


    /*!
     *@brief virtual destructor for the current termite
     */
    virtual ~Termite() {}


    /*!
     *@brief getter for the speed of the current Termite
     *
     *@return speed of the current Termite
     */
    double getSpeed() const override ;


    /*!
     *@brief draws the current Termite
     *
     *@param target window where to draw the current Termite
     */
    void drawOn(sf::RenderTarget& target) const override ;


    /*!
     *@brief manages the evolution of the current Termite in the environment
     *
     *@param dt time elapsed
     */
    void update(sf::Time dt) override ;


    /*!
     *@brief tells if an animal encountered is an enemy or not
     *
     *@param animal animal encountered
     *
     *@return true if the current Termite is an enemy of the animal encountered and if both animals are alive
     */
    bool isEnemy(Animal const* animal) const override ;


    /*!
     *@brief tells if a termite is an enemy of the current Ant
     *
     *@param other a termite
     *
     *@return always false
     */
    bool isEnemyDispatch(Termite const* other) const override ;


    /*!
     *@brief tells if an ant is an enemy of the current Termite
     *
     *@param other an ant
     *
     *@return always true
     */
    bool isEnemyDispatch(Ant const* other) const override ;


    /*!
     *@brief manages the attack of the current Termite towards its enemy
     *
     *@param enemy enemy encountered
     *@param dt time elapsed
     */
    void fight(Animal* & enemy, sf::Time dt) override ;

private:

    double _attack_delay ;

} ;

#endif // TERMITE_HPP
