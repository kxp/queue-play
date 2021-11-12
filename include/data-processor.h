#pragma once
#include <cstdint>
#include <thread>
#include <vector>
#include "state.h"
#include "generic-queue.h"

class DataProcessor
{
public:
    DataProcessor(GenericQueue<std::vector<int32_t>>& producer_queue, GenericQueue<int32_t>& consumer_queue)
                : m_source_data_queue(producer_queue)
                , m_destination_queue(consumer_queue) {
        m_current_state = state::Started;
        m_processor_thread = std::thread(&DataProcessor::data_processor, this);
    }
    ~DataProcessor() {
        m_current_state = state::Terminated;
        // maybe it could be dangerous.
        if (m_processor_thread.joinable() == true)
            m_processor_thread.join();
    }

private:

    void data_processor() const;

    GenericQueue<std::vector<int32_t>>& m_source_data_queue;
    GenericQueue<int32_t>& m_destination_queue;

    std::thread m_processor_thread;

    state m_current_state;


};
