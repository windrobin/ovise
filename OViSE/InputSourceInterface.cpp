#include "../OViSE/InputSourceInterface.h"

void InputSourceInterface::SetInputSource(InputSourceType Type)
{
	this->mActiveSource = Type;
}

InputSourceInterface::InputSourceType InputSourceInterface::GetInputSource()
{
	return this->mActiveSource;
}
