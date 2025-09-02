#include "Positionable.hpp"


Positionable::Positionable()
    : _position()
{}


Positionable::Positionable(ToricPosition const& other)
    : _position(other)
{}


ToricPosition Positionable::getPosition() const
{
    return _position ;
}


void Positionable::setPosition(const ToricPosition& position)
{
    _position = position ;
}


std::ostream& operator<<(std::ostream& out, Positionable const& position)
{
    return position.display(out) ;
}


std::ostream& Positionable::display(std::ostream& out) const
{
    return out << getPosition() ;
}
