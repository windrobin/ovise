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

void CPluginManager::LoadPlugins( const wxString& BasePath )
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

			DllPtr NWLibPtr( new wxDynamicLibrary() );
			NWLibPtr->Load( NWPluginPath + NWFilename );
			mNetworkPlugins.push_back( std::make_pair( NWFilename, NWLibPtr ) );
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

			DllPtr VILibPtr( new wxDynamicLibrary() );
			VILibPtr->Load( VIPluginPath + VIFilename );
			mVisualizationPlugins.push_back( std::make_pair( VIFilename, VILibPtr ) );
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

			DllPtr SSLibPtr( new wxDynamicLibrary() );
			SSLibPtr->Load( SSPluginPath + SSFilename );
			mSensorPlugins.push_back( std::make_pair( SSFilename, SSLibPtr ) );
		}
	}
}

void CPluginManager::UnloadPlugins()
{
	for( std::vector<DllEntry>::iterator i = mNetworkPlugins.begin();
		i != mNetworkPlugins.end();
		i++ )
	{
		i->second.reset();
	}

	for( std::vector<DllEntry>::iterator i = mVisualizationPlugins.begin();
		i != mVisualizationPlugins.end();
		i++ )
	{
		i->second.reset();
	}

	for( std::vector<DllEntry>::iterator i = mSensorPlugins.begin();
		i != mSensorPlugins.end();
		i++ )
	{
		i->second.reset();
	}
}

void CPluginManager::InitNWPlugins( CInterfaceManager& IManager )
{
	typedef void ( *FunctionType )( CInterfaceManager& );

	for( std::vector<DllEntry>::iterator i = mNetworkPlugins.begin();
		i != mNetworkPlugins.end();
		i++ )
	{
		bool Success;
		void* Function = i->second->GetSymbol( wxT( "LoadInterface" ), &Success );
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

	for( std::vector<DllEntry>::iterator i = mVisualizationPlugins.begin();
		i != mVisualizationPlugins.end();
		i++ )
	{
		bool Success;
		void* Function = i->second->GetSymbol( wxT( "LoadEntityView" ), &Success );
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

const std::vector<CPluginManager::DllEntry> CPluginManager::GetNetworkPlugins() const
{
	return mNetworkPlugins;
}

const std::vector<CPluginManager::DllEntry> CPluginManager::GetVisualizationPlugins() const
{
	return mVisualizationPlugins;
}

const std::vector<CPluginManager::DllEntry> CPluginManager::GetSensorPlugins() const
{
	return mSensorPlugins;
}
