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
#include <SFML/System/Haiku/ThreadLocalImpl.hpp>
#include <iostream>

namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
ThreadLocalImpl::ThreadLocalImpl() :
m_slotIndex(-1)
{
    m_slotIndex = tls_allocate();

    // Each process on Haiku can allocate a maximum of 64 TLS variables
    if (m_slotIndex < B_NO_ERROR) {
        std::cerr << "Couldn't allocate a tls slot, no more slots available" << std::endl;
    }
}


////////////////////////////////////////////////////////////
ThreadLocalImpl::~ThreadLocalImpl()
{
    // So, uh, there's no way to free a TLS slot in Haiku.
    // Because of this, please, be careful when using the all powerful
    // ThreadLocal object!
}


////////////////////////////////////////////////////////////
void ThreadLocalImpl::setValue(void* value)
{
    tls_set(m_slotIndex, value);
}


////////////////////////////////////////////////////////////
void* ThreadLocalImpl::getValue() const
{
    return tls_get(m_slotIndex);
}

} // namespace priv

} // namespace sf
