#include <android/log.h>
#include <substrate.h>

#define LOG_TAG "mainClass"

#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

void cigi_hook(void *orig_fcn, void* new_fcn, void **orig_fcn_ptr)
{
	MSHookFunction(orig_fcn, new_fcn, orig_fcn_ptr);
}
MSConfig(MSFilterExecutable, "/system/bin/app_process")

int (*original_arc4random)(void);
int replaced_arc4random(void)
{
	int arc_rand = original_arc4random();
	LOGI("origin rand is %d",&arc_rand);
	LOGI("origin rand is is %d",arc_rand);
    return 1000000000;
}
MSInitialize {
    cigi_hook((void *)arc4random,(void*)&replaced_arc4random,(void**)&original_arc4random);
}
