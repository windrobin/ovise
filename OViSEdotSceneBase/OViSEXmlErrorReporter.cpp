#include "OViSEXmlErrorReporter.h"

OViSEXmlErrorReporter::OViSEXmlErrorReporter() : mFoundErrors(false) { this->mLog = new OViSELogging(); }
OViSEXmlErrorReporter::~OViSEXmlErrorReporter() { delete this->mLog; }
void OViSEXmlErrorReporter::fatalError(const xercesc::SAXParseException& fatalE)
{
	this->mFoundErrors = true;

	char* buffText = 0;

	wxString tSystemId = ToWxString(fatalE.getSystemId());
	
	xercesc_3_0::XMLString::binToText(fatalE.getLineNumber(), buffText, 19, 10);
	wxString tLineNumber = ToWxString(buffText);
	delete buffText;

	xercesc_3_0::XMLString::binToText(fatalE.getColumnNumber(), buffText, 19, 10);
	wxString tColumnNumber = ToWxString(buffText);
	delete buffText;
	
	wxString tMessage = ToWxString(fatalE.getMessage());

	wxString ParsingMsg;

	ParsingMsg.Clear();
	ParsingMsg	<< ToWxString("Xerces3.0 XML-Parser: Fatal error at file \"")
				<< tSystemId
				<< ToWxString("\", line ")
				<< tLineNumber
				<< ToWxString(", column ")
				<< tColumnNumber
				<< ToWxString("!");
	this->mLog->WriteToOgreLog(ParsingMsg, OViSELogging::Critical);

	ParsingMsg.Clear();
	ParsingMsg	<< ToWxString("Xerces3.0 Message: \"")
				<< tMessage
				<< ToWxString("\"");
	this->mLog->WriteToOgreLog(ParsingMsg, OViSELogging::Critical);
}

void OViSEXmlErrorReporter::error(const xercesc::SAXParseException& defaultE)
{
	this->mFoundErrors = true;

	char* buffText = 0;

	wxString tSystemId = ToWxString(defaultE.getSystemId());
	
	xercesc_3_0::XMLString::binToText(defaultE.getLineNumber(), buffText, 19, 10);
	wxString tLineNumber = ToWxString(buffText);
	delete buffText;

	xercesc_3_0::XMLString::binToText(defaultE.getColumnNumber(), buffText, 19, 10);
	wxString tColumnNumber = ToWxString(buffText);
	delete buffText;
	
	wxString tMessage = ToWxString(defaultE.getMessage());

	wxString ParsingMsg;

	ParsingMsg.Clear();
	ParsingMsg	<< ToWxString("Xerces3.0 XML-Parser: Default error at file \"")
				<< tSystemId
				<< ToWxString("\", line ")
				<< tLineNumber
				<< ToWxString(", column ")
				<< tColumnNumber
				<< ToWxString("!");
	this->mLog->WriteToOgreLog(ParsingMsg, OViSELogging::Normal);

	ParsingMsg.Clear();
	ParsingMsg	<< ToWxString("Xerces3.0 Message: \"")
				<< tMessage
				<< ToWxString("\"");
	this->mLog->WriteToOgreLog(ParsingMsg, OViSELogging::Normal);
}

void OViSEXmlErrorReporter::warning(const xercesc::SAXParseException& warningE)
{
	this->mFoundErrors = true;

	char* buffText = 0;

	wxString tSystemId = ToWxString(warningE.getSystemId());
	
	xercesc_3_0::XMLString::binToText(warningE.getLineNumber(), buffText, 19, 10);
	wxString tLineNumber = ToWxString(buffText);
	delete buffText;

	xercesc_3_0::XMLString::binToText(warningE.getColumnNumber(), buffText, 19, 10);
	wxString tColumnNumber = ToWxString(buffText);
	delete buffText;
	
	wxString tMessage = ToWxString(warningE.getMessage());

	wxString ParsingMsg;

	ParsingMsg.Clear();
	ParsingMsg	<< ToWxString("Xerces3.0 XML-Parser: Warning at file \"")
				<< tSystemId
				<< ToWxString("\", line ")
				<< tLineNumber
				<< ToWxString(", column ")
				<< tColumnNumber
				<< ToWxString("!");
	this->mLog->WriteToOgreLog(ParsingMsg, OViSELogging::Trivial);

	ParsingMsg.Clear();
	ParsingMsg	<< ToWxString("Xerces3.0 Message: \"")
				<< tMessage
				<< ToWxString("\"");
	this->mLog->WriteToOgreLog(ParsingMsg, OViSELogging::Trivial);
}

void OViSEXmlErrorReporter::resetErrors()
{
	this->mFoundErrors = false;
}

bool OViSEXmlErrorReporter::HasValidationErrors() const
{
	return this->mFoundErrors;
}
