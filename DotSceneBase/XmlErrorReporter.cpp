/********************************************************************************
* Name:      XmlErrorReporter.cpp												*
* Purpose:   Code implements a class, handling validation-, read- and write-	*
*			  error. Any error will be send to log.								*
* Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
* Created:   2009-11-13														*
* Copyright: Henning Renartz,													*
*			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
* License:																		*
********************************************************************************/

#include "../OViSEdotSceneBase/XmlErrorReporter.h"

XmlErrorReporter::XmlErrorReporter() : mFoundErrors( false ) { }
XmlErrorReporter::~XmlErrorReporter() { }
void XmlErrorReporter::fatalError( const xercesc::SAXParseException& fatalE )
{
	this->mFoundErrors = true;

	char* buffText = 0;

	wxString tSystemId = ToWxString( fatalE.getSystemId());

	xercesc::XMLString::binToText(
		(long)fatalE.getLineNumber(), buffText, 19, 10 );
	wxString tLineNumber = ToWxString( buffText );
	delete buffText;

	xercesc::XMLString::binToText(
		(long)fatalE.getColumnNumber(), buffText, 19, 10 );
	wxString tColumnNumber = ToWxString( buffText );
	delete buffText;

	wxString tMessage = ToWxString( fatalE.getMessage());

	wxString ParsingMsg;

	ParsingMsg.Clear();
	ParsingMsg << ToWxString(
		"Xerces3.0 XML-Parser: Fatal error at file \"" )
	           << tSystemId
	           << ToWxString( "\", line " )
	           << tLineNumber
	           << ToWxString( ", column " )
	           << tColumnNumber
	           << ToWxString( "!" );
	Logging::GetSingletonPtr()->WriteToOgreLog( ParsingMsg,
		Logging::Critical );

	ParsingMsg.Clear();
	ParsingMsg << ToWxString( "Xerces3.0 Message: \"" )
	           << tMessage
	           << ToWxString( "\"" );
	Logging::GetSingletonPtr()->WriteToOgreLog( ParsingMsg,
		Logging::Critical );
}

void XmlErrorReporter::error( const xercesc::SAXParseException& defaultE )
{
	this->mFoundErrors = true;

	char* buffText = 0;

	wxString tSystemId = ToWxString( defaultE.getSystemId());

	xercesc::XMLString::binToText(
		(long)defaultE.getLineNumber(), buffText, 19, 10 );
	wxString tLineNumber = ToWxString( buffText );
	delete buffText;

	xercesc::XMLString::binToText(
		(long)defaultE.getColumnNumber(), buffText, 19, 10 );
	wxString tColumnNumber = ToWxString( buffText );
	delete buffText;

	wxString tMessage = ToWxString( defaultE.getMessage());

	wxString ParsingMsg;

	ParsingMsg.Clear();
	ParsingMsg << ToWxString(
		"Xerces3.0 XML-Parser: Default error at file \"" )
	           << tSystemId
	           << ToWxString( "\", line " )
	           << tLineNumber
	           << ToWxString( ", column " )
	           << tColumnNumber
	           << ToWxString( "!" );
	Logging::GetSingletonPtr()->WriteToOgreLog( ParsingMsg, Logging::Normal );

	ParsingMsg.Clear();
	ParsingMsg << ToWxString( "Xerces3.0 Message: \"" )
	           << tMessage
	           << ToWxString( "\"" );
	Logging::GetSingletonPtr()->WriteToOgreLog( ParsingMsg, Logging::Normal );
}

void XmlErrorReporter::warning( const xercesc::SAXParseException& warningE )
{
	this->mFoundErrors = true;

	char* buffText = 0;

	wxString tSystemId = ToWxString( warningE.getSystemId());

	xercesc::XMLString::binToText(
		(long)warningE.getLineNumber(), buffText, 19, 10 );
	wxString tLineNumber = ToWxString( buffText );
	delete buffText;

	xercesc::XMLString::binToText(
		(long)warningE.getColumnNumber(), buffText, 19, 10 );
	wxString tColumnNumber = ToWxString( buffText );
	delete buffText;

	wxString tMessage = ToWxString( warningE.getMessage());

	wxString ParsingMsg;

	ParsingMsg.Clear();
	ParsingMsg << ToWxString( "Xerces3.0 XML-Parser: Warning at file \"" )
	           << tSystemId
	           << ToWxString( "\", line " )
	           << tLineNumber
	           << ToWxString( ", column " )
	           << tColumnNumber
	           << ToWxString( "!" );
	Logging::GetSingletonPtr()->WriteToOgreLog( ParsingMsg,
		Logging::Trivial );

	ParsingMsg.Clear();
	ParsingMsg << ToWxString( "Xerces3.0 Message: \"" )
	           << tMessage
	           << ToWxString( "\"" );
	Logging::GetSingletonPtr()->WriteToOgreLog( ParsingMsg,
		Logging::Trivial );
}

void XmlErrorReporter::resetErrors()
{
	this->mFoundErrors = false;
}

bool XmlErrorReporter::HasValidationErrors() const
{
	return this->mFoundErrors;
}
