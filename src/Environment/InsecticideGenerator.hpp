/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef INSECTICIDEGENERATOR_HPP
#define INSECTICIDEGENERATOR_HPP
#pragma once
#include <Interface/Updatable.hpp>
#include <Environment/Generator.hpp>


/*!
 *@brief generates automatically the insecticide in the environment
 */


class InsecticideGenerator : public Generator, public Updatable
{

public :

    /*!
     *@brief By default constructor
     */
    InsecticideGenerator() ;


    /*!
     *@brief virtual destructor for the current InsecticideGenerator
     */
    virtual ~InsecticideGenerator() {}


    /*!
     *@brief generates randomly some instances of insecticide in the environment when a delay has passed
     *
     *@param dt time elapsed
     */
    void update(sf::Time dt) override ;

} ;


#endif // INSECTICIDEGENERATOR_HPP
