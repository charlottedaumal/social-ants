/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#pragma once
#include<Environment/ToricPosition.hpp>


/*!
 * @brief Manage a position in a toric world
 */


class Positionable
{

public:

    /*!
     *@brief Default constructor which initializes position to (0.0,0.0)
     */
    Positionable() ;


    /*!
     *@brief Constructor which initializes position with one ToricPosition
     *
     *@param other ToricPosition which is used to initialize the position
     */
    Positionable(ToricPosition const& other) ;


    /*!
     *@brief getter for the position
     *
     *@return position of the current instance
     */
    ToricPosition getPosition() const ;


    /*!
     *@brief setter for the position
     *
     *@param position will be the new position of the current instance
     */
    void setPosition(const ToricPosition& position) ;


    /*!
     *@brief display same info as operator<<
     *
     *@param out display stream
     *
     *@return stream modified by the display
     */
    std::ostream& display(std::ostream& out) const ;

private:

    ToricPosition _position ;

} ;


/*!
 *@brief display operator
 *
 *@param out display stream
 *@param position Positionable to display
 *
 *@return stream modified by the display
 */
std::ostream& operator<<(std::ostream& out, Positionable const& position) ;
