class LockInheritance
{
   friend class Base;
   private:
      LockInheritance(){}
};

/*
 constructors for virtual base classes anywhere in your class's inheritance hierarchy are called by the "most derived" class's constructor.
Если в цепочке родителей есть виртуальное наследование, то наследник должен иметь прямой доступ к конструктору данного класса
*/

class Base : public virtual  LockInheritance
{
   public:
      Base(){}
      ~Base(){}
};

class Derived : public Base
{
public:
   // created by default 
   // Derived() {};
   
};

int main()
{
   Base base; // OK
//   Derived derived; // Not OK
}
