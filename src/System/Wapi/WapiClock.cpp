////////////////////////////////////////////////////////////////////////// <!--
/// Copyright (C) 2014-2016 Frontier (fr0nt13r789@gmail.com)           ///
///                                                                    ///
/// Flib is licensed under the terms of GNU GPL.                       ///
/// Therefore you may freely use it in your project,                   ///
/// modify it, redistribute it without any warranty on the             ///
/// condition that this disclaimer is not modified/removed.            ///
/// You may not misclaim the origin of this software.                  ///
///                                                                    ///
/// If you use this software in your program/project a                 ///
/// note about it and an email for the author (fr0nt13r789@gmail.com)  ///
/// is not required but highly appreciated.                            ///
///                                                                    ///
/// You should have received a copy of GNU GPL with this software      ///
///                                                                    ///
////////////////////////////////////////////////////////////////////////// -->
#include <windows.h>

class TicksPerSecondHolder
{
public:
	LARGE_INTEGER ticksPerSecond;
	TicksPerSecondHolder()
	{
		HANDLE thread  = GetCurrentThread();
		DWORD_PTR mask = SetThreadAffinityMask(thread, 1);
		
		QueryPerformanceFrequency(&ticksPerSecond);
		
		SetThreadAffinityMask(thread,mask);
	}
};

const TicksPerSecondHolder tpsh;

fm::Time getCurrentTime()
{
	HANDLE thread  = GetCurrentThread();
    DWORD_PTR mask = SetThreadAffinityMask(thread, 1);

    LARGE_INTEGER actTime;
    QueryPerformanceCounter(&actTime);

    SetThreadAffinityMask(thread,mask);

	return fm::seconds(((double)actTime.QuadPart) / ((double)tpsh.ticksPerSecond.QuadPart));
}
