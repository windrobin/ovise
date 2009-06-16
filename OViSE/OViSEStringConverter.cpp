#include "OViSEStringConverter.h"

OViSEStringConverter::OViSEStringConverter(const char* const InputForm_c_str) { this->mStr = new wxString(InputForm_c_str, wxConvUTF8); }
OViSEStringConverter::OViSEStringConverter(std::string InputForm_std_str) { this->mStr = new wxString(InputForm_std_str.c_str(), wxConvUTF8); }
OViSEStringConverter::OViSEStringConverter(wxString InputForm_wx_str) { this->mStr = new wxString(InputForm_wx_str); }
OViSEStringConverter::OViSEStringConverter(const XMLCh* InputForm_xerces_str)
{
	char* Buff = xercesc::XMLString::transcode(InputForm_xerces_str);
	this->mStr = new wxString(Buff, wxConvUTF8);
	delete[] Buff;
}

OViSEStringConverter::~OViSEStringConverter(void)
{
	delete this->mStr;
}

const char* OViSEStringConverter::toCString() const { return this->mStr->mb_str(); }
std::string OViSEStringConverter::toStdString() const { return std::string(this->mStr->mb_str()); }
wxString OViSEStringConverter::toWxString() const { return wxString(*(this->mStr)); }
XMLCh* OViSEStringConverter::toXMLString() const {return xercesc::XMLString::transcode(this->mStr->mb_str()); }
