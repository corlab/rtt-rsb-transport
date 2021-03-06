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

#pragma once

#include <rsb/converter/Converter.h>
#include <rsb/converter/ProtocolBufferConverter.h>

namespace rtt_rsbcomm {
namespace converter {

template <typename T,
          typename I>
class Helper {
public:
    void copyForSerialize(boost::shared_ptr<T> datum,
                          boost::shared_ptr<I> intermediate);

    void copyForDeSerialize(boost::shared_ptr<I> intermediate,
                            boost::shared_ptr<I> datum);

};

template <typename T,
          typename I>
class Converter: public rsb::converter::Converter<std::string> {
public:
    Converter()
        : rsb::converter::Converter<std::string>
        (rsc::runtime::typeName<T>(),
         rsb::converter::ProtocolBufferConverter<I>().getWireSchema(),
         true) {
    }

    std::string serialize(const rsb::AnnotatedData& data,
                          std::string&              wire) {
        boost::shared_ptr<T> temp(boost::static_pointer_cast<T>(data.second));
        boost::shared_ptr<I> datum(new I());
        this->helper.copyForSerialize(temp, datum);
        return this->converter.serialize
            (rsb::AnnotatedData(rsc::runtime::typeName<I>(), datum), wire);
    }

    rsb::AnnotatedData deserialize(const std::string& wireSchema,
                                   const std::string& wire) {
        rsb::AnnotatedData intermediate
            = this->converter.deserialize(wireSchema, wire);
        boost::shared_ptr<I> temp(boost::static_pointer_cast<I>
                                  (intermediate.second));
        boost::shared_ptr<T> datum(new T());
        this->helper.copyForDeSerialize(temp, datum);
        return rsb::AnnotatedData(intermediate.first, datum);
    }
private:
    rsb::converter::ProtocolBufferConverter<I> converter;
    Helper<T, I>                               helper;
};

}
}
