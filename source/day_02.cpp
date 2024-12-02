//\==============================================================================
// Advent of code 2024 Day 2
// Question: https://adventofcode.com/2024/day/2
// Gist:  Red-Nosed Reports - Sample values must be in order (ascending or decending) with minimal variance
// Input data: calibration values mixed with letters
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
namespace day_02
{

	/**
	* For part 1 we need to read in data as two vectors
	*/
	struct Report
	{
		std::vector<int64_t> values;
	};
	/**
	/* @brief a function to read input from file
	*/
	std::vector<Report> read_input_from_file(const std::string& input_file)
	{
		std::vector<Report> reports = {};
		//open the input file for reading
		std::ifstream file_input;
		file_input.open(input_file);
		if (file_input.is_open())
		{
			for (std::string line; std::getline(file_input, line); )
			{
				if (line.length() > 0)
				{
					Report current_report{};
					uint64_t value;
					std::stringstream input_line(line);
					while (input_line >> value)
					{
						current_report.values.push_back(value);
					}
					reports.push_back(current_report);
				}

			}
			file_input.close();
		}
		return reports;
	}

	bool test_values_ascending(std::vector<int64_t> report)
	{
		for (auto i = 0; i < report.size() - 1; ++i)
		{
			int64_t diff = report[i + 1] - report[i];
			if (diff < 1 || diff > 3)
			{
				return false;
			}
		}
		return true;
	}

	bool test_values_decending(std::vector<int64_t>& report)
	{
		for (auto i = 0; i < report.size() - 1; ++i)
		{
			int64_t diff = report[i] - report[i+1];
			if (diff < 1 || diff > 3)
			{
				return false;
			}
		}
		return true;
	}
	/**
	 * @brief function to solve part 1 of the problem for day 1.
	 *
	 */
	uint64_t part_1(std::vector<Report>& input)
	{
		//iterate over each report and ensure that all values are ascending or descending
		uint64_t count{};
		for (auto& report : input)
		{
			if (test_values_ascending(report.values)) { ++count; continue; }
			if (test_values_decending(report.values)) { ++count; continue; }
		}
		return count;
	}

	/**
	 * @brief Function to solve part 2 of the question
	 *
	 */
	uint64_t part_2(std::vector<Report>& input)
	{
		//iterate over each report and ensure that all values are ascending or descending
		uint64_t count{};
		for (auto& report : input)
		{
			if (test_values_ascending(report.values)) { ++count; continue; }
			if (test_values_decending(report.values)) { ++count; continue; }
			//we can test again by removing one value from the vector and seeing if that allows a pass
			//This is a bit brute force but it works!
			//A neater solution would be to modify the test for ascending and descending to ignore one failed value
			for (int i = 0; i < report.values.size(); ++i)
			{
				std::vector<int64_t> copy = report.values;
				copy.erase(copy.begin() + i);
				if (test_values_ascending(copy)) { ++count; break; }
				if (test_values_decending(copy)) { ++count; break; }
			}

		}
		return count;
	}
}

Result aoc::day_02()
{
	timer::start();
	//vector to store the total quantity of calories that an elf is carrying
	std::vector<day_02::Report> input = day_02::read_input_from_file("./input/day_02.txt");

	const uint64_t part_1 = day_02::part_1(input);
	const uint64_t part_2 = day_02::part_2(input);
	timer::stop();

	return { std::string(" 2: Red-Nosed Reports"), part_1, part_2, timer::get_elapsed_seconds() };
}
