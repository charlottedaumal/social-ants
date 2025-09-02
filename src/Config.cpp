#include "Config.hpp"
#include <JSON/JSONSerialiser.hpp>
// window
Config::Config(std::string path) : mConfig(j::readFromFile(path))
    , simulation_debug(mConfig["debug"].toBool())
    , display_probs(mConfig["display probabilities"].toBool())
    , window_simulation_width(mConfig["window"]["simulation"]["width"].toDouble())
    , window_simulation_height(mConfig["window"]["simulation"]["height"].toDouble())
    , window_stats_width(mConfig["window"]["stats"]["width"].toDouble())
    , window_title(mConfig["window"]["title"].toString())
    , window_antialiasing_level(mConfig["window"]["antialiasing level"].toInt())

// stats
    , stats_refresh_rate(mConfig["stats"]["refresh rate"].toDouble())

// simulation
    , simulation_time_factor(mConfig["simulation"]["time"]["factor"].toDouble())
    , simulation_fixed_step(mConfig["simulation"]["time"]["fixed step"].toDouble())
    , simulation_time_max_dt(sf::seconds(mConfig["simulation"]["time"]["max dt"].toDouble()))
    , simulation_day_background(mConfig["simulation"]["day background"].toString())
    , simulation_debug_background(mConfig["simulation"]["debug background"].toString())
    , simulation_night_background(mConfig["simulation"]["night background"].toString())
    , simulation_snow_background(mConfig["simulation"]["snow background"].toString())
    , simulation_fire_background(mConfig["simulation"]["fire background"].toString())
    , simulation_day_cycle_delay(mConfig["simulation"]["day cycle delay"].toDouble())
    , simulation_high_temperature(mConfig["simulation"]["high temperature"].toDouble())
    , simulation_low_temperature(mConfig["simulation"]["low temperature"].toDouble())
    , simulation_usual_temperature(mConfig["simulation"]["usual temperature"].toDouble())
    , simulation_size(mConfig["simulation"]["size"].toInt())
    , world_size(mConfig["world"]["size"].toInt())
    , map_name(mConfig["world"]["map name"].toString())
    , map_saved_name(mConfig["world"]["map saved name"].toString())
    , text_size(mConfig["simulation"]["text size"].toDouble())

//simulation (ants)
    , beta_d(mConfig["environment"]["beta_d"].toDouble())
    , q_zero(mConfig["environment"]["q_zero"].toDouble())
    , alpha(mConfig["environment"]["alpha"].toInt())
    , temperature_initial(mConfig["environment"]["temperature initial"].toDouble())	, temperature_delta(mConfig["environment"]["temperature delta"].toDouble())
    , temperature_min(mConfig["environment"]["temperature min"].toDouble())
    , temperature_max(mConfig["environment"]["temperature max"].toDouble())

//food generator
    ,food_generator_delta(mConfig["food"]["generator"]["delta"].toDouble())

//food
    ,food_min_qty(mConfig["food"]["min qty"].toDouble())
    ,food_max_qty(mConfig["food"]["max qty"].toDouble())
    ,food_texture(mConfig["food"]["texture"].toString())
    ,food_deshydrated_texture(mConfig["food"]["deshydrated texture"].toString())
    ,food_evaporation_rate(mConfig["food"]["evaporation rate"].toDouble())

//insecticide
    ,insecticide_min_qty(mConfig["insecticide"]["min qty"].toDouble())
    ,insecticide_max_qty(mConfig["insecticide"]["max qty"].toDouble())
    ,insecticide_evaporation_rate(mConfig["insecticide"]["evaporation rate"].toDouble())
    ,insecticide_entity_distance_perception(mConfig["insecticide"]["entity distance perception"].toDouble())
    ,insecticide_evaporation_rate_high_temperature(mConfig["insecticide"]["evaporation rate high temperature"].toDouble())

//insecticide generator
    ,insecticide_generator_delta(mConfig["insecticide"]["generator"]["delta"].toDouble())

