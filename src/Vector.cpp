#include <libterra/Vector.h>

namespace LibTerra {
	tfVec3f MakeVec3f(float x, float y, float z)
	{
		tfVec3f vec = {x, y, z};
		return vec;
	}

	tfVec3f Vec3fAdd(tfVec3f v, tfVec3f w)
	{
		tfVec3f vec = {v.x+w.x, v.y+w.y, v.z+w.z};
		return vec;
	}
}
