#include <stdio.h>
#include <sys/stat.h>

const char* nvram_cmd[]={"/usr/sbin/nvram","auto-boot=true", NULL};
const char* nvram_env[]={NULL};

int main()
{
    struct stat status;
    
    if (stat("/private/var2/keybags/systembag.kb",&status) != 0)
    {
        printf("System keybag not found, fixing...\n");
        int x = MKBKeyBagCreateSystem(0, "/private/var2");
        printf("MKBKeyBagCreateSystem returned %x\n", x);
        printf("Setting auto-boot=true\n");
        execve(nvram_cmd[0], nvram_cmd, nvram_env);
    }
    else
    {
        printf("System keybag is already here, doing nothing\n");
    }
    return 0;
}
