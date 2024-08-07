#pragma  once

#include "stdafx.h"
#include "sdk_util.h"
#include "WorkerManager.h"

class CustomizedUIRecordMgr : 
	public ZOOM_SDK_NAMESPACE::IMeetingRecordingCtrlEvent
{

public:
	static CustomizedUIRecordMgr* GetInstance();
	void GetRecordController();
	bool StartRecording(time_t& startTimestamp);
	bool StopRecording(time_t& stopTimestamp);
	bool StartCloudRecording();
	bool StopCloudRecording();

	ZOOM_SDK_NAMESPACE::SDKError CanTheUserStartLocalRecording(unsigned int userid);
	ZOOM_SDK_NAMESPACE::SDKError CanTheUserStartCloudRecording(unsigned int userid);
	ZOOM_SDK_NAMESPACE::SDKError CanIStartLocalRecording();
	ZOOM_SDK_NAMESPACE::SDKError CanIStartCloudRecording();
	bool CanIChangeOthersRecordingPermission();
	bool DoesTheUserSupportLocalRecording(unsigned int userid);

	bool AllowLocalRecording(unsigned int userid);
	bool DisAllowLocalRecording(unsigned int userid);
	
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath);
	virtual void onRecording2MP4Processing(int iPercentage);
	virtual void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status);
	virtual void onCloudRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status);
	virtual void onRecordPrivilegeChanged(bool bCanRec);
	virtual void onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper);
	virtual void onLocalRecordingPrivilegeRequestStatus(ZOOM_SDK_NAMESPACE::RequestLocalRecordingStatus status) {}
	virtual void onLocalRecordingPrivilegeRequested(ZOOM_SDK_NAMESPACE::IRequestLocalRecordingPrivilegeHandler* handler) {}
	virtual void onCloudRecordingStorageFull(time_t gracePeriodDate) {}
	virtual void onRequestCloudRecordingResponse(ZOOM_SDK_NAMESPACE::RequestStartCloudRecordingStatus status) {}
	virtual void onStartCloudRecordingRequested(ZOOM_SDK_NAMESPACE::IRequestStartCloudRecordingHandler* handler) {}
	virtual void onEnableAndStartSmartRecordingRequested(ZOOM_SDK_NAMESPACE::IRequestEnableAndStartSmartRecordingHandler* handler) {}
	virtual void onSmartRecordingEnableActionCallback(ZOOM_SDK_NAMESPACE::ISmartRecordingEnableActionHandler* handler) {}
private:
	CustomizedUIRecordMgr();
	~CustomizedUIRecordMgr();

private:
	static CustomizedUIRecordMgr* s_recordMgrObj;
	time_t m_rcdStartTime; 
	ZOOM_SDK_NAMESPACE::IMeetingRecordingController* m_pRecordController;
	WorkerManager* m_workerMgr;
};