#include "loadLibrary.h"

// Start of Loader class definitions

Loader::Loader()
{
    hLibrary = NULL;
    Logger::getInstance().log_i("Loader library initialized");
}

Loader::~Loader()
{
    if (hLibrary != NULL)
    {
        FreeLibrary(hLibrary);
    }
    Logger::getInstance().log_i("Loader class destroyed");
}

/**
 * Loads a library with the specified name.
 *
 * @param libraryName the name of the library to load
 *
 * @return true if the library was loaded successfully, false otherwise
 *
 * @throws ErrorType if there was an error loading the library
 */
bool Loader::loadLibrary(LPCWSTR libraryName)
{
    // Load the library with the specified name
    hLibrary = LoadLibrary(libraryName);

    // Check if the library was loaded successfully
    if (hLibrary == NULL)
    {
        // Log an error message
        Logger::getInstance().log_e("ERROR LOADING LIBRARY");

        // Return false to indicate that the library was not loaded
        return false;
    }

    // Log a success message
    Logger::getInstance().log_i("Library loaded");

    // Return true to indicate that the library was loaded successfully
    return true;
}

/**
 * GetLibrary retrieves the library handle for the Loader object.
 *
 * @param libraryOut a pointer to the library handle output
 *
 * @return true if the library handle was successfully retrieved, false otherwise
 *
 * @throws None
 */
bool Loader::GetLibrary(HMODULE* libraryOut)
{
    // Check if the library handle is not NULL
    if (hLibrary != NULL)
    {
        // Assign the library handle to the provided pointer
        *libraryOut = hLibrary;
        return true;
    }
    return false;
}
