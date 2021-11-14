// QueueTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include "include/number-generator.h"
#include "include/data-aggregator.h"
#include "include/data-processor.h"
#include <mutex>

int main() {
    constexpr auto queue_capacity = 5;

    // initializes the srand with a time based seed
    srand((unsigned)time(NULL));

    GenericQueue <std::vector<int64_t>> generated_values_queue(queue_capacity);
    GenericQueue <int64_t> processed_values_queue(queue_capacity);

    // syncing stuff
    std::mutex sync_control_mutex;
    std::unique_lock sync_unique_lock(sync_control_mutex);
    std::condition_variable syncing_cv;

    const auto generator = new NumberGenerator(generated_values_queue, 10);
    const auto processor = new DataProcessor(generated_values_queue,processed_values_queue);
    const auto aggregator = new DataAggregator(processed_values_queue, syncing_cv);
    
    // Start the threads. 
    generator->Start();
    processor->Start();
    aggregator->Start();

    //stops and waits for ther threads to end
    syncing_cv.wait(sync_unique_lock);

    delete processor;
    delete aggregator;
}
