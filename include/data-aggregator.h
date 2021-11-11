#pragma once
#include <cstdint>
#include "generic-queue.h"
#include "state.h"

class DataAggregator
{
public:
    DataAggregator(GenericQueue<int32_t>& shared_queue)
                    : m_queue(shared_queue)
    {
        m_current_state = state::NotInitialized;
    }

private:
    GenericQueue<int32_t>& m_queue;

    state m_current_state;
};
