#include "../rapidxml-1.13/rapidxml.hpp"

#include <map>
#include <string>

#include <Entity.h>

class CVoodooParser
{
public:
	CVoodooParser();
	CVoodooParser( int ModelID );

	bool LoadBodyMapping();
	bool ParseDocument( rapidxml::xml_document<>& Document );
	void UpdateEntity( Entity* Ent );

private:
	struct Limb
	{
		Limb() { quat[0] = quat[1] = quat[2] = 0.f; quat[3] = 1.f; }
		double quat[4];
		int ModelID;
		int LimbID;
		std::string LimbName;
	};

	typedef std::map<int, CVoodooParser::Limb> LimbMapType;

	LimbMapType mLimbMap;
	int mModelID;
	std::map<int, std::string> mBodyMapping;
	bool mMappingLoaded;
};
