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

#include <rsb/Scope.h>
#include <rsb/Event.h>
#include <rsb/Listener.h>

namespace rtt_rsbcomm {
namespace transport {
namespace socket {

/**
 * Base class ChannelElement classes that receive data via RSB
 * listeners.
 */
class IncomingChannelElementBase {
public:
    /**
     * Constructor of RSB listener ChannelElement.
     *
     * Creates a listener for the scope specified in the
     * policy.name_id.
     *
     * @param port Port to which the listener will be connected.
     * @param policy Contains the scope and buffering policy.
     */
    IncomingChannelElementBase(RTT::base::PortInterface* port,
                               const RTT::ConnPolicy& policy);

    virtual ~IncomingChannelElementBase();

    virtual bool inputReady();

protected:
    rsb::Scope       scope;
    rsb::ListenerPtr listener;

    virtual void handle(rsb::EventPtr event) = 0;

private:
    struct HandlerHelper;

    boost::shared_ptr<HandlerHelper> helper;
};

template <typename T>
class IncomingChannelElement: public IncomingChannelElementBase,
                              public RTT::base::ChannelElement<T> {
public:
    IncomingChannelElement(RTT::base::PortInterface* port,
                           const RTT::ConnPolicy& policy)
        : IncomingChannelElementBase(port, policy)  {
        this->ref();
    }

    virtual ~IncomingChannelElement() {} // TODO not executed?

    virtual bool inputReady() {
        return IncomingChannelElementBase::inputReady();
    }

    /**
     * Callback to be registered as handle of the listener.
     *
     * Calls ChannelElement's signal function when events arrive.
     *
     * @param event The received event.
     */
    virtual void handle(rsb::EventPtr event) {
        typename RTT::base::ChannelElement<T>::shared_ptr output
            = this->getOutput();
        if (output) {
            output->write(*boost::static_pointer_cast<T>(event->getData()));
        }
    }
};

}
}
}
