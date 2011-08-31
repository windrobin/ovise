#ifndef OVISE_PLUGIN_BASE_H
#define OVISE_PLUGIN_BASE_H

#include <wx/string.h>
#include <wx/propdlg.h>

#include <boost/shared_ptr.hpp>

#ifdef WIN32
#define OVISE_PLUGIN_API __declspec( dllexport )
#else
#define OVISE_PLUGIN_API
#endif

class CPluginBase
{
public:
	explicit CPluginBase( const wxString& Name, const int Type );
	virtual ~CPluginBase();

	enum PluginType
	{
		PLUGIN_TYPE_NETWORK,
		PLUGIN_TYPE_VISUAL,
		PLUGIN_TYPE_SENSOR
	};

	const wxString& GetName();
	const int GetType();
	
	// TODO: make hook for GUI stuff work
	//virtual void CreateConfigDialog( wxWindow* Parent ) {}
	//wxPropertySheetDialog* GetConfigDialog();

protected:
	//wxPropertySheetDialog*	mConfigDlg;

private:
	wxString				mName;
	int						mType;
};

#endif // OVISE_PLUGIN_BASE_H
