/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef STATS_HPP
#define STATS_HPP
#pragma once
#include <memory>
#include <map>
#include <Interface/Updatable.hpp>
#include <Stats/Graph.hpp>


class Stats : public Drawable, public Updatable
{

public:

    /*!
     *@brief Default constructor
     */
    Stats() ;


    /*!
     *@brief setter for the active id
     *
     *@param id new value for the active id
     */
    void setActive(int const& id) ;


    /*!
     *@brief getter for the active id
     *
     *@return value of the active id
     */
    std::string getCurrentTitle() const ;


    /*!
     *@brief increment the active id modulo the size of _graphs
     */
    void next() ;


    /*!
     *@brief decrement the active id modulo the size of _graphs
     */
    void previous() ;


    /*!
     *@brief reset all the graphs to restart the display (destructor)
     */
    void reset() ;


    /*!
     *@brief adds a new graph to _graphs by replacing one
     *
     *@param id id of the graph to add
     *@param title title of the graph to add
     *@param series set of the curves' titles
     *@param min minimal value above which the curves' points are displayed
     *@param max maximum value below which the curves' points are displayed
     *@param size size of the window where all the displays are done
     */
    void addGraph(int id, std::string const& title, std::vector<std::string> const& series, double min, double max, Vec2d const& size) ;


    /*!
     *@brief draws the statistics
     *
     *@param target window where to draw the current Termite
     */
    void drawOn(sf::RenderTarget& target) const override ;


    /*!
     *@brief manages the evolution of the statistics
     *
     *@param dt time elapsed
     */
    void update(sf::Time dt) override ;

private:

    std::map<int, std::unique_ptr<Graph>> _graphs ;
    std::map<int, std::string> _labels ;
    // id of the graph displayed
    unsigned int _active_id ;
    sf::Time _timer ;
    // delay to refresh the stats
    sf::Time _delta ;

} ;


#endif // STATS_HPP
