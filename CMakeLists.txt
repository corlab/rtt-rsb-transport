# This file is a part of the rtt-rsb-transport project
#
# Copyright (C) 2016 Jan Moringen <jmoringe@techfak.uni-bielefeld.de>
#
# This file may be licensed under the terms of the
# GNU Lesser General Public License Version 3 (the ``LGPL''),
# or (at your option) any later version.
#
# Software distributed under the License is distributed
# on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
# express or implied. See the LGPL for the specific language
# governing rights and limitations.
#
# You should have received a copy of the LGPL along with this
# program. If not, go to http://www.gnu.org/licenses/lgpl.html
# or write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# The development of this software was supported by:
#   CoR-Lab, Research Institute for Cognition and Robotics
#     Bielefeld University

cmake_minimum_required(VERSION 2.8.3)

project(rtt_rsbcomm CXX)

# Dependencies

find_package(OROCOS-RTT REQUIRED)
include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake)

find_package(RSB REQUIRED)

include_directories(${RSB_INCLUDE_DIRS})
add_definitions(${RSB_CXX_FLAGS})

find_package(rst-rt REQUIRED)

include_directories(${RST-RT_INCLUDE_DIRS})
add_definitions(${RST-RT_CXX_FLAGS})

link_directories(${RST-RT_LIBRARY_DIRS})

find_package(RST REQUIRED)

include_directories(${RST_INCLUDE_DIRS})
add_definitions(${RST_CFLAGS})

link_directories(${RST_LIBRARY_DIRS})

# Sub-directories

add_subdirectory(src)
