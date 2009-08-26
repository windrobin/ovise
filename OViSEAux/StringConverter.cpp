#include "StringConverter.h"

StringConverter::StringConverter(const char* const InputForm_c_str) { this->mStr = new wxString(InputForm_c_str, wxConvUTF8); }
StringConverter::StringConverter(std::string InputForm_std_str) { this->mStr = new wxString(InputForm_std_str.c_str(), wxConvUTF8); }
StringConverter::StringConverter(wxString InputForm_wx_str) { this->mStr = new wxString(InputForm_wx_str); }
StringConverter::StringConverter(const XMLCh* InputForm_xerces_str)
{
	char* Buff = xercesc::XMLString::transcode(InputForm_xerces_str);
	this->mStr = new wxString(Buff, wxConvUTF8);
	delete[] Buff;
}

StringConverter::~StringConverter(void)
{
	delete this->mStr;
}

const char* StringConverter::toCString() const { return this->mStr->mb_str(); }
std::string StringConverter::toStdString() const { return std::string(this->mStr->mb_str()); }
wxString StringConverter::toWxString() const { return wxString(*(this->mStr)); }
XMLCh* StringConverter::toXMLString() const {return xercesc::XMLString::transcode(this->mStr->mb_str()); }
