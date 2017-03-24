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

#include <rst/geometry/Rotation.pb.h>
#include <rst-rt/geometry/Rotation.hpp>

#include <rst/geometry/Pose.pb.h>
#include <rst-rt/geometry/Pose.hpp>

#include <rst/kinematics/JointAngles.pb.h>
#include <rst-rt/kinematics/JointAngles.hpp>

#include <rst/kinematics/JointVelocities.pb.h>
#include <rst-rt/kinematics/JointVelocities.hpp>

#include <rst/kinematics/JointAccelerations.pb.h>
#include <rst-rt/kinematics/JointAccelerations.hpp>

#include <rst/kinematics/LinearVelocities.pb.h>
#include <rst-rt/kinematics/LinearVelocities.hpp>

#include <rst/kinematics/AngularVelocities.pb.h>
#include <rst-rt/geometry/AngularVelocity.hpp> //TODO change package in rst-rt

#include <rst/kinematics/Twist.pb.h>
#include <rst-rt/kinematics/Twist.hpp>

#include <rst/kinematics/JointJerks.pb.h>
#include <rst-rt/kinematics/JointJerks.hpp>

#include <rst/dynamics/JointTorques.pb.h>
#include <rst-rt/dynamics/JointTorques.hpp>

#include <rst/dynamics/JointImpedance.pb.h>
#include <rst-rt/dynamics/JointImpedance.hpp>

#include <rst/dynamics/Forces.pb.h>
#include <rst-rt/dynamics/Forces.hpp>

#include <rst/dynamics/Torques.pb.h>
#include <rst-rt/dynamics/Torques.hpp>

#include <rst/dynamics/Wrench.pb.h>
#include <rst-rt/dynamics/Wrench.hpp>

#include <rst/robot/JointState.pb.h>
#include <rst-rt/robot/JointState.hpp>

#include <rst/robot/Weights.pb.h>
#include <rst-rt/robot/Weights.hpp>

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
class Helper<rstrt::geometry::Rotation,
             rst::geometry::Rotation> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::geometry::Rotation> datum,
                          boost::shared_ptr<rst::geometry::Rotation>   intermediate) {
        intermediate->set_qw(datum->rotation(0));
        intermediate->set_qx(datum->rotation(1));
        intermediate->set_qy(datum->rotation(2));
        intermediate->set_qz(datum->rotation(3));
        if (!datum->frameId.empty()) {
            intermediate->set_frame_id(datum->frameId);
        }
    }

    void copyForDeSerialize(boost::shared_ptr<rst::geometry::Rotation>   intermediate,
                            boost::shared_ptr<rstrt::geometry::Rotation> datum) {
        datum->rotation(0) = intermediate->qw();
        datum->rotation(1) = intermediate->qx();
        datum->rotation(2) = intermediate->qy();
        datum->rotation(3) = intermediate->qz();
        if (intermediate->has_frame_id()) {
            datum->frameId = intermediate->frame_id();
        }
    }
};

template<>
class Helper<rstrt::geometry::Pose,
             rst::geometry::Pose> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::geometry::Pose> datum,
                          boost::shared_ptr<rst::geometry::Pose>   intermediate) {
    	// Translation
        intermediate->mutable_translation()->set_x(datum->translation.translation(0));
        intermediate->mutable_translation()->set_y(datum->translation.translation(1));
        intermediate->mutable_translation()->set_z(datum->translation.translation(2));
        intermediate->mutable_translation()->set_frame_id(datum->translation.frameId);

        // Rotation
        intermediate->mutable_rotation()->set_qw(datum->rotation.rotation(0));
        intermediate->mutable_rotation()->set_qx(datum->rotation.rotation(1));
        intermediate->mutable_rotation()->set_qy(datum->rotation.rotation(2));
        intermediate->mutable_rotation()->set_qz(datum->rotation.rotation(3));
        intermediate->mutable_rotation()->set_frame_id(datum->rotation.frameId);
    }

    void copyForDeSerialize(boost::shared_ptr<rst::geometry::Pose>   intermediate,
                            boost::shared_ptr<rstrt::geometry::Pose> datum) {
        // Translation
    	datum->translation.translation(0) = intermediate->translation().x();
		datum->translation.translation(1) = intermediate->translation().y();
		datum->translation.translation(2) = intermediate->translation().z();
		if (intermediate->translation().has_frame_id()) {
			datum->translation.frameId = intermediate->translation().frame_id();
		}

        // Rotation
		datum->rotation.rotation(0) = intermediate->rotation().qw();
		datum->rotation.rotation(1) = intermediate->rotation().qx();
		datum->rotation.rotation(2) = intermediate->rotation().qy();
		datum->rotation.rotation(2) = intermediate->rotation().qz();
		if (intermediate->rotation().has_frame_id()) {
			datum->rotation.frameId = intermediate->rotation().frame_id();
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
class Helper<rstrt::kinematics::JointJerks,
             rst::kinematics::JointJerks> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::kinematics::JointJerks> datum,
                          boost::shared_ptr<rst::kinematics::JointJerks>   intermediate) {
        for (int i = 0; i < datum->jerks.size(); ++i) {
            intermediate->add_jerks(datum->jerks(i));
        }
    }

    void copyForDeSerialize(boost::shared_ptr<rst::kinematics::JointJerks>   intermediate,
                            boost::shared_ptr<rstrt::kinematics::JointJerks> datum) {
        datum->jerks.resize(intermediate->jerks().size()) ;
        for (int i = 0; i < intermediate->jerks().size(); ++i) {
            datum->jerks(i) = intermediate->jerks().Get(i);
        }
    }
};

