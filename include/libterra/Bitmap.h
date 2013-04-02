#ifndef _LIBTERRA_INCLUDE_BITMAP_H_
#define _LIBTERRA_INCLUDE_BITMAP_H_

#include <string>
#include <stdint.h>

#include <EasyBMP.h>

namespace LibTerra {
	/**
	 * tfBitmap
	 * A wrapper around the EasyBMP library
	 * Used to read bitmaps from disk and extract the colour at each point in greyscale form
	 */
	class tfBitmap {
	public:
		tfBitmap(std::string path);
		virtual ~tfBitmap();
		
		/**
		 * At
		 * Accesses the pixel at (x, y), returning a value between
		 * 0-255, which represents the greyscale value of this pixel
		 */
		uint8_t At(int x, int y);
		int Width();
		int Height();
	private:
		BMP m_image;
	};
}

#endif /* _LIBTERRA_INCLUDE_BITMAP_H_ */
