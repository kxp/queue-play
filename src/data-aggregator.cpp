#include "data-aggregator.h"

#ifdef _WIN32
#include <Windows.h> // to have Sleep function
#else
#include <unistd.h>
#endif

void DataAggregator::data_processor() const {
    uint32_t num_processed_data = 0;
    int64_t average_of_averages = 0;

    while (m_current_state == state::Started) {

        int64_t sum = 0;
        int32_t amount_of_values = 0;

        auto average = 0;
        const auto result = m_queue.Dequeue(average);
        if (result == false) {
            //printf("No data to process.\n");
            Sleep(500);
            continue;
        }
        num_processed_data++;
        average_of_averages += average;
    }
    if(num_processed_data > 0)
        printf("The average of averages is %lld\n", average_of_averages / num_processed_data);

    printf("Data aggregator thread terminated\n");
}
