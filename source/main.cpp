

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"
#include "result.h"
#include "util.h"


std::vector< Result( * )() > questions = { aoc::day_01, aoc::day_02, aoc::day_03, aoc::day_04 };

constexpr int YEAR = 2024;

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

void print_usage()
{
	std::cout <<
		"Advent of Code " << YEAR << "\n"
		"\n"
		"Usage: aoc_2024 [options]\n"
		"\n"
		"  --day N        Run only day N. May be repeated. Default: every day.\n"
		"  --format FMT   'table' (default, human readable) or 'json' (for the test runner).\n"
		"  --list         Print the days this build knows about as JSON, then exit.\n"
		"  --help         Show this message.\n"
		"\n"
		"Puzzle input is read from ./input/day_NN.txt relative to the working\n"
		"directory, so run the binary from a directory holding an 'input' folder.\n"
		"Real puzzle inputs are deliberately not committed; ./sample holds the\n"
		"worked examples from the puzzle text.\n";
}

int main( int argc, char* argv[] )
{
	const int last_day = static_cast<int>( questions.size() );

	std::vector<int> days_to_run;
	bool as_json = false;

	for ( int i = 1; i < argc; ++i )
	{
		const std::string arg = argv[i];
		if ( arg == "--help" || arg == "-h" )
		{
			print_usage();
			return 0;
		}
		if ( arg == "--list" )
		{
			std::cout << "{\"year\":" << YEAR << ",\"days\":[";
			for ( int day = 1; day <= last_day; ++day )
			{
				std::cout << ( day > 1 ? "," : "" ) << day;
			}
			std::cout << "]}" << util::end_line;
			return 0;
		}
		if ( arg == "--format" && i + 1 < argc )
		{
			const std::string format = argv[++i];
			if ( format == "json" ) { as_json = true; }
			else if ( format == "table" ) { as_json = false; }
			else
			{
				std::cerr << "Unknown format '" << format << "', expected 'table' or 'json'." << util::end_line;
				return 2;
			}
			continue;
		}
		if ( arg == "--day" && i + 1 < argc )
		{
			const int day = std::atoi( argv[++i] );
			if ( day < 1 || day > last_day )
			{
				std::cerr << "Day " << day << " is not available in this build (have 1.." << last_day << ")." << util::end_line;
				return 2;
			}
			days_to_run.push_back( day );
			continue;
		}
		std::cerr << "Unrecognised argument '" << arg << "'. Try --help." << util::end_line;
		return 2;
	}

	//\ No explicit selection means run the lot, which keeps the old behaviour.
	if ( days_to_run.empty() )
	{
		for ( int day = 1; day <= last_day; ++day )
		{
			days_to_run.push_back( day );
		}
	}

	if ( as_json )
	{
		//\ Stream each day as it finishes. A day that hangs or crashes then still
		//\ leaves the completed days on stdout for the runner to attribute.
		std::cout << "{\"year\":" << YEAR << ",\"days\":[";
		bool first = true;
		for ( const int day : days_to_run )
		{
			const Result result = questions[day - 1]();
			std::cout << ( first ? "" : "," ) << result.to_json( day ) << std::flush;
			first = false;
		}
		std::cout << "]}" << util::end_line;
		return 0;
	}

	std::cout << get_output_header_string() << std::flush;
	for ( const int day : days_to_run )
	{
		std::cout << questions[day - 1]().to_string() << std::flush;
	}
	std::cout << util::full_separator << util::end_line;

	return 0;
}
