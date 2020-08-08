#pragma once
#include <string>
#include <exception>
#include <hikvision/HCNetSDK.h>

namespace AlertWatchdog {
	enum KEY_LOCATE {
		HOST = 0,
		PORT,
		USERNAME,
		PASSWORD
	};
	constexpr char * PREDEFINED_CONFIGURE_KEYS[] = { "host", "port", "username", "password" };
	using std::string;

	typedef char* PCHAR;

	class HikvisionBaseException : std::exception {};

	class InitializeException : HikvisionBaseException {};
	class OtherInitializeException : InitializeException {};
	class AlreadyInitializeException : InitializeException {};
	class CleanupException : HikvisionBaseException {};
	class AlreadyCleanupException : CleanupException {};
	class OtherCleanupException : CleanupException {};

	class OutOfLengthError : std::exception {};
	class ConnectException : HikvisionBaseException {};
	class LoginException : ConnectException {};
	class LogoutException : ConnectException {};
	class OtherLoginException : LoginException {};
	class AlreadyLoginedException : LoginException {};
	class NotLoginException : LogoutException {};

	class ConnectInfo {
	private:
		string url;
		unsigned short port;
		string username, password;
		NET_DVR_USER_LOGIN_INFO user_info;
		NET_DVR_DEVICEINFO_V40 device_info;
		long user_id;
		bool is_connect;
	public:
		ConnectInfo(const string& hostname, const unsigned short& port, const string& username, const string& password);
		void Login();
		void Logout();
		void InitializeUserInfo();
		bool IsConnected() const;
		long GetUserId() const;
	};

	class ArmInfo {
		LONG lHandle;
		NET_DVR_SETUPALARM_PARAM struAlarmParam = { 0 };
		bool is_setup;
	public:
		ArmInfo();
		void SetupAlarmChan(LONG userId); // ref: NET_DVR_SetupAlarmChan_V41
		bool CloseAlarmChan();
		bool GetStatus() const;
	};

	class HikvisionClient {
	private:
		ConnectInfo info;
		static bool is_init;
		ArmInfo arminfo;
	public:
		HikvisionClient(const ConnectInfo& c);
		void Initialize();
		void Login();
		void Logout();
		void SetCallbackFunction(MSGCallBack);
		void SetupAlarmChan();
		void CloseAlarmChan();
		void Cleanup();
		bool Initialized() const;
	};

}