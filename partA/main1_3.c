#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <dlfcn.h>


void (*hello_message)(const char *);

bool init_library()
{
    void *hdl = dlopen("./libhello.so", RTLD_LAZY);
    if (hdl == NULL)
        return false;
    hello_message = (void (*)(const char *))dlsym(hdl, "hello");
    if (hello_message == NULL)
        return false;
    return true;
}

int main(){
    if (init_library())
	hello_message("Ariel");
    else
        printf("Library was not loaded \n");
    return 0;
}
