#pragma once
#include <cstdio>
#include <cstdint>
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

	inline std::string pad_left( const std::string& str, const size_t size_to_pad_to, const char pad_char = ' ' )
	{
		std::string padded_string = str;
		if ( padded_string.size() < size_to_pad_to )
		{
			padded_string.insert( padded_string.begin(), size_to_pad_to - padded_string.size(), pad_char );
		}
		return padded_string;
	}

	inline std::string pad( const std::string& str, const size_t size_to_pad_to, const char pad_char = ' ' )
	{
		std::string padded_string = str;
		if ( padded_string.size() < size_to_pad_to )
		{
			padded_string.append( size_to_pad_to - padded_string.size(), pad_char );
		}
		return padded_string;
	}

	//\ Minimal JSON string escaping, enough for the day names and numeric results
	//\ this project emits. Keeps the --format json output well formed.
	inline std::string json_escape( const std::string& str )
	{
		std::string escaped;
		escaped.reserve( str.size() + 8 );
		for ( const char c : str )
		{
			switch ( c )
			{
			case '"':  escaped += "\\\""; break;
			case '\\': escaped += "\\\\"; break;
			case '\n': escaped += "\\n";  break;
			case '\r': escaped += "\\r";  break;
			case '\t': escaped += "\\t";  break;
			default:
				if ( static_cast<unsigned char>(c) < 0x20 )
				{
					char buffer[7];
					snprintf( buffer, sizeof( buffer ), "\\u%04x", c );
					escaped += buffer;
				}
				else
				{
					escaped += c;
				}
				break;
			}
		}
		return escaped;
	}
}