//pheromone
    ,pheromone_threshold(mConfig["pheromone"]["treshold"].toDouble())
    ,pheromone_evaporation_rate(mConfig["pheromone"]["evaporation rate"].toDouble())
    ,pheromone_test_density(mConfig["pheromone"]["test density"].toDouble())
    ,pheromone_temperature_threshold(mConfig["pheromone"]["temperature threshold"].toDouble())
    ,pheromone_evaporation_rate_high_temperature(mConfig["pheromone"]["evaporation rate high temperature"].toDouble())

// anthill
    ,anthill_spawn_delay(mConfig["anthill"]["spawn delay"].toDouble())
    ,anthill_worker_prob_default(mConfig["anthill"]["default worker prob"].toDouble())
    ,anthill_texture(mConfig["anthill"]["texture"].toString())
    ,anthill_size(mConfig["anthill"]["size"].toDouble())

//animal
    ,animal_next_rotation_delay(mConfig["animal"]["next rotation delay"].toDouble())
    ,animal_sight_distance(mConfig["animal"]["sight distance"].toDouble())
    ,animal_default_speed(mConfig["animal"]["default speed"].toDouble())
    ,animal_default_lifespan(mConfig["animal"]["default lifespan"].toDouble())
    ,animal_default_texture(mConfig["animal"]["default texture"].toString())
    ,animal_size(mConfig["animal"]["size"].toDouble())

// ants
    ,ant_speed(mConfig["ant"]["speed"].toDouble())
    ,ant_speed_high_temperature(mConfig["ant"]["speed high temperature"].toDouble())
    ,ant_attack_delay(mConfig["ant"]["attack"] ["delay"].toDouble())
    ,ant_smell_max_distance(mConfig["ant"]["smell"]["distance"].toDouble())
    ,ant_pheromone_density(mConfig["ant"]["pheromone"]["density"].toDouble())
    ,ant_pheromone_energy(mConfig["ant"]["pheromone"]["energy"].toDouble())
    ,ant_max_food(mConfig["ant"]["max food"].toDouble())
    ,ant_max_perception_distance(mConfig["ant"]["max perception distance"].toDouble())
    ,ant_radius(mConfig["ant"]["radius"].toDouble())

// worker ants
    , ant_worker_hp(mConfig["ant"]["worker"]["hp"].toInt())
    , ant_worker_lifespan(mConfig["ant"]["worker"]["lifespan"].toInt())
    , ant_worker_strength(mConfig["ant"]["worker"]["strength"].toInt())
    , ant_worker_strength_high_temperature(mConfig["ant"]["worker"]["strength high temperature"].toInt())
    , ant_worker_texture(mConfig["ant"]["worker"]["texture"].toString())

//soldier  ants
    , ant_soldier_hp(mConfig["ant"]["soldier"]["hp"].toInt())
    , ant_soldier_lifespan(mConfig["ant"]["soldier"]["lifespan"].toInt())
    , ant_soldier_strength(mConfig["ant"]["soldier"]["strength"].toInt())
    , ant_soldier_strength_high_temperature(mConfig["ant"]["soldier"]["strength high temperature"].toInt())
    , ant_soldier_texture(mConfig["ant"]["soldier"]["texture"].toString())

//termites
    , termite_hp(mConfig["termite"]["hp"].toInt())
    , termite_lifespan(mConfig["termite"]["lifespan"].toInt())
    , termite_strength(mConfig["termite"]["strength"].toInt())
    , termite_strength_high_temperature(mConfig["termite"]["strength high temperature"].toInt())
    , termite_speed(mConfig["termite"]["speed"].toDouble())
    , termite_speed_high_temperature(mConfig["termite"]["speed high temperature"].toDouble())
    , termite_attack_delay(mConfig["termite"]["attack delay"].toDouble())
    , termite_texture(mConfig["termite"]["texture"].toString())
{ }



// for debugging purposes
void Config::switchDebug()
{
    mConfig["debug"] = j::boolean(!mConfig["debug"].toBool());
    simulation_debug = mConfig["debug"].toBool();
}

bool Config::getDebug()
{
    return simulation_debug;
}

bool Config::getProbaDebug()
{
    return display_probs;
}

void Config::switchProbaDebug()
{
    mConfig["display probabilities"] = j::boolean(!mConfig["display probabilities"].toBool());
    display_probs = mConfig["display probabilities"].toBool();
}
