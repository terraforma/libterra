# ifndef   __LIBTERRA_INCLUDE_VERSION_H_
#  define  __LIBTERRA_INCLUDE_VERSION_H_ 1

namespace LibTerra
{
	class SemVer;
	
	SemVer GetVersion();
};

class LibTerra::SemVer
{
public :
	unsigned m_major, m_minor, m_patch;
};

# endif /* __LIBTERRA_INCLUDE_VERSION_H_ */
