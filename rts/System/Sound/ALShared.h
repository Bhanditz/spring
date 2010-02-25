/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef ALShared
#define ALShared

#include "LogOutput.h"

// Copied from efx.h, as this header only exists under windows
// so far (February 2010).
// This will change in future versions of OpenAL.
#if       !defined(AL_AIR_ABSORPTION_FACTOR)
#define AL_AIR_ABSORPTION_FACTOR                           0x20007
#define AL_MIN_AIR_ABSORPTION_FACTOR                       0.0f
#define AL_MAX_AIR_ABSORPTION_FACTOR                       10.0f
#define AL_DEFAULT_AIR_ABSORPTION_FACTOR                   0.0f
#endif // !defined(AL_AIR_ABSORPTION_FACTOR)

extern const CLogSubsystem LOG_SOUND;

bool CheckError(const char* msg);

#endif
