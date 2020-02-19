#include "RSBPublishActivity.hpp"

namespace rtt_rsbcomm {
    namespace transport {

        using namespace RTT;

        RSBPublishActivity::weak_ptr RSBPublishActivity::rsb_pub_act;

        RSBPublishActivity::RSBPublishActivity(const std::string& name)
        : Activity(ORO_SCHED_RT, RTT::os::LowestPriority, 0.0, 7, 0, name), publish_period(0.0) {
            Logger::In in(name);
            log(Info) << "Creating RSBPublishActivity: " << name << endlog();
            this->last_triggered_time = 0.0;
        }

        void RSBPublishActivity::loop() {
            if ((((1E-9 * RTT::os::TimeService::ticks2nsecs(RTT::os::TimeService::Instance()->getTicks())) - this->last_triggered_time) > this->publish_period) || (this->publish_period == 0.0)) {
                {
                    os::MutexLock lock(publishers_lock);
                    for(iterator it = publishers.begin(); it != publishers.end(); ++it) {
                        (*it)->publish();
                    }
                }
                this->last_triggered_time = 1E-9 * RTT::os::TimeService::ticks2nsecs(RTT::os::TimeService::Instance()->getTicks());
            } else {
                os::MutexLock lock(publishers_always_lock);
                for(iterator it = publishers_always.begin(); it != publishers_always.end(); ++it) {
                    (*it)->publish();
                }
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

        void RSBPublishActivity::addPublisherAlways(RSBPublisher* pub) {
            log(Info) << "Add RSBPublisher that always publishes" << endlog();
            os::MutexLock lock(publishers_always_lock);
            publishers_always.insert(pub);
        }

        void RSBPublishActivity::removePublisherAlways(RSBPublisher* pub) {
            log(Info) << "Remove RSBPublisher that always publishes" << endlog();
            os::MutexLock lock(publishers_always_lock);
            publishers_always.erase(pub);
        }

        RSBPublishActivity::~RSBPublishActivity() {
            Logger::In in("RSBPublishActivity");
            log(Info) << "RSBPublishActivity cleans up: no more work." << endlog();
            stop();
        }

        void RSBPublishActivity::setPublishPeriod(double p) {
            // this->setPeriod(p);
            if (this->publish_period == 0.0) {
                this->publish_period = p;
            }
        }

        double RSBPublishActivity::getPublishPeriod() {
            // return this->getPeriod();
            return this->publish_period;
        }
    }
}