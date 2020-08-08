#include "AlertWatchdog.h"
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#include <signal.h>

bool stand_by = true;

void MessageCallback(LONG lCommand, NET_DVR_ALARMER* pAlarmer, char* pAlarmInfo, DWORD dwBufLen, void* puser) {
	NET_DVR_ALARMINFO struAlarmInfo;
#ifdef _MSC_VER
	memcpy_s(&struAlarmInfo, sizeof(NET_DVR_ALARMINFO), pAlarmInfo, sizeof(NET_DVR_ALARMINFO));
#else
	memcpy(&struAlarmInfo, pAlarmInfo, sizeof(NET_DVR_ALARMINFO));
#endif
	switch (lCommand) {
	case COMM_ALARM:
		switch (struAlarmInfo.dwAlarmType) {
		case 3:
			for (int channel = 0; channel < MAX_CHANNUM; channel++) {
				if (struAlarmInfo.dwChannel[channel] == 1) {
#ifndef NDEBUG
					std::cout << "Channel " << channel + 1 << std::endl;
					// TODO
#endif
				}
			}
			break;
		}
	}
}

AlertWatchdog::ConnectInfo ParseConfigureJson() {
	using AlertWatchdog::PREDEFINED_CONFIGURE_KEYS;
	using AlertWatchdog::KEY_LOCATE;
	std::ifstream fin("config.json");
	if (!fin.is_open()) {
#ifndef NDEBUG
		std::cerr << "Can't open configure file";
#else
		// TODO: File can't open
#endif
	}
	nlohmann::json config;
	fin >> config;
	for (auto key: PREDEFINED_CONFIGURE_KEYS)
		if (!config.contains(key)) {
			// TODO: Key not found
		}
	return AlertWatchdog::ConnectInfo(config[PREDEFINED_CONFIGURE_KEYS[KEY_LOCATE::HOST]],
		config[PREDEFINED_CONFIGURE_KEYS[KEY_LOCATE::PORT]],
		config[PREDEFINED_CONFIGURE_KEYS[KEY_LOCATE::USERNAME]],
		config[PREDEFINED_CONFIGURE_KEYS[KEY_LOCATE::PASSWORD]]);
}

#ifdef _WIN32
BOOL WINAPI SignalHandler(DWORD signal) {
	if (signal == CTRL_C_EVENT)
		stand_by = false;

	return TRUE;
}
#else
void SignalHandler(int) {
	stand_by = false;
}
#endif

void SetSignalHandle() {
#ifdef _WIN32
	if (!SetConsoleCtrlHandler(SignalHandler, TRUE)) {
	}
#else
	signal(SIGINT, signal_handle);
#endif
}

int main() {
	SetSignalHandle();
#ifndef NDEBUG
	std::cout << "Initialize hikvision client\n";
#endif
	AlertWatchdog::HikvisionClient hikvisionClient(ParseConfigureJson());
	hikvisionClient.Initialize();
	try {
		hikvisionClient.Login();
	} catch (AlertWatchdog::LoginException e) {
		std::cerr << "Login failure (" << NET_DVR_GetLastError() << ")\n";;
	}
	hikvisionClient.SetCallbackFunction(MessageCallback);
	hikvisionClient.SetupAlarmChan();
#ifndef NDEBUG
	std::cout << "Press Control-C to exit client\n";
	//std::cout.flush();
#endif
	while (stand_by) {
		Sleep(1000);
	}
#ifndef NDEBUG
	std::cout << "Cleanup hikvision client\n";
#endif
	hikvisionClient.CloseAlarmChan();
	try {
		hikvisionClient.Logout();
	}
	catch (AlertWatchdog::LogoutException e) {
		std::cerr << "Logout failure (" << NET_DVR_GetLastError() << ")\n";;
	}
	hikvisionClient.Cleanup();
	return 0;
}
