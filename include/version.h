#ifndef  _LIBTERRA_INCLUDE_VERSION_H_
#define  _LIBTERRA_INCLUDE_VERSION_H_

namespace LibTerra
{
	class Version;

	/*
	============================================================
		GetVersion

		Returns a LibTerra::Version object which contains the
		current version of terraforma
	============================================================
	*/
	Version GetVersion();
};

/*
================================================================
	Version

	Encapsulates the versioning system and provides access to
	the major, minor, and patch versions.
================================================================
*/
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

#endif /* _LIBTERRA_INCLUDE_VERSION_H_ */
