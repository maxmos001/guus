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

add_library(blockchain_tools_common_libs INTERFACE)
target_link_libraries(blockchain_tools_common_libs INTERFACE
    cryptonote_core
    blockchain_db
    version
    Boost::filesystem
    Boost::program_options
    extra)


guus_add_executable(blockchain_import "guus-blockchain-import"
  blockchain_import.cpp
  bootstrap_file.cpp
  blocksdat_file.cpp
  )

target_link_libraries(blockchain_import PRIVATE blockchain_tools_common_libs)

if(ARCH_WIDTH)
  target_compile_definitions(blockchain_import PRIVATE ARCH_WIDTH=${ARCH_WIDTH})
endif()

guus_add_executable(blockchain_export "guus-blockchain-export"
  blockchain_export.cpp
  bootstrap_file.cpp
  blocksdat_file.cpp
  )
target_link_libraries(blockchain_export PRIVATE blockchain_tools_common_libs)


guus_add_executable(blockchain_blackball "guus-blockchain-mark-spent-outputs"
  blockchain_blackball.cpp
  )

target_link_libraries(blockchain_blackball
  PRIVATE
    blockchain_tools_common_libs
    wallet)


guus_add_executable(blockchain_usage "guus-blockchain-usage"
  blockchain_usage.cpp
  )
target_link_libraries(blockchain_usage PRIVATE blockchain_tools_common_libs)

guus_add_executable(blockchain_ancestry "guus-blockchain-ancestry"
  blockchain_ancestry.cpp
  )
target_link_libraries(blockchain_ancestry PRIVATE blockchain_tools_common_libs)

guus_add_executable(blockchain_depth "guus-blockchain-depth"
  blockchain_depth.cpp
  )
target_link_libraries(blockchain_depth PRIVATE blockchain_tools_common_libs)

guus_add_executable(blockchain_stats "guus-blockchain-stats"
  blockchain_stats.cpp
  )
target_link_libraries(blockchain_stats PRIVATE blockchain_tools_common_libs)

# TODO(guus): Blockchain pruning not supported in Guus yet
# guus_add_executable(blockchain_prune_known_spent_data "guus-blockchain-prune-known-spent-data"
#   blockchain_prune_known_spent_data.cpp
#   )
# 
# target_link_libraries(blockchain_prune_known_spent_data
#   PRIVATE
#     blockchain_tools_common_libs
#     p2p)
# 
# guus_add_executable(blockchain_prune "guus-blockchain-prune"
#   blockchain_prune.cpp
#   )
# 
# target_link_libraries(blockchain_prune
#   PRIVATE
#     blockchain_tools_common_libs
#     p2p)
