/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef ANT_HPP
#define ANT_HPP
#pragma once
#include <Utility/Types.hpp>
#include <Environment/ToricPosition.hpp>
#include <Environment/Animal.hpp>


/*!
 *@brief Represents an ant in the environment
 */


class Ant : public Animal
{

public:

    /*!
     *@brief Constructor which initializes the position, the id of the anthill, the life points and the life expectancy
     *       with 4 parameters
     *
     *@param position position of the new ant
     *@param id_anthill id of the anthill to which the new ant belongs
     *@param life_points life points of the new ant
     *@param life_expectancy life expectancy of the new ant
     */
    Ant(ToricPosition const& position, Uid const& id_anthill, int const& life_points, int const& life_expectancy, unsigned int id_type = 0) ;


    /*!
     *@brief Constructor which initializes the position and the anthill of the new ant with two parameters
     *
     *@param position position of the new ant
     *@param anthill anthill to which the new ant belongs
     */
    Ant(ToricPosition const& position, Uid const& anthill) ;


    /*!
     *@brief virtual destructor for the current Ant
     */
    virtual ~Ant() {}


    /*!
     *@brief getter for the id of the anthill
     *
     *@return the id of the anthill to which the new Ant belongs
     */
    Uid getIdAnthill() const ;


    /*!
     *@brief getter for p0
     *
     *@return value of p0
     */
    ToricPosition getP0() const ;


    /*!
     *@brief getter for the attack delay
     *
     *@return the attack delay of the current Ant
     */
    double getAttackDelay() const ;


    /*!
     *@brief setter for p0
     *
     *@param new_p0 new value for _p0
     */
    void setP0(ToricPosition const& p0) ;


    /*!
     *@brief getter for the speed of the current Ant
     *
     *@return speed of the current Ant
     */
    double getSpeed() const override ;


    /*!
     *@brief draws the current ant
     *
     *@param target window where to draw the current ant
     *@param texture texture of the drawing of the current ant
     */
    virtual void drawOn(sf::RenderTarget& target, std::string const& texture) const ;


    /*!
     *@brief draws the current ant with just one parameter
     *
     *@param target window where to draw the current ant
     */
    virtual void drawOn(sf::RenderTarget& target) const override ;


    /*!
     *@brief manages the evolution of the ants in the environment
     *
     *@param dt time elapsed
     */
    virtual void update(sf::Time dt) override ;


    /*!
     *@brief drops the pheromones while the current Ant is moving
     */
    void spreadPheromones() ;


    /*!
     *@brief displays all the data linked to the calculation of the rotation probabilities
     *
     *@param target window where to display all the data
     */
    void display(sf::RenderTarget& target) const ;


    /*!
     *@brief computation of the phi probas which is necessary for the sensorial movement
     *
     *@param begin_probas set of the basis probabilities
     *@param phi_probas phi probas to compute
     *@param I set of angles considered
     */
    void computation_phi_probas(Probs const& begin_probas, Probs& phi_probas, Intervals const& I) const ;


    /*!
     *@brief getter for a set of angles and probabilities
     *
     *@return set of angles each one associated to a probability
     */
    const RotationProbs computeRotationProbs() const override ;


    /*!
     *@brief attempt of the current Ant to turn
     */
    virtual void turn() override ;


    /*!
     *@brief tells if an animal encountered is an enemy or not
     *
     *@param animal animal encountered
     *
     *@return true if the current Ant is an enemy of the animal encountered and if both animals are alive
     */
    bool isEnemy(Animal const* animal) const override ;


    /*!
     *@brief tells if a termite is an enemy of the current Ant
     *
     *@param other a termite
     *
     *@return always true
     */
    bool isEnemyDispatch(Termite const* other) const override ;


    /*!
     *@brief tells if an ant is an enemy of the current Ant
     *
     *@param other an ant
     *
     *@return true if the current Ant isn't from the same anthill as the other Ant
     */
    bool isEnemyDispatch(Ant const* other) const override ;

private:

    Uid _id_anthill ;
    // former position of the current Ant
    ToricPosition _p0 ;
    double _attack_delay ;

} ;

#endif // ANT_HPP
