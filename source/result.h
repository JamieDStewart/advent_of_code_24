#pragma once

#include "util.h"
#include <cstdint>
#include <sstream>
#include <string>



struct Result
{
	const std::string	name;
	const uint64_t		part_1;
	const uint64_t		part_2;
	const double		execution_time;

	[[nodiscard]] std::string to_string() const 
	{
		std::stringstream ss;
		ss << util::vertical_separator;
		ss << util::pad( name, 23 ) << util::vertical_separator;
		ss << util::pad( util::to_string( part_1 ), 12 ) << util::vertical_separator;
		ss << util::pad( util::to_string( part_2 ), 15 ) << util::vertical_separator;
		ss << util::pad( util::to_string( execution_time ), 12 ) << util::vertical_separator;
		ss << util::end_line;
		return ss.str();
	}
};
