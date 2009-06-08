#ifndef __OViSEExportMeshesDialog__
#define __OViSEExportMeshesDialog__

#include "GUIFrame.h"

class OViSEExportMeshesDialog : public ExportMeshesDialog
{
protected:
	// Event handlers, overide them in your derived class
	void OnCloseDialog( wxCloseEvent& event );
	void OnClickCancel( wxCommandEvent& event );
	void OnClickOk( wxCommandEvent& event );

public:
	OViSEExportMeshesDialog( wxWindow* parent, wxWindowID id );
	~OViSEExportMeshesDialog(void);
};

#endif // __OViSEExportMeshesDialog__