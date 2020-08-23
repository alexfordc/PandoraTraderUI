//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	Create by Wu Chang Sheng on May. 10th 2020
//---
//--	Copyright (c) by Wu Chang Sheng. All rights reserved.
//--    Consult your license regarding permissions and restrictions.
//--
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////


#pragma once
#include "cwCommonUtility.h"
#include "cwBasicStrategy.h"
#include "cwKindleStickSeries.h"
#include <condition_variable>

class cwBasicKindleStrategy :
	public cwBasicStrategy
{
public:
	typedef std::shared_ptr<cwKindleStickSeries>				cwKindleSeriesPtr;

public:
	cwBasicKindleStrategy();
	virtual ~cwBasicKindleStrategy();

	///MarketData SPI
	//������£�PriceUpdate�ص�������OnBar�� ��PriceUpdate�Ѿ����Ի�ȡ���ºõ�K�ߣ�
	virtual void			PriceUpdate(cwMarketDataPtr pPriceData) {};
	//������һ����K�ߵ�ʱ�򣬻���øûص�
	virtual void			OnBar(std::string InstrumentID, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindle) {};

	///Trade SPI
	//�ɽ��ر�
	virtual void			OnRtnTrade(cwTradePtr pTrade) {};
	//�����ر�, pOrderΪ���±�����pOriginOrderΪ��һ�θ��±����ṹ�壬�п���ΪNULL
	virtual void			OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr()) {};
	//�����ɹ�
	virtual void			OnOrderCanceled(cwOrderPtr pOrder) {};
	//����¼��������Ӧ
	virtual void			OnRspOrderInsert(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo) {};
	//��������������Ӧ
	virtual void			OnRspOrderCancel(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo) {};

	///System Call Back
	//��ʱ����Ӧ
	virtual void			OnStrategyTimer(int iTimerId) {};
	//�����Խ��׳�ʼ�����ʱ�����OnReady, �����ڴ˺��������Եĳ�ʼ������
	virtual void			OnReady() {};


	//����k��
	cwKindleSeriesPtr		SubcribeKindle(const char * szInstrumentID, int iTimeScale);
	//��ȡ�Ѿ����ĵ�k��
	cwKindleSeriesPtr		GetKindleSeries(const char * szInstrumentID, int iTimeScale);

	//��������--�޼۵�
	cwOrderPtr				InputLimitOrder(const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);
	//��������--FAK����Filled And Kill �����ɽ�ʣ���Զ�����ָ�
	cwOrderPtr				InputFAKOrder(const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);
	//��������--FOK��(FOK Filled Or Kill ����ȫ���ɽ������Զ�����ָ��)
	cwOrderPtr				InputFOKOrder(const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);

	//�򻯱��������� volume����ʾ�򣬸���ʾ�����Զ���ƽ���гֲ־�ƽ�֣�û�оͿ���
	cwOrderPtr				EasyInputOrder(const char * szInstrumentID, int volume, double price,
		cwOpenCloseMode openclosemode = cwOpenCloseMode::CloseTodayThenYd,
		cwInsertOrderType insertordertype = cwInsertOrderType::cwInsertLimitOrder);

	//����
	bool					CancelOrder(cwOrderPtr pOrder);
	//ȫ������
	int						CancelAll();
	//��ָ����Լȫ������
	int						CancelAll(const char * szInstrumentID);
	//��ָ����Լ�ͷ���ȫ������
	int						CancelAll(const char * szInstrumentID, cwFtdcDirectionType direction);

	//ί�н��ף�PositionAgency����������ᰴ�������óֲ�
	//ע�⣬������PositionAgency����֮���������µ����߳������������������ͻ��

	virtual void			SetAgentManager(void * pAgentMgr);


	///ϵͳ���ýӿ���Ϣ����
	virtual void			_SetReady();
	virtual void			_PriceUpdate(cwMarketDataPtr pPriceData);
	virtual void			_OnRtnTrade(cwTradePtr pTrade);
	virtual void			_OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr());
	virtual void			_OnOrderCanceled(cwOrderPtr pOrder);
	virtual void			_OnRspOrderInsert(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo);
	virtual void			_OnRspOrderCancel(cwOrderPtr pOrder, cwRspInfoPtr pRspInfo);
	virtual void			_OnTimer(int iTimerId);
private:
	///ϵͳ���ýӿ���Ϣ����
	//����K��
	void					_UpdateKindleSeries(cwMarketDataPtr pPriceData, std::map<int, cwKindleSeriesPtr> & OnBarMap);
	bool					_GetAgentWorking(std::string instrumentid);
	
private:
	///K������ key:instrument key: TimeScale value :Kindle Series
	std::map<std::string, std::map<int, cwKindleSeriesPtr>>		m_KindleSeriesMap;

	bool					m_bAgentWork;


	bool					m_bNightMode;
	std::string				m_strAppStartDay;
	std::string				m_strAppStartNextDay;
	std::string				m_strAppStartTime;

	///Updating Thread 
	///�����¼�����
	enum StrategyEventType
	{
		EventType_OnReady = 0
		, EventType_OnTimer
		, EventType_PriceUpdate
		, EventType_OnBar
		, EventType_RtnTrade
		, EventType_RtnOrder
		, EventType_OnCanceled
		, EventType_OnRspInsert
		, EventType_OnRspCancel
		, AgentType_PriceUpdate
		, AgentType_RtnTrade
		, AgentType_RtnOrder
		, AgentType_OnCanceled
		, AgentType_OnRspInsert
		, AgentType_OnRspCancel
	};

	///�����¼���Ϣ����
	struct EventTypeStruct
	{
		StrategyEventType		EventType;
		cwMarketDataPtr			pPriceData;
		cwTradePtr				pTrade;
		cwOrderPtr				pOrder;
		cwOrderPtr				pOriginOrder;
		cwRspInfoPtr			pRspInfo;

		std::string				strInstrumentID;
		int						iBarId;
		cwKindleSeriesPtr		pKindle;
	};
	typedef std::shared_ptr<EventTypeStruct>	EventTypeStructPtr;


	std::deque<EventTypeStructPtr>				m_EventTypeStructDeque;
	cwMUTEX										m_EventTypeDequeMutex;
	std::condition_variable						m_EventWorkingMutexCv;

	std::thread									m_EventTypeWorkingThread;
	volatile bool								m_bEventTypeWorkingThreadRun;

	void										_EventTypeWorkingThread();
	void										_AddEventType(EventTypeStructPtr EventPtr);

	CW_DISALLOW_COPYCTOR_AND_ASSIGNMENT(cwBasicKindleStrategy);

	void *										m_pAgentManager;

};

