
#if !defined(DATABASE_SETUP_H)
#define DATABASE_SETUP_H
#if 0
#ifdef _DEBUG
#define DATA_SOURCE_NAME_ODBC  _T("ODBC;DSN=test_b;pwd=rgb")
#define DATA_SOURCE_NAME _T("DSN=test_b;pwd=rgb")
#else
#define DATA_SOURCE_NAME_ODBC  _T("ODBC;DSN=Smarter;pwd=rgb")
#define DATA_SOURCE_NAME _T("DSN=Smarter;pwd=rgb")
#endif

#else
#ifdef _DEBUG
#define DATA_SOURCE_NAME_ODBC  _T("DSN=simon_test_64;DBQ=D:\\test\\bankbook.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=rgb;UID=admin;")
#define DATA_SOURCE_NAME DATA_SOURCE_NAME_ODBC
#else
#define DATA_SOURCE_NAME_ODBC  _T("DSN=simon_test_64;DBQ=D:\\test\\bankbook.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=rgb;UID=admin;")
#define DATA_SOURCE_NAME DATA_SOURCE_NAME_ODBC
#endif
#endif
#define SQL_AND_BOOK_EXIST                 _T(" and Books.Book_Exist = 1 ")
#define SQL_AND_BOOK_NO_EXIST              _T(" and Books.Book_Exist is false ")

#define SQL_OPEN_ALL_SUB_COUNT         _T("select Books.Book_ID, Sub_Count_Table.SubCountID, Books.Book_Bank, Books.Book_Owner, \
                                       sum(Items.Oper) as Total, Sub_Count_Table.StartDate,Sub_Count_Table.EndDate, \
                                       Sub_Count_Table.YearRate, Sub_Count_Table.TimeSpan , Sub_Count_Table.Comment\
                                       from Books,Sub_Count_Table,Items \
                                       where Books.Book_ID = Sub_Count_Table.CountID and \
                                       Items.Item_Book_ID = Sub_Count_Table.CountID and \
                                       Items.SubCountID = Sub_Count_Table.SubCountID ")

#define SQL_AND_BOOK_ID_IS             _T(" and Sub_Count_Table.CountID = \'%s\'")

#define SQL_GROUP_SUB_COUNT_WITH_SUM  _T(" group by Books.Book_ID, Sub_Count_Table.SubCountID, Books.Book_Bank, Books.Book_Owner,\
                                       Sub_Count_Table.StartDate,Sub_Count_Table.EndDate,\
                                       Sub_Count_Table.YearRate, \
                                       Sub_Count_Table.TimeSpan, Sub_Count_Table.Comment")
                                       

#define SQL_OPEN_ALL_SUB_COUNT_BY_ID   SQL_OPEN_ALL_SUB_COUNT SQL_AND_BOOK_ID_IS
                                       

#define COLUMN_NAME_SUB_COUNT          _T("账号;子账号;到期日期;起存额;银行;所有人")
#define COLUMN_NAME_MAIN_COUNT         _T("账号;银行;所有人;起存额;备注;存在")
#define SQL_SELECT_COMING_SUB_COUNT    _T("select Sub_Count_Table.CountID,Sub_Count_Table.SubCountID,Sub_Count_Table.EndDate,Sub_Count_Table.BeginValue,  Books.Book_Bank,Books.Book_Owner\
                                       from Books,Sub_Count_Table \
                                       where Books.Book_ID = Sub_Count_Table.CountID \
                                       and Books.Book_Exist = 1 ")

#define SQL_AND_END_DATE_LESS_THAN     _T(" and Sub_Count_Table.EndDate < %s")
#define SQL_AND_END_DATE_BIG_THAN      _T(" and Sub_Count_Table.EndDate > %s")
#define SQL_AND_SUBCOUNT_EXIST         _T(" and Sub_Count_Table.Exist = 1")
                                       
#define SQL_ORDER_BY_END_DATE          _T(" order by Sub_Count_Table.EndDate")

#define SQL_OPEN_SUBCOUNT_BETWEEN_DATE SQL_SELECT_COMING_SUB_COUNT SQL_AND_END_DATE_BIG_THAN SQL_AND_END_DATE_LESS_THAN SQL_ORDER_BY_END_DATE


#define SQL_OPEN_COMING_SUB_COUNT_     SQL_SELECT_COMING_SUB_COUNT SQL_AND_END_DATE_BIG_THAN SQL_ORDER_BY_END_DATE
#define SQL_OPEN_OVER_DATE_SUB_COUNT   SQL_SELECT_COMING_SUB_COUNT SQL_AND_END_DATE_LESS_THAN SQL_AND_SUBCOUNT_EXIST SQL_ORDER_BY_END_DATE 

                                       

