
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DIABLOUI_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DIABLOUI_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef DIABLOUI_EXPORTS
#define DIABLOUI_API __declspec(dllexport)
#else
#define DIABLOUI_API __declspec(dllimport)
#endif

// This class is exported from the DiabloUI.dll
class DIABLOUI_API CDiabloUI {
public:
	CDiabloUI(void);
	// TODO: add your methods here.
};

extern DIABLOUI_API int nDiabloUI;

DIABLOUI_API int fnDiabloUI(void);

