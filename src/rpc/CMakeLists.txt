# Copyright (c) 2018, The Guus Project
# Copyright (c) 2014-2019, The Monero Project
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, are
# permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this list of
#    conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice, this list
#    of conditions and the following disclaimer in the documentation and/or other
#    materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors may be
#    used to endorse or promote products derived from this software without specific
#    prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
# THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
# THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

add_library(rpc_base
  rpc_args.cpp
  )

add_library(rpc
  core_rpc_server.cpp
  rpc_handler.cpp
  )

add_library(daemon_messages
  message.cpp
  daemon_messages.cpp
  )

add_library(daemon_rpc_server
  daemon_handler.cpp
  zmq_server.cpp
  )

target_link_libraries(rpc_base
  PUBLIC
    common
    epee
    Boost::thread
    Boost::program_options
  PRIVATE
    extra)

target_link_libraries(rpc
  PUBLIC
    rpc_base
    cryptonote_core
    cryptonote_protocol
    net
    version
    Boost::regex
  PRIVATE
    extra)

target_link_libraries(daemon_messages
  PRIVATE
    cryptonote_core
    cryptonote_protocol
    version
    serialization
    extra)

target_link_libraries(daemon_rpc_server
  PRIVATE
    rpc
    daemon_messages
    serialization
    Boost::chrono
    Boost::thread
    extra)
