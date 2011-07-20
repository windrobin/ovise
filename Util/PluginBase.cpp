#include "PluginBase.h"

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