#define SQL_SELECT_MAIN_COUNT_WITH_SUM _T("select Books.Book_ID,Books.Book_Bank,Books.Book_Owner,sum(Oper),Books.Book_Comment,Books.Book_Exist \
                                        from Books,Items \
                                        where Items.Item_Book_ID = Books.Book_ID")

#define SQL_SELECT_MAIN_COUNT_WITH_SUM_AND_NO_HIDE SQL_SELECT_MAIN_COUNT_WITH_SUM SQL_AND_BOOK_EXIST

#define SQL_GROUP_MAIN_COUNT_WITH_SUM  _T(" group by Books.Book_ID,Books.Book_Bank,Books.Book_Owner,Books.Book_Comment,Books.Book_Exist")
#define SQL_AND_WHERE_BANK_IS          _T(" and Books.Book_Bank = \'%s\'")
#define SQL_AND_WHERE_OWNER_IS         _T(" and Books.Book_Owner = \'%s\'")


#define SQL_ORDER_BY_BANK              _T(" order by Books.Book_Bank")
#define SQL_ORDER_BY_OWNER             _T(" order by Books.Book_Owner")

           

#define SQL_OPEN_ALL_MAIN_COUNT       SQL_SELECT_MAIN_COUNT_WITH_SUM SQL_GROUP_MAIN_COUNT_WITH_SUM
#define SQL_OPEN_ALL_EXIST_MAIN_COUNT       SQL_SELECT_MAIN_COUNT_WITH_SUM_AND_NO_HIDE SQL_GROUP_MAIN_COUNT_WITH_SUM

#define SQL_OPEN_MAIN_COUNT_BY_BANK   SQL_SELECT_MAIN_COUNT_WITH_SUM SQL_AND_WHERE_BANK_IS SQL_GROUP_MAIN_COUNT_WITH_SUM
#define SQL_OPEN_MAIN_COUNT_BY_OWNER  SQL_SELECT_MAIN_COUNT_WITH_SUM SQL_AND_WHERE_OWNER_IS SQL_GROUP_MAIN_COUNT_WITH_SUM

#define SQL_OPEN_EXIST_MAIN_COUNT_BY_BANK   SQL_SELECT_MAIN_COUNT_WITH_SUM_AND_NO_HIDE SQL_AND_WHERE_BANK_IS SQL_AND_BOOK_EXIST SQL_GROUP_MAIN_COUNT_WITH_SUM
#define SQL_OPEN_EXIST_MAIN_COUNT_BY_OWNER  SQL_SELECT_MAIN_COUNT_WITH_SUM_AND_NO_HIDE SQL_AND_WHERE_OWNER_IS SQL_GROUP_MAIN_COUNT_WITH_SUM

#define SQL_HAVING_TOTAL_IS_NEGATIVE  _T(" having sum(Oper) < -0.01")
#define SQL_OPEN_ALL_IN_DEBT_COUNT    SQL_SELECT_MAIN_COUNT_WITH_SUM SQL_GROUP_MAIN_COUNT_WITH_SUM SQL_HAVING_TOTAL_IS_NEGATIVE 

#define SQL_OPEN_ALL_EXIST_IN_DEBT_COUNT    SQL_SELECT_MAIN_COUNT_WITH_SUM_AND_NO_HIDE SQL_GROUP_MAIN_COUNT_WITH_SUM SQL_HAVING_TOTAL_IS_NEGATIVE 

#define SQL_SELECT_ALL_SITE    _T("select distinct(Site)\
                                       from Books,Items \
                                       where Site is not NULL ")




#define SQL_SELECT_RECENT_EXCHANGE_ITEMS _T("select Items.OperDate ,Items.Item_Book_ID,Items.Oper ,Items.Comment,Items.Site,Books.Book_Bank,Books.Book_Owner \
                                       from Items,Books  \
                                       where Items.Item_Book_ID = Books.Book_ID")

#define SQL_ORDER_BY_OPER_DATE          _T(" order by Items.OperDate")
#define SQL_AND_OPER_DATE_BIG_THAN      _T(" and Items.OperDate > %s")
                                       

#define SQL_OPEN_RECENT_EXCHANGE_ITEMS SQL_SELECT_RECENT_EXCHANGE_ITEMS SQL_AND_OPER_DATE_BIG_THAN SQL_ORDER_BY_OPER_DATE 

#define COLUMN_RECENT_EXCHANGE_ITEMS         _T("日期;账号;收支;备注;地点;银行;所有人")
                                       
#define COLUMN_SITE         _T("地点")


typedef struct GeneralInformation
{
    double mAmountEarn;
    int mTimesEarn;
    double mAmountExpense;
    int mTimesExpense;
    double mAmountTotal;
    int mTimesTotal;
}GEN_INFO,*LPGEN_INFO;
#include "DatabaseUtility.h"
#endif//DATABASE_SETUP_H