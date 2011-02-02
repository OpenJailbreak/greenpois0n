#include <stdio.h>
#include <sys/stat.h>

int main()
{
    struct stat status;
    
    if (stat("/private/var2/keybags/systembag.kb",&status) != 0)
    {
        printf("System keybag not found, fixing...\n");
        int x = MKBKeyBagCreateSystem(0, "/private/var2");
        printf("MKBKeyBagCreateSystem returned %x\n", x);
    }
    return 0;
}
