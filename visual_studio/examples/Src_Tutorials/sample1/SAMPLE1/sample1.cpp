#include "stdlib.h"
#include "stdio.h"

#include "vraniml.h"

void main(int argc, char *argv[])
{
	printf("VRaniML Pretty Printer\n");
	printf("Version 1.0\n\n");

	vrBrowser browser;

	// Read the file (note: we hardcode the filename here for ease of instruction).
	// Note: Sending NULL to ReadURL will cause the browser to read from stdin.
	if (browser.ReadURL("c:/program files/great hill corporation/vraniml/sample browser/logo.wrl"))
	{
		printf("Read status: OK\n");
		vrWriteTraverser wt;

		// Change the tab character and the number of characters per indent
		wt.SetTabStop(1, ' ');

		// Change the number of digits to write for SFFloat fields
		wt.SetDigits(2);

		// Export all fields (even if they have default values)
		wt.SetVerbose(ALL_FIELDS);

		// Change the output filename
		// wt.SetFilename("temp.wrl");

		browser.Traverse(&wt);
	} else
	{
		printf("Read failed\n");
	}
}
