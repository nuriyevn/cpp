/****************************************************************
* Project Harman Car Multimedia System 
* (c) copyright 2015
* Company Harman/Becker Automotive Systems GmbH
* All rights reserved
* Secrecy Level STRICTLY CONFIDENTIAL
****************************************************************/

/**
* @file     Attribute.hpp
* @author   YASkrypnyk
* 
*/

#ifndef imp_nav_ctrl_prj_nbt_communication_Attribute_hpp
#define imp_nav_ctrl_prj_nbt_communication_Attribute_hpp
//-----------------------------------------------------------------------------
#ifndef TEST_ENVIRONMENT

#include "imp/nav/ctrl/prj/nbt/cedeviceservice/src/private/Communication/OneArgFunction.hpp"
#include "imp/nav/ctrl/prj/nbt/cedeviceservice/src/private/Communication/Event.hpp"

#include "api/sys/colibry/pf/containers/src/THBList.hpp"
#include "api/sys/colibry/pf/base/src/THBSharedPtr.hpp"

#endif
//-----------------------------------------------------------------------------
namespace nav_nbt {
namespace communication {
//-----------------------------------------------------------------------------
template<typename AttributeType>
class IROAttribute : public IEventSubscription<const AttributeType&>
{
public:
   virtual ~IROAttribute() { }

   virtual AttributeType get() const = 0;
};
//-----------------------------------------------------------------------------
template<typename AttributeType>
class Attribute : public IROAttribute<AttributeType>
{
public:
   typedef OneArgFunction<const AttributeType &> CallbackType;

public:

   Attribute(const AttributeType &defaultValue, bool subscriptionOnDefaultValue, bool subscriptionOnEqualValue)
      : mValue(defaultValue)
      , mValueIsDefault(true)
      , mSubscriptionOnDefaultValue(subscriptionOnDefaultValue)
      , mSubscriptionOnEqualValue(subscriptionOnEqualValue)
   {
   }

   void set(const AttributeType &value)
   {
      const bool changed = mValue != value;
      mValue = value;
      mValueIsDefault = false;
      if (!changed && !mSubscriptionOnEqualValue)
         return;


      mCallbacks.call(mValue);
   }

   virtual /*override*/ AttributeType get() const 
   { 
      return mValue; 
   }

   virtual /*override*/ bool subscribe(CallbackType callback)
   {
      if (!mCallbacks.subscribe(callback))
         return false;

      if (!mValueIsDefault || mSubscriptionOnDefaultValue)
         callback.call(mValue);

      return true;
   }

   virtual /*override*/ void unsubscribe(CallbackType callback)
   {
      mCallbacks.unsubscribe(callback);
   }

   virtual /*override*/ UInt32 subscribtionsCount()
   {
      return mCallbacks.subscribtionsCount();
   }

private:
   AttributeType mValue;
   bool mValueIsDefault;
   const bool mSubscriptionOnDefaultValue;
   const bool mSubscriptionOnEqualValue;

   Event<const AttributeType &> mCallbacks;

private:
   Attribute(const Attribute<AttributeType> &);
   Attribute& operator = (const Attribute<AttributeType> &);
};
//-----------------------------------------------------------------------------
} // namespace communication
} // namespace nav_nbt

#endif // imp_nav_ctrl_prj_nbt_communication_Attribute_hpp
