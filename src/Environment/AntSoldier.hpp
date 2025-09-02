/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef ANTSOLDIER_HPP
#define ANTSOLDIER_HPP
#pragma once
#include <Environment/Ant.hpp>
#include <Environment/ToricPosition.hpp>


/*!
 *@brief Represents a soldier ant in the environment
 */


class AntSoldier : public Ant
{

public:

    /*!
     *@brief Constructor which initializes the position, the life points and the life expectancy
     *       of the new AntSoldier with three parameters
     *
     *@param position position of the new AntSoldier
     *@param id_anthill id of the anthill to which the AntSoldier belongs
     */
    AntSoldier(ToricPosition const& position, Uid const& id_anthill) ;


    /*!
     *@brief virtual destructor for the current AntSoldier
     */
    virtual ~AntSoldier() {}


    /*!
     *@brief draws the current AntSoldier
     *
     *@param target window where to draw the current AntSoldier
     */
    void drawOn(sf::RenderTarget& target) const override ;


    /*!
     *@brief manages the evolution of the current AntSoldier in the environment
     *
     *@param dt time elapsed
     */
    void update(sf::Time dt) override;


    /*!
     *@brief manages the attack of the current AntSoldier towards its enemy
     *
     *@param enemy enemy encountered
     *@param dt time elapsed
     */
    void fight(Animal* & enemy, sf::Time dt) override ;

} ;

#endif // ANTSOLDIER_HPP
