# Hikvision Alert Watchdog

## Build

* Download [Hikvision SDK](https://open.hikvision.com/download/5cda567cf47ae80dd41a54b3) and [nlohmann json header file](https://github.com/nlohmann/json)
* Also, we need [curl](https://curl.haxx.se/download.html) **static** library and header library
* Put library file to `lib/`
* Build with cmake

```bash
cmake .
cmake --build .
```

## Run

* Copy `config.json.default` as `config.json`
* Edit `config.json`
* Copy runtime library to program working directory
* Run program

## SDK version
SDK name | Version
------------|----------
Hikvision | V6.1.4.42_build20200527
curl | 7.71.1
nlohmann json | 3.9.1

## LICENSE

[![](https://www.gnu.org/graphics/agplv3-155x51.png)](https://www.gnu.org/licenses/agpl-3.0.txt)

Copyright (C) 2020 KunoiSayami

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.

## Open source license

See [OpenSourceLicense](https://github.com/KunoiSayami/Hikvision-Alert-Watchdog/blob/master/OpenSourceLicense)