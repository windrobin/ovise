#ifndef OVISE_PLUGIN_MANAGER_H
#define OVISE_PLUGIN_MANAGER_H

#include <wx/dynlib.h>
#include <boost/shared_ptr.hpp>
#include <vector>

class CInterfaceManager;
class SceneView;

class CPluginManager
{
public:
	CPluginManager();
	~CPluginManager();

	void LoadPlugins( const wxString& BasePath );
	void UnloadPlugins();

	void InitNWPlugins( CInterfaceManager& IManager );
	void InitVIPlugins( SceneView& View );
	void InitSSPlugins();

	typedef boost::shared_ptr<wxDynamicLibrary> DllPtr;
	typedef std::pair<wxString, DllPtr> DllEntry;

	const std::vector<DllEntry> GetNetworkPlugins() const;
	const std::vector<DllEntry> GetVisualizationPlugins() const;
	const std::vector<DllEntry> GetSensorPlugins() const;

private:	
	std::vector<DllEntry> mNetworkPlugins;
	std::vector<DllEntry> mVisualizationPlugins;
	std::vector<DllEntry> mSensorPlugins;
};

#endif // OVISE_PLUGIN_MANAGER_H
