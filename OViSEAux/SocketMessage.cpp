#include "SocketMessage.h"
#include <wx/tokenzr.h>

SocketMessage::SocketMessage(void)
: RawMessage( wxEmptyString ), Command( wxEmptyString )
{
}

SocketMessage::~SocketMessage(void)
{
}

bool SocketMessage::Parse( wxString MessageStr )
{
	if( MessageStr.StartsWith( wxT( ":" ) ) )
		return false;
	// Commands should be formatted like: command:arg1:arg2:arg3:...
	wxStringTokenizer Tokenizer( MessageStr, wxT(":") );
	Command = Tokenizer.GetNextToken();
	while( Tokenizer.HasMoreTokens() )
	{
		Arguments.push_back( Tokenizer.GetNextToken() );
	}

	return true;
}

const wxString& SocketMessage::GetCommand()
{
	return Command;
}

const std::vector<wxString>& SocketMessage::GetArguments()
{
	return Arguments;
}