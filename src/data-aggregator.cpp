#include "data-aggregator.h"

#ifdef _WIN32
#include <Windows.h> // to have Sleep function
#else
#include <unistd.h>
#endif

void DataAggregator::Start() {
    if (m_current_state == state::Started || m_current_state == state::Terminated)
        return;

    m_current_state = state::Started;
    m_processor_thread = std::thread(&DataAggregator::data_processor, this);
}

void DataAggregator::data_processor() const {
    uint32_t num_processed_data = 0;
    int64_t average_of_averages = 0;
    int32_t exit_control_variable = 0;

    while (m_current_state == state::Started && exit_control_variable < m_limit_retry_value) {

        int64_t sum = 0;
        int32_t amount_of_values = 0;

        int64_t average = 0;
        const auto result = m_queue.TryDequeue(average);
        if (result == false) {
            Sleep(500);
            exit_control_variable++;
            continue;
        }
        else
            exit_control_variable = 0;

        num_processed_data++;
        average_of_averages += average;
    }
    if(exit_control_variable == m_limit_retry_value)
        printf("No more data to aggregate. Limit reached:%d\n", exit_control_variable);

    if(num_processed_data > 0)
        printf("The average of averages is %lld\n", average_of_averages / num_processed_data);

    printf("Data aggregator thread terminated\n");
    m_app_lock_cv.notify_all();
}
