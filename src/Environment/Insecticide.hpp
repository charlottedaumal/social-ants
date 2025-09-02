/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef INSECTICIDE_HPP
#define INSECTICIDE_HPP
#pragma once
#include <Utility/Types.hpp>
#include <Environment/Positionable.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


/*!
 *@brief Represents an insecticide in the environment
 */


class Insecticide : public Positionable, public Drawable, public Updatable
{

public:

    /*!
     *@brief Constructor with two parameters for the position and the quantity of the new Insecticide
     *
     *@param position_toric position of the new Insecticide
     *@param quantity quantity of the new Insecticide
     */
    Insecticide(Vec2d const& position_toric, Quantity const& quantity) ;


    /*!
     *@brief virtual destructor for the current Insecticide
     */
    virtual ~Insecticide() {}


    /*!
     *@brief getter for the quantity of the current Insecticide
     *
     *@return quantity of the current Insecticide
     */
    Quantity getQuantity() const ;


    /*!
     *@brief setter for the quantity of the curreng Insecticide
     *
     *@param new_quantity new value for the quantity of the current Insecticide
     */
    void setQuantity(Quantity const& new_quantity) ;


    /*!
     *@brief draws the current Insecticide
     *
     *@param target window where to draw the current Insecticide
     */
    void drawOn(sf::RenderTarget& target) const override ;


    /*!
     *@brief manages the evolution of the current insecticide in the environment
     *
     *@param dt time elapsed
     */
    void update(sf:: Time dt) override ;

private:

    Quantity _quantity ;

} ;


#endif // INSECTICIDE_HPP
