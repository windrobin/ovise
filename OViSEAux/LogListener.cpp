#include "../OViSEAux/LogListener.h"

LogListener::LogListener(void) { EventListenerInterface::SetListenerTypeName(ToWxString("LogListener")); }
LogListener::~LogListener(void) { }
// Management of listener
void LogListener::StartListening()
{
	// Start listening events
	MovableObjectListener::StartListening();
	OgreObjectListener::StartListening();
	SceneNodeListener::StartListening();
}
void LogListener::StopListening()
{
	// Stop listening events
	MovableObjectListener::StopListening();
	OgreObjectListener::StopListening();
	SceneNodeListener::StopListening();
}
// Methods of events, inherited
void LogListener::OnChanged(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	MSG << ToWxString("Changed ");

	// Handle ContextInfo...
	QualifiedName qName = event.GetContextInfo();
	MSG << ToWxString(" '");
	MSG << qName.UniqueName();
	MSG << ToWxString("'");

	// Handle ContextData
	if ((!event.GetContextData().IsNull()) && (event.GetContextData().GetType().IsSameAs(ToWxString("arrstring"))))
	{
		wxString concatenatedString;
		wxArrayString aString = event.GetContextData().GetArrayString();
		for (unsigned long IT = 0; IT < aString.GetCount(); IT++)
		{
			concatenatedString << ToWxString(" ");
			concatenatedString << aString[IT];
		}
		MSG << concatenatedString;
	}
	// Else: do nothing!

	// Write Message
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	event.Skip();
}
void LogListener::OnConstructed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	MSG << ToWxString("Constructed ");

	// Handle ContextInfo...
	QualifiedName qName = event.GetContextInfo();
	MSG << ToWxString(" '");
	MSG << qName.UniqueName();
	MSG << ToWxString("'");

	// Handle ContextData
	if ((!event.GetContextData().IsNull()) && (event.GetContextData().GetType().IsSameAs(ToWxString("string"))))
	{
		wxString concatenatedString;
		wxArrayString aString = event.GetContextData().GetArrayString();
		for (unsigned long IT = 0; IT < aString.GetCount(); IT++)
		{
			concatenatedString << ToWxString(" ");
			concatenatedString << aString[IT];
		}
		MSG << concatenatedString;
	}
	// Else: do nothing!

	// Write Message
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	event.Skip();
}
void LogListener::OnDestructed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	MSG << ToWxString("Destructed ");

	// Handle ContextInfo...
	QualifiedName qName = event.GetContextInfo();
	MSG << ToWxString(" '");
	MSG << qName.UniqueName();
	MSG << ToWxString("'");

	// Handle ContextData
	if ((!event.GetContextData().IsNull()) && (event.GetContextData().GetType().IsSameAs(ToWxString("string"))))
	{
		wxString concatenatedString;
		wxArrayString aString = event.GetContextData().GetArrayString();
		for (unsigned long IT = 0; IT < aString.GetCount(); IT++)
		{
			concatenatedString << ToWxString(" ");
			concatenatedString << aString[IT];
		}
		MSG << concatenatedString;
	}
	// Else: do nothing!

	// Write Message
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	event.Skip();
}
void LogListener::OnRenamed(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	MSG << ToWxString("Renamed ");

	// Handle ContextInfo...
	QualifiedName qName = event.GetContextInfo();
	MSG << ToWxString(" '");
	MSG << qName.UniqueName();
	MSG << ToWxString("'");

	// Handle ContextData
	if ((!event.GetContextData().IsNull()) && (event.GetContextData().GetType().IsSameAs(ToWxString("string"))))
	{
		wxString concatenatedString;
		wxArrayString aString = event.GetContextData().GetArrayString();
		for (unsigned long IT = 0; IT < aString.GetCount(); IT++)
		{
			concatenatedString << ToWxString(" ");
			concatenatedString << aString[IT];
		}
		MSG << concatenatedString;
	}
	// Else: do nothing!

	// Write Message
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	event.Skip();
}
void LogListener::OnSelected(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	MSG << ToWxString("Selected ");

	// Handle ContextInfo...
	QualifiedName qName = event.GetContextInfo();
	MSG << ToWxString(" '");
	MSG << qName.UniqueName();
	MSG << ToWxString("'");

	// Handle ContextData
	if ((!event.GetContextData().IsNull()) && (event.GetContextData().GetType().IsSameAs(ToWxString("string"))))
	{
		wxString concatenatedString;
		wxArrayString aString = event.GetContextData().GetArrayString();
		for (unsigned long IT = 0; IT < aString.GetCount(); IT++)
		{
			concatenatedString << ToWxString(" ");
			concatenatedString << aString[IT];
		}
		MSG << concatenatedString;
	}
	// Else: do nothing!

	// Write Message
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	event.Skip();
}
void LogListener::OnUnselected(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	MSG << ToWxString("Unselected ");

	// Handle ContextInfo...
	QualifiedName qName = event.GetContextInfo();
	MSG << ToWxString(" '");
	MSG << qName.UniqueName();
	MSG << ToWxString("'");

	// Handle ContextData
	if ((!event.GetContextData().IsNull()) && (event.GetContextData().GetType().IsSameAs(ToWxString("string"))))
	{
		wxString concatenatedString;
		wxArrayString aString = event.GetContextData().GetArrayString();
		for (unsigned long IT = 0; IT < aString.GetCount(); IT++)
		{
			concatenatedString << ToWxString(" ");
			concatenatedString << aString[IT];
		}
		MSG << concatenatedString;
	}
	// Else: do nothing!

	// Write Message
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	event.Skip();
}
void LogListener::OnTranslated(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	MSG << ToWxString("Translated ");

	// Handle ContextInfo...
	QualifiedName qName = event.GetContextInfo();
	MSG << ToWxString(" '");
	MSG << qName.UniqueName();
	MSG << ToWxString("'");

	// Handle ContextData
	if ((!event.GetContextData().IsNull()) && (event.GetContextData().GetType().IsSameAs(ToWxString("string"))))
	{
		wxString concatenatedString;
		wxArrayString aString = event.GetContextData().GetArrayString();
		for (unsigned long IT = 0; IT < aString.GetCount(); IT++)
		{
			concatenatedString << ToWxString(" ");
			concatenatedString << aString[IT];
		}
		MSG << concatenatedString;
	}
	// Else: do nothing!

	// Write Message
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	event.Skip();
}
void LogListener::OnRotated(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	MSG << ToWxString("Rotated ");

	// Handle ContextInfo...
	QualifiedName qName = event.GetContextInfo();
	MSG << ToWxString(" '");
	MSG << qName.UniqueName();
	MSG << ToWxString("'");

	// Handle ContextData
	if ((!event.GetContextData().IsNull()) && (event.GetContextData().GetType().IsSameAs(ToWxString("string"))))
	{
		wxString concatenatedString;
		wxArrayString aString = event.GetContextData().GetArrayString();
		for (unsigned long IT = 0; IT < aString.GetCount(); IT++)
		{
			concatenatedString << ToWxString(" ");
			concatenatedString << aString[IT];
		}
		MSG << concatenatedString;
	}
	// Else: do nothing!

	// Write Message
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	event.Skip();
}
void LogListener::OnScaled(ImprovedEvent &event)
{
	wxString MSG = ToWxString("[-EVENT-] ");
	MSG << ToWxString("Scaled ");

	// Handle ContextInfo...
	QualifiedName qName = event.GetContextInfo();
	MSG << ToWxString(" '");
	MSG << qName.UniqueName();
	MSG << ToWxString("'");

	// Handle ContextData
	if ((!event.GetContextData().IsNull()) && (event.GetContextData().GetType().IsSameAs(ToWxString("string"))))
	{
		wxString concatenatedString;
		wxArrayString aString = event.GetContextData().GetArrayString();
		for (unsigned long IT = 0; IT < aString.GetCount(); IT++)
		{
			concatenatedString << ToWxString(" ");
			concatenatedString << aString[IT];
		}
		MSG << concatenatedString;
	}
	// Else: do nothing!

	// Write Message
	Logging::GetSingletonPtr()->WriteToOgreLog(MSG, Logging::Normal);

	event.Skip();
}
