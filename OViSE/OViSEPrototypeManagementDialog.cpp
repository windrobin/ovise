#include "OViSEPrototypeManagementDialog.h"

OViSEPrototypeManagementDialog::OViSEPrototypeManagementDialog( wxWindow* parent, OViSESceneHandling* SceneHdlr ) : PrototypeManagementDialog( parent )
{
	this->mValid = false;
	this->mResultingUniqueNameOfPrototype.Empty();

	this->mSceneHdlr = SceneHdlr;
	this->mDotSceneMgr = this->mSceneHdlr->mDotSceneMgr; // test, if it is 0!!!

	//this->mWindowManager = new wxAuiManager(this);

	this->setupPrototypeProperties();
	this->mPrototypeList->Clear();
	this->mPrototypeList->Append(this->mDotSceneMgr->GetImportedScenePrototypes());

	this->Update();
}

void OViSEPrototypeManagementDialog::setupPrototypeProperties()
{
	this->mPrototypeProperties = new wxPropertyGrid(this, PROTOPGID);
	this->ListBoxSizer->Add(this->mPrototypeProperties, 1, wxALL|wxEXPAND, 5 );
	this->Connect(PROTOPGID, wxEVT_PG_CHANGED, wxPropertyGridEventHandler(OViSEPrototypeManagementDialog::OnPropertyChange));
	this->mPrototypeProperties->SetExtraStyle(wxPG_EX_HELP_AS_TOOLTIPS);

	this->mPrototypeProperties->Append(new wxPropertyCategory(ToWxString("Prototype Names")));
	this->mPrototypeProperties->Append(new wxStringProperty(ToWxString("Unique"), ToWxString("UniqueName")));
	this->mPrototypeProperties->SetPropertyValidator(ToWxString("UniqueName"), wxTextValidator(wxFILTER_ASCII));
	this->mPrototypeProperties->DisableProperty(ToWxString("UniqueName"));
	this->mPrototypeProperties->Append(new wxStringProperty(ToWxString("Original"), ToWxString("OriginalName")));
	this->mPrototypeProperties->SetPropertyValidator(ToWxString("OriginalName"), wxTextValidator(wxFILTER_ASCII));

	this->mPrototypeProperties->Append(new wxPropertyCategory(ToWxString("Prototype Data")));
	this->mPrototypeProperties->Append(new wxDirProperty(ToWxString("Path"), ToWxString("ResourceBaseDir")));
	this->mPrototypeProperties->SetPropertyValidator(ToWxString("ResourceBaseDir"), wxTextValidator(wxFILTER_ASCII));
	this->mPrototypeProperties->Append(new wxArrayStringProperty(ToWxString("All"), ToWxString("AllFiles")));
	this->mPrototypeProperties->SetPropertyValidator(ToWxString("AllFiles"), wxTextValidator(wxFILTER_ASCII));
	this->mPrototypeProperties->Append(new wxArrayStringProperty(ToWxString("XML"), ToWxString("XMLFiles")));
	this->mPrototypeProperties->SetPropertyValidator(ToWxString("XMLFiles"), wxTextValidator(wxFILTER_ASCII));
	this->mPrototypeProperties->Append(new wxArrayStringProperty(ToWxString("Meshs"), ToWxString("MeshFiles")));
	this->mPrototypeProperties->SetPropertyValidator(ToWxString("MeshFiles"), wxTextValidator(wxFILTER_ASCII));
	this->mPrototypeProperties->Append(new wxStringProperty(ToWxString("Materials"), ToWxString("MaterialFiles")));
	this->mPrototypeProperties->SetPropertyValidator(ToWxString("MaterialFiles"), wxTextValidator(wxFILTER_ASCII));
}

void OViSEPrototypeManagementDialog::setPrototypeProperties(wxString UniquePrototypeName)
{
	this->mSelectedUniquePrototypeName = UniquePrototypeName;
	this->mPrototypeProperties->SetPropertyValue(ToWxString("UniqueName"), this->mSelectedUniquePrototypeName);
	this->mPrototypeProperties->SetPropertyValue(ToWxString("OriginalName"), this->mDotSceneMgr->GetPrototypeOriginalName(this->mSelectedUniquePrototypeName));
	this->mPrototypeProperties->SetPropertyValue(ToWxString("ResourceBaseDir"), this->mDotSceneMgr->GetPrototypeData(this->mSelectedUniquePrototypeName).ResourceBaseDir);
	this->mPrototypeProperties->SetPropertyValue(ToWxString("AllFiles"), this->mDotSceneMgr->GetPrototypeData(this->mSelectedUniquePrototypeName).Files);
	this->mPrototypeProperties->SetPropertyValue(ToWxString("XMLFiles"), this->mDotSceneMgr->GetPrototypeData(this->mSelectedUniquePrototypeName).XMLFiles);
	this->mPrototypeProperties->SetPropertyValue(ToWxString("MeshFiles"), this->mDotSceneMgr->GetPrototypeData(this->mSelectedUniquePrototypeName).MeshFiles);
	this->mPrototypeProperties->SetPropertyValue(ToWxString("MaterialFiles"), this->mDotSceneMgr->GetPrototypeData(this->mSelectedUniquePrototypeName).MaterialFiles);
}

