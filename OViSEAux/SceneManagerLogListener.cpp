#include "../OViSEAux/SceneManagerLogListener.h"

SceneManagerLogListener::SceneManagerLogListener(void) { }
SceneManagerLogListener::~SceneManagerLogListener(void) { }

// Management of listener, sealed
wxString SceneManagerLogListener::GetListenerTypeName() { return ToWxString("SceneManagerLogListener"); }

// Methods of parent events, sealed
void SceneManagerLogListener::OnChanged(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Changed Ogre::SceneManager");
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
void SceneManagerLogListener::OnConstructed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Constructed Ogre::SceneManager");
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
void SceneManagerLogListener::OnDestructed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Destructed Ogre::SceneManager");
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
void SceneManagerLogListener::OnRenamed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
	{
		MSG << event.GetContextData().GetString();
	}
	else
	{
		MSG << ToWxString("Renamed Ogre::SceneManager");
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
void SceneManagerLogListener::OnSelected(ImprovedEvent &event)
{
	if (!OgreMediator::GetSingletonPtr()->iSceneManager.Exist(event.GetContextInfo())) event.Skip();
	else
	{
		wxString MSG = ToWxString("[-EVENT-] ");
		if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
		{
			MSG << event.GetContextData().GetString();
		}
		else
		{
			MSG << ToWxString("Selected Ogre::SceneManager");
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
void SceneManagerLogListener::OnUnselected(ImprovedEvent &event)
{
	if (!OgreMediator::GetSingletonPtr()->iSceneManager.Exist(event.GetContextInfo())) event.Skip();
	else
	{
		wxString MSG = ToWxString("[-EVENT-] ");
		if ((!event.GetContextData().IsNull()) && event.GetContextData().GetType().IsSameAs(ToWxString("string")))
		{
			MSG << event.GetContextData().GetString();
		}
		else
		{
			MSG << ToWxString("Unselected Ogre::SceneManager");
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