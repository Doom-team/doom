//------------------------------------------------------------------------
//  MAC OS X NATIVE C-STYLE CALLS TO BE ACCESSED FROM THE MAIN PROGRAM
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2001-2013 Andrew Apted
//  Copyright (C) 1997-2003 AndrÈ Majorel et al
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//------------------------------------------------------------------------
//
//  Based on Yadex which incorporated code from DEU 5.21 that was put
//  in the public domain in 1994 by RaphaÎl Quinet and Brendon Wyber.
//
//------------------------------------------------------------------------

//
// Module by Ioan Chera
//

#ifdef __APPLE__

#ifndef __Eureka_Doom_Editor__OSXCalls__
#define __Eureka_Doom_Editor__OSXCalls__

//#ifdef __cplusplus__
//extern "C"
//{
//#endif

   // Currently used paths
   enum
   {
      osx_LibDir,
      osx_LibAppSupportDir,
      osx_LibCacheDir,
   };
   typedef unsigned osx_dirtype;
   
   const char *OSX_UserDomainDirectory(osx_dirtype dirtype, const char *subdir);

//#ifdef __cplusplus__
//}
//#endif

#endif /* defined(__Eureka_Doom_Editor__OSXCalls__) */

#endif

