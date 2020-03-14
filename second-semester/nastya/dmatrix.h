//---------------------------------------------------------------------------

#ifndef mymatrixH
#define mymatrixH

#include <StdCtrls.hpp>  
              


//---------------------------------------------------------------------------

// ЕСЛИ СЧИТАЕМ МАТРИЦУ СТАТИЧЕСКОЙ, ПРИ ЕЕ ОПРЕДЕЛЕНИИ ПИШЕМ:  op2.k = op2.m; op2.M = op2.m      !!!!!

class DMatrix
{

public:

  int M;                 // Максимальный номер строки (+ 1)
  int k;                 // Текущий номер последней строки (+ 1)
  int m;                 // THE NUMBER OF ROWS
  int n;                 // THE NUMBER OF COLUMNS
  long double **data;
  bool   oblom;          // Признак аварийного результата выполнения оператора

  int    Thr;            // !!! В этой версии класса задавать эту переменную надо обязательно !!!
                         // Она служит для разделения матриц temp и E для разных нитей.

  TListBox *ListBox11;
                                           
  void        __fastcall      Ini(int m0, int n0, int M0 = 0, int k0 = 0);
  void        __fastcall      de_allocate(void);
  void        __fastcall      Allocate(int k0);
  void        __fastcall      Delete(int k0);
  void        __fastcall      display(void);
  long double __fastcall      det(bool inversion);  // inversion - признак того, что дальше будем считать обратную матрицу методом Гаусса-Жордана
                                                    // Вызывается только из Inverse(), после чего в Inverse() происходит чистка матрицы E
  long double __fastcall      det(void);
  DMatrix     __fastcall      T(void);
  DMatrix     __fastcall      Inverse(void);

                                                             

  DMatrix();            // Конструктор


  DMatrix operator=(DMatrix op2);
  DMatrix operator+(DMatrix op2);         // Сложение матриц
  DMatrix operator*(DMatrix op2);         // Умножение матриц
  DMatrix operator*(long double op2);     // Умножение матрицы на число (справа!)

};
                                      
//---------------------------------------------------------------------------

class LSM
{  

public:

  DMatrix    A_buf, b_buf, Stolbets, Matritsa1, Matritsa2;
  int        frstLSM;

  // МНК для уравнения Ax = b с коэффициентом забывания W2.
  // Толщина block указывает, сколько последних строк надо использовать
  // Преобразует текущую СЛАУ в МНК
  bool        __fastcall      Ini(int rows, int cols, int thr = 0);    // thr служит для разделения матриц temp и E для разных нитей.
  void        __fastcall      Go(DMatrix *A, DMatrix *b, double W2);
  void        __fastcall      Del(void);
};

//---------------------------------------------------------------------------

class PROJECTION
{  

public:

  DMatrix       X, C, A, Z, BS, Matritsa, Stroka, Stolbets, Chislo;
  long double   y, dy, Z2, dbuf;
  int           SMAX, k, S;
  int           Superior, AIsE;


  bool          __fastcall      Ini0(int cols, int thr = 0);     // thr служит для разделения матриц temp и E для разных нитей.
  void          __fastcall      Ini1(void);
  int           __fastcall      Go(DMatrix *X0, DMatrix *Y0, int SMAX, double Z2F);
  void          __fastcall      Del(void);
};

//---------------------------------------------------------------------------

#endif
