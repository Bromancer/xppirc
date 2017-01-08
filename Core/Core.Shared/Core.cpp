#include "pch.h"
#include "Core.h"

char * Core::getTemplateInfo()
{
#ifdef __IOS__
	static char info[] = "Platform for iOS";
#elif __ANDROID__
	static char info[] = "Platform for Android";
#else _WIN32
	static char info[] = "Undefined platform";
#endif

	return info;
}

Core::Core()
{
}

Core::~Core()
{
}
