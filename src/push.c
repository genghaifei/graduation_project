#include "push.c"

int init()
{
    cJSON *jpush;
    JPushNotification *note;
    jpushInit(&jpush,&note);

    setPlatform(jpush,J_PUSH_PLATFORM_ANDROID);

    char *target[3] = {"value1",""}
}
