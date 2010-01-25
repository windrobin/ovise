#include "../OViSEAux/MovableObjectLogListener.h"

MovableObjectLogListener::MovableObjectLogListener(void) { }
MovableObjectLogListener::~MovableObjectLogListener(void) { }

// Management of listener, sealed
wxString MovableObjectLogListener::GetListenerTypeName() { return ToWxString("MovableObjectLogListener"); }

// Methods of parent events, sealed
void MovableObjectLogListener::OnChanged(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Changed Ogre::MovableObject");
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
void MovableObjectLogListener::OnConstructed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Constructed Ogre::MovableObject");
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
void MovableObjectLogListener::OnDestructed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Destructed Ogre::MovableObject");
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
void MovableObjectLogListener::OnRenamed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Renamed Ogre::MovableObject");
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
void MovableObjectLogListener::OnSelected(ImprovedEvent &event)
{
	if (!OgreMediator::GetSingletonPtr()->iMovableObject.Exist(event.GetContextInfo())) event.Skip();
	else
	{
		wxString MSG = ToWxString("[-EVENT-] ");
		if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
		{
			MSG << event.GetContextData().GetString();
		}
		else
		{
			MSG << ToWxString("Selected Ogre::MovableObject");
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
void MovableObjectLogListener::OnUnselected(ImprovedEvent &event)
{
	if (!OgreMediator::GetSingletonPtr()->iMovableObject.Exist(event.GetContextInfo())) event.Skip();
	else
	{
		wxString MSG = ToWxString("[-EVENT-] ");
		if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
		{
			MSG << event.GetContextData().GetString();
		}
		else
		{
			MSG << ToWxString("Unselected Ogre::MovableObject");
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