#pragma once

// Include STD
#ifndef STD_STING_USED
#define STD_STING_USED
#include <string>
#endif

/** Abstract base class for frame-based callbacks.
 * This class needs to be subclassed and the executeCommands() method implemented. It
 * can then be registered with a OViSEFrameListener to have its executeCommands() method
 * called at the beginning of each frame.
 */
class OViSECallbackObject
{
public:
	OViSECallbackObject(std::string name);
	~OViSECallbackObject(void);

	std::string getName();

	/// This function gets called by the frame listener this object is registered to.
	virtual void executeCommands() = 0;

private:
	/** With this name the object is registered with the frame listener.
	 * @remark Do not change before unregistering!
	 */
	std::string mName;
};
