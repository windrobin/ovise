#ifndef OVISE_PLUGIN_MANAGER_H
#define OVISE_PLUGIN_MANAGER_H

#include <wx/propdlg.h>
#include <wx/dynlib.h>

#include <map>

#include "PluginBase.h"
#include "InterfaceManager.h"
#include <SceneView.h>

class EntityPool;

typedef boost::shared_ptr<CPluginBase> DllPtr;

class CPluginManager
{
public:
	explicit CPluginManager( EntityPool& EntPool, SceneView* SView, wxWindow* Parent );
	~CPluginManager();

	void LoadPlugins( const wxString& BasePath );
	void UnloadPlugins();

	template<class PluginType> inline
	void RegisterNetworkPlugin( const std::string& Name )
	{
		mPlugins[Name].reset( new PluginType( mEntityPool, Name ) );
		mInterfaceManager.AddInterface( Name, static_cast<CNetworkInterface*>( mPlugins[Name].get() ) );
		//mInterfaceManager.GetInterface( Name ).CreateConfigDialog( mParentWindow );
	}

	template<class PluginType> inline
	void RegisterVisualPlugin( const std::string& Name )
	{
		mSceneView->RegisterView<PluginType>( Name );
		mPlugins[Name].reset( new CPluginBase( Name, CPluginBase::PLUGIN_TYPE_VISUAL ) );
	}

	const std::map<std::string, DllPtr>& GetPlugins() const;

	CInterfaceManager& GetInterfaceManager() { return mInterfaceManager; }

private:
	void LoadPlugin( const wxString& Path, const wxString& FileName );

	std::map<std::string, DllPtr> mPlugins;
	std::map<wxString, boost::shared_ptr<wxDynamicLibrary> > mPluginHandles;
	
	EntityPool&       mEntityPool;
	CInterfaceManager mInterfaceManager;
	SceneView*        mSceneView;
	
	wxWindow*         mParentWindow;
};

#endif // OVISE_PLUGIN_MANAGER_H
