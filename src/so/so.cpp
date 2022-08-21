#include "objectbase.h"
#include <cstdio>

struct ObjectDerived : public ObjectBase
{
	~ObjectDerived()
	{
		fprintf(stderr, "ObjectDerived destroyed\n");
	}
};

extern "C" ObjectBase* CreateObject() { return new ObjectDerived; }