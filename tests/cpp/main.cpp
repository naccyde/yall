#include <iostream>
#include <pthread.h>

#include <yall/Yall.hpp>

using namespace std;

pthread_t threads[5];

void memoryInfos(YallData &d, const void *args);

class Device {
public:
	Device()
	{
		Yall::setSubsystem("device", "yall_cpp_test", yall_debug, yall_console_output, "");
		YALL_DEBUG("device", "Creating the device.");
	}

	~Device()
	{

	}

	void status()
	{
		YALL_INFO("device", "Current device status : operational.");
	}
};

void *thread0(void *args)
{
	UNUSED(args);

	for (int i = 0; i < 15; ++i) {
		YALL_DEBUG("yall_cpp_test", Yall::getVersionString() << " " << Yall::getVersion());
		YALL_DEBUG("io", "IO subsystem ready.");
		YALL_CALL_ERR("memory", memoryInfos, nullptr);
		YALL_ALERT("scheduler" , "Using process 7034.");
	}

	return NULL;
}

void *thread1(void *args)
{
	UNUSED(args);

	for (int i = 0; i < 15; ++i) {
		YALL_DEBUG("yall_cpp_test", Yall::getVersionString() << " " << Yall::getVersion());
		YALL_DEBUG("io", "IO subsystem ready.");
		YALL_CALL_ERR("memory", memoryInfos, nullptr);
		YALL_ALERT("scheduler" , "Using process 7034.");
	}

	return NULL;
}

void *thread2(void *args)
{
	UNUSED(args);

	for (int i = 0; i < 15; ++i) {
		YALL_DEBUG("yall_cpp_test", Yall::getVersionString() << " " << Yall::getVersion());
		YALL_DEBUG("io", "IO subsystem ready.");
		YALL_CALL_ERR("memory", memoryInfos, nullptr);
		YALL_ALERT("scheduler" , "Using process 7034.");
	}

	return NULL;
}

void *thread3(void * args)
{
	UNUSED(args);

	for (int i = 0; i < 15; ++i) {
		YALL_DEBUG("yall_cpp_test", Yall::getVersionString() << " " << Yall::getVersion());
		YALL_DEBUG("io", "IO subsystem ready.");
		YALL_CALL_ERR("memory", memoryInfos, nullptr);
		YALL_ALERT("scheduler" , "Using process 7034.");
	}

	return NULL;
}

void *thread4(void *args)
{
	UNUSED(args);

	for (int i = 0; i < 15; ++i) {
		YALL_DEBUG("yall_cpp_test", Yall::getVersionString() << " " << Yall::getVersion());
		YALL_DEBUG("io", "IO subsystem ready.");
		YALL_CALL_ERR("memory", memoryInfos, nullptr);
		YALL_ALERT("scheduler" , "Using process 7034.");
	}

	return NULL;
}

int main(void)
{
	Yall::init();
        Yall::enableDebug();

	Device d = Device();

        Yall::config().setTabWidth(4);
        Yall::config().setStdHeaderTemplate("[%d] :: %L : %f : \n\t");
        Yall::config().setCallHeaderTemplate("[%d] :: %-9l : %s : ");

        Yall::setSubsystem("yall_cpp_test", "", yall_debug, yall_console_output, "");
        Yall::setSubsystem("io", "yall_cpp_test", yall_debug, yall_console_output, "");
        Yall::setSubsystem("memory", "yall_cpp_test", yall_debug, yall_console_output, "");
        Yall::setSubsystem("scheduler", "yall_test_cpp", yall_debug, yall_console_output, "");

	pthread_create(&threads[0], NULL, thread0, NULL);
	pthread_create(&threads[1], NULL, thread1, NULL);
	pthread_create(&threads[2], NULL, thread2, NULL);
	pthread_create(&threads[3], NULL, thread3, NULL);
	pthread_create(&threads[4], NULL, thread4, NULL);

	YALL_DEBUG("yall_cpp_test", Yall::getVersionString() << " " << Yall::getVersion());
        YALL_DEBUG("io", "IO subsystem ready.");
	YALL_CALL_ERR("memory", memoryInfos, nullptr);
        YALL_ALERT("scheduler" , "Using process 7034.");

        Yall::disableSubsystem("scheduler");
        YALL_DEBUG("scheduler", "Starting process 52233.");
        Yall::enableSubsystem("scheduler");

	d.status();

#ifdef _WIN32
        getchar();
#endif
	for (int i = 0; i < 5; ++i)
		pthread_join(threads[i], NULL);
	
	Yall::showSubsystemsTree();

	Yall::closeAll();

        return 0;
}

void memoryInfos(YallData &d, const void *args)
{
        UNUSED(args);

        d.newLine(0) << "======= Backtrace: =========";
        d.newLine(1) << "/lib/x86_64-linux-gnu/libc.so.6(+0x70bfb)[0x7ff9cd0bfbfb]";
        d.newLine(1) << "/lib/x86_64-linux-gnu/libc.so.6(+0x76fc6)[0x7ff9cd0c5fc6]";
        d.newLine(1) << "/lib/x86_64-linux-gnu/libc.so.6(+0x7780e)[0x7ff9cd0c680e]";
        d.newLine(1) << "/lib/x86_64-linux-gnu/libc.so.6(+0x35940)[0x7ff9cd084940]";
        d.newLine(1) << "/lib/x86_64-linux-gnu/libc.so.6(+0x3599a)[0x7ff9cd08499a]";
        d.newLine(1) << "/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf8)[0x7ff9cd06f2e8]";

        d.newLine(0) << "======== Memory map: ========";
        d.newLine(1) << "55d5e5d8c000-55d5e5dbe000 rw-p 00000000 00:00 0                          [heap]";
        d.newLine(1) << "7ff9c8000000-7ff9c8021000 rw-p 00000000 00:00 0 ";
        d.newLine(1) << "7ff9c8021000-7ff9cc000000 ---p 00000000 00:00 0 ";
        d.newLine(1) << "7ff9cd04f000-7ff9cd1e2000 r-xp 00000000 08:06 4195034                    /lib/x86_64-linux-gnu/libc-2.24.so";
        d.newLine(1) << "7ff9cd1e2000-7ff9cd3e2000 ---p 00193000 08:06 4195034                    /lib/x86_64-linux-gnu/libc-2.24.so";
 }