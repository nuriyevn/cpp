/****************************************************************
* Project Harman Car Multimedia System 
* (c) copyright 2015
* Company Harman/Becker Automotive Systems GmbH
* All rights reserved
* Secrecy Level STRICTLY CONFIDENTIAL
****************************************************************/

/**
* @file     CleanableReference.hpp
* @author   YASkrypnyk
* 
*/

#ifndef imp_nav_ctrl_prj_nbt_communication_CleanableReference_hpp
#define imp_nav_ctrl_prj_nbt_communication_CleanableReference_hpp
//-----------------------------------------------------------------------------
#ifndef TEST_ENVIRONMENT

#include "api/sys/colibry/pf/base/src/THBSharedPtr.hpp"

#endif 
//-----------------------------------------------------------------------------
namespace nav_nbt {
namespace communication {
//-----------------------------------------------------------------------------
template<typename ReferenceType>
class CleanableReferenceMaster;
//-----------------------------------------------------------------------------
/** 
*  do not use CleanableReferenceImpl directly. Use CleanableReference instead.
*/
//-----------------------------------------------------------------------------
template<typename ReferenceType>
class CleanableReferenceImpl 
{
public:
   void clear()
   {
      mReference = NULL;
   }

   void set(ReferenceType *reference)
   {
      mReference = reference;
   }

   bool isEmpty() const 
   {
      return mReference == NULL;
   }

   ReferenceType* get() const 
   {
      ASSERT_MSG("ERROR: using empty pointer from CleanableReference", mReference);
      return mReference;
   }

   typedef THBSharedPtr< CleanableReferenceImpl<ReferenceType> > Ptr;
private:
   ReferenceType *mReference;

   CleanableReferenceImpl()
      : mReference(NULL)
   {
   }

   friend class CleanableReferenceMaster<ReferenceType>;

private:
   CleanableReferenceImpl(const CleanableReferenceImpl&);
   CleanableReferenceImpl& operator = (const CleanableReferenceImpl&);
};
//-----------------------------------------------------------------------------
/** 
*  just a simple wrapper on pointer which allow make pointer empty in all copies of CleanableReference. 
*/
template<typename ReferenceType>
class CleanableReference
{
public:

   virtual ~CleanableReference() 
   { 
   }

   bool isEmpty() const 
   {
      return mImpl->isEmpty();
   }

   ReferenceType* operator ->() const
   {
      return mImpl->get();
   }

   ReferenceType* get() const
   {
      return mImpl->get();
   }

   // returns true if boths refers to the same reference to object (It means both are same or copy of same CleanableReference)
   bool operator == (const CleanableReference<ReferenceType> &other) const 
   {
      return mImpl.getPointer() == other.mImpl.getPointer();
   }

   // returns true if boths refers to NOT the same reference to object (It means both are NOT same or copy of same CleanableReference)
   bool operator != (const CleanableReference<ReferenceType> &other) const 
   {
      return !(*this == other);
   }
protected:
   typename CleanableReferenceImpl<ReferenceType>::Ptr mImpl;

   CleanableReference(typename CleanableReferenceImpl<ReferenceType>::Ptr impl)
      : mImpl(impl)
   {
   }

private:
   CleanableReference(); // CleanableReference should be created only as a copy of CleanableReferenceMaster or another CleanableReference
};
//-----------------------------------------------------------------------------
template<typename ReferenceType>
class CleanableReferenceMaster : public CleanableReference<ReferenceType>
{
public:
   CleanableReferenceMaster()
      : CleanableReference<ReferenceType>(typename CleanableReferenceImpl<ReferenceType>::Ptr(new CleanableReferenceImpl<ReferenceType>()))
   {
   }

   ~CleanableReferenceMaster()
   {
      clear();
   }

   void clear()
   {
      this->mImpl->clear();
   }

   void set(ReferenceType *reference)
   {
      this->mImpl->set(reference);
   }

   operator CleanableReference<ReferenceType>() const
   {
      return CleanableReference<ReferenceType>(this->mImpl);
   }

private: // we should not copy CleanableReferenceMaster because it clears in destructor. Copy CleanableReference instead.
   CleanableReferenceMaster(const CleanableReferenceMaster&);
   CleanableReferenceMaster& operator = (const CleanableReferenceMaster&);
};
//-----------------------------------------------------------------------------
} // namespace communication
} // namespace nav_nbt

#endif // imp_nav_ctrl_prj_nbt_communication_CleanableReference_hpp
