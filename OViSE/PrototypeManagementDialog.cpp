#include "PrototypeManagementDialog.h"

PrototypeManagementDialog::PrototypeManagementDialog( wxWindow* parent, OViSEDotSceneManager* DotSceneMgr ) : _PrototypeManagementDialog( parent )
{
	this->mValid = false;
	this->mResultingUniqueNameOfPrototype.Empty();

	//this->mSceneHdlr = SceneHdlr;
	this->mDotSceneMgr = DotSceneMgr; // test, if it is 0!!!

	//this->mWindowManager = new wxAuiManager(this);

	this->setupPrototypeProperties();
	this->mPrototypeList->Clear();

	if (this->mDotSceneMgr->GetImportedPrototypes().Count() > 0)
	{
		wxArrayString AS;
		for (unsigned long IT = 0; IT  < this->mDotSceneMgr->GetImportedPrototypes().Count(); IT++)
		{
			AS.Add(this->mDotSceneMgr->GetImportedPrototypes()[IT].UniqueName());
		}
		this->mPrototypeList->Append(AS);
	}
	this->Update();
}

void PrototypeManagementDialog::setupPrototypeProperties()
{
	this->mPrototypeProperties = new wxPropertyGrid(this, PROTOPGID);
	this->ListBoxSizer->Add(this->mPrototypeProperties, 1, wxALL|wxEXPAND, 5 );
	this->Connect(PROTOPGID, wxEVT_PG_CHANGED, wxPropertyGridEventHandler(PrototypeManagementDialog::OnPropertyChange));
	this->mPrototypeProperties->SetExtraStyle(wxPG_EX_HELP_AS_TOOLTIPS);

	this->mPrototypeProperties->Append(new wxPropertyCategory(ToWxString("Prototype Names")));
	this->mPrototypeProperties->Append(new wxStringProperty(ToWxString("Qualified"), ToWxString("QualifiedName")));
	this->mPrototypeProperties->SetPropertyValidator(ToWxString("QualifiedName"), wxTextValidator(wxFILTER_ASCII));
	this->mPrototypeProperties->DisableProperty(ToWxString("QualifiedName"));
	this->mPrototypeProperties->Append(new wxStringProperty(ToWxString("Native"), ToWxString("NativeName")));
	this->mPrototypeProperties->SetPropertyValidator(ToWxString("NativeName"), wxTextValidator(wxFILTER_ASCII));

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

void PrototypeManagementDialog::setPrototypeProperties(QualifiedName qPrototype)
{
	this->qSelectedPrototype = qPrototype;
	this->mPrototypeProperties->SetPropertyValue(ToWxString("QualifiedName"), qPrototype.UniqueName());
	this->mPrototypeProperties->SetPropertyValue(ToWxString("NativeName"), qPrototype.NativeName());
	this->mPrototypeProperties->SetPropertyValue(ToWxString("ResourceBaseDir"), this->mDotSceneMgr->GetPrototypeData(this->qSelectedPrototype).ResourceBaseDir);
	this->mPrototypeProperties->SetPropertyValue(ToWxString("AllFiles"), this->mDotSceneMgr->GetPrototypeData(this->qSelectedPrototype).Files);
	this->mPrototypeProperties->SetPropertyValue(ToWxString("XMLFiles"), this->mDotSceneMgr->GetPrototypeData(this->qSelectedPrototype).XMLFiles);
	this->mPrototypeProperties->SetPropertyValue(ToWxString("MeshFiles"), this->mDotSceneMgr->GetPrototypeData(this->qSelectedPrototype).MeshFiles);
	this->mPrototypeProperties->SetPropertyValue(ToWxString("MaterialFiles"), this->mDotSceneMgr->GetPrototypeData(this->qSelectedPrototype).MaterialFiles);
}

void PrototypeManagementDialog::clearPrototypeProperties()
{
	this->mPrototypeProperties->Clear();

	std::pair<wxString, wxString> test = std::pair<wxString, wxString>(wxString(), wxString());
}

void PrototypeManagementDialog::OnClickRemove( wxCommandEvent& event )
{
	int ID = this->mPrototypeList->GetSelection();
	if ( ID > -1 )
	{
		wxString LabelEqualsUniquePrototypeName = this->mPrototypeList->GetString(ID);
		QualifiedName qName = QualifiedName::GetQualifiedNameByUnique(LabelEqualsUniquePrototypeName);
		if (qName.IsValid())
		{
			if ( this->mDotSceneMgr->RemoveScenePrototype(qName) )
			{
				this->clearPrototypeProperties();
				this->qSelectedPrototype = QualifiedName();

				this->mPrototypeList->Clear();
				if (this->mDotSceneMgr->GetImportedPrototypes().Count() > 0)
				{
					wxArrayString AS;
					for (unsigned long IT = 0; IT  < this->mDotSceneMgr->GetImportedPrototypes().Count(); IT++)
					{
						AS.Add(this->mDotSceneMgr->GetImportedPrototypes()[IT].UniqueName());
					}
					this->mPrototypeList->Append(AS);
				}

				this->mRemoveButton->Disable();
				this->mExportButton->Disable();
				this->mAttachButton->Disable();
			}
		}
	}
}
void PrototypeManagementDialog::OnClickImport( wxCommandEvent& event )
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
			QualifiedName qPrototype = this->mDotSceneMgr->ImportScenePrototype(CurrentFullPath);
			if ( qPrototype.IsValid() )
			{
				int newItemID = this->mPrototypeList->Append(qPrototype.UniqueName());
				this->mPrototypeList->Select(newItemID);
				this->setPrototypeProperties(qPrototype);

				this->mRemoveButton->Enable();
				this->mExportButton->Enable();
				this->mAttachButton->Enable();
			}
		}
	}
}
void PrototypeManagementDialog::OnClickExport( wxCommandEvent& event )
{
	if ( this->qSelectedPrototype.IsValid() )
	{
		wxFileDialog* FDlg = new wxFileDialog( this, ToWxString("Select dotScene-XML file to export"), wxFileName::GetCwd(), this->qSelectedPrototype.NativeName(), ToWxString("*.xml"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
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
				this->mDotSceneMgr->ExportScenePrototype(this->qSelectedPrototype, DestinationURL);
			}
		}
	}
}

