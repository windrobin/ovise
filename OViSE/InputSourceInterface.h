#pragma once

enum InputSourceType {
	Undefined = 0,
	Gui = 1,
	Event = 2
};

class InputSourceInterface
{
protected:
	InputSourceType mActiveSource;
public:
	void			SetInputSource(InputSourceType Type);
	InputSourceType	GetInputSource();
};
