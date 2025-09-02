/*
 * prjsv 2016-21
 * Marco Antognini & Jamila Sam
 */

#ifndef INFOSV_CONFIG_HPP
#define INFOSV_CONFIG_HPP

#include <string>
#include "JSON/JSON.hpp"
#include <SFML/Graphics.hpp>




class Config
{
private:
    j::Value mConfig;
    bool simulation_debug;
    bool display_probs;

public:
    Config(std::string path);

    // enables / disables debug mode
    void switchDebug();
    void switchProbaDebug();
    bool getDebug();
    bool getProbaDebug();

    // returns read
    j::Value& getJsonRead()
    {
        return mConfig;
    }

    j::Value const& getJsonRead() const
    {
        return mConfig;
    }


    //window
    const double window_simulation_width;
    const double window_simulation_height;
    const double window_stats_width;
    const std::string  window_title;
    const int window_antialiasing_level;


    // stats
    const double stats_refresh_rate;
    const std::string stats_log_folder = "logs/";
    const std::string stats_log_prefix = "log_";
    const std::string stats_log_header = "# Plot with GNUPLOT : gnuplot -e \"plot for [i=1:6] 'log_0.txt' u i w l title columnheader(i)\"";

    // debug
    const sf::Color debug_text_color = sf::Color::White;
    const size_t default_debug_text_size = 20;


    //simulation (general)

    const double  simulation_time_factor;
    const double  simulation_fixed_step;
    const sf::Time  simulation_time_max_dt;
    const std::string simulation_day_background;
    const std::string simulation_debug_background;
    const std::string simulation_night_background;
    const std::string simulation_snow_background;
    const std::string simulation_fire_background;
    const double simulation_day_cycle_delay;
    const double simulation_high_temperature;
    const double simulation_low_temperature;
    const double simulation_usual_temperature;
    const int simulation_size;
    const int world_size;
    const std::string map_name;
    const std::string map_saved_name;
    const double text_size;

    // simulation (ants)
    const double  beta_d;
    const double  q_zero;
    const int     alpha;
    const double temperature_initial;
    const double temperature_delta;
    const double temperature_min;
    const double temperature_max;



    // food generator
    const double food_generator_delta;

    //food
    const double food_min_qty;
    const double food_max_qty;
    const std::string food_texture;
    const std::string food_deshydrated_texture;
    const double food_evaporation_rate;

    //insecticide
    const double insecticide_min_qty;
    const double insecticide_max_qty;
    const double insecticide_evaporation_rate;
    const double insecticide_entity_distance_perception;
    const double insecticide_evaporation_rate_high_temperature;

    //insecticide generator
    const double insecticide_generator_delta;

    //pheromone
    const double pheromone_threshold;
    const double pheromone_evaporation_rate;
    const double pheromone_test_density;
    const double pheromone_temperature_threshold;
    const double pheromone_evaporation_rate_high_temperature;

    // anthills
    const double anthill_spawn_delay;
    const double anthill_worker_prob_default;
    const std::string anthill_texture;
    const double anthill_size;

    // animal
    const double animal_next_rotation_delay;
    const double animal_sight_distance;
    const double animal_default_speed;
    const double animal_default_lifespan;
    const std::string animal_default_texture;
    const double animal_size;

    //ants
    const double ant_speed;
    const double ant_speed_high_temperature;
    const double ant_attack_delay;
    const double ant_smell_max_distance;
    const double ant_pheromone_density;
    const double ant_pheromone_energy;
    const double ant_max_food;
    const double ant_max_perception_distance;
    const double ant_radius;


    //worker ants
    const int ant_worker_hp;
    const int ant_worker_lifespan;
    const int ant_worker_strength;
    const int ant_worker_strength_high_temperature;
    const std::string ant_worker_texture;

    //soldier ants
    const int ant_soldier_hp;
    const int ant_soldier_lifespan;
    const int ant_soldier_strength;
    const int ant_soldier_strength_high_temperature;
    const std::string ant_soldier_texture;

    // termites
    const int termite_hp;
    const int termite_lifespan;
    const int termite_strength;
    const int termite_strength_high_temperature;
    const double termite_speed;
    const double termite_speed_high_temperature;
    const double termite_attack_delay;
    const std::string termite_texture;

};

#endif // INFOSV_CONFIG_HPP

