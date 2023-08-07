
#ifndef _CONVERT_DATA_FROM_CSV_FILE_H_
#define _CONVERT_DATA_FROM_CSV_FILE_H_



enum VALUE_ENUM
{
	VALUE_TYPE_INCOME,
	VALUE_TYPE_PAY,
	VALUE_TYPE_DATE,
	VALUE_TYPE_TYPE,
    VALUE_TYPE_SUBCOUNT,
    VALUE_TYPE_SITE,
    //add new type here...
    VALUE_TYPE_COMMENT,
	VALUE_TYPE_SUM ,
	VALUE_TYPE_ONLYTIME ,
	VALUE_TYPE_number
};

enum VALUE_SUBCOUNT_ENUM
{
	VALUE_SUBCOUNT_TYPE_SUBCOUNT,
	VALUE_SUBCOUNT_TYPE_VALUE,
	VALUE_SUBCOUNT_TYPE_DATE_START,
	VALUE_SUBCOUNT_TYPE_DATE_END,
	VALUE_SUBCOUNT_TYPE_RATE,
	VALUE_SUBCOUNT_TYPE_PERIOD,
    //add new type here...
	VALUE_SUBCOUNT_TYPE_COMMENT,
	VALUE_SUBCONNT_TYPE_SUM,
	VALUE_SUBCOUNT_TYPE_number
};



enum VALUE_MAINCOUNT_ENUM
{
	VALUE_MAINCOUNT_TYPE_MAINCOUNT  ,
	VALUE_MAINCOUNT_TYPE_BANK       ,
	VALUE_MAINCOUNT_TYPE_OWNER      ,
	VALUE_MAINCOUNT_TYPE_VALUE      ,
	//add new type here...
	VALUE_MAINCOUNT_TYPE_COMMENT    ,
	VALUE_MAINCOUNT_TYPE_number// used as exist field. because will not display as one column.
};

enum VALUE_TODO_ENUM
{
	VALUE_TODO_TYPE_INDEX  ,
	VALUE_TODO_TYPE_BODY    ,
	VALUE_TODO_TYPE_number// used as exist field. because will not display as one column.
};

enum VIEW_TYPE
{
	VIEW_TYPE_RECORD_IN_ONE_COUNT,
	VIEW_TYPE_RECORD_QUERY_START,
    VIEW_TYPE_RECORD_QUERY = VIEW_TYPE_RECORD_QUERY_START,
	VIEW_TYPE_RECORD_QUERY_DATE,
	VIEW_TYPE_RECORD_QUERY_COMMENT,
	VIEW_TYPE_RECORD_QUERY_MONEY,
	VIEW_TYPE_RECORD_QUERY_END = VIEW_TYPE_RECORD_QUERY_MONEY,
	VIEW_TYPE_SUB_COUNTS,
	VIEW_TYPE_MAIN_COUNTS,
	VIEW_TYPE_CREDIT_REPORT,
	VIEW_TYPE_SIMPLE_SUBCOUNT,
	VIEW_TYPE_TODO
};

#define IS_QUERY(v) ((v >= VIEW_TYPE_RECORD_QUERY_START) && (v <= VIEW_TYPE_RECORD_QUERY_END))
#define IS_RECORD(v) ((v == VIEW_TYPE_RECORD_IN_ONE_COUNT)||(v >= VIEW_TYPE_RECORD_QUERY_START) && (v <= VIEW_TYPE_RECORD_QUERY_END))
#define IS_COUNTS(v) ((v == VIEW_TYPE_SUB_COUNTS)||(v == VIEW_TYPE_MAIN_COUNTS))
#define IS_REPORT(v) (v == VIEW_TYPE_CREDIT_REPORT)
#define IS_TODO(v) (v == VIEW_TYPE_TODO)
#define IS_SIMPLE_SUBCOUNT(v) (v == VIEW_TYPE_SIMPLE_SUBCOUNT)

extern TCHAR cMainCountRegionName[VALUE_MAINCOUNT_TYPE_number][FIELD_NAME_LEN];


#endif//_CONVERT_DATA_FROM_CSV_FILE_H_