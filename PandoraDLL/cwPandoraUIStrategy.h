#pragma once
#include "cwBasicKindleStrategy.h"
#include "cwBasicCout.h"

class cwPandoraUIStrategy :
    public cwBasicKindleStrategy
{
public:

	//������£�PriceUpdate�ص�������OnBar�� ��PriceUpdate�Ѿ����Ի�ȡ���ºõ�K�ߣ�
    virtual void			PriceUpdate(cwMarketDataPtr pPriceData);
	typedef int (WINAPI* PriceUpdateCallBackUI)(cwFtdcDepthMarketDataField* pDepthMarketData);
	void* m_fpPriceUpdateCallBackUI;

	
	//������һ����K�ߵ�ʱ�򣬻���øûص�
	virtual void			OnBar(std::string InstrumentID, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindle) {};

	///Trade SPI
	//�ɽ��ر�
	virtual void			OnRtnTrade(cwTradePtr pTrade);
	typedef int (WINAPI* RtnTradeCallBackUI)(TRADEFIELD* pDepthMarketData);
	void* m_fpRtnTradeCallBackUI;

	//�����ر�, pOrderΪ���±�����pOriginOrderΪ��һ�θ��±����ṹ�壬�п���ΪNULL
	virtual void			OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr());
	typedef int (WINAPI* RtnOrderCallBackUI)(ORDERFIELD* pOrder, ORDERFIELD* pOriginOrder);
	void* m_fpRtnOrderCallBackUI;


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

	cwBasicCout				m_cwShow;
};

