#include "testgen.h"

#include "all.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ghInst = hInstance;
	testgen();
	return 0;
}
