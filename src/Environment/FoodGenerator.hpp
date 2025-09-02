/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP
#pragma once
#include <Interface/Updatable.hpp>
#include <Environment/Generator.hpp>


/*!
 *@brief generates automatically the food in the environment
 */


class FoodGenerator : public Generator, public Updatable
{

public :

    /*!
     *@brief By default constructor
     */
    FoodGenerator() ;


    /*!
     *@brief virtual destructor for the current FoodGenerator
     */
    virtual ~FoodGenerator() {}


    /*!
     *@brief generates randomly some instances of food in the environment when a delay has passed
     *
     *@param dt time elapsed
     */
    void update(sf::Time dt) override ;


} ;


#endif // FOODGENERATOR_HPP
