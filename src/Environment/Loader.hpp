/*
 * POOSV 2020-21
 * @author: Clemence Kiehl & Charlotte Daumal (groupe 31)
 */

#ifndef LOADER_HPP
#define LOADER_HPP
#pragma once
#include <string>


/*!
 *@brief read data in a file to use a specific configuration of the environment
 *
 *@param filepath file to read
 */
void loadMap(std::string const& filepath) ;


/*!
 *@brief save the current map in a file named "map_saved"
 *
 *@param filepath file where we want to store the current map
 */
void saveMap(std::string const& filepath) ;


#endif // LOADER_HPP
