#include "include/upload.h"

namespace AlertWatchdog {
	UploadConfigure::UploadConfigure(string url) : remote_url(url) {}

	Data::Data(): timestamp(time(nullptr)) {
		//auto obj = std::chrono::system_clock::now();
	}
}
