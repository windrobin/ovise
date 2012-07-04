#include "XMLRPCMessageAPI.h"

XMLRPCMessageAPI::XMLRPCMessageAPI()
{}

XMLRPCMessageAPI::~XMLRPCMessageAPI()
{}

// in the specification of xmlrpc is explicitly mentioned, that one have to send '\r' and '\n' for a new line
// to gaurentee that '\r' will be send also on other platforms than windows, the string "\r\n" is used instead of std::endl

std::string XMLRPCMessageAPI::GetXMLRPCMessageHeader(const std::string& MsgName) const
{
	std::stringstream msg;

	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> " << MsgName << " </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::GetXMLRPCMessageTail() const
{
	std::stringstream msg;

	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::GetAllEntityNamesMsg() const
{
	std::stringstream msg;

	msg << GetXMLRPCMessageHeader("GetAllEntityNames");
	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCMessageAPI::GetArrayParamString(size_t NumComponents, double Val1, double Val2, double Val3, double Val4) const
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
			msg << "       <value> <double> " << Val4 << " </double> </value>" << "\r\n";
	}
	msg << "      </data>" << "\r\n";
	msg << "     </array>" << "\r\n";
	msg << "    </value>" << "\r\n";
	msg << "   </param>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::InsertEntityMsg(const std::string& Name, int Id) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("InsertEntity");

	msg << GetParamString(Name);

	if(Id >= 0)
		msg << GetParamString(Id); 

	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCMessageAPI::RemoveEntityMsg(const std::string& Name) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("RemoveEntity");

	msg << GetParamString(Name);

	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCMessageAPI::RemoveEntityMsg(int Id) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("RemoveEntity");

	msg << GetParamString(Id);

	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCMessageAPI::RemoveEntitiesByAttributeMsg(const std::string& AttributeName) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("RemoveEntitiesByAttribute");

	msg << GetParamString(AttributeName);

	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCMessageAPI::AddAttributeCreateMsg(const std::string& EntityName, const std::string& AttributeName, const std::string& DataString) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("AddAttribute");
	msg << GetParamString(EntityName);
	msg << GetParamString(AttributeName);

	msg << DataString;

	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& EntityName, const std::string& AttributeName, const vec2& AttributeValue) const
{
	return AddAttributeCreateMsg(EntityName, AttributeName, GetArrayParamString(2, AttributeValue[0], AttributeValue[1]));
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& EntityName, const std::string& AttributeName, const vec3& AttributeValue) const
{
	return AddAttributeCreateMsg(EntityName, AttributeName, GetArrayParamString(3, AttributeValue[0], AttributeValue[1], AttributeValue[2]));
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& EntityName, const std::string& AttributeName, const quat& AttributeValue) const
{
	return AddAttributeCreateMsg(EntityName, AttributeName, GetArrayParamString(4, AttributeValue[0], AttributeValue[1], AttributeValue[2], AttributeValue[3]));
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& EntityName, const std::string& AttributeType, const std::string& AttributeName, const std::string& AttributeValue) const
{
	std::string msg = "";
	
	if(AttributeType == "int" || AttributeType == "i4")
		msg = AddAttributeMsg< int >(EntityName, AttributeName, boost::lexical_cast< int >(AttributeValue));
	else if(AttributeType == "double")
		msg = AddAttributeMsg< double >(EntityName, AttributeName, boost::lexical_cast< float >(AttributeValue));
	else if(AttributeType == "boolean")
	{
		bool bVal = (AttributeValue == "true" || AttributeValue == "True" || AttributeValue == "TRUE") ? true : false;
		msg = AddAttributeMsg< bool >(EntityName, AttributeName, bVal);
	}
	else if(AttributeType == "string")
	{
		msg = AddAttributeMsg< std::string >(EntityName, AttributeName, AttributeValue);
	}
	else if(AttributeType == "vector2")
	{
		std::string val1 = "";
		std::string val2 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < AttributeValue.length(); i++)
		{
			if(AttributeValue[i] == ' ')
			{
				ws++;
				continue;
			}

			if(ws == 0)
				val1 += AttributeValue[i];
			else
				val2 += AttributeValue[i];
		}

		vec2 v;
		v[0] = boost::lexical_cast< float >(val1.c_str());
		v[1] = boost::lexical_cast< float >(val2.c_str());

		msg = AddAttributeMsg(EntityName, AttributeName, v);
	}
	else if(AttributeType == "vector3")
	{
		std::string val1 = "";
		std::string val2 = "";
		std::string val3 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < AttributeValue.length(); i++)
		{
			if(AttributeValue[i] == ' ')
			{
				ws++;
				continue;
			}

			if(ws == 0)
				val1 += AttributeValue[i];
			else if(ws == 1)
				val2 += AttributeValue[i];
			else
				val3 += AttributeValue[i];
		}

		vec3 v;
		v[0] = boost::lexical_cast< float >(val1.c_str());
		v[1] = boost::lexical_cast< float >(val2.c_str());
		v[2] = boost::lexical_cast< float >(val3.c_str());

		msg = AddAttributeMsg(EntityName, AttributeName, v);
	}
	else if(AttributeType == "quaternion")
	{
		std::string val1 = "";
		std::string val2 = "";
		std::string val3 = "";
		std::string val4 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < AttributeValue.length(); i++)
		{
			if(AttributeValue[i] == ' ')
			{
				ws++;
				continue;
			}

			if(ws == 0)
				val1 += AttributeValue[i];
			else if(ws == 1)
				val2 += AttributeValue[i];
			else if(ws == 2)
				val3 += AttributeValue[i];
			else
				val4 += AttributeValue[i];
		}

		quat q;
		q[0] = boost::lexical_cast< float >(val1.c_str());
		q[1] = boost::lexical_cast< float >(val2.c_str());
		q[2] = boost::lexical_cast< float >(val3.c_str());
		q[3] = boost::lexical_cast< float >(val4.c_str());

		msg = AddAttributeMsg(EntityName, AttributeName, q);
	}

	return msg;
}

