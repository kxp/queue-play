#pragma once
#include <cstdint>
#include <mutex>
#include <thread>
#include "generic-queue.h"
#include "state.h"

class DataAggregator
{
public:
    DataAggregator(GenericQueue<int64_t>& shared_queue, std::condition_variable& app_lock_mutex)
                    : m_queue(shared_queue)
                    , m_app_lock_cv(app_lock_mutex){
        m_current_state = state::NotInitialized;
    }
    ~DataAggregator() {
        m_current_state = state::Terminated;
        // it will hold on the destructor. Maybe detach would better suite the needs.
        if (m_processor_thread.joinable() == true)
            m_processor_thread.join();
    }

    void Start();

private:
    void data_processor() const;

    std::thread m_processor_thread;
    std::condition_variable& m_app_lock_cv;           // Is released after the aggregator ends.

    GenericQueue<int64_t>& m_queue;

    const int32_t m_limit_retry_value = 10;
    state m_current_state;
};
