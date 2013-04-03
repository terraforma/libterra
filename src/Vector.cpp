#include <libterra/Vector.h>

namespace LibTerra {
	tfVec3f MakeVec3f(float x, float y, float z)
	{
		tfVec3f vec = {x, y, z};
		return vec;
	}
}
