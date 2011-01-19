#ifndef STRING_CONVERTER_H_
#define STRING_CONVERTER_H_

// Include WX
#ifdef __WXMSW__
# include "wx/msw/winundef.h"
#endif

#include <wx/string.h>

// For boost::noncopyable
#include <boost/utility.hpp>

// Include Xerces
#include <xercesc/util/XMLString.hpp>

// Include STD
#include <string>

class StringConverter :
// FIXME (ME): doesn't implement correct copy-ctor, so leave it noncopyable for now.
// Either leave it like that, implement a copy-ctor, move the code to free functions or
// use a complete variable instead of a pointer
	public boost::noncopyable 
{
private:
	wxString* mStr;

public:
	StringConverter(const char* const InputForm_c_str);
	StringConverter(std::string InputForm_std_str);
	StringConverter(wxString InputForm_wx_str);
	StringConverter(const XMLCh* InputForm_xerces_str);
	~StringConverter(void);

	const char* toCString() const;
	std::string toStdString() const;
	wxString toWxString() const;
	XMLCh* toXMLString() const;
};

#define ToCString(Str) StringConverter(Str).toCString()
#define ToStdString(Str) StringConverter(Str).toStdString()
#define ToWxString(Str) StringConverter(Str).toWxString()
#define ToXMLString(Str) StringConverter(Str).toXMLString()

#define ToOgreString(Str) StringConverter(Str).toStdString()

#endif /*STRING_CONVERTER_H_*/

/* * * Emample-Code * * *

std::string str2 = "CString";
	
char* str1 = new char[str2.size()+1];
strcpy(str1, str2.c_str());

str2 = "StdString";
wxString str3 = wxT("WxString");

const XMLCh* str4 = XMLString::transcode("XMLString");

std::string test;
test = ToStdString(str1);
test = ToStdString(str2);
test = ToStdString(str3);
test = ToStdString(str4);

test = ToStdString(str1) +  ToStdString(str2) + ToStdString(str3) + ToStdString(str4);

XMLCh* testXML;
testXML = ToXMLString(str1);
testXML = ToXMLString(str2);
testXML = ToXMLString(str3);
testXML = ToXMLString(str4);

testXML = ToXMLString(str1);
XMLString::catString(testXML, ToXMLString(str2));
XMLString::catString(testXML, ToXMLString(str3));
XMLString::catString(testXML, ToXMLString(str4));
	
wxString testWx;
testWx = ToWxString(str1);
testWx = ToWxString(str2);
testWx = ToWxString(str3);
testWx = ToWxString(str4);

testWx = ToWxString(str1).Append(ToWxString(str2)).Append(ToWxString(str3)).Append(ToWxString(str4));

* * * Emample-Code * * */