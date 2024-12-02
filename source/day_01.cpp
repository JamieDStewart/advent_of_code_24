//\==============================================================================
// Advent of code 2024 Day 1
// Question: https://adventofcode.com/2024/day/1
// Gist:  Historian Hysteria - map column A to column B
//\==============================================================================


#include "days.h"
#include "timer.h"
#include "result.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

/*
 * Creating a namespace in this file to add in any functions used in solving the problem
 * I tend to use a mixture of C/C++ styling when solving Advent of code problems as it's
 * easy for me to work this way and keep each problem in a separate file without worrying
 * about any function name clashes between days.
 */
namespace day_01
{

	/**
	* For part 1 we need to read in data as two vectors
	*/
	struct Input
	{
		std::vector<int64_t> column_1;
		std::vector<int64_t> column_2;

	};
	/**
	/* @brief a function to read input from file 
	*/
	Input read_input_from_file( const std::string& input_file )
	{
		Input input_data = {};
		//open the input file for reading
		std::ifstream file_input;
		file_input.open( input_file );
		if ( file_input.is_open() )
		{
			for ( std::string line; std::getline( file_input, line ); )
			{
				if ( line.length() > 0 )
				{
					uint64_t col1, col2;
					std::stringstream input_line(line);
					input_line >> col1 >> col2;
					input_data.column_1.push_back(col1);
					input_data.column_2.push_back(col2);
				}

			}
			file_input.close();
		}
		return input_data;
	}

	/**
	 * @brief function to solve part 1 of the problem for day 1.
	 *        
	 */
	uint64_t part_1( Input& input )
	{
		//sort the two input columns then calculate the difference between each pair
		std::sort(input.column_1.begin(), input.column_1.end());
		std::sort(input.column_2.begin(), input.column_2.end());

		int64_t total_distance{};
		for (auto i = 0; i < input.column_1.size(); ++i)
		{
			total_distance += abs(input.column_1[i] - input.column_2[i]);
		}
		return total_distance;
	}

	/**
	 * @brief Function to solve part 2 of the question
	 *        
	 */
	uint64_t part_2( Input& input )
	{
		//for part 2 use a map to track frequency of values in second column
		std::map< int64_t, int64_t> value_frequency;
		for (auto val : input.column_2)
		{
			value_frequency[val]++;
		}
		//frequencies calculated now work out similarity score
		int64_t similarity_score{};
		for (auto val : input.column_1)
		{
			similarity_score += val * value_frequency[val];
		}
		return similarity_score;
	}
}

Result aoc::day_01()
{
	timer::start();
	day_01::Input input = day_01::read_input_from_file( "./input/day_01.txt" );

	const uint64_t part_1 = day_01::part_1(input);
	const uint64_t part_2 = day_01::part_2(input);
	timer::stop();

	return { std::string(" 1: Historian Hysteria"), part_1, part_2, timer::get_elapsed_seconds()};
}
