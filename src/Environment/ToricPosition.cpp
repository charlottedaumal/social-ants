#include "ToricPosition.hpp"
#include <Application.hpp>
#include <Utility/Utility.hpp>
#include <cmath>


void ToricPosition::clamp()
{
    double x_projected(_coordinates.x()) ;
    double y_projected(_coordinates.y()) ;

    if((_dimensions.x() != 0.0) and (_dimensions.y() != 0.0)) {

        double rest_width(fmod(_coordinates.x(), _dimensions.x())) ;
        double rest_height(fmod(_coordinates.y(), _dimensions.y())) ;

        if(rest_width < 0.0) {
            x_projected += rest_width ;
        } else {
            x_projected = rest_width ;
        }

        if (rest_height < 0.0) {
            y_projected += rest_height ;
        } else {
            y_projected = rest_height ;
        }

    } else {
        // exception thrown -> division by 0.0
        throw std::domain_error("ERROR : At least one of the two dimensions of the toric world is zero.") ;
    }

    _coordinates = Vec2d(x_projected, y_projected) ;
}


ToricPosition::ToricPosition(Vec2d const& coordinates, Vec2d const& dimensions)
    : _coordinates(coordinates), _dimensions(dimensions)
{
    clamp() ;
}


ToricPosition::ToricPosition(double const& x, double const& y)
    :_coordinates(x,y),_dimensions(getAppConfig().simulation_size, getAppConfig().simulation_size)
{
    clamp() ;
}


ToricPosition::ToricPosition(Vec2d const& coordinates)
    : ToricPosition(coordinates.x(), coordinates.y())
{}


ToricPosition::ToricPosition()
    : ToricPosition(0.0,0.0)
{}


Vec2d const& ToricPosition::toVec2d() const
{
    return _coordinates ;
}


double ToricPosition::x() const
{
    return _coordinates.x() ;
}


double ToricPosition::y() const
{
    return _coordinates.y() ;
}


bool ToricPosition::operator==(ToricPosition const& other) const
{
    return ((isEqual(_coordinates.x(), other._coordinates.x())) and (isEqual(_coordinates.y(), other._coordinates.y()))) ;
}


ToricPosition& ToricPosition::operator+=(ToricPosition const& other)
{
    _coordinates = Vec2d (x() + other._coordinates.x(), y() + other._coordinates.y()) ;
    clamp() ;
    return *this ;
}


const ToricPosition operator+(ToricPosition toricposition1, ToricPosition const& toricposition2)
{
    ToricPosition tp = ToricPosition (toricposition1 += toricposition2) ;
    return tp ;
}


std::ostream&  operator<<(std::ostream& out, ToricPosition const& tp)
{
    out << "[" << tp.x() << ", " << tp.y() << "]" ;
    return out ;
}


double ToricPosition::operator[](int index) const
{
    if (index == 0) {
        return(_coordinates.x()) ;
    } else {
        if(index == 1) {
            return(_coordinates.y()) ;
        } else {
            //exception thrown -> index out of bounds
            throw std::domain_error("ERROR: index out of bounds.") ;
            return 0.0 ;
        }
    }
}


Vec2d ToricPosition::toricVector(ToricPosition const& that) const
{
    double w(_dimensions.x()) ;
    double h(_dimensions.y()) ;
    Vec2d candidate(that.toVec2d()) ;
    double min_dist(distance(candidate, toVec2d())) ;

    for ( int i(0) ; i<=1 ; ++i) { //loop which controls the power of 0

        for(int j(0) ; j<=1 ; ++j) { //loop which controls the power of w or h

            Vec2d candidate1(that.toVec2d() + Vec2d (pow(0,i) * pow(-1,j) * w, pow(-1, j+1) * h)) ;
            Vec2d candidate2(that.toVec2d() + Vec2d (pow(-1,j) * w, pow(0,i) * pow(-1,j) * h)) ;

            double dist1(distance(candidate1, toVec2d())) ;
            double dist2(distance(candidate2, toVec2d())) ;

            if (dist2 < dist1) {
                dist1 = dist2 ;
                candidate1 = candidate2 ;
            }

            if(dist1 < min_dist) {
                min_dist = dist1 ;
                candidate = candidate1 ;
            }
        }
    }

    return (candidate - toVec2d()) ;
}


double toricDistance(ToricPosition& from, ToricPosition const& to)
{
    Vec2d v(from.toricVector(to)) ;
    return v.length() ;
}
