#include "stdafx.h"
#include "chat_controller_workflow.h"



CSDKChatControllerWorkFlow::CSDKChatControllerWorkFlow()
{
	m_meeting_chat_event = NULL;
	bInited = false;
	m_meeting_chat_ctr = NULL;
	m_meeting_participants_ctr = NULL;
	InitController();
}

CSDKChatControllerWorkFlow::~CSDKChatControllerWorkFlow()
{
	m_meeting_chat_event = NULL;
	bInited = false;
	UnInit();
	m_meeting_chat_ctr = NULL;
	m_meeting_participants_ctr = NULL;
}

void CSDKChatControllerWorkFlow::onChatMsgNotifcation( ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc )
{
	if (m_meeting_chat_event)
	{
		m_meeting_chat_event->onChatMsgNotifcation(chatMsg,ccc);
	}
}

void CSDKChatControllerWorkFlow::onChatStatusChangedNotification( ZOOM_SDK_NAMESPACE::ChatStatus* status_ )
{
	if (m_meeting_chat_event)
	{
		m_meeting_chat_event->onChatStatusChangedNotification(status_);
	}
}

void CSDKChatControllerWorkFlow::SetEvent( IMeetingChatCtrlEventWrap* pSink )
{
	if (pSink)
	{
		m_meeting_chat_event = pSink;
	}
}

void CSDKChatControllerWorkFlow::UnInit()
{
	if(m_meeting_chat_ctr || m_meeting_participants_ctr)
	{		
		SDKInterfaceWrap::GetInst().UnListenChatServiceMgrEvent(this);
		m_meeting_chat_ctr = NULL;
		m_meeting_participants_ctr = NULL;
	}
}

bool CSDKChatControllerWorkFlow::InitController()
{
	if (!bInited)
	{
		if (m_meeting_chat_ctr == NULL)
		{
			m_meeting_chat_ctr = SDKInterfaceWrap::GetInst().GetMeetingChatController();
		}
		if (m_meeting_participants_ctr == NULL)
		{
			m_meeting_participants_ctr = SDKInterfaceWrap::GetInst().GetMeetingParticipantsController();
			
		}
		if (m_meeting_chat_ctr&&m_meeting_participants_ctr)
		{
			bInited = true;
			SDKInterfaceWrap::GetInst().ListenChatServiceMgrEvent(this);
			return true;
		}
	}

	return false;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKChatControllerWorkFlow::SendChatMsg(unsigned int receiver, wchar_t* content, ZOOM_SDK_NAMESPACE::SDKChatMessageType msgType)
{
	ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_INTERNAL_ERROR;
	do
	{
		if (!m_meeting_chat_ctr)
		{
			break;
		}
		ZOOM_SDK_NAMESPACE::IChatMsgInfoBuilder* pChatMsgInfoBuilder = m_meeting_chat_ctr->GetChatMessageBuilder();
		if (!pChatMsgInfoBuilder)
		{
			break;
		}
		pChatMsgInfoBuilder->SetContent(content);
		pChatMsgInfoBuilder->SetReceiver(receiver);
		pChatMsgInfoBuilder->SetMessageType(msgType);
		ZOOM_SDK_NAMESPACE::IChatMsgInfo* pChatMsgInfo = pChatMsgInfoBuilder->Build();
		if (!pChatMsgInfo)
		{
			break;
		}
		err = m_meeting_chat_ctr->SendChatMsgTo(pChatMsgInfo);
	} while (false);
	return err;
}

ZOOM_SDK_NAMESPACE::IUserInfo* CSDKChatControllerWorkFlow::GetUserInfoByID( unsigned int userid )
{
	if (m_meeting_participants_ctr)
	{
		return m_meeting_participants_ctr->GetUserByUserID(userid);
	}
	return NULL;
}