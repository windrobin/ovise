#include "../OViSEAux/LightLogListener.h"

LightLogListener::LightLogListener(void) { }
LightLogListener::~LightLogListener(void) { }

// Management of listener, sealed
wxString LightLogListener::GetListenerTypeName() { return ToWxString("LightLogListener"); }

// Methods of parent events, sealed
void LightLogListener::OnChanged(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Changed Ogre::Light");
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
void LightLogListener::OnConstructed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Constructed Ogre::Light");
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
void LightLogListener::OnDestructed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Destructed Ogre::Light");
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
void LightLogListener::OnRenamed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Renamed Ogre::Light");
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
void LightLogListener::OnSelected(ImprovedEvent &event)
{
	if (!OgreMediator::GetSingletonPtr()->iLight.Exist(event.GetContextInfo())) event.Skip();
	else
	{
		wxString MSG = ToWxString("[-EVENT-] ");
		if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
		{
			MSG << event.GetContextData().GetString();
		}
		else
		{
			MSG << ToWxString("Selected Ogre::Light");
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
void LightLogListener::OnUnselected(ImprovedEvent &event)
{
	if (!OgreMediator::GetSingletonPtr()->iLight.Exist(event.GetContextInfo())) event.Skip();
	else
	{
		wxString MSG = ToWxString("[-EVENT-] ");
		if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
		{
			MSG << event.GetContextData().GetString();
		}
		else
		{
			MSG << ToWxString("Unselected Ogre::Light");
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