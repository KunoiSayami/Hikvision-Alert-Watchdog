#pragma once

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
#include <chrono>
#include <ctime>

namespace AlertWatchdog {
	using std::string;
	class Data {
	private:
		string data;
		long long timestamp;
	public:
		Data();
		Data(string);
	};

	class UploadConfigure {
	private:
		string remote_url;
	public:
		UploadConfigure(string);
	};
}