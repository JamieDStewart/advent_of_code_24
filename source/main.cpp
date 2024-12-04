

#include <iostream>
#include <sstream>
#include <vector>

#include "days.h"
#include "result.h"
#include "util.h"


std::vector< Result( * )() > questions = { aoc::day_01, aoc::day_02, aoc::day_03, aoc::day_04 };

std::string get_output_header_string()
{
	const std::string AoC = "Advent of Code 2024";
	const std::string Day = " Day";
	const std::string Part1 = " Part 1";
	const std::string Part2 = " Part 2";
	const std::string Time = " Time";

	std::stringstream ss;
	ss << util::full_separator << util::end_line;
	ss << util::vertical_separator << util::pad_left( util::pad( AoC, 43 ), 68 ) << util::vertical_separator << util::end_line;
	ss << util::full_separator << util::end_line;
	ss << util::vertical_separator << util::pad( Day, 23 );
	ss << util::vertical_separator << util::pad( Part1, 12 );
	ss << util::vertical_separator << util::pad( Part2, 15 );
	ss << util::vertical_separator << util::pad( Time, 12 ) << util::vertical_separator << util::end_line;
	ss << util::full_separator << util::end_line;
	return ss.str();
}

int main( int argc, char* argv[] )
{
	//Create a vector to store the results for each day's solutions
	std::vector<Result> results = {};

	for( const auto& question : questions )
	{
		results.push_back( question() );
	}

	//display results to console
	//print headings
	std::cout << get_output_header_string();
	for( const auto& result : results )
	{
		std::cout << result.to_string();
	}
	std::cout << util::full_separator << util::end_line;
	
	return 0;
}
