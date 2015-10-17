#ifndef brownie_asynch_impl_GeneralNotificationAllocator_hpp
#define brownie_asynch_impl_GeneralNotificationAllocator_hpp

#include <cstring>

namespace brownie {
namespace asynch {
namespace impl {

template <int MaxSizeBase_>
struct GeneralNotificationAllocator {

   GeneralNotificationAllocator(void* pReadObject,
                                void* pWriteObject)
   : mReadIndex(-1)
   , mWriteIndex(-1) {
      memset(mAllocations, 0, sizeof(mAllocations));
      initialize(pReadObject, pWriteObject);
   }

   void initialize(void* pReadObject,
                   void* pWriteObject) {
      if ((pReadObject != 0) && (pWriteObject != 0)) {
         mAllocations[0] = pReadObject;
         mAllocations[1] = pWriteObject;
         mReadIndex = 0;
         mWriteIndex = 1;
      }
   }

   void* const getReadPtr() const {
      return mAllocations[mReadIndex];
   }

   void* const getWritePtr() const {
      return mAllocations[mWriteIndex];
   }

   const bool canAllocate() const {
      return (mAllocations[successorIndex(mWriteIndex)] == 0);
   }

   enum AddResult {
      AllocateError = -1,
      Success = 0,
      EmptyStatus = 1
   };

   AddResult addAllocatedStatus(void* pStatus);

   void nextStatus() {
      mAllocations[mReadIndex] = 0;
      mReadIndex = successorIndex(mReadIndex);
   }

   static const int successorIndex(const int index) {
      return ((index + 1) & ((sMaxSize) - 1));
   }

   static const int sMaxSize = (1 << MaxSizeBase_);
   int mReadIndex;
   int mWriteIndex;
   void* mAllocations[sMaxSize];

};

// implementation
template <int MaxSizeBase_>
typename GeneralNotificationAllocator<MaxSizeBase_>::AddResult GeneralNotificationAllocator<MaxSizeBase_>::addAllocatedStatus(void* pStatus) {
   if (canAllocate() && (pStatus != 0)) {
      mWriteIndex = successorIndex(mWriteIndex);
      mAllocations[mWriteIndex] = pStatus;
      return Success;
   } else {
      return (pStatus == 0 ? EmptyStatus : AllocateError);
   }
}

} // namespace impl
} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_impl_GeneralNotificationAllocator_hpp
