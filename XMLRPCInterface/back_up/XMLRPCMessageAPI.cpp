#include "XMLRPCMessageAPI.h"

XMLRPCMessageAPI::XMLRPCMessageAPI()
{}

XMLRPCMessageAPI::~XMLRPCMessageAPI()
{}

std::string XMLRPCMessageAPI::insertEntityMsg(const std::string& _name) const
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

std::string XMLRPCMessageAPI::insertEntityMsg(const std::string& _name, int _id) const
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

std::string XMLRPCMessageAPI::removeEntityMsg(const std::string& _name) const
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

std::string XMLRPCMessageAPI::removeEntityMsg(int _id) const
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

std::string XMLRPCMessageAPI::removeEntitiesByAttributeMsg(const std::string& _attributeName) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> removeEntityByAttribute </methodCall>" << "\r\n";
	msg << "  <params>" << "\r\n";
	msg << "   <param>" << "\r\n";
	msg << "    <value> <string> " << _attributeName << " </string> </value>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, int _attributeValue) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> addAttribute </methodCall>" << "\r\n";
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

std::string XMLRPCMessageAPI::addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, bool _attributeValue) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> addAttribute </methodCall>" << "\r\n";
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

std::string XMLRPCMessageAPI::addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, double _attributeValue) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> addAttribute </methodCall>" << "\r\n";
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

std::string XMLRPCMessageAPI::addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const std::string& _attributeValue) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> addAttribute </methodCall>" << "\r\n";
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

std::string XMLRPCMessageAPI::addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const vec2& _vec) const
{
	std::stringstream msg;
	/*msg << "<?xml version=\"1.0\"?>" << std::endl;
	msg << "<methodCall>" << std::endl;
	msg << " <methodName> addAttribute </methodName>" << std::endl;
	msg << "  <params>" << std::endl;
	msg << "   <param>" << std::endl;
	msg << "    <value> <double> " << _vec[0] << " </double> </value>" << std::endl;
	msg << "   </param>" << std::endl;
	msg << "   <param>" << std::endl;
	msg << "    <value> <double> " << _vec[1] << " </double> </value>" << std::endl;
	msg << "   </param>" << std::endl;
	msg << "  </params>" << std::endl;
	msg << "</methodCall>" << std::endl;*/


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
	msg << "      <value> <string> " << "vector2" << " </string> </value<" << "\r\n";
	msg << "      <value> <double> " << _vec[0] << " </double> </value>" << "\r\n";
	msg << "      <value> <double> " << _vec[1] << " </double> </value>" << "\r\n";
	msg << "     </data>" << "\r\n";
	msg << "    </array>" << "\r\n";
	msg << "   </param>" << "\r\n";
	msg << "  </params>" << "\r\n";
	msg << "</methodCall>" << "\r\n";

	return msg.str();
}

std::string XMLRPCMessageAPI::addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const vec3& _vec) const
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

std::string XMLRPCMessageAPI::addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const vec4& _vec) const
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

std::string XMLRPCMessageAPI::addAttributeMsg(const std::string& _entityName, const std::string& _attributeName, const quat& _quat) const
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

std::string XMLRPCMessageAPI::removeAttributeMsg(const std::string& _entityName, const std::string& _attributeName) const
{
	std::stringstream msg;
	msg << "<?xml version=\"1.0\"?>" << "\r\n";
	msg << "<methodCall>" << "\r\n";
	msg << " <methodName> removeEntityByAttribute </methodCall>" << "\r\n";
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
