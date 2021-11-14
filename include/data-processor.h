#pragma once
#include <cstdint>
#include <thread>
#include <vector>
#include "state.h"
#include "generic-queue.h"

class DataProcessor
{
public:
    DataProcessor(GenericQueue<std::vector<int64_t>>& producer_queue, GenericQueue<int64_t>& consumer_queue)
                : m_source_data_queue(producer_queue)
                , m_destination_queue(consumer_queue) {
        m_current_state = state::NotInitialized;
    }
    ~DataProcessor() {
        m_current_state = state::Terminated;
        // maybe it could be dangerous.
        if (m_processor_thread.joinable() == true)
            m_processor_thread.join();
    }
    void Start();

private:

    void data_processor() const;

    const int32_t m_limit_retry_value = 10;

    GenericQueue<std::vector<int64_t>>& m_source_data_queue;
    GenericQueue<int64_t>& m_destination_queue;

    std::thread m_processor_thread;
    state m_current_state;
};
