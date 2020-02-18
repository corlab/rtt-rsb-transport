/* ============================================================
 *
 * This file is a part of the rtt-rsb-transport project
 *
 * Copyright (C) 2020 Dennis Leroy Wigand <dwigand@techfak.uni-bielefeld.de>
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

#include "ConnPolicyTimed.hpp"

namespace rtt_rsbcomm {
    namespace transport {

        ConnPolicyTimed ConnPolicyTimed::data(RTT::Seconds publish_interval, int lock_policy /*= LOCK_FREE*/, bool init_connection /*= true*/, bool pull /*= false*/)
        {
            ConnPolicyTimed result(publish_interval, DATA, lock_policy);
            result.init = init_connection;
            result.pull = pull;
            return result;
        }

        ConnPolicyTimed ConnPolicyTimed::buffer(RTT::Seconds publish_interval, int size, int lock_policy /*= LOCK_FREE*/, bool init_connection /*= false*/, bool pull /*= false*/)
        {
            ConnPolicyTimed result(publish_interval, BUFFER, lock_policy);
            result.size = size;
            result.init = init_connection;
            result.pull = pull;
            return result;
        }

        ConnPolicyTimed::ConnPolicyTimed(RTT::Seconds publish_interval, int type, int lock_policy)
        : RTT::ConnPolicy(type, lock_policy), publish_interval(publish_interval)
        {}

    }
}