#ifndef brownie_asynch_test_simplecall
#define brownie_asynch_test_simplecall

#include <iostream>

#include "../asynch/LocalCallable.hpp"
#include "../asynch/LocalCallback.hpp"

namespace brownie {
namespace asynch {
namespace test {

// LocalCall ������������ ��� ��������� ����������� �� ������, ��������������, 
// ��� � ���������� �������� ��������� ������ ��������� ������� ����� ��������
// � ������ �������, ������ ���, ����� ����� �������������� �����, ��������
// CSimpleCallCallable::mValue ����� ��������.
// ���� �������� ��������� ������ ��� ����� 0, �� ��������� ����� ��������� 
// ��������. � ������ ���� �������� ��������� < 0, �� ����� ����� ����������
// ������
// �� �����������, ������� ������ ���������� �������� ���������� ��� ������,
// ����� ���������� ������ �������� CSimpleCallCallable::mValue � ��������
// ����������, � �������� �������� ���������, � �������� ������.

class CSimpleCallCallable: public brownie::asynch::LocalCallable<CSimpleCallCallable> 
{
public:
   CSimpleCallCallable() : mValue(0) {};

   struct CallArgument
   {
      CallArgument() : value(0) 
      {
         std::cout << "CallArgument: Default constructor" << std::endl;
      };
      CallArgument(const CallArgument& val)
      {
         value = val.value;
         std::cout << "CallArgument: Copy constructor" << std::endl;
      };
      int value;
   };

   struct CallResult
   {
      CallResult() : value(0) {};
      int value;
   };

   struct CallError
   {
      CallError() : value(0) {};
      int value;
   };

   //� ������ ���� � ��� ��������� ��� FormalOperationCall<Arg>, �� ��� ������������� 
   //���������� ����� brownie::asynch::Void. �������������� �������� ���������� ��������
   //����������, ����� ��� ����� ������ ���� ����, ����������� �� ���� �������� ���
   //��������� ������
   typedef brownie::asynch::FormalOperationCall<CallArgument> OnlyArgumentCall;

   void handleCall(OnlyArgumentCall& call)
   {
      const int val = call.getArgument().value;

      std::cout << "handleCall(OnlyArgumentCall) (arg.value = " << val << ")" << std::endl;
      if (val >= 0)
      {
         std::cout << "handleCall(OnlyArgumentCall) process result" << std::endl;
         setValue(val);
         call.sendResult();
      }
      else
      {
         std::cout << "handleCall(OnlyArgumentCall) process error" << std::endl;
         call.sendError();
      }
   };

   //� ������ ���� � ��� ��������� ��� FormalOperationCall<Arg, Res>, �� � ����� ���������
   //������, �� ������ ������� �������� ����������. � ������ ������������� ������ ��� ����� 
   //������ ��� ���� ������, ��� ��������
   typedef brownie::asynch::FormalOperationCall<CallArgument, CallResult> ArgumentAndResultCall;

   void handleCall(ArgumentAndResultCall& call)
   {
      const int val = call.getArgument().value;

      std::cout << "ArgumentAndResultCall (arg.value = " << val << ")" << std::endl;
      if (val >= 0)
      {
         std::cout << "handleCall(ArgumentAndResultCall) process result" << std::endl;
         call.result().value = mValue;
         setValue(val);
         call.sendResult();
      }
      else
      {
         std::cout << "handleCall(ArgumentAndResultCall) process error" << std::endl;
         call.sendError();
      }
   };

   //� ������ ���� � ��� ��������� ��� FormalOperationCall<Arg, Res, Err>, �� � ����� ���������
   //������, �� ������ ������� �� ������ �������� ���������� �� � �������� ������ � ������ �� �������������.
   typedef brownie::asynch::FormalOperationCall<CallArgument, CallResult, CallError> ArgumentResultAndErrorCall;

   void handleCall(ArgumentResultAndErrorCall& call)
   {
      const int val = call.getArgument().value;

      std::cout << "ArgumentResultAndErrorCall (arg.value = " << val << ")" << std::endl;
      if (val >= 0)
      {
         std::cout << "handleCall(ArgumentResultAndErrorCall) process result" << std::endl;
         call.result().value = mValue;
         setValue(val);
         call.sendResult();
      }
      else
      {
         std::cout << "handleCall(ArgumentResultAndErrorCall) process error" << std::endl;
         call.error().value = val;
         call.sendError();
      }
   };

private:
   void setValue(int val)
   {
      int oldVal = mValue;
      mValue = val;
      std::cout << "CSimpleCallCallable::mValue {old value = " << oldVal << ", new value = " << mValue << " }" << std::endl;
   }
   int mValue;
};

/***********************************************************************************/

class CSimpleCallCallback: public brownie::asynch::LocalCallback<CSimpleCallCallback> 
{
public:
   CSimpleCallCallback(CSimpleCallCallable& callable)
   : mCallable(callable)
   {
      mData.value = 1;
   };

   struct CallData
   {
      CallData() : value(0) 
      {
         std::cout << "CallData: Default constructor" << std::endl;
      };
      CallData(const CallData& val)
      {
         value = val.value;
         std::cout << "CallData: Copy constructor" << std::endl;
      };
      int value;
   };

