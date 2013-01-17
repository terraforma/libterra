# ifndef   __LIBTERRA_INCLUDE_VERSION_H_
#  define  __LIBTERRA_INCLUDE_VERSION_H_ 1

namespace LibTerra
{
	class Version;

	Version GetVersion();
};

class LibTerra::Version
{
	friend Version GetVersion();
private:
	const unsigned int m_major;
	const unsigned int m_minor;
	const unsigned int m_patch;

	Version(const unsigned int _major, const unsigned int _minor, const unsigned int _patch) :
		m_major(_major), m_minor(_minor), m_patch(_patch) {}
public:
	const unsigned int Major() const { return m_major; }
	const unsigned int Minor() const { return m_minor; }
	const unsigned int Patch() const { return m_patch; }
};

# endif /* __LIBTERRA_INCLUDE_VERSION_H_ */
