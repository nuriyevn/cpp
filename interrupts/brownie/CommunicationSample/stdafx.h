// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
//-----------------------------------------------------------------------------
// this section needed to adapt communication from mocca lib to stl
#define TEST_ENVIRONMENT

#include <memory>
#include <list>

#define THBSharedPtr std::shared_ptr
#define UInt32 size_t 
#define THBList std::list
#define getPointer get


#include "Communication\CleanableReference.hpp"
#include "Communication\OneArgFunction.hpp"
#include "Communication\Event.hpp"
#include "Communication\Attribute.hpp"
//-----------------------------------------------------------------------------

// TODO: reference additional headers your program requires here
