#pragma once

#include "ThreadSafeQueue.h"
#include <thread>
#include <atomic>
#include "AudioUtil.h"

class WorkerManager {
public:
    WorkerManager();
    ~WorkerManager();

    void start();
    void stop();

    ThreadSafeQueue<AudioData>& getAudioQueue();

private:
    void processAudioData();

    std::thread audioThread_;
    std::atomic<bool> running_;

    ThreadSafeQueue<AudioData> audioDataQueue_;

    Resampler resampler_;
};