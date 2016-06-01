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

#include <rsb/converter/Repository.h>
#include <rsb/converter/Converter.h>

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

#include "Converter.hpp"

namespace rtt_rsbcomm {
namespace converter {

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

template <typename T, typename I>
void registerConverter() {
    rsb::converter::converterRepository<std::string>()->registerConverter
        (rsb::converter::Converter<std::string>::Ptr(new Converter<T, I>()));
}

void registerConverters() {
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
}

}
}
