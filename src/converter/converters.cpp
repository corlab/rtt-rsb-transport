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

#include "Converter.hpp"

namespace rtt_rsbcomm {
namespace converter {

template <typename T, typename I>
void registerConverter() {
    rsb::converter::converterRepository<std::string>()->registerConverter
        (rsb::converter::Converter<std::string>::Ptr(new Converter<T, I>()));
}

void registerConverters() {
    registerConverter<rstrt::kinematics::JointAngles,
                      rst::kinematics::JointAngles>();
}

}
}
