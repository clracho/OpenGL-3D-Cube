#pragma once
#include <Cube3D/Prerequisites.h>



class OVec3
{
public:
	OVec3()
	{

	}
	OVec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z)
	{

	}

	OVec3 operator *(float num)
	{
		return OVec3(x * num, y * num, z * num);
	}

	OVec3 operator +(OVec3 num)
	{
		return OVec3(x + num.x, y + num.y, z + num.z);
	}

public:
	f32 x = 0, y = 0, z = 0;
};