#include "pushbutton.h"

void InitializePushButtonPortPin (void)
{
	SET_PUSHBUTTON_TO_AN_INPUT;
	// Configure port pin for pushbutton
	ENABLE_PULL_UP_PULL_DOWN_RESISTORS;
	SELECT_PULL_UP_RESISTORS;
}
