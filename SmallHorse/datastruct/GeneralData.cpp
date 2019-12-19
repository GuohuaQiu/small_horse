
#include "stdafx.h"
#include "convertdata.h"



TCHAR cRegion[VALUE_TYPE_number][FIELD_NAME_LEN]=
{
	_T("收支(收)"),
	_T("收支(支)"),
	_T("日期"),
	_T("种类"),
	_T("子账户"),
	_T("地点"),
    //add new value here...
	_T("备注"),
	_T("余额"),
    _T("当日时间")
};

//0  可有可无,要提醒
//1  必须有
//2以上  两个必有一个.有一个就不用提醒.都没有则提醒第一个.
int nRegionAttr[VALUE_TYPE_number]=
{
	2,//"收支(收)",
	2,//"收支(支)",
	1,//"日期",
	0,//"种类",
    0,//"子账户",
    0,//"地点"
    //add new value here...
	0,//"备注"
	0,//"余额"
	0//"当日时间"
};

TCHAR cSubCountRegionName[VALUE_SUBCOUNT_TYPE_number][FIELD_NAME_LEN]=
{
	_T("子账户"),
	_T("金额"),
	_T("起息日"),
	_T("到期日"),
	_T("利率"),
	_T("存期"),
    //add new value here...
	_T("备注"),
	_T("余额")
};

int nSubCountRegionAttr[VALUE_SUBCOUNT_TYPE_number]=
{
	1,//"子账户",
	1,//"金额",
	1,//"起息日",
	2,//"到期日",
	1,//"利率",
	2,//"存期",
    //add new value here...
	0,//"备注"
	0//"余额"
};

TCHAR cMainCountRegionName[VALUE_MAINCOUNT_TYPE_number][FIELD_NAME_LEN]=
{
	_T("账户"),
	_T("银行"),
	_T("户主"),
	_T("余额"),
    //add new value here...
	_T("备注")
};
