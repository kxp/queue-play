#pragma once
#include <cstdint>
#include <thread>
#include "generic-queue.h"
#include "state.h"

class DataAggregator
{
public:
    DataAggregator(GenericQueue<int32_t>& shared_queue)
                    : m_queue(shared_queue) {
        m_current_state = state::Started;
        m_processor_thread = std::thread(&DataAggregator::data_processor, this);
    }
    ~DataAggregator() {
        m_current_state = state::Terminated;
        // maybe it could be dangerous.
        if (m_processor_thread.joinable() == true)
            m_processor_thread.join();
    }

private:
    void data_processor() const;

    std::thread m_processor_thread;
    GenericQueue<int32_t>& m_queue;

    state m_current_state;
};
