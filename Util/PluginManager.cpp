#include "PluginManager.h"

#include <wx/dir.h>

namespace {
bool CheckFileName( const wxString& Filename )
{
#ifdef WIN32
#ifndef NDEBUG
	return Filename.EndsWith( wxT("_D.dll" ) );
#else
	return Filename.EndsWith( wxT(".dll") );
#endif
#else
#ifndef NDEBUG
	return Filename.EndsWith( wxT("_D.so" ) );
#else
	return Filename.EndsWith( wxT(".so") );
#endif
#endif
}
}


CPluginManager::CPluginManager( EntityPool& EntPool, SceneView* SView, wxWindow* Parent )
	: mEntityPool( EntPool ), mSceneView( SView ), mParentWindow( Parent )
{
}

CPluginManager::~CPluginManager()
{
	// need to make sure plugins are deleted before dlls are unloaded
	for( std::map<std::string, DllPtr>::iterator i = mPlugins.begin();
		i != mPlugins.end(); i++ )
	{
		i->second.reset();
	}
}

void CPluginManager::LoadPlugin( const wxString& Path, const wxString& Filename )
{
	typedef void ( *FunctionType )( CPluginManager& );

	mPluginHandles[Filename].reset( new wxDynamicLibrary( Path + Filename ) );
	if( !mPluginHandles[Filename]->IsLoaded() )
	{
		mPluginHandles.erase( Filename );
		return;
	}
			
	void* InitFunction = mPluginHandles[Filename]->GetSymbol( wxT( "InitPlugin" ) );
	if( !InitFunction )
	{
		mPluginHandles.erase( Filename );
		return;
	}

	FunctionType f = reinterpret_cast<FunctionType>( InitFunction );
	f( *this );
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

			LoadPlugin(  NWPluginPath, NWFilename );
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

			LoadPlugin( VIPluginPath, VIFilename );
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

			LoadPlugin( SSPluginPath, SSFilename );
		}
	}
}

void CPluginManager::UnloadPlugins()
{
	for( std::map<wxString, boost::shared_ptr<wxDynamicLibrary> >::iterator i = mPluginHandles.begin();
		i != mPluginHandles.end();
		i++ )
	{
		i->second.reset();
	}

	mPluginHandles.clear();
}

const std::map<std::string, DllPtr>& CPluginManager::GetPlugins() const
{
	return mPlugins;
}