void PrototypeManagementDialog::OnClickBuild( wxCommandEvent& event )
{
	wxString VersionString = ToWxString("1.0.0");
	wxString NotUniquePrototypeName = ToWxString("Unnamend");
	
	QualifiedName qPrototype = this->mDotSceneMgr->MakePrototypeFromOgreScene(NotUniquePrototypeName, SelectionManager::getSingletonPtr()->Selection, VersionString);
	if ( qPrototype.IsValid() )
	{
		int newItemID = this->mPrototypeList->Append(qPrototype.UniqueName());
		this->mPrototypeList->Select(newItemID);
		this->setPrototypeProperties(qPrototype);

		this->mRemoveButton->Enable();
		this->mExportButton->Enable();
		this->mAttachButton->Enable();
	}
}
void PrototypeManagementDialog::OnClickAttach( wxCommandEvent& event )
{
	Ogre::SceneNode* AnchorNode;

	if (SelectionManager::getSingletonPtr()->Selection.Count() > 0)
	{
		QualifiedName qNameOfFirst = SelectionManager::getSingletonPtr()->Selection[0];
		Ogre::MovableObject* MO = OgreMediator::GetSingletonPtr()->iMovableObject.GetPtr(qNameOfFirst);
		if ( MO == 0 )
		{
			AnchorNode = OgreMediator::GetSingletonPtr()->iSceneManager.GetPtr(OgreMediator::GetSingletonPtr()->iSceneManager.GetActiveSceneManager())->getRootSceneNode();
		}
		else AnchorNode = MO->getParentSceneNode();
	}
	else
	{
		AnchorNode = OgreMediator::GetSingletonPtr()->iSceneManager.GetPtr(OgreMediator::GetSingletonPtr()->iSceneManager.GetActiveSceneManager())->getRootSceneNode();
	}

	if ( this->qSelectedPrototype.IsValid() )
	{
		QualifiedName qAnchorSN = QualifiedName::GetQualifiedNameByUnique(ToWxString(AnchorNode->getName()));
		this->mDotSceneMgr->MakeOgreSceneFromPrototype(this->qSelectedPrototype, qAnchorSN);
	}

	//OgreMediator::GetSingletonPtr()->SendOgreChanged();
}

void PrototypeManagementDialog::OnClickClose( wxCommandEvent& event ) { this->Destroy(); }
void PrototypeManagementDialog::OnCloseDialog( wxCloseEvent& event ) {	this->Destroy(); }
void PrototypeManagementDialog::OnProtoTypeListSelect( wxCommandEvent& event )
{
	this->mRemoveButton->Disable();
	this->mExportButton->Disable();
	this->mAttachButton->Disable();

	int ID = this->mPrototypeList->GetSelection();
	if ( ID > -1 )
	{
		wxString LabelEqualsUniquePrototypeName = this->mPrototypeList->GetString(ID);
		QualifiedName qName = QualifiedName::GetQualifiedNameByUnique(LabelEqualsUniquePrototypeName);
		if (qName.IsValid())
		{
			this->setPrototypeProperties(qName);

			this->mRemoveButton->Enable();
			this->mExportButton->Enable();
			this->mAttachButton->Enable();
		}
	}
}

