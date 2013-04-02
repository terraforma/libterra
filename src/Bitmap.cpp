#include <libterra/Bitmap.h>

namespace LibTerra {
	tfBitmap::tfBitmap(std::string path) 
	{
		m_image.ReadFromFile(path.c_str());
	}
	tfBitmap::~tfBitmap() { }

	uint8_t tfBitmap::At(int x, int y)
	{
		// A greyscale pixel has r == g == b, just return r.>
		return m_image(x, y)->Red;
	}
	int tfBitmap::Width()
	{
		return m_image.TellWidth();
	}
	int tfBitmap::Height()
	{
		return m_image.TellHeight();
	}
}
