#include "../OViSEAux/EntityLogListener.h"

EntityLogListener::EntityLogListener(void) { }
EntityLogListener::~EntityLogListener(void) { }

// Management of listener, sealed
wxString EntityLogListener::GetListenerTypeName() { return ToWxString("EntityLogListener"); }

// Methods of parent events, sealed
void EntityLogListener::OnChanged(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Changed Ogre::Entity");
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
void EntityLogListener::OnConstructed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Constructed Ogre::Entity");
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
void EntityLogListener::OnDestructed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Destructed Ogre::Entity");
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
void EntityLogListener::OnRenamed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Renamed Ogre::Entity");
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
void EntityLogListener::OnSelected(ImprovedEvent &event)
{
	if (!OgreMediator::GetSingletonPtr()->iEntity.Exist(event.GetContextInfo())) event.Skip();
	else
	{
		wxString MSG = ToWxString("[-EVENT-] ");
		if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
		{
			MSG << event.GetContextData().GetString();
		}
		else
		{
			MSG << ToWxString("Selected Ogre::Entity");
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
void EntityLogListener::OnUnselected(ImprovedEvent &event)
{
	if (!OgreMediator::GetSingletonPtr()->iEntity.Exist(event.GetContextInfo())) event.Skip();
	else
	{
		wxString MSG = ToWxString("[-EVENT-] ");
		if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
		{
			MSG << event.GetContextData().GetString();
		}
		else
		{
			MSG << ToWxString("Unselected Ogre::Entity");
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