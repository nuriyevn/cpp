/****************************************************************
* Project Harman Car Multimedia System 
* (c) copyright 2015
* Company Harman/Becker Automotive Systems GmbH
* All rights reserved
* Secrecy Level STRICTLY CONFIDENTIAL
****************************************************************/

/**
* @file     NoArgFunction.hpp
* @author   YASkrypnyk
* 
*/

#ifndef imp_nav_ctrl_prj_nbt_communication_NoArgFunction_hpp
#define imp_nav_ctrl_prj_nbt_communication_NoArgFunction_hpp
//-----------------------------------------------------------------------------
#ifndef TEST_ENVIRONMENT

#include "api/sys/colibry/pf/base/src/THBSharedPtr.hpp"
#include "imp/nav/ctrl/prj/nbt/cedeviceservice/src/private/Communication/CleanableReference.hpp"

#endif
//-----------------------------------------------------------------------------
namespace nav_nbt {
namespace communication {
//-----------------------------------------------------------------------------
/**
* Just a simple wrapper to pointer to function with no arguments: void (*function) ();
* Member functions can be called using MemberNoArgCallback.
* During comparation only function pointer and abject pointer are compared (not binded parameters).
* Please replace me by std::function in some day, when it become available.
*/
class NoArgFunction
{
public:
   class ICallback
   {
   public:
      virtual ~ICallback() {}
      virtual void operator() () const = 0;
   };

   typedef THBSharedPtr<ICallback> CallbackPtr;


public:
   NoArgFunction()
      : mCallback()
   {
   }

   NoArgFunction(const CallbackPtr callback)
      : mCallback(callback)
   {
   }

   NoArgFunction(const NoArgFunction& other)
      : mCallback(other.mCallback)
   {
   }

   NoArgFunction& operator = (const NoArgFunction& other)
   {
      mCallback = other.mCallback;
      return *this;
   }

   // returns true if both objects are copy of the same one.
   bool operator == (const NoArgFunction& other) const
   {
      return mCallback.getPointer() == other.mCallback.getPointer();
   }

   bool operator != (const NoArgFunction& other) const
   {
      return !(*this == other);
   }

   void clear()
   {
      mCallback = CallbackPtr();
   }

   void call()
   {
      if (mCallback != 0)
         (*mCallback)();
   } 

   bool isEmpty() const
   {
      return mCallback == 0;
   }
private:
   CallbackPtr mCallback;

};
//-----------------------------------------------------------------------------
/**
* Binds a pointer to object to a member function.
* Result is NoArgFunction.
*/
template<typename T>
class MemberNoArgCallback : public NoArgFunction::ICallback
{
public:
   typedef void (T::*NoArgCallbackFunc)();

   static NoArgFunction create(NoArgCallbackFunc func, T* object)
   {
      return NoArgFunction(typename NoArgFunction::CallbackPtr(new MemberNoArgCallback<T>(func, object)));
   }

   virtual void operator() () const
   {
      (mObject->*mFunc)();
   };

private:
   MemberNoArgCallback(NoArgCallbackFunc func, T* object)
      : mFunc(func),
        mObject(object)
   {
   }
   
   NoArgCallbackFunc mFunc;
   T *mObject;
};

template<typename T>
NoArgFunction bind(void (T::*func)(), T* object)
{
   return MemberNoArgCallback<T>::create(func, object);
}
//-----------------------------------------------------------------------------
/**
* Binds a pointer to object to a member function.
* Result is NoArgFunction.
*/
template<typename T, typename Data>
class MemberNoArgCallbackWithData : public NoArgFunction::ICallback
{
public:
   typedef void (T::*NoArgCallbackFunc)(Data);

   static NoArgFunction create(NoArgCallbackFunc func, T* object, Data data)
   {
      return NoArgFunction(typename NoArgFunction::CallbackPtr(new MemberNoArgCallbackWithData<T, Data>(func, object, data)));
   }

   virtual void operator() () const
   {
      (mObject->*mFunc)(mData);
   }

private:
   MemberNoArgCallbackWithData(NoArgCallbackFunc func, T* object, Data data)
      : mFunc(func),
        mObject(object),
        mData(data)
   {
   }
   
   NoArgCallbackFunc mFunc;
   T *mObject;
   Data mData;
};
//-----------------------------------------------------------------------------
template<typename T, typename Data>
NoArgFunction bind(void (T::*func)(Data), T* object, Data data)
{
   return MemberNoArgCallbackWithData<T, Data>::create(func, object, data);
}
//-----------------------------------------------------------------------------
/**
* Binds a CleanableReference to a member function.
* Function call will be skipped if reference to object is empty.
* Result is NoArgFunction.
*/
template<typename T>
class CleanableMemberNoArgCallback : public NoArgFunction::ICallback
{
public:
   typedef void (T::*NoArgCallbackFunc)();

   static NoArgFunction create(NoArgCallbackFunc func, CleanableReference<T> object)
   {
      return NoArgFunction(typename NoArgFunction::CallbackPtr(new CleanableMemberNoArgCallback<T>(func, object)));
   }

   virtual void operator() () const
   {
      if (!mObject.isEmpty())
         (mObject.get()->*mFunc)();
   }

private:
   CleanableMemberNoArgCallback(NoArgCallbackFunc func, CleanableReference<T> object)
      : mFunc(func),
        mObject(object)
   {
   }
   
   NoArgCallbackFunc mFunc;
   CleanableReference<T> mObject;
};
//-----------------------------------------------------------------------------
template<typename T>
NoArgFunction bind(void (T::*func)(), CleanableReference<T> object)
{
   return CleanableMemberNoArgCallback<T>::create(func, object);
}
//-----------------------------------------------------------------------------
/**
* Binds a CleanableReference to a member function.
* Function call will be skipped if reference to object is empty.
* Result is NoArgFunction.
*/
template<typename T, typename Data>
class CleanableMemberNoArgCallbackWithData : public NoArgFunction::ICallback
{
public:
   typedef void (T::*NoArgCallbackFunc)(Data);

   static NoArgFunction create(NoArgCallbackFunc func, CleanableReference<T> object, Data data)
   {
      return NoArgFunction(typename NoArgFunction::CallbackPtr(new CleanableMemberNoArgCallbackWithData<T, Data>(func, object, data)));
   }

   virtual void operator() () const
   {
      if (!mObject.isEmpty())
         (mObject.get()->*mFunc)(mData);
   }

private:
   CleanableMemberNoArgCallbackWithData(NoArgCallbackFunc func, CleanableReference<T> object, Data data)
      : mFunc(func),
        mObject(object),
        mData(data)
   {
   }
   
   NoArgCallbackFunc mFunc;
   CleanableReference<T> mObject;
   Data mData;
};
//-----------------------------------------------------------------------------
template<typename T, typename Data>
NoArgFunction bind(void (T::*func)(Data), CleanableReference<T> object, Data data)
{
   return CleanableMemberNoArgCallbackWithData<T, Data>::create(func, object, data);
}
//-----------------------------------------------------------------------------
} // namespace communication
} // namespace nav_nbt

#endif // imp_nav_ctrl_prj_nbt_communication_NoArgFunction_hpp
