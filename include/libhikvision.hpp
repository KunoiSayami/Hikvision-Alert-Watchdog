#pragma once
#include <string>
#include <exception>
#include <HCNetSDK.h>

namespace AlertWatchdog {
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
		/*class ClassConnectInfo {
		private:
			PCHAR loc, user, password;
			unsigned short port;
			LPNET_DVR_USER_LOGIN_INFO login_info;
			void PasteParams(const string&, const unsigned short&, const string&, const string&);
		public:
			ClassConnectInfo(const string&, const unsigned short&, const string&, const string&);
			ClassConnectInfo(const ConnectInfo&);
			ClassConnectInfo(const ConnectInfo*);
			~ClassConnectInfo();
			PCHAR GetLocation();
			PCHAR GetUser();
			PCHAR GetPassword();
			unsigned short GetPort();
		};*/

		ConnectInfo(const string&, const unsigned short&, const string&, const string&);
		//ConnectInfo(ConnectInfo&);
		void Login();
		void Logout();
		void InitializeUserInfo();
		bool IsConnected() const;
	};

	class HikvisionClient {
	private:
		ConnectInfo info;
		static bool is_init;
	public:
		HikvisionClient(const ConnectInfo&);
		void Initialize();
		//void Login();
		void Cleanup();
		bool Initialized() const;
	};

}