#pragma once
#include "stdafx.h"
#include "rawdata/rawdata_audio_helper_interface.h"
#include "WorkerManager.h"


class ZoomSDKAudioRawDataDelegate : public ZOOM_SDK_NAMESPACE::IZoomSDKAudioRawDataDelegate
{
public:
    ZoomSDKAudioRawDataDelegate(WorkerManager* manager);
    virtual ~ZoomSDKAudioRawDataDelegate(){};
    virtual void onMixedAudioRawDataReceived(AudioRawData* data_) override;
    virtual void onOneWayAudioRawDataReceived(AudioRawData* data_, uint32_t node_id) override;
    virtual void onShareAudioRawDataReceived(AudioRawData* data_) override;
    virtual void onOneWayInterpreterAudioRawDataReceived(AudioRawData* data_, const zchar_t* pLanguageName) override;
private:
    WorkerManager* manager_;
};