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

#include <stdexcept>

#include <rtt/types/TypeTransporter.hpp>
#include <rtt/Port.hpp>
#include <rtt/TaskContext.hpp>
#include <rtt/ConnPolicy.hpp>
#include <rtt/Logger.hpp>

#include <rsc/runtime/TypeStringTools.h>

#include "../../util.hpp"

#include "IncomingChannelElement.hpp"
#include "OutgoingChannelElement.hpp"

namespace rtt_rsbcomm {
namespace transport {
namespace socket {

class TransporterBase: public RTT::types::TypeTransporter {
public:
    virtual RTT::base::ChannelElementBase::shared_ptr
    createStream(RTT::base::PortInterface *port,
                 const RTT::ConnPolicy    &policy,
                 bool                      is_sender) const;

protected:
    virtual RTT::base::ChannelElementBase::shared_ptr
    createIncomingStream(RTT::base::PortInterface *port,
                         const RTT::ConnPolicy    &policy) const = 0;

    virtual RTT::base::ChannelElementBase::shared_ptr
    createOutgoingStream(RTT::base::PortInterface *port,
                         const RTT::ConnPolicy    &policy) const = 0;
};

template <typename T>
class Transporter: public TransporterBase {
protected:
    RTT::base::ChannelElementBase::shared_ptr
    createIncomingStream(RTT::base::PortInterface *port,
                         const RTT::ConnPolicy    &policy) const {
        RTT::log(RTT::Debug)
            << "Creating " << rsc::runtime::typeName< IncomingChannelElement<T> >()
            << " for port `" << displayNameForPort(port) << "'"
            << RTT::endlog();

        // Pull semantics are not supported by the RSB message transport.
        if (policy.pull) {
            RTT::log(RTT::Error) << "Pull connections are not supported by the RSB message transport." << RTT::endlog();
            return RTT::base::ChannelElementBase::shared_ptr();
        }

        /*switch (policy.type) {
        case RTT::ConnPolicy::UNBUFFERED:
            RTT::log(RTT::Debug)
                << "Creating unbuffered listener connection for port "
                << port->getName() << ". This may not be real-time safe!"
                << RTT::endlog();
            break;
        default:
            throw std::runtime_error("Only unbuffered mode is supported.");
            }*/

        RTT::base::ChannelElementBase::shared_ptr tmp(new IncomingChannelElement<T>(port, policy));

        // RTT::base::ChannelElementBase::shared_ptr buf(RTT::internal::ConnFactory::buildDataStorage<T>(policy));
        // if (!buf) {
        //     return RTT::base::ChannelElementBase::shared_ptr();
        // }

    #if !RTT_VERSION_GTE(2,8,99)
        RTT::base::ChannelElementBase::shared_ptr buf = RTT::internal::ConnFactory::buildDataStorage<T>(policy);
        if (!buf) return RTT::base::ChannelElementBase::shared_ptr();
        tmp->setOutput(buf);
    #endif
        
        // tmp->setOutput(buf);

        return tmp;
    }

    RTT::base::ChannelElementBase::shared_ptr
    createOutgoingStream(RTT::base::PortInterface *port,
                         const RTT::ConnPolicy    &policy) const {

        // Pull semantics are not supported by the RSB message transport.
        if (policy.pull) {
            RTT::log(RTT::Error) << "Pull connections are not supported by the RSB message transport." << RTT::endlog();
            return RTT::base::ChannelElementBase::shared_ptr();
        }
        
        // RTT::OutputPort<T>* output_port = static_cast<RTT::OutputPort<T>*>(port);
        // T tmp_sample = output_port->getLastWrittenValue();

        // RTT::base::OutputPortInterface* output_port_if = static_cast<RTT::base::OutputPortInterface>(port);

        RTT::base::ChannelElementBase::shared_ptr buf(RTT::internal::ConnFactory::buildDataStorage<T>(policy/*, output_port->getDataSource()*/));
        RTT::base::ChannelElementBase::shared_ptr tmp(new OutgoingChannelElement<T>(port, policy));

        if (!buf) {
            return RTT::base::ChannelElementBase::shared_ptr();
        }

#if RTT_VERSION_GTE(2,8,99)
        buf->connectTo(tmp);
#else
        buf->setOutput(tmp);
#endif
        // tmp->setOutput(buf);
        return buf;
    }
};

}
}
}
