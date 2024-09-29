#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <string.h>
#define BUFFERLEN 128

 char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

 char * fetchUser() {
    char *data;
    data=(char *)malloc(10*sizeof(char));
    data=getlogin();
    return(data);
}
// TODO: Split into functions without breaking fetchUTS
int fetchUTS() {
    char *username;
    username = fetchUser();
    struct utsname data;
    if (uname(&data))
    return 1;
    char* s = concat(username, "@");
    char* d = concat(s, data.nodename);
    printf("%s\n", d);
    printf("OS Type: %s\n", data.sysname);
    printf("Kernel version: %s\n", data.version);
    printf("Architecture: %s\n", data.machine);
    return 0;
 }

void fetchCTL() {
    char data[BUFFERLEN];
    size_t bufferlen = BUFFERLEN;
    sysctlbyname("machdep.cpu.brand_string",&data,&bufferlen,NULL,0);
    printf("CPU: %s\n", data);
    
}
 
int main() {
    
    fetchUTS();
    fetchCTL();
    
    return 0;
}

