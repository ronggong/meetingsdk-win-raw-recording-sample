#include "stdafx.h"
#include "WorkerManager.h"
#include <iostream>


WorkerManager::WorkerManager() 
    : running_(false)
    , resampler_(32000, 16000, 1)
{}

WorkerManager::~WorkerManager() {
    stop();
}

void WorkerManager::start() {
    running_ = true;
    audioThread_ = std::thread(&WorkerManager::processAudioData, this);
}

void WorkerManager::stop() {
    running_ = false;
    if (audioThread_.joinable()) audioThread_.join();
}

ThreadSafeQueue<AudioData>& WorkerManager::getAudioQueue() {
    return audioDataQueue_;
}

void WorkerManager::processAudioData() {
    while (running_) {
        AudioData rawData = audioDataQueue_.pop();
        // Perform heavy operations on rawData here
        vector<float> floatData;
        AudioUtil::convertPCM16ToFloat(rawData.data_, floatData);
        size_t resampledSz = size_t(floatData.size() * resampler_.getRatio());
        float* resampledData = new float[resampledSz];
        resampler_.process(floatData.data(), floatData.size(), resampledData, resampledSz);
        cout << "get buffer ";
        for (size_t i = 0; i < 10; i++) {
            cout << resampledData[i] << " ";
        }
        cout << endl;
        delete[] resampledData;
		//cout << "get buffer " << rawData.data_.size() << "b" << endl;
    }
}