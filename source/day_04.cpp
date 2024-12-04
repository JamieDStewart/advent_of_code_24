//\==============================================================================
// Advent of code 2024 Day 4
// Question: https://adventofcode.com/2024/day/4
// Gist:  Ceres Search - A wordsearch problem. Find XMAS in the wordsearch.
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
namespace day_04
{

	struct Wordsearch
	{
		std::vector<std::string> rows;
	};
	/**
	  @brief a function to read input from file
	*/
	Wordsearch read_input_from_file( const std::string& input_file )
	{
		Wordsearch ws = {};

		if ( std::ifstream file_input( input_file ); file_input.is_open() )
		{
			for ( std::string line{}; std::getline( file_input, line ); )
			{
				if ( !line.empty() )
				{
					ws.rows.push_back( line );
				}
			}
		}
		return ws;
	}


	struct Direction
	{
		int x{};
		int y{};
	};

	std::vector<Direction> dirs{ {0, -1}, {1,-1}, {1,0}, {1,1},
								 {0, 1}, {-1,1}, {-1,0}, {-1,-1} };

	uint64_t part_1( const Wordsearch& ws )
	{
		//Look through the wordsearch and find all occurrences of XMAS
		uint64_t count{};
		const std::string xmas = "XMAS";

		const auto row_len = ws.rows[0].length();
		const auto row_count = ws.rows.size();

		for( auto r = 0; r < row_count; ++r )
		{
			for( auto c = 0; c < row_len; ++c )
			{
				if( auto p = 0; ws.rows[r][c] == xmas[p] )
				{					 
					//Get neighbouring indexes and find remaining 'MAS'
					for( auto [x,y] : dirs)
					{
						p = 1;
						auto nc{ 0 }; auto nr{ 0 };
						for ( nc = c + x, nr = r + y; nc >= 0 && nc < row_len && nr >= 0 && nr < row_count; nc += x, nr += y )
						{
							if( ws.rows[nr][nc] == xmas[p] )
							{
								++p;
								if( p == xmas.length() )
								{
									++count;
									break;
								}
								continue;
							}
							break;							
						}
					}
				}
			}			
		}	
		return count;
	}

	std::vector<Direction> dir_pair{ {1, -1}, {1,1} };

	uint64_t part_2( const Wordsearch& ws )
	{
		//Look through the wordsearch and find all occurrences of Overlapped MAS x MAS in the shape of an X
		uint64_t count{};

		const auto row_len = ws.rows[0].length();
		const auto row_count = ws.rows.size();

		for ( auto r = 0; r < row_count; ++r )
		{
			for ( auto c = 0; c < row_len; ++c )
			{
				auto p = 0;
				if ( ws.rows[r][c] == 'A' )
				{
					auto found_mas_count = 0;
					//Get neighbouring indexes and find remaining 'MAS'
					for ( auto [x, y] : dir_pair )
					{
						p = 1;
						const auto mc = c - x; const auto mr = r - y; //1 grid location forward
						const auto sc = c + x; const auto sr = r + y; //1 grid location backward
						if( mc >= 0 && mc < row_len && mr >= 0 && mr < row_count &&
							sc >= 0 && sc < row_len && sr >= 0 && sr < row_count )
						{
							if( ws.rows[mr][mc] == 'M' && ws.rows[sr][sc] == 'S' || 
								ws.rows[mr][mc] == 'S' && ws.rows[sr][sc] == 'M' )
							{
								++found_mas_count;
							}
						}
					}
					if( found_mas_count == 2 )
					{
						++count;
					}
				}
			}
		}

		return count;
	}
}

Result aoc::day_04()
{
	timer::start();

	const day_04::Wordsearch input = day_04::read_input_from_file( "./input/day_04.txt" );

	const uint64_t part_1 = day_04::part_1( input );
	const uint64_t part_2 = day_04::part_2( input );

	timer::stop();

	return { std::string( " 4.Ceres Search" ), part_1, part_2, timer::get_elapsed_seconds() };
}
