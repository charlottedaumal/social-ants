/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef ANTHILL_HPP
#define ANTHILL_HPP
#pragma once
#include <Utility/Types.hpp>
#include <Environment/Positionable.hpp>
#include <Interface/Updatable.hpp>
#include <Interface/Drawable.hpp>


/*!
 *@brief Represents an anthill in the environment
 */


class Anthill : public Positionable, public Drawable, public Updatable
{

public:

    /*!
     *@brief Constructor which initializes the toric position of the anthill with one parameter
     *
     *@param position_toric toric position of the new anthill
     */
    Anthill(ToricPosition const&  position_toric) ;


    /*!
     *@brief virtual destructor for the current Anthill
     */
    virtual ~Anthill() {}


    /*!
     *@brief getter for the food stock
     *
     *@return food stock of the current anthill
     */
    Quantity getFoodStock() const ;


    /*!
     *@brief setter for the foodstock
     *
     *@param food_stock new food stock of the anthill
     */
    void setFoodStock(Quantity const& food_stock) ;


    /*!
     *@brief getter for the name
     *
     *@return name of the current anthill
     */
    Uid getId() const ;


    /*!
     *@brief getter for the timer
     *
     *@return value of the timer
     */
    sf::Time getTimer() const ;


    /*!
     *@brief setter for the timer
     *
     *@param new_timer new value for the timer of the anthill
     */
    void setTimer(sf::Time const&  new_timer) ;


    /*!
     *@brief getter for the probability that a worker has to appear in its anthill
     *
     *@return the probability that a worker has to appear in its anthill
     */
    double getProbaWorker() const ;


    /*!
     *@brief getter for the size of the current Anthill
     *
     *@return the size of the current Anthill
     */
    double getSize() const ;


    /*!
     *@brief draws the current anthill
     *
     *@param target window where to draw the current ant
     */
    void drawOn(sf::RenderTarget& target) const override ;


    /*!
     *@brief manages the evolution of the current Anthill in the environment
     *
     *@param dt time elapsed
     */
    void update(sf::Time dt) override ;


    /*!
     *@brief tells if the current Anthill is contaminated
     *
     *@return true if the current Anthill is contaminated
     */
    bool isContaminated() const ;

private:

    Quantity _food_stock ;
    Uid _id ;
    sf::Time _timer ;
    double _size ;

} ;

#endif // ANTHILL_HPP   */