template<>
class Helper<rstrt::kinematics::LinearVelocities,
             rst::kinematics::LinearVelocities> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::kinematics::LinearVelocities> datum,
                          boost::shared_ptr<rst::kinematics::LinearVelocities>   intermediate) {
        intermediate->set_x(datum->linearVelocities(0));
        intermediate->set_y(datum->linearVelocities(1));
        intermediate->set_z(datum->linearVelocities(2));
    }

    void copyForDeSerialize(boost::shared_ptr<rst::kinematics::LinearVelocities>   intermediate,
                            boost::shared_ptr<rstrt::kinematics::LinearVelocities> datum) {
        datum->linearVelocities(0) = intermediate->x();
        datum->linearVelocities(1) = intermediate->y();
        datum->linearVelocities(2) = intermediate->z();
    }
};

template<>
class Helper<rstrt::geometry::AngularVelocity,
             rst::kinematics::AngularVelocities> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::geometry::AngularVelocity> datum,
                          boost::shared_ptr<rst::kinematics::AngularVelocities>   intermediate) {
        intermediate->set_a(datum->angularVelocity(0));
        intermediate->set_b(datum->angularVelocity(1));
        intermediate->set_c(datum->angularVelocity(2));
    }

    void copyForDeSerialize(boost::shared_ptr<rst::kinematics::AngularVelocities>   intermediate,
                            boost::shared_ptr<rstrt::geometry::AngularVelocity> datum) {
        datum->angularVelocity(0) = intermediate->a();
        datum->angularVelocity(1) = intermediate->b();
        datum->angularVelocity(2) = intermediate->c();
    }
};

template<>
class Helper<rstrt::kinematics::Twist,
             rst::kinematics::Twist> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::kinematics::Twist> datum,
                          boost::shared_ptr<rst::kinematics::Twist>   intermediate) {
        // LinearVelocity
        intermediate->mutable_linear()->set_x(datum->linear(0));
        intermediate->mutable_linear()->set_y(datum->linear(1));
        intermediate->mutable_linear()->set_z(datum->linear(2));

        // AngularVelocity
        intermediate->mutable_angular()->set_a(datum->angular(0));
        intermediate->mutable_angular()->set_b(datum->angular(1));
        intermediate->mutable_angular()->set_c(datum->angular(2));
    }

    void copyForDeSerialize(boost::shared_ptr<rst::kinematics::Twist>   intermediate,
                            boost::shared_ptr<rstrt::kinematics::Twist> datum) {
    	// LinearVelocity
    	datum->linear(0) = intermediate->linear().x();
		datum->linear(1) = intermediate->linear().y();
		datum->linear(2) = intermediate->linear().z();

		// AngularVelocity
		datum->angular(0) = intermediate->angular().a();
		datum->angular(1) = intermediate->angular().b();
		datum->angular(2) = intermediate->angular().c();
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
class Helper<rstrt::dynamics::Forces,
             rst::dynamics::Forces> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::dynamics::Forces> datum,
                          boost::shared_ptr<rst::dynamics::Forces>   intermediate) {
        intermediate->set_x(datum->forces(0));
        intermediate->set_y(datum->forces(1));
        intermediate->set_z(datum->forces(2));
    }

    void copyForDeSerialize(boost::shared_ptr<rst::dynamics::Forces>   intermediate,
                            boost::shared_ptr<rstrt::dynamics::Forces> datum) {
        datum->forces(0) = intermediate->x();
        datum->forces(1) = intermediate->y();
        datum->forces(2) = intermediate->z();
    }
};

