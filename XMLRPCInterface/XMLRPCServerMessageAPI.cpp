#include "XMLRPCServerMessageAPI.h"

XMLRPCServerMessageAPI::XMLRPCServerMessageAPI()
{}

XMLRPCServerMessageAPI::~XMLRPCServerMessageAPI()
{}

std::string XMLRPCServerMessageAPI::GetXMLRPCMessageHeader(const std::string& MsgName) const
{
	std::stringstream msg;

	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodResponse>" << "\r\n";
	msg << " <methodName> " << MsgName << " </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";

	return msg.str();
}

std::string XMLRPCServerMessageAPI::GetXMLRPCMessageTail() const
{
	std::stringstream msg;

	msg << "  </params>" << "\r\n";
	msg << "</methodResponse>" << "\r\n";

	return msg.str();
}

std::string XMLRPCServerMessageAPI::GetArrayParamString(size_t NumComponents, double Val1, double Val2, double Val3, double Val4) const
{
	if(NumComponents < 2 || NumComponents > 4)
		throw WrongParameterNumberException();

	std::stringstream msg;
	msg << "   <param>" << "\r\n";
	msg << "    <value>" << "\r\n";
	msg << "     <array>" << "\r\n";
	msg << "      <data>" << "\r\n";
	msg << "       <value> <double> " << Val1 << " </double> </value>" << "\r\n";
	msg << "       <value> <double> " << Val2 << " </double> </value>" << "\r\n";
	if(NumComponents == 3)
	{
		msg << "       <value> <double> " << Val3 << " </double> </value>" << "\r\n";

		if(NumComponents == 4)
			msg << "      <value> <double> " << Val4 << " </double> </value>" << "\r\n";
	}
	msg << "      </data>" << "\r\n";
	msg << "     </array>" << "\r\n";
	msg << "    </value>" << "\r\n";
	msg << "   </param>" << "\r\n";

	return msg.str();
}

std::string XMLRPCServerMessageAPI::ErrorResponseMsg(const std::string& Error) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("ErrorResponse");

	msg << GetParamString(Error);
	
	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCServerMessageAPI::StatusResponseMsg(const std::string& Status) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("StatusResponse");

	msg << GetParamString(Status);
	
	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCServerMessageAPI::AllEntityNamesResponseMsg(const std::vector< std::string >& Names) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("AllEntityNamesResponse");

	msg << "   <param>" << "\r\n";
	msg << "    <array>" << "\r\n";
	msg << "     <data>" << "\r\n";

	std::vector< std::string >::const_iterator it = Names.begin();
	while(it != Names.end())
	{
		msg << "      <value> <string> " << (*it) << " </string> </value>" << "\r\n";
		it++;
	}

	msg << "     </data>" << "\r\n";
	msg << "    </array>" << "\r\n";
	msg << "   </param>" << "\r\n";
	
	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCServerMessageAPI::AttributeCreateResponseMsg(const std::string& DataString) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("AttributeResponse");
	msg << DataString;
	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCServerMessageAPI::AttributeResponseMsg(const vec2& Val) const
{
	return AttributeCreateResponseMsg(GetArrayParamString(2, Val[0], Val[1]));
}

std::string XMLRPCServerMessageAPI::AttributeResponseMsg(const vec3& Val) const
{
	return AttributeCreateResponseMsg(GetArrayParamString(3, Val[0], Val[1], Val[2]));
}

std::string XMLRPCServerMessageAPI::AttributeResponseMsg(const vec4& Val) const
{
	return AttributeCreateResponseMsg(GetArrayParamString(4, Val[0], Val[1], Val[2], Val[3]));
}

std::string XMLRPCServerMessageAPI::AttributeResponseMsg(const quat& Quat) const
{
	return AttributeCreateResponseMsg(GetArrayParamString(4, Quat[0], Quat[1], Quat[2], Quat[3]));
}

std::string XMLRPCServerMessageAPI::AllAttributeNamesResponseMsg(const std::vector< std::string >& Names) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("AttributeResponse");

	msg << "   <param>" << "\r\n";
	msg << "    <array>" << "\r\n";
	msg << "     <data>" << "\r\n";

	std::vector< std::string >::const_iterator it = Names.begin();
	while(it != Names.end())
	{
		msg << "      <value> <string> " << (*it) << " </string> </value>" << "\r\n";
		it++;
	}

	msg << "     </data>" << "\r\n";
	msg << "    </array>" << "\r\n";
	msg << "   </param>" << "\r\n";
	
	msg << GetXMLRPCMessageTail();

	return msg.str();
}
