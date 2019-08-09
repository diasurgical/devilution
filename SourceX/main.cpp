#include <string>
#include <SDL.h>
#ifdef __SWITCH__
#include "platform/switch/network.h"
#endif
#include <config.h>

#include "devilution.h"

#if !defined(__APPLE__)
extern "C" const char *__asan_default_options()
{
	return "halt_on_error=0";
}
#endif

static std::string build_cmdline(int argc, char **argv)
{
	std::string str;
	for (int i = 1; i < argc; i++) {
		if (i != 1) {
			str += ' ';
		}
		str += argv[i];
	}

	return str;
}

static bool HasArgumst(const char *arg, int argc, char **argv)
{
	for (int i = 1; i < argc; i++) {
		if (strcasecmp(arg, argv[i]) == 0) {
			return true;
		}
	}

	return false;
}

static void ShowCLIinfo(int argc, char **argv)
{
	if (HasArgumst("-h", argc, argv) || HasArgumst("--help", argc, argv)) {
		printf("Options:\n");
		printf("    %-20s %-30s\n", "-h, --help", "Print this message and exit");
		printf("    %-20s %-30s\n", "--version", "Print the version and exit");
		printf("    %-20s %-30s\n", "-n", "Skip startup videos");
		printf("    %-20s %-30s\n", "-f", "Display frames per second");
		printf("    %-20s %-30s\n", "-x", "Run in windows mode");
#ifdef _DEBUG
		printf("\nDebug options:\n");
		printf("    %-20s %-30s\n", "-d", "Increaased item drops");
		printf("    %-20s %-30s\n", "-w", "Enable cheats");
		printf("    %-20s %-30s\n", "-$", "Enable god mode");
		printf("    %-20s %-30s\n", "-^", "Enable god mode and debug tools");
		//printf("    %-20s %-30s\n", "-b", "Enable item drop log");
		printf("    %-20s %-30s\n", "-v", "Highlight visibility");
		printf("    %-20s %-30s\n", "-i", "Ignore network timeout");
		//printf("    %-20s %-30s\n", "-j <##>", "Init trigger at level");
		printf("    %-20s %-30s\n", "-l <##> <##>", "Start in level as type");
		printf("    %-20s %-30s\n", "-m <##>", "Add debug monster, up to 10 allowed");
		printf("    %-20s %-30s\n", "-q <#>", "Force a certain quest");
		printf("    %-20s %-30s\n", "-r <##########>", "Set map seed");
		printf("    %-20s %-30s\n", "-t <##>", "Set current quest level");
#endif
		printf("\nReport bugs at https://github.com/diasurgical/devilutionX/\n");
		exit(0);
	}
	if (HasArgumst("--version", argc, argv)) {
		printf("%s v%s\n", PROJECT_NAME, PROJECT_VERSION);
		exit(0);
	}
}

int main(int argc, char **argv)
{
	ShowCLIinfo(argc, argv);
#ifdef __SWITCH__
	switch_enable_network();
#endif

	auto cmdline = build_cmdline(argc, argv);
	return dvl::DiabloMain(cmdline.c_str());
}
