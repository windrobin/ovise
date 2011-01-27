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
		double xPos;
		double yPos;
		double zPos;
		double z0;
		double y1;
		double z2;
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
