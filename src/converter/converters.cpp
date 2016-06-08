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

#include "converters.hpp"

#include <rtt/Logger.hpp>

#include <rsb/converter/Repository.h>
#include <rsb/converter/Converter.h>

#include <rst/geometry/Translation.pb.h>
#include <rst-rt/geometry/Translation.hpp>

#include <rst/kinematics/JointAngles.pb.h>
#include <rst-rt/kinematics/JointAngles.hpp>

#include <rst/kinematics/JointVelocities.pb.h>
#include <rst-rt/kinematics/JointVelocities.hpp>

#include <rst/kinematics/JointAccelerations.pb.h>
#include <rst-rt/kinematics/JointAccelerations.hpp>

#include <rst/dynamics/JointTorques.pb.h>
#include <rst-rt/dynamics/JointTorques.hpp>

#include <rst/dynamics/JointImpedance.pb.h>
#include <rst-rt/dynamics/JointImpedance.hpp>

#include <rst/robot/JointState.pb.h>
#include <rst-rt/robot/JointState.hpp>

#include "Converter.hpp"

namespace rtt_rsbcomm {
namespace converter {

template<>
class Helper<rstrt::geometry::Translation,
             rst::geometry::Translation> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::geometry::Translation> datum,
                          boost::shared_ptr<rst::geometry::Translation>   intermediate) {
        intermediate->set_x(datum->translation(0));
        intermediate->set_y(datum->translation(1));
        intermediate->set_z(datum->translation(2));
        if (!datum->frameId.empty()) {
            intermediate->set_frame_id(datum->frameId);
        }
    }

    void copyForDeSerialize(boost::shared_ptr<rst::geometry::Translation>   intermediate,
                            boost::shared_ptr<rstrt::geometry::Translation> datum) {
        datum->translation(0) = intermediate->x();
        datum->translation(1) = intermediate->y();
        datum->translation(2) = intermediate->z();
        if (intermediate->has_frame_id()) {
            datum->frameId = intermediate->frame_id();
        }
    }
};

template<>
class Helper<rstrt::kinematics::JointAngles,
             rst::kinematics::JointAngles> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::kinematics::JointAngles> datum,
                          boost::shared_ptr<rst::kinematics::JointAngles>   intermediate) {
        for (int i = 0; i < datum->angles.size(); ++i) {
            intermediate->add_angles(datum->angles(i));
        }
    }

    void copyForDeSerialize(boost::shared_ptr<rst::kinematics::JointAngles>   intermediate,
                            boost::shared_ptr<rstrt::kinematics::JointAngles> datum) {
        datum->angles.resize(intermediate->angles().size()) ;
        for (int i = 0; i < intermediate->angles().size(); ++i) {
            datum->angles(i) = intermediate->angles().Get(i);
        }
    }
};

template<>
class Helper<rstrt::kinematics::JointVelocities,
             rst::kinematics::JointVelocities> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::kinematics::JointVelocities> datum,
                          boost::shared_ptr<rst::kinematics::JointVelocities>   intermediate) {
        for (int i = 0; i < datum->velocities.size(); ++i) {
            intermediate->add_velocities(datum->velocities(i));
        }
    }

    void copyForDeSerialize(boost::shared_ptr<rst::kinematics::JointVelocities>   intermediate,
                            boost::shared_ptr<rstrt::kinematics::JointVelocities> datum) {
        datum->velocities.resize(intermediate->velocities().size()) ;
        for (int i = 0; i < intermediate->velocities().size(); ++i) {
            datum->velocities(i) = intermediate->velocities().Get(i);
        }
    }
};

template<>
class Helper<rstrt::kinematics::JointAccelerations,
             rst::kinematics::JointAccelerations> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::kinematics::JointAccelerations> datum,
                          boost::shared_ptr<rst::kinematics::JointAccelerations>   intermediate) {
        for (int i = 0; i < datum->accelerations.size(); ++i) {
            intermediate->add_accelerations(datum->accelerations(i));
        }
    }

    void copyForDeSerialize(boost::shared_ptr<rst::kinematics::JointAccelerations>   intermediate,
                            boost::shared_ptr<rstrt::kinematics::JointAccelerations> datum) {
        datum->accelerations.resize(intermediate->accelerations().size()) ;
        for (int i = 0; i < intermediate->accelerations().size(); ++i) {
            datum->accelerations(i) = intermediate->accelerations().Get(i);
        }
    }
};

