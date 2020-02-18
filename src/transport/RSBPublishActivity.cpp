#include "RSBPublishActivity.hpp"

namespace rtt_rsbcomm {
    namespace transport {

        using namespace RTT;

        RSBPublishActivity::weak_ptr RSBPublishActivity::rsb_pub_act;

        RSBPublishActivity::RSBPublishActivity(const std::string& name)
        : Activity(ORO_SCHED_RT, RTT::os::LowestPriority, 0.0, 0, name), publish_period(0.0) {
            Logger::In in(name);
            log(Info) << "Creating RSBPublishActivity: " << name << endlog();
        }

        void RSBPublishActivity::loop() {
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
            log(Info) << "Add RSBPublisher" << endlog();
            os::MutexLock lock(publishers_lock);
            publishers.insert(pub);
        }

        void RSBPublishActivity::removePublisher(RSBPublisher* pub) {
            log(Info) << "Remove RSBPublisher" << endlog();
            os::MutexLock lock(publishers_lock);
            publishers.erase(pub);
        }

        RSBPublishActivity::~RSBPublishActivity() {
            Logger::In in("RSBPublishActivity");
            log(Info) << "RSBPublishActivity cleans up: no more work." << endlog();
            stop();
        }

        void RSBPublishActivity::setPublishPeriod(double p) {
            // this->setPeriod(p);
            this->publish_period = p;
        }

        double RSBPublishActivity::getPublishPeriod() {
            // return this->getPeriod();
            return this->publish_period;
        }
    }
}