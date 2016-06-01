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

#include <rst/dynamics/JointTorques.pb.h>
#include <rst-rt/dynamics/JointTorques.hpp>

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

template <typename T, typename I>
void registerConverter() {
    rsb::converter::converterRepository<std::string>()->registerConverter
        (rsb::converter::Converter<std::string>::Ptr(new Converter<T, I>()));
}

void registerConverters() {
    registerConverter<rstrt::kinematics::JointAngles,
                      rst::kinematics::JointAngles>();
    registerConverter<rstrt::dynamics::JointTorques,
                      rst::dynamics::JointTorques>();
}

}
}
