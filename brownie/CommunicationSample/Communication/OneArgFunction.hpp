/****************************************************************
* Project Harman Car Multimedia System 
* (c) copyright 2015
* Company Harman/Becker Automotive Systems GmbH
* All rights reserved
* Secrecy Level STRICTLY CONFIDENTIAL
****************************************************************/

/**
* @file     OneArgFunction.hpp
* @author   YASkrypnyk
* 
*/

#ifndef imp_nav_ctrl_prj_nbt_communication_OneArgFunction_hpp
#define imp_nav_ctrl_prj_nbt_communication_OneArgFunction_hpp
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
* Just a simple wrapper to pointer to function with one argument: void (*function) (ArgType);
* Member functions can be called using MemberOneArgCallback.
* Please replace me by std::function in some day, when it become available.
*/
template<typename ArgType>
class OneArgFunction
{
public:
   class ICallback
   {
   public:
      virtual ~ICallback() {}
      virtual void operator ()(ArgType) const = 0;
   };

   typedef THBSharedPtr<ICallback> CallbackPtr;

public:
   OneArgFunction()
      : mCallback()
   {
   }

   OneArgFunction(const CallbackPtr callback)
      : mCallback(callback)
   {
   }

   OneArgFunction(const OneArgFunction& other)
      : mCallback(other.mCallback)
   {
   }

   OneArgFunction& operator = (const OneArgFunction<ArgType>& other)
   {
      mCallback = other.mCallback;
      return *this;
   }

   // returns true if both objects are copy of the same one.
   bool operator == (const OneArgFunction<ArgType>& other) const
   {
      return mCallback.getPointer() == other.mCallback.getPointer();
   }

   bool operator != (const OneArgFunction<ArgType>& other) const
   {
      return !(*this == other);
   }

   void clear()
   {
      mCallback = CallbackPtr();
   }

   bool isEmpty() const
   {
      return mCallback == 0;
   }

   void call(ArgType arg)
   {
      if (mCallback != 0)
         (*mCallback)(arg);
   } 

private:
   CallbackPtr mCallback;

};
//-----------------------------------------------------------------------------
/**
* Binds a pointer to object to a member function.
* Result is OneArgFunction.
*/
template<typename T, typename ArgType>
class MemberOneArgCallback : public OneArgFunction<ArgType>::ICallback
{
public:
   typedef void (T::*OneArgCallbackFunc)(ArgType);
   typedef OneArgFunction<ArgType> BaseOneArgFunction;

   static BaseOneArgFunction create(OneArgCallbackFunc func, T* object)
   {
      return BaseOneArgFunction(typename BaseOneArgFunction::CallbackPtr(new MemberOneArgCallback<T, ArgType>(func, object)));
   }

   virtual void operator() (ArgType arg) const
   {
      (mObject->*mFunc)(arg);
   };

private:
   MemberOneArgCallback(OneArgCallbackFunc func, T* object)
      : mFunc(func),
        mObject(object)
   {
   }
   
   OneArgCallbackFunc mFunc;
   T *mObject;
};

template<typename T, typename ArgType>
OneArgFunction<ArgType> bind(void (T::*func)(ArgType), T* object)
{
   return MemberOneArgCallback<T, ArgType>::create(func, object);
}
//-----------------------------------------------------------------------------
/**
* Binds a pointer to object to a member function.
* Result is OneArgFunction.
*/
template<typename T, typename ArgType, typename Data>
class MemberOneArgCallbackWithData : public OneArgFunction<ArgType>::ICallback
{
public:
   typedef void (T::*OneArgCallbackFunc)(ArgType, Data);
   typedef OneArgFunction<ArgType> BaseOneArgFunction;

   static BaseOneArgFunction create(OneArgCallbackFunc func, T* object, Data data)
   {
      return BaseOneArgFunction(typename BaseOneArgFunction::CallbackPtr(new MemberOneArgCallbackWithData<T, Data, ArgType>(func, object, data)));
   }

