#ifndef __RTT_RSBCOMM_RSB_ACTIVITY_HPP_
#define __RTT_RSBCOMM_RSB_ACTIVITY_HPP_

#include <rtt/Activity.hpp>
#include <rtt/os/Mutex.hpp>
#include <rtt/os/MutexLock.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <rtt/Logger.hpp>

#include <set>

namespace rtt_rsbcomm {
    namespace transport {

    /**
     * The interface a channel element must implement in
     * order to publish data to a RSB scope.
     */
    struct RSBPublisher
    {
    public:
        /**
         * Publish all data in the channel to a RSB scope.
         */
        virtual void publish()=0;
    };


    /**
     * A process wide thread that handles all publishing of
     * RSB scopes of the current process.
     * There is no strong reason why only one publisher should
     * exist, in later implementations, one publisher thread per
     * channel may exist as well. See the usage recommendations
     * for Instance()
     */
    class RSBPublishActivity : public RTT::Activity
    {
    public:
        typedef boost::shared_ptr<RSBPublishActivity> shared_ptr;

        RSBPublishActivity(const std::string& name);
    private:
        typedef boost::weak_ptr<RSBPublishActivity> weak_ptr;
        //! This pointer may not be refcounted since it would prevent cleanup.
        static weak_ptr rsb_pub_act;

        //! A set keeping track of all publishers in the current
        //! process. It must be guarded by the mutex since
        //! insertion/removal happens concurrently.
        typedef std::set< RSBPublisher* > Publishers;
        typedef Publishers::iterator iterator;
        Publishers publishers;
        RTT::os::Mutex publishers_lock;

        Publishers publishers_always;
        RTT::os::Mutex publishers_always_lock;

        // RSBPublishActivity(const std::string& name);

        void loop();

    public:
        /**
         * Returns the single instance of the RSBPublisher. This function
         * is not thread-safe when it creates the RSBPublisher object.
         * Therefore, it is advised to cache the object which Intance() returns
         * such that, in the unlikely event that two publishers exist,
         * you consistently keep using the same instance, which is fine then.
         */
        static shared_ptr Instance();

        void addPublisher(RSBPublisher* pub);
        void removePublisher(RSBPublisher* pub);

        void addPublisherAlways(RSBPublisher* pub);
        void removePublisherAlways(RSBPublisher* pub);

        void setPublishPeriod(double p);
        double getPublishPeriod();
        double publish_period;

        double last_triggered_time;

        ~RSBPublishActivity();

    };//class
    }//namespace
}
#endif
