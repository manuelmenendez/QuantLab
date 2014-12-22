//// 
//// Autogenerated by xlw 
//// Do not edit this file, it will be overwritten 
//// by InterfaceGenerator 
////

#include "xlw/MyContainers.h"
#include <xlw/CellMatrix.h>
#include <stdexcept>
#include "cppinterface.h"
#include <xlw/xlwManaged.h>
using namespace System;
using namespace Runtime::InteropServices;
using namespace System;






CellMatrix mxlw_GetHistoricDataFromYahoo
		(
		std::string symbol,
		double beginDatea,
		double endDatea
		)
		{
		MANAGED_EXECL_BEGIN
			DateTime beginDate( DateTime::FromOADate(beginDatea ));

			DateTime endDate( DateTime::FromOADate(endDatea ));

			return GetHistoricDataFromYahoo(symbol,beginDate,endDate );
		MANAGED_EXECL_END
		}

////////////////////////////////////

double mxlw_EchoDate
		(
		double datea
		)
		{
		MANAGED_EXECL_BEGIN
			DateTime date( DateTime::FromOADate(datea ));

			return EchoDate(date );
		MANAGED_EXECL_END
		}

////////////////////////////////////

std::string mxlw_SHA1Hash
		(
		std::string value
		)
		{
		MANAGED_EXECL_BEGIN
			return SHA1Hash(value );
		MANAGED_EXECL_END
		}

////////////////////////////////////

