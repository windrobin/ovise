#include "../OViSEAux/CameraLogListener.h"

CameraLogListener::CameraLogListener(void) { }
CameraLogListener::~CameraLogListener(void) { }

// Management of listener, sealed
wxString CameraLogListener::GetListenerTypeName() { return ToWxString("CameraLogListener"); }

// Methods of parent events, sealed
void CameraLogListener::OnChanged(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Changed Ogre::Camera");
		QualifiedName qName = event.GetContextInfo();
		if (qName.IsValid())
		{
			MSG << ToWxString(" '");
			MSG << qName.UniqueName();
			MSG << ToWxString("'");
		}
	}
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);
	event.Skip();
}
void CameraLogListener::OnConstructed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Constructed Ogre::Camera");
		QualifiedName qName = event.GetContextInfo();
		if (qName.IsValid())
		{
			MSG << ToWxString(" '");
			MSG << qName.UniqueName();
			MSG << ToWxString("'");
		}
	}
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);
	event.Skip();
}
void CameraLogListener::OnDestructed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Destructed Ogre::Camera");
		QualifiedName qName = event.GetContextInfo();
		if (qName.IsValid())
		{
			MSG << ToWxString(" '");
			MSG << qName.UniqueName();
			MSG << ToWxString("'");
		}
	}
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);
	event.Skip();
}
void CameraLogListener::OnRenamed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Renamed Ogre::Camera");
		QualifiedName qName = event.GetContextInfo();
		if (qName.IsValid())
		{
			MSG << ToWxString(" '");
			MSG << qName.UniqueName();
			MSG << ToWxString("'");
		}
	}
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);
	event.Skip();
}
void CameraLogListener::OnSelected(ImprovedEvent &event)
{
	if (!OgreMediator::GetSingletonPtr()->iCamera.Exist(event.GetContextInfo())) event.Skip();
	else
	{
		wxString MSG = ToWxString("[-EVENT-] ");
		if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
		{
			MSG << event.GetContextData().GetString();
		}
		else
		{
			MSG << ToWxString("Selected Ogre::Camera");
			QualifiedName qName = event.GetContextInfo();
			if (qName.IsValid())
			{
				MSG << ToWxString(" '");
				MSG << qName.UniqueName();
				MSG << ToWxString("'");
			}
		}
		Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);
		event.Skip();
	}
}
void CameraLogListener::OnUnselected(ImprovedEvent &event)
{
	if (!OgreMediator::GetSingletonPtr()->iCamera.Exist(event.GetContextInfo())) event.Skip();
	else
	{
		wxString MSG = ToWxString("[-EVENT-] ");
		if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
		{
			MSG << event.GetContextData().GetString();
		}
		else
		{
			MSG << ToWxString("Unselected Ogre::Camera");
			QualifiedName qName = event.GetContextInfo();
			if (qName.IsValid())
			{
				MSG << ToWxString(" '");
				MSG << qName.UniqueName();
				MSG << ToWxString("'");
			}
		}
		Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);
		event.Skip();
	}
}