// RUN: %clang_cc1 -load %llvmshlibdir/kiselev_i_first_lab_ClangAST%pluginext -plugin override_check -fsyntax-only %s 2>&1 | FileCheck %s

class Base1 { 
public:
  virtual void foo();
};

class Derived1 : public Base1 {
public:
  void foo() {}
};

// CHECK: {{.*}}warning: method 'foo' overrides base method but is not marked 'override'

class Base2 { // good case
public:
  virtual void foo();
};

class Derived2 : public Base2 {
public:
  void foo() override {}
};

// CHECK-NOT: warning: method 'foo' overrides base method but is not marked 'override'

class A1 { // override with param
public:
  virtual int sum(int a, int b);
};

class B1 : public A1 {
public:
  int sum(int a, int b) { return a + b; }
};

// CHECK: {{.*}}warning: method 'sum' overrides base method but is not marked 'override'

class A2 { // multiple inheritances
public:
  virtual void foo();
};

class B2 : public A2 {
public:
  void foo() {}
};

class C2 : public B2 {
public:
  void foo() {}
};

// CHECK: {{.*}}warning: method 'foo' overrides base method but is not marked 'override'
// CHECK: {{.*}}warning: method 'foo' overrides base method but is not marked 'override'

class L1 { // intermediate class case
public:
  virtual void f();
};

class L2 : public L1 {};

class L3 : public L2 {
public:
  void f() {}
};

// CHECK: {{.*}}warning: method 'f' overrides base method but is not marked 'override'

class A { // several subclass
public:
  virtual void f();
};

class B {
public:
  virtual void g();
};

class C : public A, public B {
public:
  void f() {}
  void g() {}
};

// CHECK: {{.*}}warning: method 'f' overrides base method but is not marked 'override'
// CHECK: {{.*}}warning: method 'g' overrides base method but is not marked 'override'

class Abstract {
public:
  virtual void run() = 0;
};

class Impl : public Abstract {
public:
  void run() {}
};

// CHECK: {{.*}}warning: method 'run' overrides base method but is not marked 'override'