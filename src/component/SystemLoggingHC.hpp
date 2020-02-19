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

#pragma once

#include <rtt/Port.hpp>
#include <rtt/TaskContext.hpp>
#include <string>
#include <rst-rt/dynamics/JointTorques.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <mutex>

namespace cosima
{

class SystemLoggingHC : public RTT::TaskContext
{
public:
  SystemLoggingHC(std::string const &name);

  bool configureHook();
  bool startHook();
  void updateHook();
  void stopHook();
  void cleanupHook();

private:
  // Vector of input ports.
  std::vector<std::shared_ptr<RTT::InputPort<rstrt::dynamics::JointTorques>>> in_torques_ports;
  std::vector<RTT::FlowStatus> in_torques_flows;
  std::vector<rstrt::dynamics::JointTorques> in_torques_vars;

  // Event port to switch the output
  RTT::InputPort<int> ev_switch_active_port;

  // Gravity port for fadeing
  RTT::InputPort<Eigen::VectorXf> in_coriolisAndGravity_port;
  Eigen::VectorXf in_coriolisAndGravity_var;
  RTT::FlowStatus in_coriolisAndGravity_flow;
  int newPortId;
  double startFadeTime;
  float fadeDuration;
  rstrt::dynamics::JointTorques selected_out_torques_var;

  // Output port for the current active input port.
  RTT::OutputPort<rstrt::dynamics::JointTorques> out_torques_port;
  rstrt::dynamics::JointTorques out_torques_var;
  rstrt::dynamics::JointTorques last_out_torques_var;

  Eigen::VectorXf maxJerkPerJoint, maxTorquePerJoint;
};

} // namespace cosima