#include <libterra/Vector.h>

#include <cmath>

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

	tfVec3f Vec3fSub(tfVec3f v, tfVec3f w)
	{
		tfVec3f vec = {v.x-w.x, v.y-w.y, v.z-w.z};
		return vec;
	}

	tfVec3f Vec3fMul(tfVec3f v, float s)
	{
		tfVec3f vec = {v.x*s, v.y*s, v.z*s};
		return vec;
	}

	tfVec3f Vec3fCross(tfVec3f v, tfVec3f w)
	{
		tfVec3f vec = {v.y*w.z - v.z*w.y, v.z*w.x - v.x*w.z, v.x*w.y - v.y*w.x};
		return vec;
	}

	float Vec3fDot(tfVec3f v, tfVec3f w)
	{
		return v.x*w.x+v.y*w.y+v.z*w.z;
	}

	float Vec3fLen(tfVec3f v)
	{
		return sqrt((v.x*v.x)+(v.y*v.y)+(v.z*v.z));
	}

	tfVec3f Vec3fNormalize(tfVec3f v)
	{
		float len = Vec3fLen(v);
		tfVec3f vec = {v.x/len, v.y/len, v.z/len};
		return vec;
	}
}
