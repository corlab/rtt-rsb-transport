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

#include "IncomingChannelElement.hpp"

#include <boost/bind.hpp>

#include <rtt/TaskContext.hpp>

#include <rsc/runtime/TypeStringTools.h>

#include <rsb/Factory.h>
#include <rsb/Handler.h>

#include "../../util.hpp"

namespace rtt_rsbcomm {
namespace transport {
namespace socket {

// This helper is necessary because rsb::Listener::addHandler only
// accepts shared_ptrs but the IncomingChannelElement[Base] instance
// cannot obtain a shared_ptr to itself during construction.
struct IncomingChannelElementBase::HandlerHelper : public rsb::Handler {
    IncomingChannelElementBase* parent;

    HandlerHelper(IncomingChannelElementBase* parent)
        : parent(parent) {
    }

    void handle(rsb::EventPtr event) {
        parent->handle(event);
    }
};

IncomingChannelElementBase::IncomingChannelElementBase(RTT::base::PortInterface* port,
                                                       const RTT::ConnPolicy& policy)
    : scope(policy.name_id),
      helper(new IncomingChannelElementBase::HandlerHelper(this)) {
    RTT::Logger::In in(rsc::runtime::typeName(*this)
                       + " " + this->scope.toString());

    RTT::log(RTT::Debug)
        << "Creating RSB listener for port `"
        << displayNameForPort(port)
        << "' on scope " << this->scope.toString()
        << RTT::endlog();

    this->listener = rsb::getFactory().createListener(this->scope);
    this->listener->addHandler(rsb::HandlerPtr(this->helper));
}

IncomingChannelElementBase::~IncomingChannelElementBase() {
    RTT::Logger::In in(this->scope.toString());

    RTT::log(RTT::Debug)
        << "Destroying RSB listener on scope " << this->scope.toString()
        << RTT::endlog();

    this->listener->removeHandler(this->helper);
    this->listener.reset();
}

bool IncomingChannelElementBase::inputReady() {
    return true;
}

}
}
}
