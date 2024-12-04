//\==============================================================================
// Advent of code 2024 Day 3
// Question: https://adventofcode.com/2024/day/3
// Gist:  Mull It Over - use a regex to solve some corrupted input data
//\==============================================================================


#include "days.h"
#include "timer.h"
#include "result.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

/*
 * Creating a namespace in this file to add in any functions used in solving the problem
 * I tend to use a mixture of C/C++ styling when solving Advent of code problems as it's
 * easy for me to work this way and keep each problem in a separate file without worrying
 * about any function name clashes between days.
 */
namespace day_03
{

	struct Input
	{
		std::vector<std::string> instructions;
	};
	/**
	  @brief a function to read input from file
	*/
	Input read_input_from_file( const std::string& input_file )
	{
		Input input = {};

		if ( std::ifstream file_input( input_file); file_input.is_open() )
		{
			for ( std::string line; std::getline( file_input, line ); )
			{
				if ( !line.empty() )
				{
					input.instructions.push_back( line );
				}
			}
		}
		return input;
	}

	
	/**
	 * @brief function to solve part 1 of the problem for day 1.
	 *
	 */
	uint64_t part_1( Input& input )
	{
		//iterate over each report and ensure that all values are ascending or descending
		uint64_t count{};
		std::regex regex( R"(mul\(([0-9]{1,3}),([0-9]{1,3})\))" );

		const auto matches_end = std::sregex_iterator();

		for ( auto& instruction : input.instructions )
		{
			for ( auto iter = std::sregex_iterator( instruction.begin(), instruction.end(), regex ); iter != matches_end; ++iter )
			{
				const std::smatch& match = *iter;

				const uint64_t x = std::stoull( match[1] );
				const uint64_t y = std::stoull( match[2] );
				count += x * y;
			}
			
		}
		return count;
	}

	/**
	 * @brief Function to solve part 2 of the question
	 *
	 */
	uint64_t part_2( Input& input )
	{
		uint64_t count{};
		std::regex regex( R"(mul\(([0-9]{1,3}),([0-9]{1,3})\)|do\(\)|don't\(\))" );
		constexpr size_t do_length = 4;
		constexpr  size_t dont_length = 7;

		const auto matches_end = std::sregex_iterator();

		bool skip = false;
		for ( auto& instruction : input.instructions )
		{
			for ( auto iter = std::sregex_iterator( instruction.begin(), instruction.end(), regex ); iter != matches_end; ++iter )
			{
				const std::smatch& match = *iter;
				if ( match.length() == do_length ) { skip = false; continue; }
				if ( match.length() == dont_length ) { skip = true; continue; }
				if ( skip ) { continue; }

				const uint64_t x = std::stoull( match[1] );
				const uint64_t y = std::stoull( match[2] );
				count += x * y;
			}

		}
		return count;
	}
}

Result aoc::day_03()
{
	timer::start();

	day_03::Input input = day_03::read_input_from_file( "./input/day_03.txt" );

	const uint64_t part_1 = day_03::part_1( input );
	const uint64_t part_2 = day_03::part_2( input );
	timer::stop();

	return { std::string( " 3.Mull It Over" ), part_1, part_2, timer::get_elapsed_seconds() };
}
