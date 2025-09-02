/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef FOOD_HPP
#define FOOD_HPP
#pragma once
#include <Utility/Types.hpp>
#include <Environment/Positionable.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>


/*!
 *@brief Represents a source of food in the environment
 */


class Food : public Positionable, public Drawable, public Updatable
{

public :

    /*!
     *@brief Constructor which initializes the position and the quantity with two parameters
     *
     *@param position_toric position of the new Food
     *@param quantity quantity of the new Food
     */
    Food(Vec2d const& position_toric, Quantity const& quantity) ;


    /*!
     *@brief virtual destructor for the current Food
     */
    virtual ~Food() {}


    /*!
     *@brief getter for the quantity
     *
     *@return quantity of the current instance
     */
    Quantity getQuantity() const ;


    /*!
     *@brief setter for the quantity
     *
     *@param new_quantity new value for the quantity of the current instance
     */
    void setQuantity(Quantity const& new_quantity) ;


    /*!
     *@brief Collect quantity of food from the source
     *
     *@param quantity_to_collect quantity of food to collect from the source
     *
     *@return quantity of food collected
     */
    Quantity takeQuantity(Quantity const& quantity_to_collect) ;


    /*!
     *@brief draws the food
     *
     *@param target window where to draw the current instance
     */
    void drawOn(sf::RenderTarget& target) const override ;


    /*!
     *@brief manages the evolution of a source of food in the environment
     *
     *@param dt time elapsed
     */
    void update(sf::Time dt) override ;


    /*!
     *@brief tells if the current Food is contaminated
     *
     *@return true if the current Food is contaminated
     */
    bool isContaminated() const ;

private:

    Quantity _quantity ;

} ;

#endif // FOOD_HPP
