#include <stdio.h>
#include <unistd.h>

int main()
{
    int i = 0;
   while (1)
   {
        dprintf(1, "i = %d\n", i);
        i++;
        sleep(1);
    }
}
