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

#include "ScopeService.hpp"

#include <rtt/RTT.hpp>
#include <rtt/internal/GlobalService.hpp>

#include "../constants.hpp"

namespace rtt_rsbcomm {
namespace scope {

RTT::ConnPolicy scope(const std::string& name) {
    RTT::ConnPolicy cp = RTT::ConnPolicy::data();
    // cp.type = RTT::ConnPolicy::UNBUFFERED;
    cp.transport = socket_protocol_id;
    cp.name_id = name;
    cp.init = false;
    cp.pull = false;
    return cp;
}

RTT::ConnPolicy scopeBuffer(const std::string& name, int size) {
    RTT::ConnPolicy cp = RTT::ConnPolicy::buffer(size);
    cp.transport = socket_protocol_id;
    cp.name_id = name;
    cp.init = false;
    cp.pull = false;
    return cp;
}

void loadRSBScopeService() {
    RTT::Service::shared_ptr rsb = RTT::internal::GlobalService::Instance()->provides("rsb");
    RTT::Service::shared_ptr transport = rsb->provides("transport");

    // Scope service for socket transport.
    RTT::Service::shared_ptr socket = transport->provides("socket");

    socket->addConstant("protocol_id", rtt_rsbcomm::socket_protocol_id);

    socket->addOperation("scope", &scope)
        .doc("Creates a ConnPolicy for listening on or publishing to a scope. No buffering is done.")
        .arg("scope", "The RSB scope name");

    socket->addOperation("scopeBuffer", &scopeBuffer)
        .doc("Creates a buffered ConnPolicy for listening on or publishing to a scope.")
        .arg("scope", "The RSB scope name")
        .arg("size", "The size of the buffer");
}

}
}

extern "C" {

    bool loadRTTPlugin(RTT::TaskContext* c) {
        if (c != 0) {
            return false;
        }

        rtt_rsbcomm::scope::loadRSBScopeService();
        return true;
    }

    std::string getRTTPluginName() {
        return "rtt-rsb-scope-service";
    }

    std::string getRTTTargetName() {
        return OROCOS_TARGET_NAME;
    }

}
