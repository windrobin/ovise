#include "PluginManager.h"

#include <wx/dir.h>

namespace {
bool CheckFileName( const wxString& Filename )
{
#ifdef WIN32
	return Filename.EndsWith( wxT(".dll") );
#else
	return Filename.EndsWith( wxT(".so") );
#endif
}
}


CPluginManager::CPluginManager()
{
}

CPluginManager::~CPluginManager()
{
}

void CPluginManager::LoadPlugins( const wxString& BasePath, wxWindow* Parent )
{
	wxString NWPluginPath; // network
	wxString VIPluginPath; // visualization
	wxString SSPluginPath; // sensors

#ifdef WIN32
#ifdef NDEBUG
	NWPluginPath = BasePath + "/Interfaces/Release/";
	VIPluginPath = BasePath + "/Visualization/Release/";
	SSPluginPath = BasePath + "/Sensors/Release/";
#else
	NWPluginPath = BasePath + "/Interfaces/Debug/";
	VIPluginPath = BasePath + "/Visualization/Debug/";
	SSPluginPath = BasePath + "/Sensors/Debug/";
#endif
#else
	NWPluginPath = BasePath + "/Interfaces/";
	VIPluginPath = BasePath + "/Visualization/";
	SSPluginPath = BasePath + "/Sensors/";
#endif
	wxDir NWDirectory( NWPluginPath );
	wxDir VIDirectory( VIPluginPath );
	wxDir SSDirectory( SSPluginPath );

	if ( NWDirectory.IsOpened() )
	{
		// Check for DLL files
		wxString NWFilename;
		for ( bool c=NWDirectory.GetFirst( &NWFilename );
				c;
				c=NWDirectory.GetNext( &NWFilename ) )
		{
			//std::cout << "Loading network plugin " << Filename << std::endl;
			if( !CheckFileName( NWFilename ) )
				continue;

			CPlugin Plugin;
			Plugin.Load( NWPluginPath + NWFilename, Plugin::TYPE_NETWORK, Parent );
			mPlugins.push_back( Plugin );
		}
	}

	if ( VIDirectory.IsOpened() )
	{
		// Check for DLL files
		wxString VIFilename;
		for ( bool c=VIDirectory.GetFirst( &VIFilename );
				c;
				c=VIDirectory.GetNext( &VIFilename ) )
		{
			//std::cout << "Loading network plugin " << Filename << std::endl;
			if( !CheckFileName( VIFilename ) )
				continue;

			CPlugin Plugin;
			Plugin.Load( VIPluginPath + VIFilename, Plugin::TYPE_VISUAL, Parent );
			mPlugins.push_back( Plugin );
		}
	}

	if ( SSDirectory.IsOpened() )
	{
		// Check for DLL files
		wxString SSFilename;
		for ( bool c=SSDirectory.GetFirst( &SSFilename );
				c;
				c=SSDirectory.GetNext( &SSFilename ) )
		{
			//std::cout << "Loading network plugin " << Filename << std::endl;
			if( !CheckFileName( SSFilename ) )
				continue;

			CPlugin Plugin;
			Plugin.Load( SSPluginPath + SSFilename, Plugin::TYPE_SENSOR, Parent );
			mPlugins.push_back( Plugin );
		}
	}
}

void CPluginManager::UnloadPlugins()
{
	for( std::vector<CPlugin>::iterator i = mPlugins.begin();
		i != mPlugins.end();
		i++ )
	{
		i->Unload();
	}
	mPlugins.clear();
}

void CPluginManager::InitNWPlugins( CInterfaceManager& IManager )
{
	typedef void ( *FunctionType )( CInterfaceManager& );

	for( std::vector<CPlugin>::iterator i = mPlugins.begin();
		i != mPlugins.end();
		i++ )
	{
		if( i->mType != Plugin::TYPE_NETWORK ) continue;
		
		bool Success;
		void* Function = i->mDllPointer->GetSymbol( wxT( "LoadInterface" ), &Success );
		if( Success && Function )
		{
			FunctionType f = reinterpret_cast<FunctionType>( Function );
			f( IManager );
		}
	}
}

void CPluginManager::InitVIPlugins( SceneView& View )
{
	typedef void ( *FunctionType )( SceneView& );

	for( std::vector<CPlugin>::iterator i = mPlugins.begin();
		i != mPlugins.end();
		i++ )
	{
		if( i->mType != Plugin::TYPE_VISUAL ) continue;
		
		bool Success;
		void* Function = i->mDllPointer->GetSymbol( wxT( "LoadEntityView" ), &Success );
		if( Success && Function )
		{
			FunctionType f = reinterpret_cast<FunctionType>( Function );
			f( View );
		}
	}
}

void CPluginManager::InitSSPlugins()
{

}

const std::vector<CPlugin>& CPluginManager::GetPlugins() const
{
	
	return mPlugins;
}
