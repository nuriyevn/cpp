#pragma once
//-----------------------------------------------------------------------------
#include "stdafx.h"

#include "Communication\Attribute.hpp"

using namespace nav_nbt;
//-----------------------------------------------------------------------------
class AcyncCalculator
{
public:
   AcyncCalculator();

   void addition(int first, int second, communication::OneArgFunction<int /*result*/> callback);
   void subtraction(int first, int second, communication::OneArgFunction<int /*result*/> callback);

   communication::IROAttribute<size_t>& operationCount() { return mOperationCount; } //Attribute. You can get value or subscribe on change.

private:
   communication::Attribute<size_t> mOperationCount;
};
//-----------------------------------------------------------------------------
