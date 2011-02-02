#include <stdio.h>

//ripped off geohot's hacktivation.dylib
int patch_dword(unsigned int* addr, unsigned int value)
{
    int pageSize = getpagesize();
    void* page = (((unsigned int)addr)/pageSize) * pageSize;
    
    int x = vm_protect(mach_task_self(), page, pageSize, 0, 0x13);
    
    if (x)
    {
        printf("patch_dword FAIL: vm_protect returned %x, need kernel patch!\n", x);
        return 1;
    }
    *addr = value;
    vm_protect(mach_task_self(), page, pageSize, 0, 0x5);
    return 0;
}

void __attribute__((constructor)) hacktivate()
{
    int i;
    void* search = 0x1000;  //lockdownd base addr
    void* callsite = NULL;
    
    for (i=0; i < 0x54000; i++)
    {
        //signature works on iphone 4 
        //04 E0 20 46 29 46 32 46
        if (!memcmp(search, "\x04\xE0\x20\x46\x29\x46\x32\x46",8))
        {
            callsite = search;
            break;
        }
        search++;
    }
    if ( callsite == NULL)
    {
        printf("Cannot find call to determine_activation_state_old, hacktivation FAIL\n");
        return;
    }
    printf("Found call to determine_activation_state_old at %p\n", callsite);
    
    callsite += 4; 
    //patch the mov r2, r6 to mov r2, 1
    if(!patch_dword(callsite, 0x22014629))
    {
        printf("Patch OK!\n");
    }

}