void OViSEPrototypeManagementDialog::clearPrototypeProperties()
{
	this->mPrototypeProperties->ClearPropertyValue(ToWxString("UniqueName"));
	this->mPrototypeProperties->ClearPropertyValue(ToWxString("OriginalName"));
	this->mPrototypeProperties->ClearPropertyValue(ToWxString("ResourceBaseDir"));
	this->mPrototypeProperties->ClearPropertyValue(ToWxString("AllFiles"));
	this->mPrototypeProperties->ClearPropertyValue(ToWxString("XMLFiles"));
	this->mPrototypeProperties->ClearPropertyValue(ToWxString("MeshFiles"));
	this->mPrototypeProperties->ClearPropertyValue(ToWxString("MaterialFiles"));
}

void OViSEPrototypeManagementDialog::OnClickRemove( wxCommandEvent& event )
{
	int ID = this->mPrototypeList->GetSelection();
	if ( ID > -1 )
	{
		wxString LabelEqualsUniquePrototypeName = this->mPrototypeList->GetString(ID);
		if ( this->mDotSceneMgr->RemoveScenePrototype(LabelEqualsUniquePrototypeName) )
		{
			this->clearPrototypeProperties();
			this->mSelectedUniquePrototypeName.Clear();

			this->mPrototypeList->Clear();
			this->mPrototypeList->Append( this->mDotSceneMgr->GetImportedScenePrototypes() );

			this->mRemoveButton->Disable();
			this->mExportButton->Disable();
			this->mAttachButton->Disable();
		}
	}
}
void OViSEPrototypeManagementDialog::OnClickImport( wxCommandEvent& event )
{
	wxFileDialog* FDlg = new wxFileDialog(this, ToWxString("Choose dotScene-XML file to import"), wxFileName::GetCwd(), wxEmptyString, ToWxString("*.xml"), wxFD_OPEN);
	FDlg->ShowModal();

	wxArrayString ResultingFullPaths;
	FDlg->GetPaths(ResultingFullPaths);
	FDlg->Destroy();
	delete FDlg;

	for ( unsigned int iter = 0; iter < ResultingFullPaths.Count(); iter++)
	{
		wxFileName CurrentFullPath(ResultingFullPaths[iter]);
		if ( CurrentFullPath.GetExt().IsSameAs(ToWxString("xml")) )
		{
			wxString UniquePrototypeName = this->mDotSceneMgr->ImportScenePrototype(CurrentFullPath);
			if ( !UniquePrototypeName.IsEmpty() )
			{
				int newItemID = this->mPrototypeList->Append(UniquePrototypeName);
				this->mPrototypeList->Select(newItemID);
				this->setPrototypeProperties(UniquePrototypeName);
			}
		}
	}
}
void OViSEPrototypeManagementDialog::OnClickExport( wxCommandEvent& event )
{
	if ( !this->mSelectedUniquePrototypeName.IsEmpty() )
	{
		wxFileDialog* FDlg = new wxFileDialog( this, ToWxString("Select dotScene-XML file to export"), wxFileName::GetCwd(), this->mDotSceneMgr->GetPrototypeOriginalName(this->mSelectedUniquePrototypeName), ToWxString("*.xml"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
		int ReturnCode = FDlg->ShowModal();

		wxArrayString ResultingFullPaths;
		FDlg->GetPaths(ResultingFullPaths);
		FDlg->Destroy();
		delete FDlg;

		if ( ReturnCode == 5100 ) // 5101 = Cancel
		{
			if ( ResultingFullPaths.Count() > 0 )
			{
				wxFileName DestinationURL(ResultingFullPaths[0]);
				this->mDotSceneMgr->ExportScenePrototype(this->mSelectedUniquePrototypeName, DestinationURL);
			}
		}
	}
}

void OViSEPrototypeManagementDialog::OnClickBuild( wxCommandEvent& event )
{
	wxString VersionString = ToWxString("1.0.0");
	wxString NotUniquePrototypeName = ToWxString("Unnamend");
	
	wxString UniquePrototypeName = this->mDotSceneMgr->MakePrototypeFromOgreScene(NotUniquePrototypeName, this->mSceneHdlr->getSelectedObjects(), VersionString);
	if ( !UniquePrototypeName.IsEmpty() )
	{
		int newItemID = this->mPrototypeList->Append(UniquePrototypeName);
		this->mPrototypeList->Select(newItemID);
		this->setPrototypeProperties(UniquePrototypeName);
	}
}
void OViSEPrototypeManagementDialog::OnClickAttach( wxCommandEvent& event )
{
	OViSESelectionMap Selection = this->mSceneHdlr->getSelectedObjects();
	Ogre::SceneNode* AnchorNode;
	if ( Selection.size() > 0 )
	{
		AnchorNode = Selection.begin()->second->getParentSceneNode();
		if ( AnchorNode == 0 )
		{
			AnchorNode = this->mSceneHdlr->getSceneManager()->getRootSceneNode();
		}
	}
	else
	{
		AnchorNode = this->mSceneHdlr->getSceneManager()->getRootSceneNode();
	}

	if ( !this->mSelectedUniquePrototypeName.IsEmpty() )
	{
		this->mDotSceneMgr->MakeOgreSceneFromPrototype(this->mSelectedUniquePrototypeName, ToWxString(AnchorNode->getName()));
	}
}

void OViSEPrototypeManagementDialog::OnClickClose( wxCommandEvent& event ) { this->Destroy(); }
void OViSEPrototypeManagementDialog::OnCloseDialog( wxCloseEvent& event ) {	this->Destroy(); }
void OViSEPrototypeManagementDialog::OnProtoTypeListSelect( wxCommandEvent& event )
{
	int ID = this->mPrototypeList->GetSelection();
	if ( ID > -1 )
	{
		wxString LabelEqualsUniquePrototypeName = this->mPrototypeList->GetString(ID);
		this->setPrototypeProperties(LabelEqualsUniquePrototypeName);

		this->mRemoveButton->Enable();
		this->mExportButton->Enable();
		this->mAttachButton->Enable();
	}
	else
	{
		this->mRemoveButton->Disable();
		this->mExportButton->Disable();
		this->mAttachButton->Disable();
	}
}

void OViSEPrototypeManagementDialog::OnPropertyChange(wxPropertyGridEvent& event)
{
	wxPGProperty *ChangedProperty = event.GetProperty();

	// It may be NULL
    if ( !ChangedProperty ) return;

    // Get name of changed property
    const wxString& ChangedPropertyName = ChangedProperty->GetName();

	// REMEMBER: Associated prototype in containers can still be accessed by "this->mSelectedUniquePrototypeName"

	bool Match = false;
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("UniqueName")) ) )
	{
		// User changed UniqueName, that not allowed
		Match = true;
	}
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("OriginalName")) ) )
	{
		// User changed OriginalName
		wxString NewOriginalPrototypeName = this->mPrototypeProperties->GetPropertyValueAsString(ToWxString("OriginalName"));
		this->setPrototypeProperties(this->mDotSceneMgr->RenameScenePrototype(this->mSelectedUniquePrototypeName, NewOriginalPrototypeName));
		this->mPrototypeList->Clear();
		this->mPrototypeList->Append(this->mDotSceneMgr->GetImportedScenePrototypes());
	}
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("ResourceBaseDir")) ) )
	{
		// User changed ResourceBaseDir
		ScenePrototypeData Data = this->mDotSceneMgr->GetPrototypeData(this->mSelectedUniquePrototypeName);
		Data.ResourceBaseDir = this->mPrototypeProperties->GetPropertyValueAsString(ToWxString("ResourceBaseDir"));
		this->mDotSceneMgr->SetPrototypeData(this->mSelectedUniquePrototypeName, Data);
		Match = true;
	}
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("AllFiles")) ) )
	{
		// User changed AllFiles
		ScenePrototypeData Data = this->mDotSceneMgr->GetPrototypeData(this->mSelectedUniquePrototypeName);
		Data.Files.Clear();
		Data.Files = wxArrayString(this->mPrototypeProperties->GetPropertyValueAsArrayString(ToWxString("AllFiles")));
		this->mDotSceneMgr->SetPrototypeData(this->mSelectedUniquePrototypeName, Data);
		Match = true;
	}
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("XMLFiles")) ) )
	{
		// User changed XMLFiles
		ScenePrototypeData Data = this->mDotSceneMgr->GetPrototypeData(this->mSelectedUniquePrototypeName);
		Data.XMLFiles.Clear();
		Data.XMLFiles = wxArrayString(this->mPrototypeProperties->GetPropertyValueAsArrayString(ToWxString("XMLFiles")));
		this->mDotSceneMgr->SetPrototypeData(this->mSelectedUniquePrototypeName, Data);
		Match = true;
	}
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("MeshFiles")) ) )
	{
		// User changed MeshFiles
		ScenePrototypeData Data = this->mDotSceneMgr->GetPrototypeData(this->mSelectedUniquePrototypeName);
		Data.MeshFiles.Clear();
		Data.MeshFiles = wxArrayString(this->mPrototypeProperties->GetPropertyValueAsArrayString(ToWxString("MeshFiles")));
		this->mDotSceneMgr->SetPrototypeData(this->mSelectedUniquePrototypeName, Data);
		Match = true;
	}
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("MaterialFiles")) ) )
	{
		// User changed MaterialFiles
		ScenePrototypeData Data = this->mDotSceneMgr->GetPrototypeData(this->mSelectedUniquePrototypeName);
		Data.MaterialFiles.Clear();
		Data.MaterialFiles = wxArrayString(this->mPrototypeProperties->GetPropertyValueAsArrayString(ToWxString("MaterialFiles")));
		this->mDotSceneMgr->SetPrototypeData(this->mSelectedUniquePrototypeName, Data);
		Match = true;
	}

	// For debugging:
	if ( !Match ) return;
}
/*
void OViSEPrototypeManagementDialog::OnProtoTypeListSelect( wxCommandEvent& event )
{
	if (this->mValid)
	{
		this->mResultingUniqueNameOfPrototype = this->mPrototypeList->GetString(this->mPrototypeList->GetSelection());
	}
	else
	{
		this->mResultingUniqueNameOfPrototype.Empty();
	}
}

void OViSEPrototypeManagementDialog::OnClickCancel( wxCommandEvent& event )
{
	this->Close();
	this->mResultingUniqueNameOfPrototype.Empty();
}

void OViSEPrototypeManagementDialog::OnClickOk( wxCommandEvent& event )
{
	this->Close();
}

void OViSEPrototypeManagementDialog::SetAvailablePrototypes(wxArrayString ListOfAvailablePrototypes)
{
	this->mPrototypeList->Append(ListOfAvailablePrototypes);
	if (this->mPrototypeList->GetCount() > 0) this->mValid = true;
	else this->mValid = false;
}

wxString OViSEPrototypeManagementDialog::GetResultingUniqueNameOfPrototype() { return this->mResultingUniqueNameOfPrototype; }
*/

