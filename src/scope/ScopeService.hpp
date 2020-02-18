/* ============================================================
 *
 * This file is a part of the rtt-rsb-transport project
 *
 * Copyright (C) 2016 Jan Moringen <jmoringe@techfak.uni-bielefeld.de>
 *
 * This file may be licensed under the terms of the
 * GNU Lesser General Public License Version 3 (the ``LGPL''),
 * or (at your option) any later version.
 *
 * Software distributed under the License is distributed
 * on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
 * express or implied. See the LGPL for the specific language
 * governing rights and limitations.
 *
 * You should have received a copy of the LGPL along with this
 * program. If not, go to http://www.gnu.org/licenses/lgpl.html
 * or write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The development of this software was supported by:
 *   CoR-Lab, Research Institute for Cognition and Robotics
 *     Bielefeld University
 *
 * ============================================================ */

#pragma once

#include <rtt/ConnPolicy.hpp>

#include "../transport/ConnPolicyTimed.hpp"

namespace rtt_rsbcomm {
namespace scope {

/**
 * Returns a ConnPolicy object for streaming to or from
 * the given RSB scope. No buffering is done.
 */
RTT::ConnPolicy scope(const std::string& name);

/**
 * Returns a ConnPolicy(Timed) object for streaming to or from
 * the given RSB scope. No buffering is done.
 */
RTT::ConnPolicy scopeTimed(const std::string& name, const RTT::Seconds& interval);

/**
 * Returns a ConnPolicy object for streaming to or from 
 * the given RSB scope. Also specifies the buffer size of
 * the connection to be created.
 */
RTT::ConnPolicy scopeBuffer(const std::string& name, int size);

/**
 * Returns a ConnPolicy(Timed) object for streaming to or from 
 * the given RSB scope. Also specifies the buffer size of
 * the connection to be created.
 */
RTT::ConnPolicy scopeBufferTimed(const std::string& name, int size, const RTT::Seconds& interval);

}
}
