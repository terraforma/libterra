#ifndef _INCLUDE_LIBTERRA_VECTOR_H_
#define _INCLUDE_LIBTERRA_VECTOR_H_

namespace LibTerra {
	struct tfVec3f {
		float x;
		float y;
		float z;
	};
	tfVec3f MakeVec3f(float x, float y, float z);
}

#endif /* _INCLUDE_LIBTERRA_VECTOR_H_ */