   //����� ������� ����������� �����, ���������� ������ ��������
   typedef ConcreteOperationCall<CSimpleCallCallable::OnlyArgumentCall> MyCallWithArgument;
   
   void onResult(MyCallWithArgument& call)
   {
      std::cout << "onResult(MyCallWithArgument&)" << std::endl;
   }
   
   void onError(MyCallWithArgument& call)
   {
      std::cout << "onError(MyCallWithArgument&)" << std::endl;
   }

   void DoCallWithArgument(int value)
   {
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "Example DoCallWithArgument v.1" << std::endl;
      MyCallWithArgument *pCall;
      if (createCall(pCall)) 
      {
         pCall->argument().value = value;
         pCall->sendTo(mCallable);
      }
   };

   void DoCallWithArgument(CSimpleCallCallable::CallArgument& arg)
   {
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "Example DoCallWithArgument v.2" << std::endl;
      MyCallWithArgument *pCall;
      if (createCallArg(pCall, arg)) 
      {
         pCall->sendTo(mCallable);
      }
   };

   //�������� Data � ������� ConcreteOperationCall ��������� ��� ��������� �����-�� ���������
   //� �� �����, ��� �� ������ ������������ �����.
   typedef ConcreteOperationCall<CSimpleCallCallable::OnlyArgumentCall, CallData> MyCallWithArgumentAndData;
   
   void onResult(MyCallWithArgumentAndData& call)
   {
      std::cout << "onResult(MyCallWithArgumentAndData&)" << std::endl;
      std::cout << "Data value = " << call.data().value << std::endl;
   }
   
   void onError(MyCallWithArgumentAndData& call)
   {
      std::cout << "onError(MyCallWithArgumentAndData&)" << std::endl;
      std::cout << "Data value = " << call.data().value << std::endl;
   }

   void DoCallWithArgumentAndData(int value, int data)
   {
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "Example DoCallWithArgumentAndData v.1" << std::endl;
      MyCallWithArgumentAndData *pCall;
      if (createCall(pCall)) 
      {
         pCall->data().value = data;
         pCall->argument().value = value;
         pCall->sendTo(mCallable);
      }
   };

   void DoCallWithArgumentAndData(int value)
   {
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "Example DoCallWithArgumentAndData v.2" << std::endl;
      MyCallWithArgumentAndData *pCall;
      if (createCallData(pCall, mData)) 
      {
         pCall->argument().value = value;
         pCall->sendTo(mCallable);
      }
   };

   void DoCallWithArgumentAndData(CSimpleCallCallable::CallArgument& arg, int data)
   {
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "Example DoCallWithArgumentAndData v.3" << std::endl;
      MyCallWithArgumentAndData *pCall;
      if (createCallArg(pCall, arg)) 
      {
         pCall->data().value = data;
         pCall->sendTo(mCallable);
      }
   };

   void DoCallWithArgumentAndData(CSimpleCallCallable::CallArgument& arg)
   {
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "Example DoCallWithArgumentAndData v.4" << std::endl;
      MyCallWithArgumentAndData *pCall;
      if (createCallArgData(pCall, arg, mData)) 
      {
         pCall->sendTo(mCallable);
      }
   };

   //������ ������������� ������ � ��������� ��������
   typedef ConcreteOperationCall<CSimpleCallCallable::ArgumentAndResultCall> MyCallWithArgumentAndResult;
   
   void onResult(MyCallWithArgumentAndResult& call)
   {
      std::cout << "onResult(MyCallWithArgumentAndResult&)" << std::endl;
      std::cout << "Result value = " << call.getResult().value << std::endl;
   }
   
   void onError(MyCallWithArgumentAndResult& call)
   {
      std::cout << "onError(MyCallWithArgumentAndResult&)" << std::endl;
   }

   void DoCallWithArgumentAndResult(int value)
   {
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "Example DoCallWithArgumentAndResult" << std::endl;
      MyCallWithArgumentAndResult *pCall;
      if (createCall(pCall)) 
      {
         pCall->argument().value = value;
         pCall->sendTo(mCallable);
      }
   };

   //������ ������������� ������ � ��������� �������� ���������� � ������
   typedef ConcreteOperationCall<CSimpleCallCallable::ArgumentResultAndErrorCall> MyCallWithArgumentResultAndError;
   
   void onResult(MyCallWithArgumentResultAndError& call)
   {
      std::cout << "onResult(MyCallWithArgumentAndResult&)" << std::endl;
      std::cout << "Result value = " << call.getResult().value << std::endl;
   }
   
   void onError(MyCallWithArgumentResultAndError& call)
   {
      std::cout << "onError(MyCallWithArgumentAndResult&)" << std::endl;
      std::cout << "Error value = " << call.getError().value << std::endl;
   }

   void DoCallWithArgumentResultAndError(int value)
   {
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "Example DoCallWithArgumentResultAndError" << std::endl;
      MyCallWithArgumentResultAndError *pCall;
      if (createCall(pCall)) 
      {
         pCall->argument().value = value;
         pCall->sendTo(mCallable);
      }
   };

private:
   CSimpleCallCallable& mCallable;
   CallData mData;
};

}
}
}

#endif //brownie_asynch_test_simplecall