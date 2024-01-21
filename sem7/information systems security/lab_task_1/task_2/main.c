#include <stdio.h>
#include <io.h>
#include <fcntl.h>

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    wchar_t character = L'◙';
    wprintf(L"%lc\n", character);

    return 0;
}
