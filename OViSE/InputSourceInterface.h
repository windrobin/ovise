#pragma once

class InputSourceInterface
{
public:
	enum InputSourceType {
		Undefined = 0,
		Gui = 1,
		Event = 2
	};
	void			SetInputSource( InputSourceType Type );
	InputSourceType	GetInputSource();

protected:
	InputSourceType mActiveSource;
};
