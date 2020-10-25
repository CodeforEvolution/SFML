////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2020 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/Haiku/SleepImpl.hpp>
#include <kernel/OS.h>


namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
void sleepImpl(Time time)
{
    // Let's calculate the end time! (There isn't much to it!)
    Uint64 endTime = system_time() + time.asMicroseconds();

    // Wait...
    // If snooze_until returns B_INTERRUPTED, we continue sleeping
    // until the complete duration has passed. We stop sleeping if it
    // was due to an error.
    while (snooze_until(endTime, B_SYSTEM_TIMEBASE) == B_INTERRUPTED)
    {
    }
}

} // namespace priv

} // namespace sf
