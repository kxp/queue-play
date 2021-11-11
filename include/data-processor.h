#pragma once
#include <cstdint>
#include <vector>

#include "state.h"
#include "generic-queue.h"

class DataProcessor
{
public:
    DataProcessor(GenericQueue<std::vector<int32_t>>& producer_queue, GenericQueue<int32_t>& consumer_queue)
                : m_source_data_queue(producer_queue)
                , m_destination_queue(consumer_queue)
    {
        //already initialized
        m_current_state = state::NotInitialized;
    }

private:
    GenericQueue<std::vector<int32_t>>& m_source_data_queue;
    GenericQueue<int32_t>& m_destination_queue;

    state m_current_state;


};
