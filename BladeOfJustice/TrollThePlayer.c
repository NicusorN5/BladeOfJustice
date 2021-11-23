#include "TrollThePlayer.h"

void RealBlueScreen()
{
    /*
    BOOLEAN t;
    RtlAdjustPrivilege(19, TRUE, FALSE, &t); //shutdown privilege
    unsigned long response;
    NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response); //BSOD :DDDD
    */
}

void SpamMessages(const char* message, const char* title)
{
    while (1)
    {
        MessageBoxA(NULL, message, title, MB_OK);
    }
}

void SpamRandomMessages(const char** messages, size_t nummessages, const char** titles)
{
    while (1)
    {
        srand(time(NULL));
        int r = rand() % nummessages;
        MessageBoxA(NULL, messages[r], titles[r], MB_OK);
    }
}


