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

#import "Foundation/Foundation.h"
#include "OSXCalls.h"


//
// OSX_UserDomainDirectory
//
// Returns the directory where to save configs
//
const char *OSX_UserDomainDirectory(osx_dirtype dirtype, const char *subdir)
{
   NSSearchPathDirectory spd;
   switch (dirtype)
   {
      case osx_LibDir:
         spd = NSLibraryDirectory;
         break;
         
      case osx_LibAppSupportDir:
         spd = NSApplicationSupportDirectory;
         break;
         
      case osx_LibCacheDir:
         spd = NSCachesDirectory;
         break;
   }
   
   NSArray *paths = NSSearchPathForDirectoriesInDomains(spd, NSUserDomainMask, YES);
   if([paths count] <= 0)
      return "."; // shouldn't normally occur
   
   NSString *retDir = [paths objectAtIndex:0];
   if(subdir)
      retDir = [retDir stringByAppendingPathComponent:[NSString stringWithCString:subdir encoding:NSUTF8StringEncoding]];
   
   return [retDir cStringUsingEncoding:NSUTF8StringEncoding];
}

#endif
