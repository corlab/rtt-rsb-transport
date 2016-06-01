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

#include <rtt/types/TransportPlugin.hpp>
#include <rtt/types/TypekitPlugin.hpp>

#include <rst-rt/kinematics/JointAngles.hpp>

#include "../../constants.hpp"

#include "../../converter/converters.hpp"

#include "Transporter.hpp"

namespace rtt_rsbcomm {
namespace transport {
namespace socket {

struct TransportPlugin : public RTT::types::TransportPlugin {

    bool registerConverters() {
        try {
            RTT::Logger::In in(rsc::runtime::typeName(*this));

            RTT::log(RTT::Debug) << "Registering converters" << RTT::endlog();
            rtt_rsbcomm::converter::registerConverters();
        } catch (const std::exception&) {
            return false;
        }
        return true;
    }

    bool registerTransport(std::string name, RTT::types::TypeInfo* ti) {
        if (name == "rstrt.kinematics.JointAngles") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::kinematics::JointAngles>());
        } else {
            return false;
        }
    }

    std::string getTransportName() const {
        return "rsb+socket";
    }

    std::string getTypekitName() const {
        return "rsb";
    }

    std::string getName() const {
        return std::string("rtt-rsb-socket-transport");
    }

};

}
}
}

namespace RTT { class TaskContext; }

extern "C" {

RTT_EXPORT bool loadRTTPlugin(RTT::TaskContext* tc);
bool loadRTTPlugin(RTT::TaskContext* tc) {
    if (tc == 0) {
        rtt_rsbcomm::transport::socket::TransportPlugin* plugin
            = new rtt_rsbcomm::transport::socket::TransportPlugin();
        RTT::types::TypekitRepository::Import(plugin);
        return plugin->registerConverters();
    }
    return false;
}

RTT_EXPORT std::string getRTTPluginName();
std::string getRTTPluginName() {
    rtt_rsbcomm::transport::socket::TransportPlugin tk;
    return tk.getName();
}

RTT_EXPORT std::string getRTTTargetName();
std::string getRTTTargetName() {
    return OROCOS_TARGET_NAME;
}

}
