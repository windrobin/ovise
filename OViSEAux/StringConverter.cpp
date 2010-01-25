#include "StringConverter.h"

StringConverter::StringConverter(const char* const InputForm_c_str) {
	#if wxUSE_UNICODE
		this->mStr = new wxString(InputForm_c_str);
	#else
		this->mStr = new wxString(InputForm_c_str, wxConvUTF8);
	#endif
}
StringConverter::StringConverter(std::string InputForm_std_str) {
	#if wxUSE_UNICODE
		this->mStr = new wxString(InputForm_std_str.c_str()); 
	#else
		this->mStr = new wxString(InputForm_std_str.c_str(), wxConvUTF8); 
	#endif
}
StringConverter::StringConverter(wxString InputForm_wx_str) { this->mStr = new wxString(InputForm_wx_str); }
StringConverter::StringConverter(const XMLCh* InputForm_xerces_str)
{
	char* Buff = xercesc::XMLString::transcode(InputForm_xerces_str);
	this->mStr = new wxString(Buff, wxConvUTF8);
	delete[] Buff;
}

StringConverter::~StringConverter(void) { delete this->mStr; }

const char* StringConverter::toCString() const { return this->toStdString().c_str(); }
std::string StringConverter::toStdString() const {
	#if wxUSE_UNICODE
		return std::string(this->mStr->mb_str(wxConvUTF8));
	#else
		return std::string(this->mStr->mb_str());
	#endif
}
wxString StringConverter::toWxString() const { return wxString(*(this->mStr)); }
XMLCh* StringConverter::toXMLString() const {return xercesc::XMLString::transcode(this->mStr->mb_str()); }

/*
Interesting example, if problems with umlauds occure again and the actual solution doesn't match:
Scoure: "http://groups.google.com/group/comp.soft-sys.wxwindows/browse_thread/thread/cdc929ea38b23b32/a860e8159afd9e9c?lnk=gst&q=Ryan+Wilcox"
Posting of : "Gunnar Roth"

CODE:

inline const wxCharBuffer ConvToUTF8( const wxString &s )
{
#if wxUSE_UNICODE
	return wxConvUTF8.cWC2MB(s); 
#else
	return wxConvUTF8.cWC2WX(wxConvCurrent->cMB2WC(s)); 
#endif
} 


#if wxUSE_UNICODE 
inline const wxWCharBuffer ConvFromUTF8( const char *s ) 
{ 
        wxWCharBuffer buf(wxConvUTF8.cMB2WC(s)); 
        if(buf.data()) 
                return buf; 
        return wxWCharBuffer(L"");
} 


#else 
inline const wxCharBuffer ConvFromUTF8( const char *s ) 
{ 
        wxWCharBuffer buf(wxConvUTF8.cMB2WC(s)); 
        if(buf.data()) 
                return wxConvCurrent->cWC2WX(buf); 
        return wxCharBuffer("");
} 
#endif 
*/