std::string XMLRPCMessageAPI::GetAttributeMsg(const std::string& EntityName, const std::string& AttributeName) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("GetAttribute");

	msg << GetParamString(EntityName);
	msg << GetParamString(AttributeName);
	
	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCMessageAPI::GetAttributeNamesMsg(const std::string& EntityName) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("GetAttributeNames");

	msg << GetParamString(EntityName);

	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCMessageAPI::RemoveAttributeMsg(const std::string& EntityName, const std::string& AttributeName) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("RemoveAttribute");

	msg << GetParamString(EntityName);
	msg << GetParamString(AttributeName);
	
	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCMessageAPI::ChangeAttributeCreateMsg(const std::string& EntityName, const std::string& AttributeName, const std::string& DataString) const
{
	std::stringstream msg;
	msg << GetXMLRPCMessageHeader("ChangeAttribute");
	msg << GetParamString(EntityName);
	msg << GetParamString(AttributeName);

	msg << DataString;

	msg << GetXMLRPCMessageTail();

	return msg.str();
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& EntityName, const std::string& AttributeName, const vec2& Vec) const
{
	return ChangeAttributeCreateMsg(EntityName, AttributeName, GetArrayParamString(2, Vec[0], Vec[1]));
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& EntityName, const std::string& AttributeName, const vec3& Vec) const
{
	return ChangeAttributeCreateMsg(EntityName, AttributeName, GetArrayParamString(3, Vec[0], Vec[1], Vec[2]));
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& EntityName, const std::string& AttributeName, const quat& Quat) const
{
	return ChangeAttributeCreateMsg(EntityName, AttributeName, GetArrayParamString(4, Quat[0], Quat[1], Quat[2], Quat[3]));
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& EntityName, const std::string& AttributeName, const std::string& AttributeType, const std::string& AttributeValue) const
{
	std::string msg = "";
	
	if(AttributeType == "int" || AttributeType == "i4")
		msg = ChangeAttributeMsg< int >(EntityName, AttributeName, boost::lexical_cast< int >(AttributeValue));
	else if(AttributeType == "double")
		msg = ChangeAttributeMsg< double >(EntityName, AttributeName, boost::lexical_cast< float >(AttributeValue));
	else if(AttributeType == "boolean")
	{
		bool bVal = (AttributeValue == "true" || AttributeValue == "True" || AttributeValue == "TRUE") ? true : false;
		msg = ChangeAttributeMsg< bool >(EntityName, AttributeName, bVal);
	}
	else if(AttributeType == "string")
	{
		msg = ChangeAttributeMsg< std::string >(EntityName, AttributeName, AttributeValue);
	}
	else if(AttributeType == "vector2")
	{
		std::string val1 = "";
		std::string val2 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < AttributeValue.length(); i++)
		{
			if(AttributeValue[i] == ' ')
			{
				ws++;
				continue;
			}

			if(ws == 0)
				val1 += AttributeValue[i];
			else
				val2 += AttributeValue[i];
		}

		vec2 v;
		v[0] = boost::lexical_cast< float >(val1.c_str());
		v[1] = boost::lexical_cast< float >(val2.c_str());

		msg = ChangeAttributeMsg(EntityName, AttributeName, v);
	}
	else if(AttributeType == "vector3")
	{
		std::string val1 = "";
		std::string val2 = "";
		std::string val3 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < AttributeValue.length(); i++)
		{
			if(AttributeValue[i] == ' ')
			{
				ws++;
				continue;
			}

			if(ws == 0)
				val1 += AttributeValue[i];
			else if(ws == 1)
				val2 += AttributeValue[i];
			else
				val3 += AttributeValue[i];
		}

		vec3 v;
		v[0] = boost::lexical_cast< float >(val1.c_str());
		v[1] = boost::lexical_cast< float >(val2.c_str());
		v[2] = boost::lexical_cast< float >(val3.c_str());

		msg = ChangeAttributeMsg(EntityName, AttributeName, v);
	}
	else if(AttributeType == "quaternion")
	{
		std::string val1 = "";
		std::string val2 = "";
		std::string val3 = "";
		std::string val4 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < AttributeValue.length(); i++)
		{
			if(AttributeValue[i] == ' ')
			{
				ws++;
				continue;
			}

			if(ws == 0)
				val1 += AttributeValue[i];
			else if(ws == 1)
				val2 += AttributeValue[i];
			else if(ws == 2)
				val3 += AttributeValue[i];
			else
				val4 += AttributeValue[i];
		}

		quat q;
		q[0] = boost::lexical_cast< float >(val1.c_str());
		q[1] = boost::lexical_cast< float >(val2.c_str());
		q[2] = boost::lexical_cast< float >(val3.c_str());
		q[3] = boost::lexical_cast< float >(val4.c_str());

		msg = ChangeAttributeMsg(EntityName, AttributeName, q);
	}

	return msg;
}