   virtual void operator() (ArgType arg) const
   {
      (mObject->*mFunc)(arg, mData);
   }

private:
   MemberOneArgCallbackWithData(OneArgCallbackFunc func, T* object, Data data)
      : mFunc(func),
        mObject(object),
        mData(data)
   {
   }
   
   OneArgCallbackFunc mFunc;
   T* mObject;
   Data mData;
};
//-----------------------------------------------------------------------------
template<typename T, typename ArgType, typename Data>
OneArgFunction<ArgType> bind(void (T::*func)(ArgType, Data), T* object, Data data)
{
   return MemberOneArgCallbackWithData<T, ArgType, Data>::create(func, object, data);
}
//-----------------------------------------------------------------------------
/**
* Binds a CleanableReference to a member function.
* Function call will be skipped if reference to object is empty.
* Result is OneArgFunction.
*/
template<typename T, typename ArgType>
class CleanableMemberOneArgCallback : public OneArgFunction<ArgType>::ICallback
{
public:
   typedef void (T::*OneArgCallbackFunc)(ArgType);
   typedef OneArgFunction<ArgType> BaseOneArgFunction;

   static BaseOneArgFunction create(OneArgCallbackFunc func, CleanableReference<T> object)
   {
      return BaseOneArgFunction(typename BaseOneArgFunction::CallbackPtr(new CleanableMemberOneArgCallback<T, ArgType>(func, object)));
   }

   virtual void operator() (ArgType arg) const
   {
      if (!mObject.isEmpty())
         (mObject.get()->*mFunc)(arg);
   }

private:
   CleanableMemberOneArgCallback(OneArgCallbackFunc func, CleanableReference<T> object)
      : mFunc(func),
        mObject(object)
   {
   }
   
   OneArgCallbackFunc mFunc;
   CleanableReference<T> mObject;
};

template<typename T, typename ArgType>
OneArgFunction<ArgType> bind(void (T::*func)(ArgType), CleanableReference<T> object)
{
   return CleanableMemberOneArgCallback<T, ArgType>::create(func, object);
}
//-----------------------------------------------------------------------------
/**
* Binds a CleanableReference to a member function.
* Function call will be skipped if reference to object is empty.
* Result is OneArgFunction.
*/
template<typename T, typename ArgType, typename Data>
class CleanableMemberOneArgCallbackWithData : public OneArgFunction<ArgType>::ICallback
{
public:
   typedef void (T::*OneArgCallbackFunc)(ArgType, Data);
   typedef OneArgFunction<ArgType> BaseOneArgFunction;

   static BaseOneArgFunction create(OneArgCallbackFunc func, CleanableReference<T> object, Data data)
   {
      return BaseOneArgFunction(typename BaseOneArgFunction::CallbackPtr(new CleanableMemberOneArgCallbackWithData<T, Data, ArgType>(func, object, data)));
   }

   virtual void operator() (ArgType arg) const
   {
      if (!mObject.isEmpty())
         (mObject.get()->*mFunc)(arg, mData);
   }

private:
   CleanableMemberOneArgCallbackWithData(OneArgCallbackFunc func, CleanableReference<T> object, Data data)
      : mFunc(func),
        mObject(object),
        mData(data)
   {
   }
   
   OneArgCallbackFunc mFunc;
   CleanableReference<T> mObject;
   Data mData;
};

template<typename T, typename ArgType, typename Data>
OneArgFunction<ArgType> bind(void (T::*func)(ArgType, Data), CleanableReference<T> object, Data data)
{
   return CleanableMemberOneArgCallbackWithData<T, ArgType, Data>::create(func, object, data);
}
//-----------------------------------------------------------------------------
} // namespace communication
} // namespace nav_nbt

#endif // imp_nav_ctrl_prj_nbt_communication_OneArgFunction_hpp