void PrototypeManagementDialog::OnPropertyChange(wxPropertyGridEvent& event)
{
	wxPGProperty *ChangedProperty = event.GetProperty();

	// It may be NULL
    if ( !ChangedProperty ) return;

    // Get name of changed property
    const wxString& ChangedPropertyName = ChangedProperty->GetName();

	// REMEMBER: Associated prototype in containers can still be accessed by "this->mSelectedUniquePrototypeName"

	bool Match = false;
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("QualifiedName")) ) )
	{
		// User changed UniqueName, that not allowed
		Match = true;
	}
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("NativeName")) ) )
	{
		// User changed OriginalName
		wxString NewNativePrototypeName = this->mPrototypeProperties->GetPropertyValueAsString(ToWxString("NativeName"));
		this->setPrototypeProperties(this->mDotSceneMgr->RenameScenePrototype(this->qSelectedPrototype, NewNativePrototypeName));
		this->mPrototypeList->Clear();

		wxArrayString AS;
		for (unsigned long IT = 0; IT  < this->mDotSceneMgr->GetImportedPrototypes().Count(); IT++)
		{
			AS.Add(this->mDotSceneMgr->GetImportedPrototypes()[IT].UniqueName());
		}

		this->mPrototypeList->Append(AS);
	}
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("ResourceBaseDir")) ) )
	{
		// User changed ResourceBaseDir
		ScenePrototypeData Data = this->mDotSceneMgr->GetPrototypeData(this->qSelectedPrototype);
		Data.ResourceBaseDir = this->mPrototypeProperties->GetPropertyValueAsString(ToWxString("ResourceBaseDir"));
		this->mDotSceneMgr->SetPrototypeData(this->qSelectedPrototype, Data);
		Match = true;
	}
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("AllFiles")) ) )
	{
		// User changed AllFiles
		ScenePrototypeData Data = this->mDotSceneMgr->GetPrototypeData(this->qSelectedPrototype);
		Data.Files.Clear();
		Data.Files = wxArrayString(this->mPrototypeProperties->GetPropertyValueAsArrayString(ToWxString("AllFiles")));
		this->mDotSceneMgr->SetPrototypeData(this->qSelectedPrototype, Data);
		Match = true;
	}
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("XMLFiles")) ) )
	{
		// User changed XMLFiles
		ScenePrototypeData Data = this->mDotSceneMgr->GetPrototypeData(this->qSelectedPrototype);
		Data.XMLFiles.Clear();
		Data.XMLFiles = wxArrayString(this->mPrototypeProperties->GetPropertyValueAsArrayString(ToWxString("XMLFiles")));
		this->mDotSceneMgr->SetPrototypeData(this->qSelectedPrototype, Data);
		Match = true;
	}
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("MeshFiles")) ) )
	{
		// User changed MeshFiles
		ScenePrototypeData Data = this->mDotSceneMgr->GetPrototypeData(this->qSelectedPrototype);
		Data.MeshFiles.Clear();
		Data.MeshFiles = wxArrayString(this->mPrototypeProperties->GetPropertyValueAsArrayString(ToWxString("MeshFiles")));
		this->mDotSceneMgr->SetPrototypeData(this->qSelectedPrototype, Data);
		Match = true;
	}
	if ( (!Match) && ( ChangedPropertyName.IsSameAs(ToWxString("MaterialFiles")) ) )
	{
		// User changed MaterialFiles
		ScenePrototypeData Data = this->mDotSceneMgr->GetPrototypeData(this->qSelectedPrototype);
		Data.MaterialFiles.Clear();
		Data.MaterialFiles = wxArrayString(this->mPrototypeProperties->GetPropertyValueAsArrayString(ToWxString("MaterialFiles")));
		this->mDotSceneMgr->SetPrototypeData(this->qSelectedPrototype, Data);
		Match = true;
	}

	// For debugging:
	if ( !Match ) return;
}
/*
void PrototypeManagementDialog::OnProtoTypeListSelect( wxCommandEvent& event )
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

void PrototypeManagementDialog::OnClickCancel( wxCommandEvent& event )
{
	this->Close();
	this->mResultingUniqueNameOfPrototype.Empty();
}

void PrototypeManagementDialog::OnClickOk( wxCommandEvent& event )
{
	this->Close();
}

void PrototypeManagementDialog::SetAvailablePrototypes(wxArrayString ListOfAvailablePrototypes)
{
	this->mPrototypeList->Append(ListOfAvailablePrototypes);
	if (this->mPrototypeList->GetCount() > 0) this->mValid = true;
	else this->mValid = false;
}

wxString PrototypeManagementDialog::GetResultingUniqueNameOfPrototype() { return this->mResultingUniqueNameOfPrototype; }
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
