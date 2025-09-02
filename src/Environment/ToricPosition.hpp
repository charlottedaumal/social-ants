/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#pragma once
#include <Utility/Vec2d.hpp>


/*!
 * @brief Handle toric coordinate, distance and other
 * basic math operation in a toric world
 *
 * @note Gets the dimensions of the world from getAppConfig()
 */


class ToricPosition
{

public:

    /*!
     *@brief Constructor which initializes coordinates and dimensions with two Vec2d
     *
     *@param coordinates coordinates of ToricPosition
     *@param dimensions dimensions of the toric world
     */
    ToricPosition(Vec2d const& coordinates, Vec2d const& dimensions) ;


    /*!
     *@brief Constructor which initializes coordinates with two doubles
     *       dimensions of the toric world are determined by default
     *
     *@param x coordinate x of ToricPosition
     *@param y coordinate y of ToricPosition
     */
    ToricPosition(double const& x, double const& y) ;


    /*!
     *@brief Constructor which initializes coordinates with one Vect2d
     *       dimensions of the toric world are determined by default
     *
     *@param coordinates coordinates of Toric Position
     */
    ToricPosition(Vec2d const& coordinates) ;


    /*!
     *@brief By default constructor which initializes the coordinates to (0.0,0.0)
     *       dimensions of the toric world are determined by default
     */
    ToricPosition() ;


    /*!
     *@brief By default copy constructor
     *
     *@param other Toricposition to copy
     */
    ToricPosition(ToricPosition const& other) = default ;


    /*!
     *@brief By default operator=
     *
     *@param other Toricposition for the equality
     *
     *@return ToricPosition which has the same coordinates and dimensions of other
     */
    ToricPosition& operator=(ToricPosition const& other) = default ;


    /*!
     *@brief getter for the coordinates
     *
     *@return Coordinates of the current ToricPosition
     */
    Vec2d const& toVec2d() const ;


    /*!
     *@brief getter for coordinate x
     *
     *@return coordinate x of the current ToricPosition
     */
    double x() const ;


    /*!
     *@brief getter for coordinate y
     *
     *@return coordinate y of the current ToricPosition
     */
    double y() const ;


    /*!
     *@brief returns true if the two objects have approximately the same coordinates
     *
     *@param other ToricPosition to which this is compared
     *
     *@return true if other is equal to the current ToricPosition
     */
    bool operator==(ToricPosition const& other) const ;


    /*!
     *@brief add other's position to this' position
     *
     *@param other ToricPosition which coordinates will be added to the ones of the current ToricPosition
     *
     *@return current ToricPosition with its new coordinates
     */
    ToricPosition& operator+=(ToricPosition const& other) ;


    /*!
     *@brief indexation operator
     *
     *@param index index
     *
     *@return coordinate[index] of the current ToricPosition
     */
    double operator[](int index) const ;


    /*!
     *@brief calculates the shorter vector between the current instance (this) and that
     *
     *@param that ToricPosition
     *
     *@return shorter vector between this and that (Vec2d)
     */
    Vec2d toricVector(ToricPosition const& that) const ;

private :

    Vec2d _coordinates ;
    Vec2d _dimensions ;


    /*!
     *@brief projects the coordinates in the toric world
     */
    void clamp() ;

} ;


/*!
 *@brief addition of two ToricPosition
 *
 *@param toricposition1 ToricPosition to add to toricposition2
 *@param toricposition2 ToricPosition to add to toricposition1
 *
 *@return addition of toricposition1 and toricposition2
 */
const ToricPosition operator+(ToricPosition toricposition1, ToricPosition const& toricposition2) ;


/*!
 *@brief display operator
 *
 *@param out stream where we display
 *@param tp ToricPosition to display (just its coordinates)
 *
 *@return stream modified by the display
 */
std::ostream& operator<<(std::ostream& out, ToricPosition const& tp) ;


/*!
 *@brief Calculates the shorter distance between from and to
 *
 *@param from first ToricPosition
 *@param to second ToricPosition
 *
 *@return distance between from and to
 */
double toricDistance(ToricPosition& from, ToricPosition const& to) ;
