#ifndef _INCLUDE_LIBTERRA_VECTOR_H_
#define _INCLUDE_LIBTERRA_VECTOR_H_

namespace LibTerra {
	struct tfVec3f {
		float x;
		float y;
		float z;
	};
	tfVec3f MakeVec3f(float x, float y, float z);
	tfVec3f Vec3fAdd(tfVec3f v, tfVec3f w);
	tfVec3f Vec3fSub(tfVec3f v, tfVec3f w);
	tfVec3f Vec3fMul(tfVec3f v, float s);
	tfVec3f Vec3fCross(tfVec3f v, tfVec3f w);
	float Vec3fDot(tfVec3f v, tfVec3f w);
	float Vec3fLen(tfVec3f v);
	tfVec3f Vec3fNormalize(tfVec3f v);
}

#endif /* _INCLUDE_LIBTERRA_VECTOR_H_ */
