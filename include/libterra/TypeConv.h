#ifndef _INCLUDE_LIBTERRA_TYPECONV_H_
#define _INCLUDE_LIBTERRA_TYPECONV_H_

#include <sstream>
#include <string>

namespace LibTerra {
	template<typename T, typename U>
    inline U Convert(T source) 
	{
		// This should be avoided. Unreliable type conversion
		return (U)source;
	}
	// Conversions to a string (These are mostly the same, sadly we cant partially specialize function templates)
	template <>
    inline const char* Convert<int, const char*>(int source) 
	{
		std::stringstream stream;
		stream << source;
		return stream.str().c_str();
	}
	template <>
    inline const char* Convert<bool, const char*>(bool source) 
	{
		std::stringstream stream;
		stream << source;
		return stream.str().c_str();
	}
	template <>
    inline const char* Convert<float, const char*>(float source) 
	{
		std::stringstream stream;
		stream << source;
		return stream.str().c_str();
	}

	template <>
	inline float Convert<const char*, float>(const char* source)
	{
		std::stringstream stream(source);
		float f;
		stream >> f;
		return f;
	}

	template <>
	inline int Convert<const char*, int>(const char* source)
	{
		std::stringstream stream(source);
		int i;
		stream >> i;
		return i;
	}
}

#endif /* _INCLUDE_LIBTERRA_TYPECONV_H_ */
