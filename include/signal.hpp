/***********************************************************************************************************************
*                                                                                                                      *
* Threaded Signals v0.1                                                                                                      *
*                                                                                                                      *
* Copyright (c) 2015-(today) Arthur de A. Farias                                                                       *
* All rights reserved.                                                                                                 *
*                                                                                                                      *
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the     *
* following conditions are met:                                                                                        *
*                                                                                                                      *
*    * Redistributions of source code must retain the above copyright notice, this list of conditions, and the         *
*      following disclaimer.                                                                                           *
*                                                                                                                      *
*    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the       *
*      following disclaimer in the documentation and/or other materials provided with the distribution.                *
*                                                                                                                      *
*    * Neither the name of the author nor the names of any contributors may be used to endorse or promote products     *
*      derived from this software without specific prior written permission.                                           *
*                                                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE AUTHORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   *
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL *
* THE AUTHORS BE HELD LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES        *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR       *
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                                                                          *
*                                                                                                                      *
***********************************************************************************************************************/

/**
	@file signal.hpp
	@author Arthur de A. Farias <arthur@afarias.org>
	@brief Signal Class Declaration/Definition
 */

#ifndef _threaded_signals_hpp_
#define _threaded_signals_hpp_

#include <functional>
#include <future>
#include <list>

#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "thread_pool.hpp"

template<typename sender_type, typename... args_types>
class signal
{
public:
  signal()
    : thread_pool()
  {
  }

  signal(signal&) = delete;

  using slot_type = std::function<void(sender_type, args_types...)>;

  void connect(const slot_type& slot) { sinks.push_back(std::move(slot)); }

  void operator()(sender_type sender, args_types... args)
  {
    for (auto slot : sinks) {
      thread_pool.push(slot, sender, std::forward<args_types>(args)...);
    }
  }

  signal& operator+=(const slot_type& slot)
  {
    connect(slot);
    return *this;
  }

protected:
  std::list<slot_type> sinks;
  lt::threading::thread_pool<sender_type, args_types...> thread_pool;
};

#endif