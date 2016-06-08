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

# Transport plugin

orocos_typekit(rtt-rsb-socket-transport

               util.cpp

               converter/converters.cpp

               transport/socket/OutgoingChannelElement.cpp
               transport/socket/IncomingChannelElement.cpp
               transport/socket/Transporter.cpp

               transport/socket/plugin.cpp)

target_link_libraries(rtt-rsb-socket-transport
                      ${RSB_LIBRARIES}
                      ${RST-RT_LIBRARIES}
                      ${RST_LIBRARIES}
                      ${RSTSANDBOX_LIBRARIES})

# Scope service plugin

orocos_service(rtt-rsb-scope-service
               scope/ScopeService.cpp)

target_link_libraries(rtt-rsb-scope-service
                      ${RSB_LIBRARIES}
                      rtt-rsb-socket-transport)
