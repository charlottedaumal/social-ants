/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef PHEROMONE_HPP
#define PHEROMONE_HPP
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Environment/Positionable.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>


/*!
 *@brief Represents a pheromone in the environment
 */


class Pheromone : public Positionable, public Drawable, public Updatable
{

public:

    /*!
     *@brief Constructor which initializes the position and the quantity of the new pheromone with
     *       two parameters
     *
     *@param position position of the new pheromone
     *@param quantity quantity of the new pheromone
     */
    Pheromone(Vec2d const& position, double const& quantity) ;


    /*!
     *@brief virtual destructor for the current Pheromone
     */
    virtual ~Pheromone() {}


    /*!
     *@brief getter for the quantity
     *
     *@return quantity of the current pheromone
     */
    double getQuantity() const ;


    /*!
     *@brief setter for the quantity
     *
     *@param quantity new value for the quantity of the current pheromone
     */
    void setQuantity(double const& quantity) ;


    /*!
     *@brief draws the current pheromone
     *
     *@param target window where to draw the current pheromone
     */
    void drawOn(sf::RenderTarget& target) const override ;


    /*!
     *@brief manages the evolution of the pheromones in the environment
     *
     *@param dt time elapsed
     */
    void update(sf::Time dt) override ;


    /*!
     *@brief shows if the quantity of the current pheromone is considered as negligible
     *
     *@return true if the quantity of the current pheromone is considered as negligible
     */
    bool isNegligible() const ;

private:

    double _quantity ;

} ;

#endif // PHEROMONE_HPP

