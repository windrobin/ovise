#ifndef OVISE_PLUGIN_MANAGER_H
#define OVISE_PLUGIN_MANAGER_H

#include <wx/propdlg.h>
#include <wx/dynlib.h>

#include <map>

#include "../Util/PluginBase.h"
#include "../Util/InterfaceManager.h"

class EntityPool;
class SceneView;

typedef boost::shared_ptr<CPluginBase> DllPtr;

class CPluginManager
{
public:
	explicit CPluginManager( EntityPool& EntPool, wxWindow* Parent );
	~CPluginManager();

	void LoadPlugins( const wxString& BasePath );
	void UnloadPlugins();

	template<class PluginType> inline
	void RegisterPlugin( const std::string& Name, const int Type )
	{
		switch( Type )
		{
		case CPluginBase::PLUGIN_TYPE_NETWORK:
			mPlugins[Name].reset( new PluginType( mEntityPool, Name ) );
			mInterfaceManager.AddInterface( Name, dynamic_cast<CNetworkInterface*>( mPlugins[Name].get() ) );
			mPlugins[Name]->CreateConfigDialog( mParentWindow );
			break;
		case CPluginBase::PLUGIN_TYPE_VISUAL:
			mPlugins[Name].reset( new PluginType( Name ) );
			break;
		case CPluginBase::PLUGIN_TYPE_SENSOR:
			break;
		default: break;
		}
	}

	const std::map<std::string, DllPtr>& GetPlugins() const;

	const CInterfaceManager& GetInterfaceManager();

private:
	void LoadPlugin( const wxString& Path, const wxString& FileName );

	std::map<std::string, DllPtr> mPlugins;
	std::map<wxString, boost::shared_ptr<wxDynamicLibrary> > mPluginHandles;
	
	EntityPool& mEntityPool;
	CInterfaceManager mInterfaceManager;
	
	wxWindow* mParentWindow;
};

#endif // OVISE_PLUGIN_MANAGER_H
