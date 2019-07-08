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

#include <rst-rt/geometry/Translation.hpp>
#include <rst-rt/geometry/Rotation.hpp>
#include <rst-rt/geometry/Pose.hpp>

#include <rst-rt/kinematics/JointAngles.hpp>
#include <rst-rt/kinematics/JointVelocities.hpp>
#include <rst-rt/kinematics/JointAccelerations.hpp>
#include <rst-rt/kinematics/JointJerks.hpp>
#include <rst-rt/kinematics/LinearVelocities.hpp>
#include <rst-rt/geometry/AngularVelocity.hpp>
#include <rst-rt/kinematics/Twist.hpp>

#include <rst-rt/dynamics/JointTorques.hpp>
#include <rst-rt/dynamics/JointImpedance.hpp>
#include <rst-rt/dynamics/Forces.hpp>
#include <rst-rt/dynamics/Torques.hpp>
#include <rst-rt/dynamics/Wrench.hpp>

#include <rst-rt/robot/JointState.hpp>
#include <rst-rt/robot/Weights.hpp>
#include <rst-rt/robot/ForceApplication.hpp>

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
        // Primitive types.
        /*if (name == "void") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<void>());
        } else*/ if (name == "bool") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<bool>());
        } else if (name == "char") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<char>());
        } else if (name == "int") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<long>());
        } else if (name == "uint") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<unsigned long>());
        } else if (name == "double") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<double>());
        } else if (name == "float") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<float>());
        }
        else if (name == "string") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<std::string>());
        } /*else if (name == "rt_string") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<unsigned int>());
        }*/

        // RST-RT types.
        if (name == "rstrt.geometry.Translation") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::geometry::Translation>());
        } else if (name == "rstrt.geometry.Rotation") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::geometry::Rotation>());
        } else if (name == "rstrt.geometry.Pose") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::geometry::Pose>());
        }

        if (name == "rstrt.kinematics.JointAngles") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::kinematics::JointAngles>());
        } else if (name == "rstrt.kinematics.JointVelocities") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::kinematics::JointVelocities>());
        } else if (name == "rstrt.kinematics.JointAccelerations") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::kinematics::JointAccelerations>());
        } else if (name == "rstrt.kinematics.JointJerks") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::kinematics::JointJerks>());
        } else if (name == "rstrt.kinematics.LinearVelocities") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::kinematics::LinearVelocities>());
        } else if (name == "rstrt.geometry.AngularVelocity") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::geometry::AngularVelocity>());
        } else if (name == "rstrt.kinematics.Twist") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::kinematics::Twist>());
        }

        if (name == "rstrt.dynamics.JointTorques") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::dynamics::JointTorques>());
        } else if (name == "rstrt.dynamics.JointImpedance") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::dynamics::JointImpedance>());
        } else if (name == "rstrt.dynamics.Forces") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::dynamics::Forces>());
        } else if (name == "rstrt.dynamics.Torques") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::dynamics::Torques>());
        } else if (name == "rstrt.dynamics.Wrench") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::dynamics::Wrench>());
        }

        if (name == "rstrt.robot.JointState") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::robot::JointState>());
        } else if (name == "rstrt.robot.Weights") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::robot::Weights>());
        } else if (name == "rstrt.robot.ForceApplication") {
            return ti->addProtocol(ORO_RSB_SOCKET_PROTOCOL_ID,
                                   new socket::Transporter<rstrt::robot::ForceApplication>());
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
