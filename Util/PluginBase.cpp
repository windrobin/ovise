#include "PluginBase.h"

const int CPluginBase::PLUGIN_TYPE_NETWORK = 10;
const int CPluginBase::PLUGIN_TYPE_VISUAL  = 11;
const int CPluginBase::PLUGIN_TYPE_SENSOR  = 12;

CPluginBase::CPluginBase( const wxString& Name, const int Type )
	: mName( Name ), mType( Type ), mConfigDlg( NULL )
{
}

CPluginBase::~CPluginBase()
{
}

const wxString& CPluginBase::GetName()
{
	return mName;
}

const int CPluginBase::GetType()
{
	return mType;
}

wxPropertySheetDialog* CPluginBase::GetConfigDialog()
{
	return mConfigDlg;
}
