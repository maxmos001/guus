// Copyright (c) 2019, The Guus Project
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <mutex>
#include <shared_mutex>
#include <tuple>
#include <boost/thread/lock_algorithms.hpp>

namespace tools {

/// Takes any number of lockable objects, locks them atomically, and returns a tuple of
/// std::unique_lock holding the individual locks.
template <typename... T>
#ifdef __GNUG__
[[gnu::warn_unused_result]]
#endif
std::tuple<std::unique_lock<T>...> unique_locks(T& ...lockables) {
    boost::lock(lockables...);
    auto locks = std::make_tuple(std::unique_lock<T>(lockables, std::adopt_lock)...);
    return locks;
}

/// Shortcut around getting a std::unique_lock<T> without worrying about T.  The first argument is
/// the mutex (or other Lockable object); it and any remaining args (such as `std::defer_lock`) are
/// forwarded to the std::unique_lock<T> constructor.
template <typename T, typename... Args>
#ifdef __GNUG__
[[gnu::warn_unused_result]]
#endif
std::unique_lock<T> unique_lock(T& lockable, Args&&... args) {
    return std::unique_lock<T>(lockable, std::forward<Args>(args)...);
}

/// Shortcut for getting a std::shared_lock<T> without worrying about T.  First argument is the
/// shared lockable; it any any remaining args (such as `std::defer_lock`) are forwarded to the
/// std::shared_lock<T> constructor.
template <typename T, typename... Args>
#ifdef __GNUG__
[[gnu::warn_unused_result]]
#endif
std::shared_lock<T> shared_lock(T& lockable, Args&&... args) {
    return std::shared_lock<T>(lockable, std::forward<Args>(args)...);
}

}