template<>
class Helper<rstrt::dynamics::JointTorques,
             rst::dynamics::JointTorques> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::dynamics::JointTorques> datum,
                          boost::shared_ptr<rst::dynamics::JointTorques>   intermediate) {
        for (int i = 0; i < datum->torques.size(); ++i) {
            intermediate->add_torques(datum->torques(i));
        }
    }

    void copyForDeSerialize(boost::shared_ptr<rst::dynamics::JointTorques>   intermediate,
                            boost::shared_ptr<rstrt::dynamics::JointTorques> datum) {
        datum->torques.resize(intermediate->torques().size()) ;
        for (int i = 0; i < intermediate->torques().size(); ++i) {
            datum->torques(i) = intermediate->torques().Get(i);
        }
    }
};

template<>
class Helper<rstrt::dynamics::JointImpedance,
             rst::dynamics::JointImpedance> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::dynamics::JointImpedance> datum,
                          boost::shared_ptr<rst::dynamics::JointImpedance>   intermediate) {
        for (int i = 0; i < datum->stiffness.size(); ++i) {
            intermediate->add_stiffness(datum->stiffness(i));
        }

        for (int i = 0; i < datum->damping.size(); ++i) {
            intermediate->add_damping(datum->damping(i));
        }
    }

    void copyForDeSerialize(boost::shared_ptr<rst::dynamics::JointImpedance>   intermediate,
                            boost::shared_ptr<rstrt::dynamics::JointImpedance> datum) {
        datum->stiffness.resize(intermediate->stiffness().size()) ;
        for (int i = 0; i < intermediate->stiffness().size(); ++i) {
            datum->stiffness(i) = intermediate->stiffness().Get(i);
        }

        datum->damping.resize(intermediate->damping().size()) ;
        for (int i = 0; i < intermediate->damping().size(); ++i) {
            datum->damping(i) = intermediate->damping().Get(i);
        }
    }
};

template<>
class Helper<rstrt::robot::JointState,
             rst::robot::JointState> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::robot::JointState> datum,
                          boost::shared_ptr<rst::robot::JointState>   intermediate) {
        // Angles
        for (int i = 0; i < datum->angles.size(); ++i) {
            intermediate->mutable_angles()->add_angles(datum->angles(i));
        }
        // Velocities
        for (int i = 0; i < datum->velocities.size(); ++i) {
            intermediate->mutable_velocities()->add_velocities(datum->velocities(i));
        }
        // Torques
        for (int i = 0; i < datum->torques.size(); ++i) {
            intermediate->mutable_torques()->add_torques(datum->torques(i));
        }

    }

    void copyForDeSerialize(boost::shared_ptr<rst::robot::JointState>   intermediate,
                            boost::shared_ptr<rstrt::robot::JointState> datum) {
        // Angles
        datum->angles.resize(intermediate->angles().angles().size()) ;
        for (int i = 0; i < intermediate->angles().angles().size(); ++i) {
            datum->angles(i) = intermediate->angles().angles().Get(i);
        }

        // Velocities
        datum->velocities.resize(intermediate->velocities().velocities().size()) ;
        for (int i = 0; i < intermediate->velocities().velocities().size(); ++i) {
            datum->velocities(i) = intermediate->velocities().velocities().Get(i);
        }
        // Torques
        datum->torques.resize(intermediate->torques().torques().size()) ;
        for (int i = 0; i < intermediate->torques().torques().size(); ++i) {
            datum->torques(i) = intermediate->torques().torques().Get(i);
        }

    }
};

template <typename T, typename I>
void registerConverter() {
    RTT::Logger::In in("rtt_rsbcomm::transport::socket::registerConverter");

    rsb::converter::Converter<std::string>::Ptr
        converter(new Converter<T, I>());

    RTT::log(RTT::Debug)
        << "Registering converter " << converter << RTT::endlog();

    rsb::converter::converterRepository<std::string>()
        ->registerConverter (converter);
}

void registerConverters() {
    registerConverter<rstrt::geometry::Translation,
                      rst::geometry::Translation>();

    registerConverter<rstrt::kinematics::JointAngles,
                      rst::kinematics::JointAngles>();
    registerConverter<rstrt::kinematics::JointVelocities,
                      rst::kinematics::JointVelocities>();
    registerConverter<rstrt::kinematics::JointAccelerations,
                      rst::kinematics::JointAccelerations>();

    registerConverter<rstrt::dynamics::JointTorques,
                      rst::dynamics::JointTorques>();
    registerConverter<rstrt::dynamics::JointImpedance,
                      rst::dynamics::JointImpedance>();

    registerConverter<rstrt::robot::JointState,
                      rst::robot::JointState>();
}

}
}
