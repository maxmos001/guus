# Copyright (c) 2018, The Guus Project
# Copyright (c) 2014-2017, The Monero Project
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

add_library(device
  device.cpp
  device_default.cpp
  log.cpp
  )

target_link_libraries(device
  PUBLIC
    cncrypto
    ringct_basic
    OpenSSL::Crypto
    Boost::serialization
  PRIVATE
    version
    extra)

find_package(HIDAPI)

if (HIDAPI_FOUND)
    message(STATUS "Using HIDAPI ${HIDAPI_LIBRARIES} (includes at ${HIDAPI_INCLUDE_DIR})")
  target_sources(device PRIVATE
    device_ledger.cpp
    device_io_hid.cpp
    )
  target_compile_definitions(device PUBLIC HAVE_HIDAPI)
  target_include_directories(device PRIVATE ${HIDAPI_INCLUDE_DIR})
  target_link_libraries(device PRIVATE ${HIDAPI_LIBRARIES})
else (HIDAPI_FOUND)
  message(STATUS "Could not find HIDAPI")
endif()
