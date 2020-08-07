#pragma once

#include <iostream>
#include <libhikvision.hpp>

#ifdef MAX_CHANNUM
#undef MAX_CHANNUM
constexpr auto MAX_CHANNUM = 8;
#endif