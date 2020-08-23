//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	author: Wu Chang Sheng
//---
//--	Copyright (c) by Wu Chang Sheng. All rights reserved.
//--    Consult your license regarding permissions and restrictions.
//--
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>
#include <vector>
#include <deque>
#include "cwTradeCommonDefine.h"
#include "cwKindleStick.h"

typedef std::shared_ptr<cwKindleStick> cwKindleStickPtr;

class cwKindleStickSeries
{
public:

public:
	cwKindleStickSeries();
	~cwKindleStickSeries();

	bool InitialKindleStickSeries(uint32_t iTimeScale = 60);
	void PriceUpdate(cwMarketDataPtr pPriceData);

	inline uint32_t GetTimeScale() { return m_iTimeScale; }

public:
	cwMarketDataPtr					m_PrePriceData;
	cwKindleStickPtr				m_pCurrentKindleStick;
	uint32_t						m_iCurrentKindleLeftTime;
	std::deque<cwKindleStickPtr>	m_KindleStickDeque;

	bool		m_bIsNewKindle;

public:
	cwKindleStickPtr GetKindleStick(unsigned int nCount = 0);
	
	cwKindleStickPtr GetLastKindleStick(unsigned int nCount = 0);

	/*�������ܣ���ȡK�����г���
	* ����������
	*     NULL
	* ����ֵ��
	*     k�����г���
	*
	*/
	inline size_t			GetKindleSize() { return m_KindleStickDeque.size(); }

	/*�������ܣ���ȡK����ߵ�k�ߣ�����ж��һ���ߵģ����������һ��
	* ����������
	*     [in] nBegin	- K�߷�Χ��ʼ��ţ�
	*     [in] nEnd		- K�߷�Χ������ţ�
	* ����ֵ��
	*     ���K�ߵı�ţ����-1.��ʧ�ܣ���������
	*/
	int GetKindleStickHighest();
	int GetKindleStickHighest(unsigned int nBegin, unsigned int nEnd);
	int GetKindleStickHighest(unsigned int nCount);

	/*�������ܣ���ȡK����͵�k�ߣ�����ж��һ���͵ģ����������һ��
	* ����������
	*     [in] nBegin	- K�߷�Χ��ʼ��ţ�
	*     [in] nEnd		- K�߷�Χ������ţ�
	* ����ֵ��
	*     ���K�ߵı�ţ����-1.��ʧ�ܣ���������
	*/
	int GetKindleStickLowest();
	int GetKindleStickLowest(unsigned int nBegin, unsigned int nEnd);
	int GetKindleStickLowest(unsigned int nCount);
	
	/*�������ܣ���ȡָ����ΧK�ߵĲ���λ��
	* ����������
	*     [in] nBegin	- K�߷�Χ��ʼ��ţ�
	*     [in] nEnd		- K�߷�Χ������ţ�
	*	  [in] nUnilateralCompareNum - ���߱Ƚ���������2�����ʾ������2��K�߶��ߣ��ұ���������K�߶���Ϊ���壬���Ϊ�㣬���������K��
	*     [in, out] nIndexVector - ����Ҫ���K�߱��
	*	  [in, out] nIndexHighestPeak - ��߲����λ��
	* ����ֵ��
	*     true �ҵ�����Ҫ���K�ߣ�false δ�ҵ�����Ҫ���K��
	*/
	bool GetKindleStickPeak(unsigned int nBegin, unsigned int nEnd,
		unsigned int nUnilateralCompareNum, std::vector<unsigned int>& nIndexVector, unsigned int& nIndexHighestPeak);
	
	/*�������ܣ���ȡָ����ΧK�ߵĲ���λ��
	* ����������
	*     [in] nBegin	- K�߷�Χ��ʼ��ţ�
	*     [in] nEnd		- K�߷�Χ������ţ�
	*	  [in] nUnilateralCompareNum - ���߱Ƚ���������2�����ʾ������2��K�߶��ͣ��ұ���������K�߶���Ϊ���ȣ����Ϊ�㣬���������K��
	*     [in, out] nIndexVector - ����Ҫ���K�߱��
	*	  [in, out] nIndexLowestTrough - ��Ͳ��ȵ�λ��
	* ����ֵ��
	*     true �ҵ�����Ҫ���K�ߣ�false δ�ҵ�����Ҫ���K��
	*/
	bool GetKindleStickTrough(unsigned int nBegin, unsigned int nEnd,
		unsigned int nUnilateralCompareNum, std::vector<unsigned int>& nIndexVector, unsigned int& nIndexLowestTrough);
	
private:
	//K�����ڣ���Ϊ��λ
	uint32_t	m_iTimeScale;
	bool		m_bIsInitialed;
};