template<>
class Helper<rstrt::dynamics::Torques,
             rst::dynamics::Torques> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::dynamics::Torques> datum,
                          boost::shared_ptr<rst::dynamics::Torques>   intermediate) {
        intermediate->set_a(datum->torques(0));
        intermediate->set_b(datum->torques(1));
        intermediate->set_c(datum->torques(2));
    }

    void copyForDeSerialize(boost::shared_ptr<rst::dynamics::Torques>   intermediate,
                            boost::shared_ptr<rstrt::dynamics::Torques> datum) {
        datum->torques(0) = intermediate->a();
        datum->torques(1) = intermediate->b();
        datum->torques(2) = intermediate->c();
    }
};

template<>
class Helper<rstrt::dynamics::Wrench,
             rst::dynamics::Wrench> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::dynamics::Wrench> datum,
                          boost::shared_ptr<rst::dynamics::Wrench>   intermediate) {
        // Forces
        intermediate->mutable_forces()->set_x(datum->forces(0));
        intermediate->mutable_forces()->set_y(datum->forces(1));
        intermediate->mutable_forces()->set_z(datum->forces(2));

        // Torques
        intermediate->mutable_torques()->set_a(datum->torques(0));
        intermediate->mutable_torques()->set_b(datum->torques(1));
        intermediate->mutable_torques()->set_c(datum->torques(2));
    }

    void copyForDeSerialize(boost::shared_ptr<rst::dynamics::Wrench>   intermediate,
                            boost::shared_ptr<rstrt::dynamics::Wrench> datum) {
        // Forces
    	datum->forces(0) = intermediate->forces().x();
		datum->forces(1) = intermediate->forces().y();
		datum->forces(2) = intermediate->forces().z();

        // Torques
		datum->torques(0) = intermediate->torques().a();
		datum->torques(1) = intermediate->torques().b();
		datum->torques(2) = intermediate->torques().c();
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

template<>
class Helper<rstrt::robot::Weights,
             rst::robot::Weights> {
public:
    void copyForSerialize(boost::shared_ptr<rstrt::robot::Weights> datum,
                          boost::shared_ptr<rst::robot::Weights>   intermediate) {
        for (int i = 0; i < datum->weights.size(); ++i) {
            intermediate->add_weights(datum->weights(i));
        }

    }

    void copyForDeSerialize(boost::shared_ptr<rst::robot::Weights>   intermediate,
                            boost::shared_ptr<rstrt::robot::Weights> datum) {
        datum->weights.resize(intermediate->weights().size()) ;
        for (int i = 0; i < intermediate->weights().size(); ++i) {
            datum->weights(i) = intermediate->weights().Get(i);
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
    registerConverter<rstrt::geometry::Rotation,
                      rst::geometry::Rotation>();
    registerConverter<rstrt::geometry::Pose,
                      rst::geometry::Pose>();

    registerConverter<rstrt::kinematics::JointAngles,
                      rst::kinematics::JointAngles>();
    registerConverter<rstrt::kinematics::JointVelocities,
                      rst::kinematics::JointVelocities>();
    registerConverter<rstrt::kinematics::JointAccelerations,
                      rst::kinematics::JointAccelerations>();
    registerConverter<rstrt::kinematics::JointJerks,
                      rst::kinematics::JointJerks>();
    registerConverter<rstrt::kinematics::LinearVelocities,
                      rst::kinematics::LinearVelocities>();
    registerConverter<rstrt::geometry::AngularVelocity,
                      rst::kinematics::AngularVelocities>();
    registerConverter<rstrt::kinematics::Twist,
                      rst::kinematics::Twist>();

    registerConverter<rstrt::dynamics::JointTorques,
                      rst::dynamics::JointTorques>();
    registerConverter<rstrt::dynamics::JointImpedance,
                      rst::dynamics::JointImpedance>();

    registerConverter<rstrt::robot::JointState,
                      rst::robot::JointState>();
    registerConverter<rstrt::robot::Weights,
                      rst::robot::Weights>();
}

}
}
