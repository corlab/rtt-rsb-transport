/* ============================================================
 *
 * This file is a part of CoSiMA (CogIMon) project
 *
 * Copyright (C) 2020 by Dennis Leroy Wigand <dwigand@techfak.uni-bielefeld.de>
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

#include "SystemLoggingHC.hpp"
#include <rtt/Component.hpp> // needed for the macro at the end of this file

using namespace cosima;

SystemLoggingHC::SystemLoggingHC(std::string const &name) : RTT::TaskContext(name)
{
    
}

bool SystemLoggingHC::configureHook()
{
    // if (in_torques_ports.size() <= 0)
    // {
    //     RTT::log(RTT::Error) << "Before this component can be configured, input ports need to be generated!" << RTT::endlog();
    //     return false;
    // }

    // if (ports()->getPort("out_torques_port"))
    // {
    //     ports()->removePort("out_torques_port");
    // }

    // out_torques_var = rstrt::dynamics::JointTorques(DOFsize);
    // last_out_torques_var = rstrt::dynamics::JointTorques(DOFsize);
    // out_torques_var.torques.setZero();
    // out_torques_port.setName("out_torques_port");
    // out_torques_port.doc("Output port for sending torque values");
    // out_torques_port.setDataSample(out_torques_var);
    // ports()->addPort(out_torques_port);

    // if (ports()->getPort("in_coriolisAndGravity_port"))
    // {
    //     ports()->removePort("in_coriolisAndGravity_port");
    // }
    // in_coriolisAndGravity_var = Eigen::VectorXf::Zero(DOFsize);
    // in_coriolisAndGravity_flow = RTT::NoData;
    // in_coriolisAndGravity_port.setName("in_coriolisAndGravity_port");
    // in_coriolisAndGravity_port.doc("Input port for Gravity and Coriolis joint torques used for fading.");
    // ports()->addPort(in_coriolisAndGravity_port);
    // selected_out_torques_var = rstrt::dynamics::JointTorques(DOFsize);

    // if (ports()->getPort("ev_switch_active_port"))
    // {
    //     ports()->removePort("ev_switch_active_port");
    // }
    // ev_switch_active_port.setName("ev_switch_active_port");
    // ev_switch_active_port.doc("Event port to switch the output");
    // ports()->addEventPort(ev_switch_active_port);

    // maxJerkPerJoint = Eigen::VectorXf::Zero(DOFsize);
    // maxTorquePerJoint = Eigen::VectorXf::Zero(DOFsize);

    // maxJerkPerJoint.fill(1.0);

    // // TODO do not hardcode this!
    // if (DOFsize >= 7) // ARM 1
    // {
    //     maxTorquePerJoint(0) = 176;
    //     maxTorquePerJoint(1) = 176;
    //     maxTorquePerJoint(2) = 100;
    //     maxTorquePerJoint(3) = 100;
    //     maxTorquePerJoint(4) = 100;
    //     maxTorquePerJoint(5) = 30;
    //     maxTorquePerJoint(6) = 30;
    // }
    // if (DOFsize >= 14) // ARM 2
    // {
    //     maxTorquePerJoint(7) = 176;
    //     maxTorquePerJoint(8) = 176;
    //     maxTorquePerJoint(9) = 100;
    //     maxTorquePerJoint(10) = 100;
    //     maxTorquePerJoint(11) = 100;
    //     maxTorquePerJoint(12) = 30;
    //     maxTorquePerJoint(13) = 30;
    // }
    // if (DOFsize >= 20) // OBJ 1
    // {
    //     maxTorquePerJoint(14) = 200;
    //     maxTorquePerJoint(15) = 200;
    //     maxTorquePerJoint(16) = 200;
    //     maxTorquePerJoint(17) = 200;
    //     maxTorquePerJoint(18) = 200;
    //     maxTorquePerJoint(19) = 200;
    // }
    // configured = true;
    // return configured;
}

bool SystemLoggingHC::startHook()
{
    return true;
}

void SystemLoggingHC::updateHook()
{
    // for (unsigned int i = 0; i < in_torques_ports.size(); i++)
    // {
    //     std::shared_ptr<RTT::InputPort<rstrt::dynamics::JointTorques>> tmpPort = in_torques_ports.at(i);
    //     if (tmpPort->connected())
    //     {
    //         in_torques_flows.at(i) = tmpPort->read(in_torques_vars.at(i));
    //     }
    // }

    // // DO NOT SEND ZERO TORQUES!!!! THE ARM WILL FALL DOWN! JUST DO NOT SEND ANYTHING!
    // // THIS MIGHT HAVE BEEN THE ISSUE WHEN THE ROBOT CRASHED INTO THE TABLE!
    // int tmpActivePortId = -1;
    // {
    //     // TODO this is not allowed to wait, in case of a wait it should just proceed with the old value
    //     // Or perhaps use an atomic?
    //     std::lock_guard<std::mutex> lockGuard(mutex);
    //     tmpActivePortId = activePortId;
    // }

    // if (tmpActivePortId < 0)
    // {
    //     return;
    // }

    // if (in_torques_flows.at(tmpActivePortId) == RTT::NoData)
    // {
    //     return;
    // }

    // selected_out_torques_var.torques = in_torques_vars.at(tmpActivePortId).torques;
}

void SystemLoggingHC::stopHook()
{
    // stops the component (update hook wont be  called anymore)
}

void SystemLoggingHC::cleanupHook()
{

}

// double SystemLoggingHC::getOrocosTime()
// {
//     return 1E-9 * RTT::os::TimeService::ticks2nsecs(RTT::os::TimeService::Instance()->getTicks());
// }

//this macro should appear only once per library
ORO_CREATE_COMPONENT_LIBRARY()

// This macro, as you can see, creates the component. Every component should have this!
ORO_LIST_COMPONENT_TYPE(cosima::SystemLoggingHC)
