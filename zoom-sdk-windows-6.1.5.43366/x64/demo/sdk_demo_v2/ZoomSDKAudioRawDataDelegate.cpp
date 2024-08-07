#include "stdafx.h"
#include "ZoomSDKAudioRawDataDelegate.h"

#include <iostream>
#include <zoom_sdk_raw_data_def.h>


void ZoomSDKAudioRawDataDelegate::onMixedAudioRawDataReceived(AudioRawData* data_)
{
    cout << "Received " << data_->GetBufferLen() << "b from Mixed audio." << endl;
}

void ZoomSDKAudioRawDataDelegate::onOneWayAudioRawDataReceived(AudioRawData* data_, uint32_t node_id)
{
    cout << "Received " << data_->GetBufferLen() << "b from "<< "Node " << node_id << endl;
}

void ZoomSDKAudioRawDataDelegate::onShareAudioRawDataReceived(AudioRawData* data_)
{

}

void ZoomSDKAudioRawDataDelegate::onOneWayInterpreterAudioRawDataReceived(AudioRawData* data_, const zchar_t* pLanguageName)
{

}