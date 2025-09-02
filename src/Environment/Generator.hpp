/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#pragma once
#include <Environment/Generator.hpp>
#include <Utility/Types.hpp>
#include <Utility/Vec2d.hpp>


/*!
 *@brief Represents the random generator for entities in the environment
 */


class Generator
{

public:

    /*!
     *@brief By default constructor
     */
    Generator() ;


    /*!
     *@brief virtual destructor for the current Generator
     */
    virtual ~Generator() {}


    /*!
     *@brief generates randomly some instances of entities in the environment when a delay has passed
     *
     *@param dt time elapsed
     *@param delta delay to pass to between two generations
     *@param min_qty minimum quantity of the entity to generate
     *@param max_qty maximul quantity of the entity to generate
     *@param new_coordinates coordinates of the new entity generated in the environment
     *@param new_quantity quantity of the new entity generated in the environment
     */
    virtual void update_entity(sf::Time dt,  double const& delta, double const& min_qty, double const& max_qty, Vec2d& new_coordinates, Quantity& new_quantity) ;

private:

    // time spent between each generation
    sf::Time _timer ;

} ;


#endif // GENERATOR_HPP
