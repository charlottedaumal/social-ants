#include "Environment.hpp"
#include "Application.hpp"


Environment::Environment()
    :_animals(), _food(), _foodgenerator(), _insecticide_generator(), _anthills(), _pheromones(), _insecticides(), _is_drawable_with_pheromones(true), _temperature(20), _daycycle(Day), _timer(sf::Time::Zero)
{}


void Environment::addAnimal(Animal* const& animal)
{
    if (animal != nullptr) {
        _animals.push_back(animal) ;
    }
}


void Environment::addFood(Food* const& food)
{
    if(food != nullptr) {
        _food.push_back(food) ;
    }
}


void Environment::addAnthill(Anthill* const& anthill)
{
    if(anthill != nullptr) {
        _anthills.push_back(anthill) ;
    }
}


void Environment::addPheromone(Pheromone* const& pheromone)
{
    if(pheromone != nullptr) {
        _pheromones.push_back(pheromone) ;
    }
}


void Environment::addInsecticide(Insecticide* const& insecticide)
{
    if(insecticide != nullptr) {
        _insecticides.push_back(insecticide) ;
    }
}


bool Environment::getIsDrawableWithPheromones() const
{
    return _is_drawable_with_pheromones ;
}


void Environment::setIsDrawableWithPheromones (bool const& value)
{
    _is_drawable_with_pheromones = value ;
}


double Environment::getTemperature() const
{
    return _temperature ;
}


void Environment::setTemperature(double const& temperature)
{
    _temperature = temperature ;

    //Attempt of extension with the temperature which didn't succeed
    /*do {
        std::cout << "Enter a temperature for the simulation : " << std::flush ;
        std::cin >> std::ws ;
        std::cin >> _temperature ;
    }while((_temperature < -20) or (_temperature > 45)) ;*/
}


DayCycle Environment::getDayCycle() const
{
    return _daycycle ;
}


void Environment::changeDayCyle()
{
    if(_daycycle == Day) {
        _daycycle = Night ;
        setTemperature(0) ;
    } else {
        _daycycle = Day ;
        setTemperature(getAppConfig().simulation_usual_temperature) ;
    }
}


void Environment::update(sf::Time dt)
{
    _timer += dt ;
    if(_timer > sf::seconds(getAppConfig().simulation_day_cycle_delay)) {
        _timer = sf::Time::Zero ;
        changeDayCyle() ;
    }

    _foodgenerator.update(dt) ;
    _insecticide_generator.update(dt) ;

    for(auto& animal:_animals) {
        if(!animal->isDead()) {
            animal->update(dt) ;
        } else {
            delete animal ;
            animal = nullptr ;
        }
    }
    _animals.erase(std::remove(_animals.begin(), _animals.end(), nullptr), _animals.end());

    for(auto& anthill:_anthills) {
        anthill->update(dt) ;

        if(anthill->getSize() <= 0.0) {
            delete anthill ;
            anthill = nullptr ;
        }
    }
    _anthills.erase(std::remove(_anthills.begin(), _anthills.end(), nullptr), _anthills.end());

    for(auto& pheromone:_pheromones) {
        pheromone->update(dt) ;

        if(pheromone->isNegligible()) {
            delete pheromone ;
            pheromone = nullptr ;
        }
    }
    _pheromones.erase(std::remove(_pheromones.begin(), _pheromones.end(), nullptr), _pheromones.end());

    for(auto& food:_food) {
        food->update(dt) ;

        if(food->getQuantity() <= 0.0) {
            delete food ;
            food = nullptr ;
        }
    }
    _food.erase(std::remove(_food.begin(), _food.end(), nullptr), _food.end()) ;

    for(auto& insecticide:_insecticides) {
        insecticide->update(dt) ;

        if(insecticide->getQuantity() <= 0.0) {
            delete insecticide ;
            insecticide = nullptr ;
        }
    }
    _insecticides.erase(std::remove(_insecticides.begin(), _insecticides.end(), nullptr), _insecticides.end()) ;
}


