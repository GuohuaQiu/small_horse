// CreditPaySet.cpp : implementation file
//

#include "stdafx.h"
#include "..\SmallHorse.h"
#include "CreditPaySet.h"
#include "database_setup.h"
#include "smartdate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreditPaySet

IMPLEMENT_DYNAMIC(CCreditPaySet, CRecordset)

CCreditPaySet::CCreditPaySet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCreditPaySet)
	m_BookID = _T("");
	m_StartYear = 0;
	m_StartMonth = 0;
	m_StatementDate = 0;
	m_PaymentDueDate = 0;
	m_Comment = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CCreditPaySet::GetDefaultConnect()
{
	return DATA_SOURCE_NAME_ODBC;
}

CString CCreditPaySet::GetDefaultSQL()
{
	return _T("[CreditPayTable]");
}

void CCreditPaySet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCreditPaySet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[BookID]"), m_BookID);
	RFX_Int(pFX, _T("[StartYear]"), m_StartYear);
	RFX_Byte(pFX, _T("[StartMonth]"), m_StartMonth);
	RFX_Byte(pFX, _T("[StatementDate]"), m_StatementDate);
	RFX_Byte(pFX, _T("[PaymentDueDate]"), m_PaymentDueDate);
	RFX_Text(pFX, _T("[Comment]"), m_Comment);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCreditPaySet diagnostics

#ifdef _DEBUG
void CCreditPaySet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCreditPaySet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CCreditPaySet::GetPayInfo(const CString& strID,int nYear, int nMonth, COleDateTime &dayBegin, COleDateTime &dayEnd, COleDateTime &dayPay)
{
    if(!IsOpen())
    {
        Open();
    }
    m_strFilter.Format(_T("BookID = \'%s\'"),strID);
	m_strSort=_T("StartYear,StartMonth");// '379 70052992*3'
    this->Requery();
    if(this->GetRecordCount() == 0)
    {
        return FALSE;
    }
    this->MoveFirst();
    int nPayDay = -1;
    int nStatementDay = -1;
    int nPreStatementDay = -1;
    while(!this->IsEOF())
    {
        int span = GetSpan(this->m_StartYear, this->m_StartMonth,  nYear, nMonth);
        trace();
        if(span > 1)
        {//can get normal day using previous one.
            if(nPayDay == -1 || nStatementDay == -1 )
            {//if no period can get ,use the close one.
                nPayDay = this->m_PaymentDueDate;
                nStatementDay = this->m_StatementDate;
            }
            break;
        }
        else if( span > -1 )
        {//should get a big month whose begin is previous and end is this one.
                nPreStatementDay = nStatementDay;

        }
//continue to find more...
            

        nPayDay = this->m_PaymentDueDate;
        nStatementDay = this->m_StatementDate;
        if(nPreStatementDay != -1)
        {//very closely ,stop! will use this->m_StartMonth, so cant MoveNext.
            break;
        }
        else
        {
            this->MoveNext();
        }
    }
    if(nPayDay!= -1&&nStatementDay!=-1)
    {
        if(nPreStatementDay == -1)
        {
			int thisYear = nYear;
			int thisMonth = nMonth;
			int thisDay = nStatementDay-1;

			CSmartDate::Validate(thisYear,thisMonth,thisDay);

			int status = dayEnd.SetDateTime(thisYear,thisMonth,thisDay,23,59,59);
			if(status != 0)
			{
				ASSERT(FALSE);
			}

            thisYear = nMonth==1 ? nYear-1 : nYear;
            thisMonth = nMonth==1 ? 12 : nMonth - 1;
            thisDay = nStatementDay;

			CSmartDate::Validate(thisYear,thisMonth,thisDay);
            
            status = dayBegin.SetDateTime(thisYear,thisMonth,thisDay,0,0,0);
			if(status != 0)
			{
				thisDay = 1;
				thisMonth += 1;
				dayBegin.SetDateTime(thisYear,thisMonth,thisDay,0,0,0);
			}

            
            if(nStatementDay > nPayDay)
            {
                thisYear = nMonth!=12 ? nYear : nYear+1;
                thisMonth = nMonth!=12 ? nMonth+1 : 1;
                dayPay.SetDate(thisYear,thisMonth,nPayDay);
            }
            else
            {
                dayPay = dayEnd;
                dayPay += (nPayDay - nStatementDay);
            }
        }
        else//big month.
        {
            dayEnd.SetDateTime(nYear,this->m_StartMonth,nStatementDay-1,23,59,59);
            
            int thisYear = this->m_StartMonth==1 ? nYear-1 : nYear;
            int thisMonth = this->m_StartMonth==1 ? 12 : this->m_StartMonth - 1;
            int thisDay = nPreStatementDay;
            
            if(nPreStatementDay > nStatementDay)
            {
                AddMonth(thisYear,thisMonth,-1);
            }
            
            int status = dayBegin.SetDateTime(thisYear,thisMonth,thisDay,0,0,0);
			if(status != 0)
			{
				ASSERT(FALSE);
			}
           
            if(nStatementDay > nPayDay)
            {
                thisYear = nYear;
                thisMonth = this->m_StartMonth;
                AddMonth(thisYear,thisMonth,1);
                int status = dayPay.SetDate(thisYear,thisMonth,nPayDay);
				if(status != 0)
				{
					ASSERT(FALSE);
				}
			}
            else
            {
                dayPay = dayEnd;
                dayPay += (nPayDay - nStatementDay);
            }
        }
        return TRUE;
    }
	return FALSE;
}

void CCreditPaySet::trace()
{
    TRACE("\nID:%s ; Start: %4d-%.2d; Statement: %.2d; Pay:%.2d;%s",	m_BookID,m_StartYear,m_StartMonth,m_StatementDate,m_PaymentDueDate,m_Comment);
}


/*******************************************
    Function Name :	 
    Create by     :	  Qiu Simon
    Input         :   
    Output        :   
    Description   :   
    Date          :   2010-8-27 14:33:34
********************************************/
int CCreditPaySet::GetSpan(int aYear, int aMonth, int bYear, int bMonth)
{
    return (aYear - bYear) * 12 + (aMonth - bMonth);
}

#if 0//test code.
    for(int aYear = 2002;aYear<=2010;aYear++)
    {
        for(int m = 1;m<=12;m++)
        {
            int bYear = 2007;
            int bm = 3;
            int span = GetSpan( aYear, m,  bYear, bm);
            TRACE("\n%.4d-%.2d <> %.4d-%.2d -> %.3d" , aYear, m,  bYear, bm,span);

        }
    }
#endif
#if 0//test code.
        for(int m = -25;m<=25;m++)
        {
            int bYear = 2007;
            int bm = 3;
            CCreditPaySet::AddMonth( bYear, bm,  m);
            TRACE("\n2007-03 +%.2d = %.4d-%.2d " ,m, bYear, bm);
        }
#endif



void CCreditPaySet::AddMonth(int &year, int &month, int ms)
{
    month += ms;
    year += month/12;
    month = month%12 ;
    if(month == 0)
    {
        month = 12;
        year -= 1;
    }
    else if(month <0)
    {
        year -= 1;
        month += 12;
    }
}


BOOL CCreditPaySet::GetPeriodStart(const CString& strID,int inY, int inM, int inD, int &outY, int &outM, int &outD)
{
	COleDateTime dayBegin,dayEnd,dayPay;
	
	GetPayInfo(strID,inY,inM,dayBegin,dayEnd,dayPay);

	return TRUE;
	
	
	
}
