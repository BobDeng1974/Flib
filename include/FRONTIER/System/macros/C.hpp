//////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2014 Frontier (fr0nt13r789@gmail.com)                ///
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
/// You should have recieved a copy of GNU GPL with this software      ///
///                                                                    ///
//////////////////////////////////////////////////////////////////////////
#ifndef FRONTIER_C_HPP_INCLUDED
#define FRONTIER_C_HPP_INCLUDED
#include <FRONTIER/System/macros/SIZE.hpp>
#define FRONTIER_C

	#define C(nnn)  for (fm::Size i=0;i<(nnn);i++)
	#define Cx(nnn) for (fm::Size x=0;x<(nnn);x++)
	#define Cy(nnn) for (fm::Size y=0;y<(nnn);y++)
	#define Cz(nnn) for (fm::Size z=0;z<(nnn);z++)
	#define Cxy(Xnnn,Ynnn) for (fm::Size x=0;x<(Xnnn);x++)  for (fm::Size y=0;y<(Ynnn);y++)

#endif // FRONTIER_C_HPP_INCLUDED