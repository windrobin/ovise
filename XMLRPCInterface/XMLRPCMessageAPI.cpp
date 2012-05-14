#include "XMLRPCMessageAPI.h"

XMLRPCMessageAPI::XMLRPCMessageAPI()
{}

XMLRPCMessageAPI::~XMLRPCMessageAPI()
{}

std::string XMLRPCMessageAPI::GetAllEntityNamesMsg() const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> getAllEntityNames </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::InsertEntityMsg(const std::string& _name) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> insertEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _name << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::InsertEntityMsg(const std::string& _name, int _id) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> insertEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _name << "  </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <i4> " << _id << " </i4> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::RemoveEntityMsg(const std::string& _name) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> removeEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _name << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::RemoveEntityMsg(int _id) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> removeEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <i4> " << _id << " </i4> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::RemoveEntitiesByAttributeMsg(const std::string& _attributeName) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> removeEntitiesByAttribute </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& _entityName, const std::string& _attributeName, int _attributeValue) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> addAttribute </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <i4> " << _attributeValue << " </i4> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& _entityName, const std::string& _attributeName, bool _attributeValue) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> addAttribute </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <boolean> " << _attributeValue << " </boolean> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& _entityName, const std::string& _attributeName, double _attributeValue) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> addAttribute </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <double> " << _attributeValue << " </double> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const std::string& _attributeValue) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> addAttribute </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeValue << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const vec2& _vec) const
{
	std::stringstream msg;

	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> addAttribute </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <array>" << "\r\n";
	msg << "     <data>" << "\r\n";
	msg << "      <value> <string> " << "vector2" << " </string> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[0] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[1] << " </double> </value>" << "\r\n";
	msg << "     </data>" << "\r\n";
	msg << "    </array>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const vec3& _vec) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> addAttribute </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <array>" << "\r\n";
	msg << "     <data>" << "\r\n";
	msg << "      <value> <string> " << "vector3" << " </string> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[0] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[1] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[2] << " </double> </value>" << "\r\n";
	msg << "     </data>" << "\r\n";
	msg << "    </array>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const vec4& _vec) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> addAttribute </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <array>" << "\r\n";
	msg << "     <data>" << "\r\n";
	msg << "      <value> <string> " << "vector4" << " </string> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[0] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[1] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[2] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[3] << " </double> </value>" << "\r\n";
	msg << "     </data>" << "\r\n";
	msg << "    </array>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const quat& _quat) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> addAttribute </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <array>" << "\r\n";
	msg << "     <data>" << "\r\n";
	msg << "      <value> <string> " << "quaternion" << " </string> </value>" << "\r\n";
	msg << "      <value> <double> " << _quat[0] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _quat[1] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _quat[2] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _quat[3] << " </double> </value>" << "\r\n";
	msg << "     </data>" << "\r\n";
	msg << "    </array>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::AddAttributeMsg(const std::string& _entityName, const std::string& _attributeType, const std::string& _attributeName, const std::string& _attributeValue) const
{
	std::string msg = "";
	
	if(_attributeType == "int" || _attributeType == "i4")
		msg = AddAttributeMsg(_entityName, _attributeName, atoi(_attributeValue.c_str()));
	else if(_attributeType == "double")
		msg = AddAttributeMsg(_entityName, _attributeName, atof(_attributeValue.c_str()));
	else if(_attributeType == "boolean")
	{
		bool bVal = (_attributeValue == "true" || _attributeValue == "True" || _attributeValue == "TRUE") ? true : false;
		msg = AddAttributeMsg(_entityName, _attributeName, bVal);
	}
	else if(_attributeType == "string")
	{
		msg = AddAttributeMsg(_entityName, _attributeName, _attributeValue);
	}
	else if(_attributeType == "vector2")
	{
		std::string val1 = "";
		std::string val2 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < _attributeValue.length(); i++)
		{
			if(_attributeValue[i] == ' ')
				ws++;

			if(ws == 0)
				val1 += _attributeValue[i];
			else
				val2 += _attributeValue[i];
		}

		vec2 v;
		v[0] = atof(val1.c_str());
		v[1] = atof(val2.c_str());

		msg = AddAttributeMsg(_entityName, _attributeName, v);
	}
	else if(_attributeType == "vector3")
	{
		std::string val1 = "";
		std::string val2 = "";
		std::string val3 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < _attributeValue.length(); i++)
		{
			if(_attributeValue[i] == ' ')
				ws++;

			if(ws == 0)
				val1 += _attributeValue[i];
			else if(ws == 1)
				val2 += _attributeValue[i];
			else
				val3 += _attributeValue[i];
		}

		vec3 v;
		v[0] = atof(val1.c_str());
		v[1] = atof(val2.c_str());
		v[2] = atof(val3.c_str());

		msg = AddAttributeMsg(_entityName, _attributeName, v);
	}
	else if(_attributeType == "vector4")
	{
		std::string val1 = "";
		std::string val2 = "";
		std::string val3 = "";
		std::string val4 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < _attributeValue.length(); i++)
		{
			if(_attributeValue[i] == ' ')
				ws++;

			if(ws == 0)
				val1 += _attributeValue[i];
			else if(ws == 1)
				val2 += _attributeValue[i];
			else if(ws == 2)
				val3 += _attributeValue[i];
			else
				val4 += _attributeValue[i];
		}

		vec4 v;
		v[0] = atof(val1.c_str());
		v[1] = atof(val2.c_str());
		v[2] = atof(val3.c_str());
		v[3] = atof(val4.c_str());

		msg = AddAttributeMsg(_entityName, _attributeName, v);
	}
	else if(_attributeType == "quaternion")
	{
		std::string val1 = "";
		std::string val2 = "";
		std::string val3 = "";
		std::string val4 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < _attributeValue.length(); i++)
		{
			if(_attributeValue[i] == ' ')
				ws++;

			if(ws == 0)
				val1 += _attributeValue[i];
			else if(ws == 1)
				val2 += _attributeValue[i];
			else if(ws == 2)
				val3 += _attributeValue[i];
			else
				val4 += _attributeValue[i];
		}

		quat q;
		q[0] = atof(val1.c_str());
		q[1] = atof(val2.c_str());
		q[2] = atof(val3.c_str());
		q[3] = atof(val4.c_str());

		msg = AddAttributeMsg(_entityName, _attributeName, q);
	}

	return msg;
}

