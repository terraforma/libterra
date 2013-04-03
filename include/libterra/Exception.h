#ifndef _INCLUDE_LIBTERRA_EXCEPTION_H
#define _INCLUDE_LIBTERRA_EXCEPTION_H

#include <stdexcept>

namespace LibTerra {
	class tfException : public std::runtime_error {
	public:
		explicit tfException(const std::string& what)  :
                std::runtime_error(what) {}
	};
}

#endif /* _INCLUDE_LIBTERRA_EXCEPTION_H */