void Environment::drawOn(sf::RenderTarget& targetWindow) const
{
    for (auto& food: _food) {
        food->drawOn(targetWindow) ;
    }

    for(auto& animal: _animals) {
        animal->drawOn(targetWindow) ;
    }

    for(auto& anthill: _anthills) {
        anthill->drawOn(targetWindow) ;
    }

    for(auto& insecticide: _insecticides) {
        insecticide->drawOn(targetWindow) ;
    }

    if(getIsDrawableWithPheromones() == true) {
        for(auto& pheromone: _pheromones) {
            pheromone->drawOn(targetWindow) ;
        }
    }
}


void Environment::reset()
{
    for (auto& animal: _animals) {
        delete animal ;
        animal = nullptr ;
    }
    _animals.clear() ;

    for(auto& food: _food) {
        delete food ;
        food = nullptr ;
    }
    _food.clear() ;

    for(auto& anthill: _anthills) {
        delete anthill ;
        anthill = nullptr ;
    }
    _anthills.clear() ;

    for(auto& pheromone: _pheromones) {
        delete pheromone ;
        pheromone = nullptr ;
    }
    _pheromones.clear() ;

    for(auto& insecticide: _insecticides) {
        delete insecticide ;
        insecticide = nullptr ;
    }
    _insecticides.clear() ;
}


Food* Environment::getClosestFoodForAnt(ToricPosition const& position) const
{
    double dist_final(getAppConfig().ant_max_perception_distance) ;
    Food* closest_food (nullptr) ;

    for(auto& food: _food) {
        ToricPosition food_position (food->getPosition()) ;
        double dist(toricDistance(food_position, position)) ;
        if (dist <= dist_final) {
            dist_final = dist ;
            closest_food = food ;
        }
    }
    return closest_food ;
}


Anthill* Environment::getAnthillForAnt(ToricPosition const& position, Uid anthill_Id) const
{
    Anthill* anthill_for_ant (nullptr) ;

    for(auto& anthill: _anthills) {
        ToricPosition anthill_position (anthill->getPosition()) ;
        if((anthill->getId() == anthill_Id) and (toricDistance(anthill_position, position) <= getAppConfig().ant_max_perception_distance)) {
            anthill_for_ant = anthill ;
        }
    }
    return anthill_for_ant ;
}


bool Environment::togglePheromoneDisplay()
{
    if (getIsDrawableWithPheromones()) {
        setIsDrawableWithPheromones(false) ;
    } else {
        setIsDrawableWithPheromones(true) ;
    }
    return getIsDrawableWithPheromones() ;
}


double normalize(double& angle)
{
    while (angle < 0) {
        angle += 360 ;
    }

    while(angle >= 360) {
        angle -= 360 ;
    }
    return angle ;
}


Quantities Environment::getPheromoneQuantitiesPerIntervalForAnt(ToricPosition const& position, Angle direction_rad, Intervals const& angles)
{
    Quantities Q(angles.size(), 0.0) ;

    for(auto const& pheromone: _pheromones) {

        ToricPosition pheromone_position(pheromone->getPosition()) ;
        if (toricDistance(pheromone_position, position) <= getAppConfig().ant_smell_max_distance) {

            // computation of beta
            ToricPosition v(position.toricVector(pheromone_position)) ;
            double beta(((v.toVec2d()).angle()-direction_rad)/DEG_TO_RAD) ;
            normalize(beta) ;

            // comparison of beta with all the angles in the set in parameters
            Angle alpha (angles[0]) ;
            normalize(alpha) ;
            size_t j(0) ;

            for(size_t i(1) ; i < angles.size() ; ++i) {
                Angle angle(angles[i]) ;
                normalize(angle) ;
                if (abs(beta - angle) < abs(beta - alpha)) {
                    alpha = angle ;
                    j = i ;
                }
            }

            Q[j] = pheromone->getQuantity() ;
        }
    }

    return Q ;
}


Animal* Environment::getClosestEnemy(Animal* const& animal_searching) const
{
    double dist_final(getAppConfig().animal_sight_distance) ;
    Animal* closest_enemy (nullptr) ;

    for (auto& animal: _animals) {
        if(animal != nullptr) {
            ToricPosition animal_position(animal->getPosition()) ;
            double dist(toricDistance(animal_position, animal_searching->getPosition())) ;
            if ((dist <= dist_final) and (animal_searching->isEnemy(animal))) {
                dist_final = dist ;
                closest_enemy = animal ;
            }
        }
    }
    return closest_enemy ;
}


