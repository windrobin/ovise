#pragma once

#ifndef OVISE_STRING_CONVERTER_H_
#define OVISE_STRING_CONVERTER_H_

// Include Xerces
#ifndef XERCESC_UTIL_XMLSTRING_USED
#define XERCESC_UTIL_XMLSTRING_USED
#include <xercesc/util/XMLString.hpp>
#endif

// Include WX
#ifndef WX_STRING_USED
#define WX_STRING_USED
#include <wx/string.h>
#endif

// Include STD
#ifndef STD_STING_USED
#define STD_STING_USED
#include <string>
#endif

class OViSEStringConverter
{
private:
	wxString* mStr;

public:
	OViSEStringConverter(const char* const InputForm_c_str);
	OViSEStringConverter(std::string InputForm_std_str);
	OViSEStringConverter(wxString InputForm_wx_str);
	OViSEStringConverter(const XMLCh* InputForm_xerces_str);
	~OViSEStringConverter(void);

	const char* toCString() const;
	std::string toStdString() const;
	wxString toWxString() const;
	XMLCh* toXMLString() const;
};

#define ToCString(Str) OViSEStringConverter(Str).toCString()
#define ToStdString(Str) OViSEStringConverter(Str).toStdString()
#define ToWxString(Str) OViSEStringConverter(Str).toWxString()
#define ToXMLString(Str) OViSEStringConverter(Str).toXMLString()

#define ToOgreString(Str) OViSEStringConverter(Str).toStdString()

#endif /*OVISE_STRING_CONVERTER_H_*/

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