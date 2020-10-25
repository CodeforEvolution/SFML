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
#include <SFML/System/Haiku/ThreadImpl.hpp>
#include <SFML/System/Thread.hpp>
#include <cassert>
#include <iostream>

namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
ThreadImpl::ThreadImpl(Thread* owner) :
m_isActive(true)
{
    m_thread = spawn_thread(&ThreadImpl::entryPoint, "SFML thread", B_NORMAL_PRIORITY, owner);

    if (m_thread < B_NO_ERROR) {
        m_isActive = false;
        std::cerr << "Failed to create thread" << std::endl;
        return;
    }

    if (resume_thread(m_thread) == B_OK) {
        m_isActive = true;
    } else {
        m_isActive = false;
        std::cerr << "Failed to start thread" << std::endl;
    }
}


////////////////////////////////////////////////////////////
void ThreadImpl::wait()
{
    if (m_isActive)
    {
        // A thread cannot wait for itself!
        assert(find_thread(NULL) != m_thread);

        wait_for_thread(m_thread, NULL);
    }
}


////////////////////////////////////////////////////////////
void ThreadImpl::terminate()
{
    // Haiku has "pthread_cancel", though not an equivalent for its native
    // threading API...huh...
    if (m_isActive)
    {
        // Don't do this at home kids!
        kill_thread(m_thread);
    }
}


////////////////////////////////////////////////////////////
status_t ThreadImpl::entryPoint(void* userData)
{
    // The Thread instance is stored in the user data
    Thread* owner = static_cast<Thread*>(userData);

    // Forward to the owner
    owner->run();

    return B_NO_ERROR;
}

} // namespace priv

} // namespace sf