/*
void OViSEWxFrame::OnImportScenePrototype( wxCommandEvent& event )
{
	//TODO: Dynamische Namensvergabe für die Childnode implementieren, die erzeugt wird.
	/*wxFileDialog fd(this, wxT("Choose dotScene file"), wxEmptyString, wxEmptyString, wxT("*.xml"));
	int ret = fd.ShowModal();

	if(ret == wxID_CANCEL)
		return;*/
/*
	// TODO: Later use a selected node. Acually the sceneroot is used.
	// If that SceneNode-param is not used, it's NULL. That 'll be interpreted as srootscenenode of default-scenemanager.
	/// mSceneHdlr->loadSceneFromXML(fd.GetPath()), *** SOME ANCHOR NODE ***;
	//mSceneHdlr->ImportPrototypeFromXML(fd.GetPath());
	this->mSceneHdlr->createDefaultScene();
}

void OViSEWxFrame::OnExportScenePrototype( wxCommandEvent& event )
{
	wxFileDialog SelectDestinationDialog(this, wxT("Create or overwrite dotScene file"), wxEmptyString, wxT("Output.xml"), wxT("*.xml"));
	int ReturnValue = SelectDestinationDialog.ShowModal();
	
	if (ReturnValue == wxID_CANCEL) return;

	OViSEExportMeshesDialog MeshExportDlg(this, wxID_HIGHEST + 1);
	ReturnValue = MeshExportDlg.ShowModal();

	bool doExportMeshFiles = false;
	if (ReturnValue == wxID_OK) doExportMeshFiles = true;

	Ogre::SceneNode *dotSceneNode = this->mSceneHdlr->getSceneManager()->getRootSceneNode(); // TODO: use selected  scenenode !!!
	mSceneHdlr->ExportPrototypeToXML(SelectDestinationDialog.GetPath(), wxT("BaseSceneManager"), dotSceneNode, doExportMeshFiles); // TODO: extra dialog, asking "copy meshes as well"
}
*/