void Environment::countEntities(double& workers_count, double& soldiers_count, double& termites_count, double& food_count) const
{
    for(auto& animal : _animals) {
        if(animal->getIdType() == 1) {
            workers_count += 1 ;
        }

        if(animal->getIdType() == 2) {
            soldiers_count += 1 ;
        }

        if(animal->getIdType() == 3) {
            termites_count += 1 ;
        }
    }

    food_count = _food.size() - 1 ;
}


std::unordered_map<std::string, double> Environment::fetchData(std::string const& title)
{
    std::unordered_map<std::string, double> new_data ;
    std::vector<std::string> anthills_id (getAppEnv().getAnthillsIds()) ;
    std::vector<double> anthills_foodstock ;

    for(auto& anthill : _anthills) {
        anthills_foodstock.push_back(anthill->getFoodStock()) ;
    }

    double workers_count(0.0) ;
    double soldiers_count(0.0) ;
    double termites_count(0.0) ;
    double food_count(0.0) ;
    getAppEnv().countEntities(workers_count, soldiers_count, termites_count, food_count) ;

    if(title == s::GENERAL) {
        new_data = { {"worker ants", workers_count}, {"soldier ants", soldiers_count},
            {"termites", termites_count}, {"temperature", _temperature}
        } ;
    }

    if(title == s::FOOD) {
        new_data = {{"food", food_count}} ;
    }

    if(title == s::ANTHILLS) {
        for(unsigned int i(0) ; i < anthills_id.size() ; ++i) {
            new_data.insert({{anthills_id[i], anthills_foodstock[i]}}) ;
        }
    }

    return new_data ;
}


std::vector<std::string> Environment::getAnthillsIds() const
{
    std::vector<std::string> anthills_id ;
    for(auto& anthill : _anthills) {
        std::string id(std::to_string(anthill->getId())) ;
        std::string chain ("anthill #" + id ) ;
        anthills_id.push_back(chain) ;
    }
    return anthills_id ;
}


Insecticide* Environment::getClosestInsecticideForEntity(Positionable* const& entity) const
{
    double dist_final(getAppConfig().insecticide_entity_distance_perception) ;
    Insecticide* closest_insecticide (nullptr) ;

    for (auto& insecticide: _insecticides) {

        if(insecticide != nullptr) {
            ToricPosition insecticide_position(insecticide->getPosition()) ;
            double dist(toricDistance(insecticide_position, entity->getPosition())) ;

            if (dist <= dist_final) {
                closest_insecticide = insecticide ;
                dist_final = dist ;
            }
        }
    }
    return closest_insecticide ;
}


Insecticide* Environment:: getClosestInsecticideForAnimal(Animal* const& animal) const
{
    double dist_final(getAppConfig().ant_max_perception_distance) ;
    Insecticide* closest_insecticide (nullptr) ;

    for (auto& insecticide: _insecticides) {

        if(insecticide != nullptr) {
            ToricPosition insecticide_position(insecticide->getPosition()) ;
            double dist(toricDistance(insecticide_position, animal->getPosition())) ;

            if (dist <= dist_final) {
                closest_insecticide = insecticide ;
                dist_final = dist ;
            }
        }
    }
    return closest_insecticide ;
}


std::vector<ToricPosition> Environment::getAnthillsPositions() const
{
    std::vector<ToricPosition> positions ;
    for(auto anthill : _anthills) {
        positions.push_back(anthill->getPosition()) ;
    }
    return positions ;
}


std::vector<ToricPosition> Environment::getFoodPositions() const
{
    std::vector<ToricPosition> positions ;
    for(auto food : _food) {
        positions.push_back(food->getPosition()) ;
    }
    return positions ;
}


Quantities Environment::getFoodQuantities() const
{
    Quantities quantities ;
    for(auto food : _food) {
        quantities.push_back(food->getQuantity()) ;
    }
    return quantities ;
}


std::vector<ToricPosition> Environment::getTermitesPositions() const
{
    std::vector<Animal*> termites ;
    for(auto animal : _animals) {
        if(animal->getIdType() == 3) {
            termites.push_back(animal) ;
        }
    }

    std::vector<ToricPosition> positions ;
    for(auto termite : termites) {
        positions.push_back(termite->getPosition()) ;
    }
    return positions ;
}


