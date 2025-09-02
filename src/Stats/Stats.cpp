#include "Stats.hpp"
#include <Application.hpp>


Stats::Stats()
    : _graphs(), _labels(), _active_id(0), _timer(sf::Time::Zero), _delta(sf::Time::Zero)
{}


void Stats::setActive(int const& id)
{
    _active_id = id ;
}


std::string Stats::getCurrentTitle() const
{
    return _labels.at(_active_id) ;
}


void Stats::next()
{
    if(_active_id == _graphs.size() - 1) {
        _active_id = 0 ;
    } else {
        _active_id += 1 ;
    }
}


void Stats::previous()
{
    if(_active_id == 0) {
        _active_id = _graphs.size() - 1 ;
    } else {
        _active_id -= 1 ;
    }
}


void Stats::reset()
{
    for(unsigned int i(0) ; i < _graphs.size() ; ++i) {
        _graphs[i].reset() ;
    }
    _active_id = 0 ;
}


void Stats::addGraph(int id, std::string const& title, std::vector<std::string> const& series, double min, double max, Vec2d const& size)
{
    _graphs[id].reset(new Graph(series, size, min, max)) ;
    _labels[id] = title ;
    _active_id = id ;
}


void Stats::drawOn(sf::RenderTarget& target) const
{
    if(_active_id >= 0) {
        _graphs.at(_active_id)->drawOn(target) ;
    }
}


void Stats::update(sf::Time dt)
{
    _timer += dt ;
    _delta += dt ;
    if(_delta > sf::seconds(getValueConfig()["stats"]["refresh rate"].toDouble())) {
        _delta = sf::Time::Zero ;
        std::unordered_map<std::string, double> new_data (getAppEnv().fetchData(getCurrentTitle())) ;
        _graphs.at(_active_id)->updateData(_timer, new_data) ;
    }
}


