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

	class OutOfLengthError: std::exception {};

	class ConnectInfo {
	private:
		string url;
		unsigned short port;
		string username, password;
		NET_DVR_DEVICEINFO device_info;
	public:
		class ClassConnectInfo {
		private:
			PCHAR loc, user, password;
			unsigned short port;
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
		};

		ConnectInfo(const string&, const unsigned short&, const string&, const string&);
		//ConnectInfo(ConnectInfo&);
		void Login();
	};

	class HikvisionClient {
	private:
		ConnectInfo info;
		static bool is_init;
	public:
		HikvisionClient(const ConnectInfo&);
		void Initialize();
		void Login();
		void Cleanup();
		bool Initialized() const;
	};

}