#ifndef OVISE_PLUGIN_MANAGER_H
#define OVISE_PLUGIN_MANAGER_H

#include <wx/propdlg.h>
#include <vector>
#include "../Util/Plugin.h"

class CInterfaceManager;
class SceneView;


class CPluginManager
{
public:
	CPluginManager();
	~CPluginManager();

	void LoadPlugins( const wxString& BasePath, wxWindow* Parent );
	void UnloadPlugins();

	void InitNWPlugins( CInterfaceManager& IManager );
	void InitVIPlugins( SceneView& View );
	void InitSSPlugins();

	const std::vector<CPlugin>& GetPlugins() const;

private:	
	std::vector<CPlugin> mPlugins;
};

#endif // OVISE_PLUGIN_MANAGER_H
