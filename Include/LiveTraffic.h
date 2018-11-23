//
//  LiveTraffic.h
//  LiveTraffic
//

/*
 * Copyright (c) 2018, Birger Hoppe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef LiveTraffic_h
#define LiveTraffic_h

// LiveTraffic is coded against SDK 2.1 (X-Plane 10 and above), so both XPLM200 and XPLM210 must be defined
#if !defined(XPLM200) || !defined(XPLM210)
#error This is made to be compiled against the XPLM210 SDK (X-plane 10 and above)
#endif

// MARK: Includes
// Standard C
#include <cstdio>
#include <cstdarg>
#include <cmath>
#include <cstring>
#include <ctime>

// Windows
#if IBM
#include <windows.h>
// we prefer std::max/min of <algorithm>
#undef max
#undef min
#endif

// Open GL
#if LIN
#include <GL/gl.h>
#elif __GNUC__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

// C++
#include <utility>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <thread>
#include <algorithm>

// X-Plane SDK
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"
#include "XPLMMenus.h"
#include "XPLMPlugin.h"
#include "XPLMProcessing.h"
#include "XPLMCamera.h"
#include "XPWidgets.h"
#include "XPWidgetUtils.h"
#include "XPStandardWidgets.h"

// XP Multiplayer API
#include "xplanemp/XPMPMultiplayer.h"

// LiveTraffic Includes
#include "Constants.h"
#include "DataRefs.h"
#include "CoordCalc.h"
#include "TextIO.h"
#include "LTAircraft.h"
#include "LTFlightData.h"
#include "LTChannel.h"
#include "TFWidgets.h"
#include "SettingsUI.h"
#include "ACInfoWnd.h"

// MARK: Global variables
// Global DataRef object, which also includes 'global' variables
extern DataRefs dataRefs;

// MARK: Path Conversion
// Convert HFS (as used by XPLM) to Posix (as used by XPMP)
std::string& LTHFS2Posix ( std::string& path );

// if necessary exchange the directory separator from / to a local one.
// (works only well on partial paths as defined in Constants.h!)
std::string LTPathToLocal ( const char* p, bool bXPMPStyle );

// deal with paths: make a full one from a relative one or keep a full path
std::string LTCalcFullPath ( const char* path );

// given a path (in XPLM notation) returns number of files in the path
// or 0 in case of errors
int LTNumFilesInPath ( const char* path );

// return the directory containing resources like Doc8643.txt and CSLs
std::string LTFindResourcesDirectory ();

// MARK: Utility Functions
// change a std::string to uppercase
std::string& str_toupper(std::string& s);
// format timestamp
std::string ts2string (time_t t);
// limits text to m characters, replacing the last ones with ... if too long
inline std::string strAtMost(const std::string s, size_t m) {
    return s.length() <= m ? s :
    s.substr(0, m-3) + "...";
}

// push a new item to the end only if it doesn't exist yet
template< class ContainerT, class T>
void push_back_unique(ContainerT& list, const T& key)
{
    if ( std::find(list.cbegin(),list.cend(),key) == list.cend() )
        list.push_back(key);
}

// MARK: Compiler differences

#ifdef APL
// XCode doesn't provide the _s functions, not even with __STDC_WANT_LIB_EXT1__ 1
inline errno_t strerror_s( char *buf, rsize_t bufsz, errno_t errnum )
{ return strerror_r(errnum, buf, bufsz); }

// not quite the same but close enough for our purposes
inline void strcpy_s(char * dest, rsize_t destsz, const char * src)
{ strncpy(dest, src, destsz); dest[destsz-1]=0; }
inline void strcat_s(char * dest, rsize_t destsz, const char * src)
{ strncat(dest, src, destsz - strlen(dest) - 1); }

// these simulate the VC++ version, not the C standard versions!
inline struct tm *gmtime_s(struct tm * result, const time_t * time)
{ return gmtime_r(time, result); }
inline struct tm *localtime_s(struct tm * result, const time_t * time)
{ return localtime_r(time, result); }

#endif

#endif /* LiveTraffic_h */
