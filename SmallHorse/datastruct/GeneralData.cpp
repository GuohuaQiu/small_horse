
#include "stdafx.h"
#include "convertdata.h"



TCHAR cRegion[VALUE_TYPE_number][FIELD_NAME_LEN]=
{
	_T("��֧(��)"),
	_T("��֧(֧)"),
	_T("����"),
	_T("����"),
	_T("���˻�"),
	_T("�ص�"),
    //add new value here...
	_T("��ע"),
	_T("���"),
    _T("����ʱ��")
};

//0  ���п���,Ҫ����
//1  ������
//2����  ��������һ��.��һ���Ͳ�������.��û�������ѵ�һ��.
int nRegionAttr[VALUE_TYPE_number]=
{
	2,//"��֧(��)",
	2,//"��֧(֧)",
	1,//"����",
	0,//"����",
    0,//"���˻�",
    0,//"�ص�"
    //add new value here...
	0,//"��ע"
	0,//"���"
	0//"����ʱ��"
};

TCHAR cSubCountRegionName[VALUE_SUBCOUNT_TYPE_number][FIELD_NAME_LEN]=
{
	_T("���˻�"),
	_T("���"),
	_T("��Ϣ��"),
	_T("������"),
	_T("����"),
	_T("����"),
    //add new value here...
	_T("��ע"),
	_T("���")
};

int nSubCountRegionAttr[VALUE_SUBCOUNT_TYPE_number]=
{
	1,//"���˻�",
	1,//"���",
	1,//"��Ϣ��",
	2,//"������",
	1,//"����",
	2,//"����",
    //add new value here...
	0,//"��ע"
	0//"���"
};

TCHAR cMainCountRegionName[VALUE_MAINCOUNT_TYPE_number][FIELD_NAME_LEN]=
{
	_T("�˻�"),
	_T("����"),
	_T("����"),
	_T("���"),
    //add new value here...
	_T("��ע")
};
