#pragma once

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
//#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>

namespace AlertWatchdog {
	using std::string;
	class Data {
	protected:
		nlohmann::json data;
		long long timestamp;
	public:
		Data();
		//Data(string);
		string GetJson() const;
	};

	class PostData : public Data {
		const static unsigned long version = 0x1;
	public:
		PostData(unsigned long type, string message);
	};

	class UploadConfigure {
	private:
		string remote_url;
	public:
		UploadConfigure(string);
	};
}