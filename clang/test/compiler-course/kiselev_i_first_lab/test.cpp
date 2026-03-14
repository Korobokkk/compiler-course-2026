// RUN: %clang_cc1 -load %llvmshlibdir/kiselev_i_first_lab_ClangAST%pluginext -plugin override_check -fsyntax-only %s 2>&1 | FileCheck %s

class Base1 { 
public:
  virtual void foo();
};

class Derived1 : public Base1 {
public:
  void foo() {}
};

// CHECK: CXXMethodDecl {{.*}} foo 'void ()'
// CHECK: CompoundStmt

class Base2 { //good case
public:
  virtual void foo();
};

class Derived2 : public Base2 {
public:
  void foo() override {}
};

// CHECK-NOT: foo 'void ()'

class A1 { // override with param
public:
  virtual int sum(int a, int b);
};

class B1 : public A1 {
public:
  int sum(int a, int b) { return a + b; }
};

// CHECK: CXXMethodDecl {{.*}} sum 'int (int, int)'
// CHECK: ParmVarDecl {{.*}} a 'int'
// CHECK: ParmVarDecl {{.*}} b 'int'
// CHECK: CompoundStmt

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

// CHECK: CXXMethodDecl {{.*}} foo 'void ()'
// CHECK: CXXMethodDecl {{.*}} foo 'void ()'

class L1 { // intermediate class case
public:
  virtual void f();
};

class L2 : public L1 {};

class L3 : public L2 {
public:
  void f() {}
};

// CHECK: CXXMethodDecl {{.*}} f 'void ()'

class A { //several subclass
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

// CHECK: CXXMethodDecl {{.*}} f 'void ()'
// CHECK: CXXMethodDecl {{.*}} g 'void ()'

class Abstract {
public:
  virtual void run() = 0;
};

class Impl : public Abstract {
public:
  void run() {}
};

// CHECK: CXXMethodDecl {{.*}} run 'void ()'