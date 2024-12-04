#pragma once
#include <sstream>
#include <string>

namespace util
{
	const std::string full_separator = "========================================================================";
	const std::string vertical_separator = "||";
	const std::string end_line = "\n";


	template<class T>
	std::string to_string( T value_type )
	{
		std::stringstream ss;
		ss << value_type;
		return ss.str();
	}

	inline std::string pad_left( const std::string& str, const uint32_t size_to_pad_to, const char pad_char = ' ' )
	{
		std::string padded_string = str;
		if ( const auto padding = size_to_pad_to - padded_string.size(); padding > 0 )
		{
			padded_string.insert( padded_string.begin(), padding, pad_char );
		}
		return padded_string;
	}

	inline std::string pad( const std::string& str, const uint32_t size_to_pad_to, const char pad_char = ' ' )
	{
		std::string padded_string = str;
		if ( const auto padding = size_to_pad_to - padded_string.size(); padding > 0 )
		{
			padded_string.append( padding, pad_char );
		}
		return padded_string;
	}

}