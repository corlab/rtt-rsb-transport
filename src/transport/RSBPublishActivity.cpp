#include "RSBPublishActivity.hpp"

namespace rtt_rsbcomm {
    namespace transport {

        using namespace RTT;

        RSBPublishActivity::weak_ptr RSBPublishActivity::rsb_pub_act;

        RSBPublishActivity::RSBPublishActivity( const std::string& name)
        : Activity(ORO_SCHED_RT, RTT::os::LowestPriority, 0.0, 0, name) {
            Logger::In in("RSBPublishActivity");
            log(Debug)<<"Creating RSBPublishActivity"<<endlog();
        }

        void RSBPublishActivity::loop(){
            os::MutexLock lock(publishers_lock);
            for(iterator it = publishers.begin(); it != publishers.end(); ++it) {
                (*it)->publish();
            }
        }

        RSBPublishActivity::shared_ptr RSBPublishActivity::Instance() {
        shared_ptr ret = rsb_pub_act.lock();
        if ( !ret ) {
            ret.reset(new RSBPublishActivity("RSBPublishActivity"));
            rsb_pub_act = ret;
            ret->start();
        }
        return ret;
        }

        void RSBPublishActivity::addPublisher(RSBPublisher* pub) {
            os::MutexLock lock(publishers_lock);
            publishers.insert(pub);
        }

        void RSBPublishActivity::removePublisher(RSBPublisher* pub) {
            os::MutexLock lock(publishers_lock);
            publishers.erase(pub);
        }

        RSBPublishActivity::~RSBPublishActivity() {
            Logger::In in("RSBPublishActivity");
            log(Info) << "RSBPublishActivity cleans up: no more work."<<endlog();
            stop();
        }

    }
}