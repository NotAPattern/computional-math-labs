//---------------------------------------------------------------------------

#ifndef mymatrixH
#define mymatrixH

#include <StdCtrls.hpp>  
              


//---------------------------------------------------------------------------

// ���� ������� ������� �����������, ��� �� ����������� �����:  op2.k = op2.m; op2.M = op2.m      !!!!!

class DMatrix
{

public:

  int M;                 // ������������ ����� ������ (+ 1)
  int k;                 // ������� ����� ��������� ������ (+ 1)
  int m;                 // THE NUMBER OF ROWS
  int n;                 // THE NUMBER OF COLUMNS
  long double **data;
  bool   oblom;          // ������� ���������� ���������� ���������� ���������

  int    Thr;            // !!! � ���� ������ ������ �������� ��� ���������� ���� ����������� !!!
                         // ��� ������ ��� ���������� ������ temp � E ��� ������ �����.

  TListBox *ListBox11;
                                           
  void        __fastcall      Ini(int m0, int n0, int M0 = 0, int k0 = 0);
  void        __fastcall      de_allocate(void);
  void        __fastcall      Allocate(int k0);
  void        __fastcall      Delete(int k0);
  void        __fastcall      display(void);
  long double __fastcall      det(bool inversion);  // inversion - ������� ����, ��� ������ ����� ������� �������� ������� ������� ������-�������
                                                    // ���������� ������ �� Inverse(), ����� ���� � Inverse() ���������� ������ ������� E
  long double __fastcall      det(void);
  DMatrix     __fastcall      T(void);
  DMatrix     __fastcall      Inverse(void);

                                                             

  DMatrix();            // �����������


  DMatrix operator=(DMatrix op2);
  DMatrix operator+(DMatrix op2);         // �������� ������
  DMatrix operator*(DMatrix op2);         // ��������� ������
  DMatrix operator*(long double op2);     // ��������� ������� �� ����� (������!)

};
                                      
//---------------------------------------------------------------------------

class LSM
{  

public:

  DMatrix    A_buf, b_buf, Stolbets, Matritsa1, Matritsa2;
  int        frstLSM;

  // ��� ��� ��������� Ax = b � ������������� ��������� W2.
  // ������� block ���������, ������� ��������� ����� ���� ������������
  // ����������� ������� ���� � ���
  bool        __fastcall      Ini(int rows, int cols, int thr = 0);    // thr ������ ��� ���������� ������ temp � E ��� ������ �����.
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


  bool          __fastcall      Ini0(int cols, int thr = 0);     // thr ������ ��� ���������� ������ temp � E ��� ������ �����.
  void          __fastcall      Ini1(void);
  int           __fastcall      Go(DMatrix *X0, DMatrix *Y0, int SMAX, double Z2F);
  void          __fastcall      Del(void);
};

//---------------------------------------------------------------------------

#endif
