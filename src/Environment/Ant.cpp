#include "Ant.hpp"
#include <Application.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <cmath>


Ant::Ant(ToricPosition const& position, Uid const& id_anthill, int const& life_points, int const& life_expectancy, unsigned int id_type)
    : Animal(position, life_points, life_expectancy,id_type), _id_anthill(id_anthill), _p0(position), _attack_delay(getAppConfig().ant_attack_delay)
{}


Ant::Ant(ToricPosition const& position, Uid const& id_anthill)
    : Animal(position), _id_anthill(id_anthill)
{}


Uid Ant::getIdAnthill() const
{
    return _id_anthill ;
}


ToricPosition Ant::getP0() const
{
    return _p0 ;
}


double Ant::getAttackDelay() const
{
    return _attack_delay ;
}


void Ant::setP0(ToricPosition const& p0)
{
    _p0 = p0 ;
}


double Ant::getSpeed() const
{
    if(getAppEnv().getTemperature() == getAppConfig().simulation_usual_temperature) {
        return getAppConfig().ant_speed ;
    } else {
        return getAppConfig().ant_speed_high_temperature ;
    }
}

void Ant::update(sf::Time dt)
{
    Animal:: update(dt) ;
    spreadPheromones() ;
}


void Ant::drawOn(sf::RenderTarget& target, std::string const& texture) const
{
    auto const antSprite = buildSprite((getPosition()).toVec2d(), getAppConfig().animal_size, getAppTexture(texture), getDirection() / DEG_TO_RAD) ;
    target.draw(antSprite) ;

    if (isDebugOn()) {
        auto const text = buildText(to_nice_string(getLifePoints()), (getPosition()).toVec2d() + Vec2d(0,30), getAppFont(), getAppConfig().text_size, sf::Color::Black, getDirection() / DEG_TO_RAD) ;
        target.draw(text) ;
        sf::VertexArray ligne(sf::PrimitiveType::Lines, 2) ;
        ligne[0] = { getPosition().toVec2d(), sf::Color::Black } ;
        ligne[1] = { getPosition().toVec2d() + 100 * Vec2d::fromAngle(getDirection()), sf::Color::Blue } ;
        target.draw(ligne) ;
        auto const ring = buildAnnulus(getPosition().toVec2d(), getAppConfig().ant_smell_max_distance, sf::Color::Blue, 5.0) ;
        target.draw(ring) ;

        if (getAppConfig().getProbaDebug() == true) {
            display(target) ;
        }
    }
}


void Ant::drawOn(sf::RenderTarget& target) const
{
    drawOn(target, getAppConfig().animal_default_texture) ;
}


void Ant::spreadPheromones()
{
    ToricPosition p0(getP0()) ;
    double dist_between_positions(toricDistance(p0, getPosition())) ;
    int nb_pheromones(dist_between_positions * getAppConfig().ant_pheromone_density) ;
    double dist(dist_between_positions / nb_pheromones) ;
    double world_width (getAppConfig().simulation_size) ;
    double world_height (getAppConfig().simulation_size) ;

    if((getPosition().x() != p0.x() + world_width) or (getPosition().x() != p0.x() - world_width) or (getPosition().y() != p0.y() + world_height) or (getPosition().y() != p0.y() - world_height)) {
        for(int i(1) ; i <= nb_pheromones ; ++i) {
            getAppEnv().addPheromone(new Pheromone(p0.toVec2d() + i/dist*(p0.toricVector(getPosition())), getAppConfig().ant_pheromone_energy)) ;
            setP0(getPosition()) ;
        }
    } else {
        setP0(getPosition()) ;
    }
}


void Ant::display (sf::RenderTarget& target) const
{
    auto const intervalProbs = computeRotationProbs() ;
    for (std::size_t i = 0; i < intervalProbs.first.size(); ++i) {
        auto const msg = std::to_string(intervalProbs.second[i]).substr(2, 4) ;
        auto const angle = intervalProbs.first[i] ;
        auto const local = Vec2d::fromAngle(getDirection() + angle * DEG_TO_RAD) * 250 ;
        auto const text = buildText(msg, getPosition().toVec2d() + local, getAppFont(), 15, sf::Color::Black) ;
        target.draw(text) ;
    }

    auto const quantities = getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(getPosition(), getDirection(), computeRotationProbs().first) ;
    for (std::size_t i = 0; i < quantities.size(); ++i) {
        auto const msg = std::to_string(quantities[i]).substr(0, 4) ;
        auto const angle = computeRotationProbs().first[i] ;
        auto const local = Vec2d::fromAngle(getDirection() + angle * DEG_TO_RAD) * 200 ;
        auto const text = buildText(msg, getPosition().toVec2d() + local, getAppFont(), getAppConfig().text_size, sf::Color::Red) ;
        target.draw(text) ;
    }
}


void Ant::turn()
{
    Animal::turn() ;

    RotationProbs data(computeRotationProbs()) ;
    Probs no_perception(data.second.size(), 0.0) ;

    //follows the pheromones
    if((getTimer() >= sf::seconds(getAppConfig().animal_next_rotation_delay)) and (data.second != no_perception)) {
        double q(data.second[0]) ;
        double j(0) ;
        for(size_t i(1) ; i < data.second.size() ; ++i) {
            if(q < data.second[i]) {
                q = data.second[i] ;
                j = i ;
            }
        }

        double gamma(normalize(data.first[j]) * DEG_TO_RAD) ;
        setDirection(getDirection() + gamma) ;
        setTimer(sf::Time::Zero) ;
    }
}


void Ant::computation_phi_probas (Probs const& begin_probas, Probs& phi_probas, Intervals const& I) const
{
    double sum(0.0) ;
    Quantities Q(getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(getPosition(), getDirection(), I)) ;

    for(size_t i(0) ; i<begin_probas.size() ; ++i) {
        phi_probas[i] = 1 / (1 + exp((-getAppConfig().beta_d) * (Q[i] - getAppConfig().q_zero))) ;
        sum += phi_probas[i] ;
    }

    if(sum != 0.0) {
        for(auto& element : phi_probas) {
            element /= sum ;
        }
    }
}



const RotationProbs Ant::computeRotationProbs() const
{
    Probs begin_probabilities = { 0.0000, 0.0000, 0.0005, 0.0010, 0.0050, 0.9870, 0.0050, 0.0010, 0.0005, 0.0000, 0.0000 } ;
    Intervals I = {   -180,   -100,    -55,    -25,    -10,      0,     10,     25,     55,    100,    180 } ;
    Probs phi_probabilities (begin_probabilities.size(), 0.0) ;

    computation_phi_probas(begin_probabilities, phi_probabilities, I) ;

    Probs probas_product(begin_probabilities.size(), 0.0) ;
    double z_alpha(0.0) ;
    for(size_t i(0) ; i < begin_probabilities.size() ; ++i) {
        probas_product[i] = begin_probabilities[i] * pow(phi_probabilities[i], getAppConfig().alpha) ;
        z_alpha += probas_product[i] ;
    }

    Probs final_probas(begin_probabilities.size(), 0.0) ;
    if(z_alpha != 0.0) {
        for(size_t i(0) ; i < begin_probabilities.size() ; ++i) {
            final_probas[i] = (1/z_alpha) * probas_product[i] ;
        }
    }

    return RotationProbs(I, final_probas) ;
}


bool Ant::isEnemy(Animal const* animal) const
{
    return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this) ;
}


bool Ant::isEnemyDispatch(Termite const* other) const
{
    return true ;
}


bool Ant::isEnemyDispatch(Ant const* other) const
{
    return (other->getIdAnthill() != _id_anthill) ;
}
