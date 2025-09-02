/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Environment/Animal.hpp>
#include <Environment/Food.hpp>
#include <Environment/FoodGenerator.hpp>
#include <Environment/Anthill.hpp>
#include <Environment/Pheromone.hpp>
#include <Environment/Insecticide.hpp>
#include <Environment/InsecticideGenerator.hpp>


/*!
 *@brief Manage the evolution of animals and food in the environment it modelizes
 */


enum DayCycle {

    Day, Night

} ;


class Environment : public Drawable, public Updatable
{

public:

    /*!
     *@brief By default constructor
     */
    Environment() ;


    /*!
     *@brief Eliminating the copy constructor of the environment
     *
     *@param other Environment to copy
     */
    Environment(Environment const& autre) = delete ;


    /*!
     *@brief add animals to the fauna
     *
     *@param animal animal to add to the environment
     */
    void addAnimal(Animal* const& animal) ;


    /*!
     *@brief add food to the environment
     *
     *@param food food to add to the environment
     */
    void addFood(Food* const& food) ;


    /*!
     *@brief add an anthill to the environment
     *
     *@param anthill anthill to add to the environment
     */
    void addAnthill(Anthill* const& anthill) ;


    /*!
     *@brief add a pheromone to the environment
     *
     *@param pheromone pheromone to add to the environment
     */
    void addPheromone(Pheromone* const& pheromone) ;


    /*!
     *@brief add an insecticide to the environment
     *
     *@param insecticide insecticide to add to the environment
     */
    void addInsecticide(Insecticide* const& insecticide) ;


    /*!
     *@brief getter for the attribute _is_drawable_with_pheromones
     *
     *@return bool value of the attribute _is_drawable_with_pheromones
     */
    bool getIsDrawableWithPheromones() const ;


    /*!
     *@brief setter for the attribute _is_drawable_with_pheromones
     *
     *@param value new bool value for the attribute _is_drawable_with_pheromones
     */
    void setIsDrawableWithPheromones(bool const& value) ;


    /*!
     *@brief getter for the temperature of the environment
     *
     *@return temperature of the environment
     */
    double getTemperature() const ;


    /*!
     *@brief setter for the temperature of the environment
     *
     *@param temperature new temperature of the environment
     */
    void setTemperature(double const& temperature) ;


    /*!
     *@brief getter for the status (day or night) of the environment
     *
     *@return status (day or night) of the environment
     */
    DayCycle getDayCycle() const ;


    /*!
     *@brief switch between day and night when a delay has passed
     */
    void changeDayCyle() ;


    /*!
     *@brief manages the evolution of the animals in the fauna
     *
     *@param dt time elapsed
     */
    void update(sf::Time dt) override ;


    /*!
     *@brief draws the animals and the sources of food in the environment
     *
     *@param targetWindow window where to draw the animals and the sources of food
     */
    void drawOn(sf::RenderTarget& targetWindow) const override ;


    /*!
     *@brief deletes all the food ressources and the animals of the environment
     */
    virtual void reset() ;


    /*!
     *@brief gets the closest food source of one ant
     *
     *@param position position of the ant
     *
     *@return the closest food source of the ant
     */
    Food* getClosestFoodForAnt(ToricPosition const& position) const ;


    /*!
     *@brief gets the closest anthill of a ant and compares if it is the anthill to which the ant belongs
     *
     *@param position position of the ant
     *@param anthillId id of the anthill near the ant
     *
     *@return the anthill if it is the one to which the ant belongs
     */
    Anthill* getAnthillForAnt(ToricPosition const& position, Uid anthill_Id) const ;


    /*!
     *@brief set the value of the attribute _is_drawable_with_pheromones with its opposite value
     *
     *@return opposite value of the attribute _is_drawable_with_pheromones
     */
    bool togglePheromoneDisplay() ;


    /*!
     *@brief calculates pheromone's quantities detected by the ant per interval
     *
     *@param position position of the ant
     *@param angle_rad angle of the direction of the ant
     *@param angles set of angles in degrees
     *
     *@return set of pheromone's quantities detected by the ant per interval
     */
    Quantities getPheromoneQuantitiesPerIntervalForAnt(ToricPosition const& position, Angle direction_rad, Intervals const& angles) ;


    /*!
     *@brief gets the closest enemy of the animal searching
     *
     *@param animal_searching animal searching for its closest enemy
     *
     *@return the closest animal considered as an enemy for the animal put in parameters
     */
    Animal* getClosestEnemy(Animal* const& animal_searching) const ;


    /*!
     *@brief counts the entities currently in the environment
     *
     *@param workers_count counter for workers
     *@param soldiers_count counter for soldiers
     *@param termites_count counter for termites
     *@param food_count counter for food
     */
    void countEntities(double& workers_count, double& soldiers_count, double& termites_count, double& food_count) const ;


    /*!
     *@brief calculates the set of values and ids corresponding to the graph wanted
     *
     *@param title title of the graph
     *
     *@return set of values and ids that corresponds to the graph wanted
     */
    std::unordered_map<std::string, double> fetchData(std::string const& title) ;


    /*!
     *@brief stores in a table all the anthills' ids in the environment
     *
     *@return table containing all the ids of the anthills currently in the environment
     */
    std::vector<std::string> getAnthillsIds() const ;


    /*!
     *@brief gets the closest insecticide of the entity searching
     *
     *@param entity entity searching for the closest insecticide
     *
     *@return closest insecticide of the entity
     */
    Insecticide* getClosestInsecticideForEntity(Positionable* const& entity) const ;


    /*!
     *@brief gets the closest insecticide of the animal searching
     *
     *@param animal animal searching for the closest insecticide
     *
     *@return closest insecticide of the animal
     */
    Insecticide* getClosestInsecticideForAnimal(Animal* const& animal) const ;


    /*!
     *@brief stores in a table all the anthills' positions in the environment
     *
     *@return table containing all the positions of the anthills currently in the environment
     */
    std::vector<ToricPosition> getAnthillsPositions() const ;


    /*!
     *@brief stores in a table all the foods' positions in the environment
     *
     *@return table containing all the positions of the foods currently in the environment
     */
    std::vector<ToricPosition> getFoodPositions() const ;


    /*!
     *@brief stores in a table all the food's quantities in the environment
     *
     *@return table containing all th quantities of the foods in the environment
     */
    Quantities getFoodQuantities() const ;


    /*!
     *@brief stores in a table all the termites' positions in the environment
     *
     *@return table containing all the positions of the termites currently in the environment
     */
    std::vector<ToricPosition> getTermitesPositions() const ;

private:

    std::vector<Animal*> _animals;
    std::vector<Food*> _food;
    FoodGenerator _foodgenerator ;
    InsecticideGenerator _insecticide_generator ;
    std::vector<Anthill*> _anthills ;
    std::vector<Pheromone*> _pheromones ;
    std::vector<Insecticide*> _insecticides ;
    bool _is_drawable_with_pheromones ;
    double _temperature ;
    // represents the days passing by
    DayCycle _daycycle ;
    // timer which counts the time spent in day or in night in the environment
    sf::Time _timer ;

} ;


/*!
 *@brief normalize and angle between 0 and 360
 *
 *@param angle angle to normalize
 *
 *@return the angle normalized between 0 and 360
 */
double normalize(double& angle) ;


#endif // ENVIRONMENT_HPP

