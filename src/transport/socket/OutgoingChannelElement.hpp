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

#include <rtt/base/ChannelElement.hpp>
#include <rtt/ConnPolicy.hpp>

#include <rsc/runtime/TypeStringTools.h>

#include <rsb/Scope.h>
#include <rsb/Informer.h>

namespace rtt_rsbcomm {
namespace transport {
namespace socket {

class OutgoingChannelElementBase {
public:

    /**
     * Contructor of to create ROS publisher ChannelElement, it will
     * create a topic from the name given by the policy.name_id, if
     * this is empty a default is created as hostname/componentname/portname/pid
     *
     * @param port port for which we will create a the ROS publisher
     * @param policy connection policy containing the topic name and buffer size
     *
     * @return ChannelElement that will publish data to topics
     */
    OutgoingChannelElementBase(RTT::base::PortInterface* port,
                               const RTT::ConnPolicy& policy);

    virtual ~OutgoingChannelElementBase();

    /**
     * Function to see if the ChannelElement is ready to receive inputs
     *
     * @return always true in our case
     */
    virtual bool inputReady();

protected:
    rsb::Scope           scope;
    rsb::InformerBasePtr informer;
};

template <typename T>
class OutgoingChannelElement: public OutgoingChannelElementBase,
                              public RTT::base::ChannelElement<T> {
public:
    OutgoingChannelElement(RTT::base::PortInterface* port,
                           const RTT::ConnPolicy& policy)
        : OutgoingChannelElementBase(port, policy) {
    }

    virtual ~OutgoingChannelElement() {}

    /**
     * Create a data sample, this could be used to allocate the necessary memory
     *
     * @param sample
     *
     * @return always true
     */
    virtual bool data_sample(typename RTT::base::ChannelElement<T>::param_t sample) {
        this->sample = sample;
        return true;
    }

    /**
     * signal from the port that new data is availabe to publish
     *
     * @return true if publishing succeeded
     */
    bool signal() {
        //Logger::In in(topicname);
        //log(Debug)<<"Requesting publish"<<endlog();
        //return act->trigger();
    }

    void publish() {
        // this read should always succeed since signal() means 'data
        // available in a data element'.
        typename RTT::base::ChannelElement<T>::shared_ptr input = this->getInput();
        while (input && (input->read(this->sample, false) == RTT::NewData)) {
            write(this->sample);
        }
    }

    bool write(typename RTT::base::ChannelElement<T>::param_t sample) {
        this->informer->publish(boost::shared_ptr<T>(new T(sample)),
                                rsc::runtime::typeName<T>());
        return true;
    }

private:
    typename RTT::base::ChannelElement<T>::value_t sample;
};

}
}
}
