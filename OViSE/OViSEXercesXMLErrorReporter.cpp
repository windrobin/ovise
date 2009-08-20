#include "OViSEXercesXMLErrorReporter.h"

OViSEXercesXMLErrorReporter::OViSEXercesXMLErrorReporter() : mFoundErrors(false) { this->mLog = new OViSELogging(); }
OViSEXercesXMLErrorReporter::~OViSEXercesXMLErrorReporter() { delete this->mLog; }
void OViSEXercesXMLErrorReporter::fatalError(const xercesc::SAXParseException& fatalE)
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

void OViSEXercesXMLErrorReporter::error(const xercesc::SAXParseException& defaultE)
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

void OViSEXercesXMLErrorReporter::warning(const xercesc::SAXParseException& warningE)
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

void OViSEXercesXMLErrorReporter::resetErrors()
{
	this->mFoundErrors = false;
}

bool OViSEXercesXMLErrorReporter::HasValidationErrors() const
{
	return this->mFoundErrors;
}
