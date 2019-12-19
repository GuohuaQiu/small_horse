// SmartData.cpp: implementation of the CSmartDate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SmartDate.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSmartDate::CSmartDate()
{

}
CSmartDate::CSmartDate(int y,int m, int d)
{
	year =y;
	month =m;
	day = d;
}
CSmartDate::CSmartDate(const COleDateTime& date)
{
	year =date.GetYear();
	month =date.GetMonth();
	day = date.GetDay();
}

CSmartDate::~CSmartDate()
{

}

void CSmartDate::Validate(int& y,int& m,int& d)
{
	if(m == 2 && d > 28)
	{
		d = 29;
		if(y%4!=0 ||(y%100==0 && y%400!=0) )
		{
			d = 28;
		}
	}
}

bool CSmartDate::operator ==(const CSmartDate &rSrc) const
{
	if(year != rSrc.year)
	{
		return false;
	}
	if(month != rSrc.month)
	{
		return false;
	}
	if(day != rSrc.day)
	{
		return false;
	}
	return true;
}

bool CSmartDate::operator <=(const CSmartDate &rSrc) const
{
	if(year < rSrc.year)
	{
		return true;
	}
	else if(year == rSrc.year)
	{
		if(month < rSrc.month)
		{
			return true;
		}
		else if(month == rSrc.month)
		{
			return day <= rSrc.day;
		}
	}
	return false;
}

bool CSmartDate::operator >=(const CSmartDate &rSrc) const
{
	if(year > rSrc.year)
	{
		return true;
	}
	else if(year == rSrc.year)
	{
		if(month > rSrc.month)
		{
			return true;
		}
		else if(month == rSrc.month)
		{
			return day >= rSrc.day;
		}
	}
	return false;
}

bool CSmartDate::operator >(const CSmartDate &rSrc) const
{
	if(year > rSrc.year)
	{
		return true;
	}
	else if(year == rSrc.year)
	{
		if(month > rSrc.month)
		{
			return true;
		}
		else if(month == rSrc.month)
		{
			return day > rSrc.day;
		}
	}
	return false;
}
bool CSmartDate::operator <(const CSmartDate &rSrc) const
{
	if(year < rSrc.year)
	{
		return true;
	}
	else if(year == rSrc.year)
	{
		if(month < rSrc.month)
		{
			return true;
		}
		else if(month == rSrc.month)
		{
			return day < rSrc.day;
		}
	}
	return false;
}

void CSmartDate::Set(int y,int m, int d)
{
	year =y;
	month =m;
	day = d;
	if(month == 2 && day > 28)
	{
		day = 29;
		if(year%4!=0 ||(year%100==0 && year%400!=0) )
		{
			day = 28;
		}
	}
}

#define LY (date[i][j][k].year)
#define LM (date[i][j][k].month)
#define LD (date[i][j][k].day)
#define RY (date[ii][jj][kk].year)
#define RM (date[ii][jj][kk].month)
#define RD (date[ii][jj][kk].day)

void CSmartDate::Test()
{
	CSmartDate date[3][5][3];
	int c = 0;
	for(int i = 0;i<3;i++)
	{
		for(int j=0;j<5;j++)
		{
			for(int k = 0;k<3;k++)
			{
				date[i][j][k].year = 2000+i;
				date[i][j][k].month = j+1;
				date[i][j][k].day = k+1;
				date[i][j][k].test = c++;
			}
		}
	}
	
	for(int i = 0;i<3;i++)
	{
		for(int j =0;j<5;j++)
		{
			for(int k = 0;k<3;k++)
			{
				for(int ii = 0;ii<3;ii++)
				{
					for(int jj =0;jj<5;jj++)
					{
						for(int kk = 0;kk<3;kk++)
						{
							if((date[i][j][k] < date[ii][jj][kk]) == (date[i][j][k].test < date[ii][jj][kk].test) )
							{
								TRACE("%d,%d,%d < %d,%d,%d  = %d no problem!\n",LY,LM,LD,RY,RM,RD,date[i][j][k] < date[ii][jj][kk]);
							}
							else
							{
								TRACE("%d,%d,%d < %d,%d,%d has problem!\n",LY,LM,LD,RY,RM,RD);
							}
							if((date[i][j][k] > date[ii][jj][kk]) == (date[i][j][k].test > date[ii][jj][kk].test))
							{
								TRACE("%d,%d,%d > %d,%d,%d = %d no problem!\n",LY,LM,LD,RY,RM,RD, date[i][j][k] > date[ii][jj][kk]);
							}
							else
							{
								TRACE("%d,%d,%d > %d,%d,%d has problem!\n",LY,LM,LD,RY,RM,RD);
							}
						}
					}
				}
			}
		}
	}

}
