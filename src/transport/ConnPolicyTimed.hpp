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

#ifndef __RTT_CONN_POLICY_TIMED_HPP_
#define __RTT_CONN_POLICY_TIMED_HPP_

#include <rtt/ConnPolicy.hpp>
#include <rtt/Time.hpp>

namespace rtt_rsbcomm {
    namespace transport {

    /**
     * A custom connection policy object describes how a given connection should
     * behave, including the timed interval in which data is published.
     */
    class ConnPolicyTimed : public RTT::ConnPolicy
    {
    public:
        /**
         * Create a policy for a (lock-free) shared data connection of a given size that publishes data at a specific timed interval.
         * @param publish_interval The timed interval to publish data
         * @param lock_policy The locking policy
         * @param init_connection If the data object should be initialised with the last value of the OutputPort upon creation.
         * @param pull In inter-process cases, should the consumer pull data itself ?
         * @return the specified policy.
         */
        static ConnPolicyTimed data(RTT::Seconds publish_interval, int lock_policy = LOCK_FREE, bool init_connection = true, bool pull = false);

        /**
         * Create a policy for a (lock-free) fifo buffer connection of a given size that publishes data at a specific timed interval.
         * @param publish_interval The timed interval to publish data
         * @param size The size of the buffer in this connection
         * @param lock_policy The locking policy
         * @param init_connection If an initial sample should be pushed into the buffer upon creation.
         * @param pull In inter-process cases, should the consumer pull itself ?
         * @return the specified policy.
         */
        static ConnPolicyTimed buffer(RTT::Seconds publish_interval, int size, int lock_policy = LOCK_FREE, bool init_connection = false, bool pull = false);

        /**
         * The default policy is data driven, lock-free, local and publishes data at a specific timed interval.
         * It is unsafe to rely on these defaults. It is prefered
         * to use the above buffer() and data() functions.
         * @param publish_interval The timed interval to publish data
         * @param type
         * @param lock_policy
         * @return
         */
        ConnPolicyTimed(RTT::Seconds publish_interval, int type = DATA, int lock_policy = LOCK_FREE);

        /**
         * The desired publish interval for the connection.
         */
        RTT::Seconds    publish_interval;
    };//class
    }//namespace
}
#endif
