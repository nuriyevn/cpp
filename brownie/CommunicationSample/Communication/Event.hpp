/****************************************************************
* Project Harman Car Multimedia System 
* (c) copyright 2015
* Company Harman/Becker Automotive Systems GmbH
* All rights reserved
* Secrecy Level STRICTLY CONFIDENTIAL
****************************************************************/

/**
* @file     Event.hpp
* @author   YASkrypnyk
* 
*/

#ifndef imp_nav_ctrl_prj_nbt_communication_Event_hpp
#define imp_nav_ctrl_prj_nbt_communication_Event_hpp
//-----------------------------------------------------------------------------
#ifndef TEST_ENVIRONMENT

#include "imp/nav/ctrl/prj/nbt/cedeviceservice/src/private/Communication/OneArgFunction.hpp"

#include "api/sys/colibry/pf/containers/src/THBList.hpp"
#include "api/sys/colibry/pf/base/src/THBSharedPtr.hpp"

#endif
//-----------------------------------------------------------------------------
namespace nav_nbt {
namespace communication {
//-----------------------------------------------------------------------------
template<typename ArgumentType>
class IEventSubscription
{
public:
   typedef OneArgFunction<ArgumentType> CallbackType;

public:
   virtual ~IEventSubscription() { }

   /**
   * Returns true if subscribtion was sucsessfully added. 
   * Otherwice returns false. For example if the same subscriptions is already exists or callback is empty.
   */
   virtual bool subscribe(CallbackType callback) = 0;

   /**
   * To unsubscribe you should pass the callback which was passed as parameter during subscription (or copy) 
   * but not new callback object with the same parameters.
   */
   virtual void unsubscribe(CallbackType callback) = 0;

   virtual UInt32 subscribtionsCount() = 0;
};
//-----------------------------------------------------------------------------
template<typename ArgumentType>
class Event : public IEventSubscription<ArgumentType>
{
public:
   typedef OneArgFunction<ArgumentType> CallbackType; // parent CallbackType declaration does not work in some compilers

public:

   Event()
   {
   }

   void call(ArgumentType value)
   {
      for(typename THBList<CallbackType>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it)
      {
         it->call(value);
      }
   }

   virtual /*override*/ bool subscribe(CallbackType callback)
   {
      if (callback.isEmpty())
         return false;

      for(typename THBList<CallbackType>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it)
      {
         if (*it == callback)
            return false;
      }

      mCallbacks.push_back(callback);
      return true;
   }

   virtual /*override*/ void unsubscribe(CallbackType callback)
   {
      if (callback.isEmpty())
         return;

      mCallbacks.remove(callback);
   }

   virtual /*override*/ UInt32 subscribtionsCount()
   {
      return mCallbacks.size();
   }

private:
   THBList<CallbackType> mCallbacks;

private:
   Event(const Event<ArgumentType> &);
   Event& operator = (const Event<ArgumentType> &);
};
//-----------------------------------------------------------------------------
} // namespace communication
} // namespace nav_nbt

#endif // imp_nav_ctrl_prj_nbt_communication_Event_hpp
