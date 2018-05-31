// RateSet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "RateSet.h"
#include "smartdate.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRateSet

IMPLEMENT_DYNAMIC(CRateSet, CRecordset)

CRateSet::CRateSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRateSet)
	m_Deposit = 0.0f;
	m_Fix3Month = 0.0f;
	m_Fix6Month = 0.0f;
	m_Fix1Year = 0.0f;
	m_Fix2Year = 0.0f;
	m_Fix3Year = 0.0f;
	m_Fix5Year = 0.0f;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
    m_strSort = _T("FromDate ASC");
}


CString CRateSet::GetDefaultConnect()
{
	return DATA_SOURCE_NAME_ODBC;
}

CString CRateSet::GetDefaultSQL()
{
	return _T("[Rate]");
}

void CRateSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRateSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Date(pFX, _T("[FromDate]"), m_FromDate);
	RFX_Single(pFX, _T("[Deposit]"), m_Deposit);
	RFX_Single(pFX, _T("[Fix3Month]"), m_Fix3Month);
	RFX_Single(pFX, _T("[Fix6Month]"), m_Fix6Month);
	RFX_Single(pFX, _T("[Fix1Year]"), m_Fix1Year);
	RFX_Single(pFX, _T("[Fix2Year]"), m_Fix2Year);
	RFX_Single(pFX, _T("[Fix3Year]"), m_Fix3Year);
	RFX_Single(pFX, _T("[Fix5Year]"), m_Fix5Year);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRateSet diagnostics

#ifdef _DEBUG
void CRateSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRateSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG



/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   12/29/2010 11:17:41 AM
********************************************/
float CRateSet::GetRate(const COleDateTime &date, int nMonth)
{
    if(this->GetRecordCount() == 0)
    {
        return FALSE;
    }

    //to do... time should be ingore.
    float *pRate = GetRatePtr(nMonth);
    if(pRate == NULL)
    {
        TRACE("\nError: Month is wrong when call GetRate\n");
        return 0.0f;
    }
    MoveLast();
    while(!this->IsBOF())
    {
        if(date>=m_FromDate)
        {
            return *pRate;
        }
        MovePrev();
    }
    return *pRate;
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   12/29/2010 11:26:28 AM
********************************************/
float* CRateSet::GetRatePtr(int nMonth)
{
    switch(nMonth)
    {
    case 0:
        return &m_Deposit;
    case 3:
        return &m_Fix3Month;
    case 6:
        return &m_Fix6Month;
    case 12:
        return &m_Fix1Year;
    case 24:
        return &m_Fix2Year;
    case 36:
        return &m_Fix3Year;
    case 60:
        return &m_Fix5Year;
    }
    return NULL;
}

void CRateSet::TRACE_ALL()
{
    if(this->GetRecordCount() == 0)
    {
        return ;
    }
        TRACE("Date\t");
        TRACE("m_Fix3Month\t\t",m_Fix3Month);
        TRACE("m_Fix6Month\t\t",m_Fix6Month);
        TRACE("m_Fix1Year\t\t",m_Fix1Year);
        TRACE("m_Fix2Year\t\t",m_Fix2Year);
        TRACE("m_Fix3Year\t\t",m_Fix3Year);
        TRACE("m_Fix5Year\t\n",m_Fix5Year);

    MoveLast();
    while(!this->IsBOF())
    {
        TRACE("%s\t",m_FromDate.Format("%Y-%m-%d"));
        TRACE("%5.2f\t\t",m_Fix3Month);
        TRACE("%5.2f\t\t",m_Fix6Month);
        TRACE("%5.2f\t\t",m_Fix1Year);
        TRACE("%5.2f\t\t",m_Fix2Year);
        TRACE("%5.2f\t\t",m_Fix3Year);
        TRACE("%5.2f\t\t\n",m_Fix5Year);
        MovePrev();
    }
}

#define TRACE_TIME(reason,time) TRACE("%s:%s\n",reason,time.Format("%Y-%m-%d"));
#define TRACE_TIME_SPAN(reason,time,time1) TRACE("%s:%s - %s\n",reason,time.Format("%Y-%m-%d"),time1.Format("%Y-%m-%d"));
#define TRACE_TIME_SPAN_RATE(rate,time,time1) TRACE("rate %f  %s - %s\n",rate,time.Format("%Y-%m-%d"),time1.Format("%Y-%m-%d"));
/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :  get rate accroding to fromDate and fill the endDate that the rate valid. 
    Date          :   1/6/2011 3:55:55 PM
********************************************/
float CRateSet::GetDepositRate(const COleDateTime &fromDate, COleDateTime &toDate)
{
   TRACE_TIME("INTPUT ~fromDate",fromDate);
    if(this->GetRecordCount() == 0)
    {
        return FALSE;
    }
    float fRate = 0.0;
    toDate = COleDateTime::GetCurrentTime();

    //to do... time should be ingore.
    MoveLast();
    float fOldRate = m_Deposit;
    while(!this->IsBOF())
    {
        TRACE_TIME("~fromDate",fromDate);
        TRACE_TIME("~m_FromDate",m_FromDate);
        if(fromDate>=m_FromDate)
        {
            fRate = m_Deposit;
            break;
        }
        else
        {
            //deposit rate is same , toDate will include those periods.
            if(fabs(fOldRate - m_Deposit ) > 0.0001f )
            {
                toDate = m_FromDate;
            }
        }
        MovePrev();
    }
	TRACE_TIME_SPAN_RATE(fRate,fromDate,toDate);
    return fRate;
}

void CRateSet::AddRate(const COleDateTime &fromDate, float* rates)
{
	if(HasRecord(fromDate))
	{
		TRACE("AddRate:This date exist.\n");
		return;
	}
	AddNew();
	m_FromDate = fromDate;
	m_Deposit = rates[0];
	m_Fix3Month = rates[1];
	m_Fix6Month = rates[2];
	m_Fix1Year = rates[3];
	m_Fix2Year = rates[4];
	m_Fix3Year = rates[5];
	m_Fix5Year = rates[6];
	BOOL b = Update();

	TRACE("AddRate:New item ok? %s\n", b?"TRUE":"FALSE");

}

BOOL CRateSet::HasRecord(const COleDateTime &date)
{
    if(this->GetRecordCount() == 0)
    {
        return FALSE;
    }
    //to do... time should be ingore.
    MoveLast();

	CSmartDate guestDate(date);

    while(!this->IsBOF())
    {
		CSmartDate thisDate(m_FromDate);
		if (thisDate == guestDate) {
			return TRUE;
		}
        MovePrev();
    }
	return FALSE;
}
