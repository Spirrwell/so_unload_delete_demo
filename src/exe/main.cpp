#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>

#include "objectbase.h"

int main()
{
	void* lib = dlopen("libso.so", RTLD_LAZY);
	if (!lib) {
		fprintf(stderr, "Failed to open libso.so: %s\n", dlerror());
		return EXIT_FAILURE;
	}

	typedef ObjectBase*(*CREATE_OBJECT_FN)();
	CREATE_OBJECT_FN fn = reinterpret_cast<CREATE_OBJECT_FN>(dlsym(lib, "CreateObject"));

	if (!fn) {
		fprintf(stderr, "Failed to lookup CreateObject() function: %s\n", dlerror());
		dlclose(lib);

		return EXIT_FAILURE;
	}

	ObjectBase* base = fn();

	// Close the library before we call delete to trigger a segfault
	// It's worth noting that dlclose won't necessarily unload the SO from memory.
	// Sometimes it will, it depends on the implementation.
	// This requires we use the -fno-gnu-unique option to work around that
	dlclose(lib);

	delete base;
	return EXIT_SUCCESS;
}