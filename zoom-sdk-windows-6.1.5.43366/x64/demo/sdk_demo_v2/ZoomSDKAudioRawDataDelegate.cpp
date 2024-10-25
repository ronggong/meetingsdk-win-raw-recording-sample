#include "stdafx.h"
#include <zoom_sdk_raw_data_def.h>
#include <iostream>
#include "ZoomSDKAudioRawDataDelegate.h"
#include "AudioUtil.h"

ZoomSDKAudioRawDataDelegate::ZoomSDKAudioRawDataDelegate(WorkerManager* manager) : manager_(manager)
{
}

void ZoomSDKAudioRawDataDelegate::onMixedAudioRawDataReceived(AudioRawData* data_)
{
}

void ZoomSDKAudioRawDataDelegate::onOneWayAudioRawDataReceived(AudioRawData* data_, uint32_t node_id)
{
    if (node_id_ == 0) {
        node_id_ = node_id;
    }

    if (node_id_ == node_id) {
        //cout << "sampling rate " << data_->GetSampleRate() << " channel num " << data_->GetChannelNum() << endl;
        AudioData audioData(data_->GetBuffer(), data_->GetBufferLen(), data_->GetSampleRate(), data_->GetChannelNum());
        manager_->getAudioQueue().push(audioData);
    }
}

void ZoomSDKAudioRawDataDelegate::onShareAudioRawDataReceived(AudioRawData* data_)
{

}

void ZoomSDKAudioRawDataDelegate::onOneWayInterpreterAudioRawDataReceived(AudioRawData* data_, const zchar_t* pLanguageName)
{

}