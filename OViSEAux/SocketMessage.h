#ifndef OVISE_SOCKET_MESSAGE_H
#define OVISE_SOCKET_MESSAGE_H

#include <wx/string.h>
#include <vector>

class SocketMessage
{
public:
	SocketMessage();
	~SocketMessage();

	bool Parse( wxString MessageStr );

	const wxString& GetCommand();
	const std::vector<wxString>& GetArguments();

private:
	wxString RawMessage;
	wxString Command;
	std::vector<wxString> Arguments;
};

#endif // OVISE_SOCKET_MESSAGE_H
