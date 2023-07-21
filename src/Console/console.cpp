#include "console.h"

void console::startConsole()
{
    AllocConsole();

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int fileDescriptor = _open_osfhandle(reinterpret_cast<intptr_t>(consoleHandle), _O_TEXT);
    FILE* consoleFile = _fdopen(fileDescriptor, "w");
    *stdout = *consoleFile;
    setvbuf(stdout, nullptr, _IONBF, 0);

    // Redirect stdout to the console
    freopen_s(&consoleFile, "CONOUT$", "w", stdout);
}

void console::endConsole()
{
    // flush and close stdout
    fflush(stdout);
    fclose(stdout);

    // free the console
    FreeConsole();
}