#ifndef CALLBACK_OBJECT_H
#define CALLBACK_OBJECT_H

#include <string>

/** Abstract base class for frame-based callbacks.
 * This class needs to be subclassed and the executeCommands() method implemented. It
 * can then be registered with a CustomFrameListener to have its executeCommands() method
 * called at the beginning of each frame.
 */
class CallbackObject
{
public:
	CallbackObject(std::string name);
	~CallbackObject(void);

	std::string getName();

	/// This function gets called by the frame listener this object is registered to.
	virtual void executeCommands() = 0;

private:
	/** With this name the object is registered with the frame listener.
	 * @remark Do not change before unregistering!
	 */
	std::string mName;
};

#endif //CALLBACK_OBJECT_H
