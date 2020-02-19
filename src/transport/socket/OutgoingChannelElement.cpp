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

#include "OutgoingChannelElement.hpp"

#include <rtt/TaskContext.hpp>

#include <rsc/runtime/TypeStringTools.h>

#include <rsb/Factory.h>

#include <rsb/converter/UnambiguousConverterMap.h>

#include <rsb/converter/IntegerConverter.h>

#include "../../util.hpp"

namespace rtt_rsbcomm {
namespace transport {
namespace socket {

OutgoingChannelElementBase::OutgoingChannelElementBase(RTT::base::PortInterface *port,
                                                       const RTT::ConnPolicy    &policy) : last_triggered_time(0.0) {
    double period = 0;
    if (policy.name_id.rfind("#", 0) == 0) {
        // we have to deal with a timed connection
        std::string transform_str = policy.name_id;
        transform_str.erase(0,1);

        size_t found = transform_str.find("#"); 
        if (found != std::string::npos) {
            // get substring and convert to double
            period = std::stod(transform_str.substr(0, found));
            // erase substring plus last # to get the real name
            transform_str.erase(0,found+1);
        } else {
            RTT::log(RTT::Error)
            << "Something cannot be parsed regarding " << policy.name_id << ": `"
            <<  displayNameForPort(port)
            << "' on scope " << transform_str << " !!!!!!!!!!!!!!!!!!"
            << RTT::endlog();
        }
        this->scope = transform_str;
    } else {
        this->scope = policy.name_id;
    }
    RTT::Logger::In in(std::string("OCE_") + this->scope.toString());

    RTT::log(RTT::Info)
        << "Creating RSB informer for port `"
        <<  displayNameForPort(port)
        << "' on scope " << this->scope
        << RTT::endlog();

    // rsb::ParticipantConfig config = rsb::getFactory().getDefaultParticipantConfig();

    // std::set<rsb::ParticipantConfig::Transport> transports = config.getTransports();

    // for (std::set<rsb::ParticipantConfig::Transport>::const_iterator it = transports.begin(); it != transports.end(); ++it) {

    //     rsb::ParticipantConfig::Transport& transport = config.mutableTransport(it->getName());

    //     // rsc::runtime::Properties& options = transport.mutableOptions();

    //     // rsb::ParticipantConfig::Transport::ConverterNames cNames = transport.getConverters();

    //     // cNames.insert(std::make_pair("int", boost::shared_ptr<typename rsb::converter::Converter<std::string> >(new rsb::converter::Int64Converter())));

    //     std::vector<std::string> tmp_vec;
    //     tmp_vec.push_back("converter");
    //     tmp_vec.push_back("cpp");
    //     tmp_vec.push_back("int");
    //     transport.handleOption(tmp_vec, "int64");

    //     // options.get<rsb::converter::UnambiguousConverterMap<std::string> >("converters").addConverter("int", boost::shared_ptr<typename rsb::converter::Converter<std::string> >(new rsb::converter::Int64Converter()));
    // }

    this->informer = rsb::getFactory().createInformer<rsb::AnyType>(this->scope);

    act = RSBPublishActivity::Instance();
    // act = boost::shared_ptr<RSBPublishActivity>(new RSBPublishActivity(displayNameForPort(port) + std::string("->") + this->scope.toString()));

    act->setPublishPeriod(period);
}

OutgoingChannelElementBase::~OutgoingChannelElementBase() {
    RTT::Logger::In in(this->scope.toString());

    RTT::log(RTT::Debug)
        << "Destroying " << rsc::runtime::typeName(*this)
        << " on scope " << this->scope
        << RTT::endlog();
    act->removePublisher(this);
    // act->reset(...)?
}

bool OutgoingChannelElementBase::inputReady() {
    return true;
}

}
}
}