std::string XMLRPCMessageAPI::GetAttributeMsg(const std::string& _entityName, const std::string& _attributeName) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> getAttribute </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::GetAttributeNamesFromEntityMsg(const std::string& _entityName) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> getAttributeNamesFromEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::RemoveAttributeFromEntityMsg(const std::string& _entityName, const std::string& _attributeName) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> removeAttributeFromEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& _entityName, const std::string& _attributeName, int _attributeValue) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> changeAttributeOfEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <i4> " << _attributeValue << " </i4> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& _entityName, const std::string& _attributeName, bool _attributeValue) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> changeAttributeOfEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <boolean> " << _attributeValue << " </boolean> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& _entityName, const std::string& _attributeName, double _attributeValue) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> changeAttributeOfEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <double> " << _attributeValue << " </double> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const std::string& _attributeValue) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> changeAttributeOfEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeValue << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const vec2& _vec) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> changeAttributeOfEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <array>" << "\r\n";
	msg << "     <data>" << "\r\n";
	msg << "      <value> <string> " << "vector2" << " </string> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[0] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[1] << " </double> </value>" << "\r\n";
	msg << "     </data>" << "\r\n";
	msg << "    </array>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const vec3& _vec) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> changeAttributeOfEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <array>" << "\r\n";
	msg << "     <data>" << "\r\n";
	msg << "      <value> <string> " << "vector3" << " </string> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[0] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[1] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[2] << " </double> </value>" << "\r\n";
	msg << "     </data>" << "\r\n";
	msg << "    </array>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const vec4& _vec) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> changeAttributeOfEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <array>" << "\r\n";
	msg << "     <data>" << "\r\n";
	msg << "      <value> <string> " << "vector4" << " </string> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[0] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[1] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[2] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[3] << " </double> </value>" << "\r\n";
	msg << "     </data>" << "\r\n";
	msg << "    </array>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const quat& _quat) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> changeAttributeOfEntity </methodName>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _entityName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <array>" << "\r\n";
	msg << "     <data>" << "\r\n";
	msg << "      <value> <string> " << "quaternion" << " </string> </value>" << "\r\n";
	msg << "      <value> <double> " << _quat[0] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _quat[1] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _quat[2] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _quat[3] << " </double> </value>" << "\r\n";
	msg << "     </data>" << "\r\n";
	msg << "    </array>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::ChangeAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const std::string& _attributeType, const std::string& _attributeValue) const
{
	std::string msg = "";
	
	if(_attributeType == "int" || _attributeType == "i4")
		msg = ChangeAttributeMsg(_entityName, _attributeName, atoi(_attributeValue.c_str()));
	else if(_attributeType == "double")
		msg = ChangeAttributeMsg(_entityName, _attributeName, atof(_attributeValue.c_str()));
	else if(_attributeType == "boolean")
	{
		bool bVal = (_attributeValue == "true" || _attributeValue == "True" || _attributeValue == "TRUE") ? true : false;
		msg = ChangeAttributeMsg(_entityName, _attributeName, bVal);
	}
	else if(_attributeType == "string")
	{
		msg = ChangeAttributeMsg(_entityName, _attributeName, _attributeValue);
	}
	else if(_attributeType == "vector2")
	{
		std::string val1 = "";
		std::string val2 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < _attributeValue.length(); i++)
		{
			if(_attributeValue[i] == ' ')
				ws++;

			if(ws == 0)
				val1 += _attributeValue[i];
			else
				val2 += _attributeValue[i];
		}

		vec2 v;
		v[0] = atof(val1.c_str());
		v[1] = atof(val2.c_str());

		msg = ChangeAttributeMsg(_entityName, _attributeName, v);
	}
	else if(_attributeType == "vector3")
	{
		std::string val1 = "";
		std::string val2 = "";
		std::string val3 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < _attributeValue.length(); i++)
		{
			if(_attributeValue[i] == ' ')
				ws++;

			if(ws == 0)
				val1 += _attributeValue[i];
			else if(ws == 1)
				val2 += _attributeValue[i];
			else
				val3 += _attributeValue[i];
		}

		vec3 v;
		v[0] = atof(val1.c_str());
		v[1] = atof(val2.c_str());
		v[2] = atof(val3.c_str());

		msg = ChangeAttributeMsg(_entityName, _attributeName, v);
	}
	else if(_attributeType == "vector4")
	{
		std::string val1 = "";
		std::string val2 = "";
		std::string val3 = "";
		std::string val4 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < _attributeValue.length(); i++)
		{
			if(_attributeValue[i] == ' ')
				ws++;

			if(ws == 0)
				val1 += _attributeValue[i];
			else if(ws == 1)
				val2 += _attributeValue[i];
			else if(ws == 2)
				val3 += _attributeValue[i];
			else
				val4 += _attributeValue[i];
		}

		vec4 v;
		v[0] = atof(val1.c_str());
		v[1] = atof(val2.c_str());
		v[2] = atof(val3.c_str());
		v[3] = atof(val4.c_str());

		msg = ChangeAttributeMsg(_entityName, _attributeName, v);
	}
	else if(_attributeType == "quaternion")
	{
		std::string val1 = "";
		std::string val2 = "";
		std::string val3 = "";
		std::string val4 = "";

		unsigned int ws = 0;
		for(unsigned int i = 0; i < _attributeValue.length(); i++)
		{
			if(_attributeValue[i] == ' ')
				ws++;

			if(ws == 0)
				val1 += _attributeValue[i];
			else if(ws == 1)
				val2 += _attributeValue[i];
			else if(ws == 2)
				val3 += _attributeValue[i];
			else
				val4 += _attributeValue[i];
		}

		quat q;
		q[0] = atof(val1.c_str());
		q[1] = atof(val2.c_str());
		q[2] = atof(val3.c_str());
		q[3] = atof(val4.c_str());

		msg = ChangeAttributeMsg(_entityName, _attributeName, q);
	}

	return msg;
}
