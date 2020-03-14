//---------------------------------------------------------------------------


#pragma hdrstop

#include <vcl.h>

#include "dmatrix.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

DMatrix temp[10], E[10];    // ������ ���������� ����������

//--------------------------------------------------------------------------- 

DMatrix::DMatrix()
{
  data = NULL;           // �� ���������� � ������� ����������
}

//---------------------------------------------------------------------------

DMatrix DMatrix::operator+(DMatrix op2)
{
  int i, j;                                     // op2 - ������ �������; ������ ������� ����� - this,
                                                // n, k, m - ����� ����� ������� (� �������� ����������)

  if(n!=op2.n || m!=op2.m)
  {
    Application->MessageBox("��������� ������������ ������ �� ���������!","",MB_OK);
    oblom = true;
    return *this;     // ���������� ������ �������, �� ���� ������ �� ������
  }


  temp[Thr].data = NULL;
  temp[Thr].data = new long double*[m];
                                               
  for (j = 0; j < m; j++)
  {
    temp[Thr].data[j] = new long double[n];
  }
  temp[Thr].n = n; temp[Thr].m = m; temp[Thr].k = temp[Thr].m;


  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
    {
      temp[Thr].data[i][j] = data[i+k-m][j] + op2.data[i + op2.k-op2.m][j];
    }


  return temp[Thr];
}

//------------------------------------------------------------------------------

DMatrix DMatrix::operator*(DMatrix op2)
{
  int i, j, s;
  long double x;


  if(n!=op2.m)
  {
    Application->MessageBox("   ����� �������� ������ ���������\n\n �� ���������\n\n � ������ ����� ������� ���������!","",MB_OK);
    oblom = true;
    return *this;     // ���������� ������ �������, �� ���� ������ �� ������
  }

  
  temp[Thr].data = NULL;
  temp[Thr].data = new long double*[m];
                                               
  for (j = 0; j < m; j++)
  {
    temp[Thr].data[j] = new long double[op2.n];    // �������� - ������� ��, ������� � ������� ��������
  }
  temp[Thr].m = m;                            // ����� - ������� ��, ������� � ������� ��������
  temp[Thr].n = op2.n;                        // �������� - ������� ��, ������� � ������� ��������
  temp[Thr].k = temp[Thr].m;


  for (i = 0; i < m; i++)                       // ���� �� ������� ������ �������
    for (j = 0; j < op2.n; j++)                 // ���� �� �������� ������ �������
    {
      x = 0;
      for (s = 0; s < n; s++)                   // �������� ������ �� �������
      {
        x = x + (data[i+k-m][s] * op2.data[s+op2.k-op2.m][j]);
      }
      temp[Thr].data[i][j] = x;
    }


  return temp[Thr];
}

//------------------------------------------------------------------------------

DMatrix DMatrix::operator*(long double op2)
{
  int i, j;


  temp[Thr].data = NULL;
  temp[Thr].data = new long double*[m];            // �������� ������ ��� temp[Thr].data
                                                
  for (j = 0; j < m; j++)
  {
    temp[Thr].data[j] = new long double[n]; 
  }
  temp[Thr].n = n; temp[Thr].m = m; temp[Thr].k = temp[Thr].m;


  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
    {
      temp[Thr].data[i][j] = data[i+k-m][j] * op2;
    }


  return temp[Thr];
}

//------------------------------------------------------------------------------  

DMatrix __fastcall DMatrix::T()
{
  int i, j;


  temp[Thr].data = NULL;
  temp[Thr].data = new long double*[n];
                                                
  for (j = 0; j < n; j++)
  {
    temp[Thr].data[j] = new long double[m];
  }     
  temp[Thr].m = n;  temp[Thr].n = m;  temp[Thr].k = temp[Thr].m;
  
                                                                                 
  for(i=0; i<temp[Thr].m; i++)
    for(j=0; j<temp[Thr].n; j++)
    {
      temp[Thr].data[i][j] = data[j+k-m][i];
    }

    
  return temp[Thr];
}    

//------------------------------------------------------------------------------  

long double __fastcall DMatrix::det()
{
  return det(false);
}

//------------------------------------------------------------------------------  

long double __fastcall DMatrix::det(bool inversion)       // ����� ������
{
  int           i1, i2, i3;
  bool          nl;
  long double   fraction, res;


  // m = n, ������� ����� m �� ����������!!!
  if(n != m)  { Application->MessageBox("������� - �� ����������!","",MB_OK);  oblom = true;  return 0; }


  temp[Thr].data = NULL;
  temp[Thr].data = new long double*[n];
  for (i1 = 0; i1 < n; i1++)
    temp[Thr].data[i1] = new long double[n];
  temp[Thr].n = n; temp[Thr].m = m; temp[Thr].k = temp[Thr].m;  
  for (i1 = 0; i1 < n; i1++)
    for (i2 = 0; i2 < n; i2++)
      temp[Thr].data[i1][i2] = data[i1 + k - n][i2];

  if(inversion)
  {
    E[Thr].data = NULL;
    E[Thr].data = new long double*[n];
    for (i1 = 0; i1 < n; i1++)
      E[Thr].data[i1] = new long double[n];
    E[Thr].n = n; E[Thr].m = m; E[Thr].k = E[Thr].m;
    for (i1 = 0; i1 < n; i1++)
      for (i2 = 0; i2 < n; i2++)
        {
          if(i1 == i2)  E[Thr].data[i1][i2] = 1;
          else          E[Thr].data[i1][i2] = 0;
        }
  }


  res = 1;
  for(i1 = 0; i1 < n - 1; i1++)       // ���� �� ��������� (�� �� �����)
  {
    if(temp[Thr].data[i1][i1] == 0)        // ��������� ������ ���� �� ���������
    {
      nl = true;
      for(i2 = i1 + 1; i2 < n; i2++)  // ������� ���� ������ � ��������� ��������� � ���� �������...
        if(temp[Thr].data[i2][i1] != 0)
        {
          for(i3 = 0; i3 < n; i3++)   // ...� ���������� ��� ������
          {
            temp[Thr].data[i1][i3] = temp[Thr].data[i1][i3] + temp[Thr].data[i2][i3];
            if(inversion)  E[Thr].data[i1][i3] = E[Thr].data[i1][i3] + E[Thr].data[i2][i3];
          }
          nl = false;
          break;
        }
      if(nl)
      {
        if(!inversion && temp[Thr].data)
        { temp[Thr].de_allocate();  temp[Thr].data = NULL; }  // ���� ������� ������, �.�. det() ���������� ����� � ���������� ��������� "=" �� ����������, � ������ �������� temp[Thr] ���������� ��� ����������
        return 0;
      }
    }

    res = res * temp[Thr].data[i1][i1];

    // ��������� � ������ ������� ��� ����������
    for(i2 = i1 + 1; i2 < n; i2++)    // ���� �� �������
    {
      fraction = temp[Thr].data[i2][i1] / temp[Thr].data[i1][i1];
      for(i3 = 0; i3 < n; i3++)       // ���� �� ��������
      {
        temp[Thr].data[i2][i3] = temp[Thr].data[i2][i3] - (fraction * temp[Thr].data[i1][i3]);
        if(inversion)  E[Thr].data[i2][i3] = E[Thr].data[i2][i3] - (fraction * E[Thr].data[i1][i3]);
      }
    }
  }

  res = res * temp[Thr].data[n - 1][n - 1];     // ��������� �� ��������� ������� ���������


  if(!inversion && temp[Thr].data)
  { temp[Thr].de_allocate();  temp[Thr].data = NULL; }  // ���� ������� ������, �.�. det() ���������� ����� � ���������� ��������� "=" �� ����������, � ������ �������� temp[Thr] ���������� ��� ����������
  return res;
}  

//------------------------------------------------------------------------------  

DMatrix __fastcall DMatrix::Inverse()    // ����� ������-������� (��. cleverstudents.ru/matrix/finding_the_inverse_matrix.html)
{                                          // !!! ������ ����, ��������� ��� ����������, �������� � det() !!!
  int           i1, i2, i3;
  long double   mult, dt;


  dt = det(true);
  if(oblom) return *this;     // ���������� �������� �������, �� ���� ������ �� ������
  if(dt == 0)
  {
    Application->MessageBox("������� - �����������!", "", MB_OK);
    oblom = true;
    if(E[Thr].data)     { E[Thr].de_allocate();  E[Thr].data = NULL; }
    return *this;     // ���������� �������� �������, �� ���� ������ �� ������
  }

  // ������ �� ��������� �������
  for(i1 = 0; i1 < n; i1++)        
  {
    mult = temp[Thr].data[i1][i1];
    for(i2 = 0; i2 < n; i2++)
    {
      temp[Thr].data[i1][i2] = temp[Thr].data[i1][i2] / mult;
      E[Thr].data[i1][i2] = E[Thr].data[i1][i2] / mult;
    }
  }

  // �������� ��� ���� ���������
  for(i1 = 1; i1 < n; i1++)            // ���� �� ���������
  {
    for(i2 = i1 - 1; i2 >= 0; i2--)    // ���� �� �������
    {
      mult = temp[Thr].data[i2][i1];
      for(i3 = 0; i3 < n; i3++)        // ���� �� ��������
      {
        temp[Thr].data[i2][i3] = temp[Thr].data[i2][i3] - (temp[Thr].data[i1][i3] * mult);
        E[Thr].data[i2][i3] = E[Thr].data[i2][i3] - (E[Thr].data[i1][i3] * mult);
      }
    }
  }


  // ���������� ������ � temp[Thr]
  for(i1 = 0; i1 < n; i1++)
    for(i2 = 0; i2 < n; i2++)
      temp[Thr].data[i1][i2] = E[Thr].data[i1][i2];

  if(E[Thr].data)     { E[Thr].de_allocate();  E[Thr].data = NULL; }
  return temp[Thr];
}

//------------------------------------------------------------------------------

DMatrix DMatrix::operator=(DMatrix op2)
{    
  int i, j;


  if(oblom || n!=op2.n || m!=op2.m)
  {
    if(n!=op2.n || m!=op2.m)  Application->MessageBox("��������� ������ �� ��������� (��� ����������)!","",MB_OK);
    oblom = true;
    if(temp[Thr].data)  { temp[Thr].de_allocate(); temp[Thr].data = NULL; }
    return *this;     // ���������� ������ �������, �� ���� ������ �� ������
  }


  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
    {
      data[i+k-m][j] = op2.data[i + op2.k-op2.m][j];  // ���������� ������ ������ ���������� �� "������" ����� ������ ������� � "�����" ���� �����
    }
                     

  if(temp[Thr].data)  { temp[Thr].de_allocate(); temp[Thr].data = NULL; }
  return *this;
}

//------------------------------------------------------------------------------

void __fastcall DMatrix::display()
{
String S;

  ListBox11->Items->Add("*****");

  for (int i = k-m; i < k; i++)
  {
    for (int j = 0; j < n; j++)
    {
      S = IntToStr(i) + "  /  " + IntToStr(j) + "  :  " + FloatToStr(data[i][j]);
      ListBox11->Items->Add(S);
    }
  }

  ListBox11->ItemIndex = ListBox11->Items->Count - 1;
}        

//------------------------------------------------------------------------------

void __fastcall  DMatrix::Ini(int m0, int n0, int M0, int k0)
{
int   i;


  Thr = 0;

  m = m0;
  n = n0;
  M = M0;
  k = k0;
  oblom = false;

  data = new long double*[M];

  for(i = 0; i < M; i++)    data[i] = NULL;

  for(i = 0; i < k; i++)    data[i] = new long double[n];
}

//------------------------------------------------------------------------------

void __fastcall  DMatrix::de_allocate()
{
  for (int i = k-m; i < k && k >= m; i++)       
    if(data[i])  { delete[] data[i];  data[i] = NULL; }       

  delete[] data;
  data = NULL;
}

//------------------------------------------------------------------------------

void __fastcall  DMatrix::Allocate(int k0)
{
  if(k0 < M)  data[k0] = new long double[n];    // �������� ������ ��� ������
  else  oblom = true;
}

//------------------------------------------------------------------------------

void __fastcall  DMatrix::Delete(int k0)
{
  if(k0 < M && data[k0])  { delete[] data[k0];  data[k0] = NULL; }   // ������� ������
  else  oblom = true;
}

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
//--------------------------------TOOLS-----------------------------------------
//------------------------------------------------------------------------------

//--------------------------------���-------------------------------------------

bool __fastcall  LSM::Ini(int rows, int cols, int thr)
{
int  i;


try
{ 
  A_buf.Ini(cols, cols, cols, cols);
  b_buf.Ini(cols, 1, cols, cols);
  Stolbets.Ini(cols, 1, cols, cols);           // ����� - �������
  Matritsa1.Ini(cols, rows, cols, cols);       // ����� - ������� (��� X.T())
  Matritsa2.Ini(cols, cols, cols, cols);       // ����� - ������� (����������)

  A_buf.Thr = thr;  b_buf.Thr = thr;  Stolbets.Thr = thr;  Matritsa1.Thr = thr;  Matritsa2.Thr = thr;
}
catch ( ... )
{
  Application->MessageBox("������ ��� �������������� ��������� ������ � iniLSM!","",MB_OK);
  return false;
}


frstLSM = 1;  
return true;
}

//------------------------------------------------------------------------------

void __fastcall  LSM::Go(DMatrix *A, DMatrix *b, double W2)
{
  Matritsa1 = A->T();

  Matritsa2 = Matritsa1 * (*A);
  Stolbets = Matritsa1 * (*b);

  if(frstLSM)  { A_buf = Matritsa2;  b_buf = Stolbets;  frstLSM = 0; }         
  else   // �� ���� ���� ��� ���� ������ A_buf
  {
    A_buf = A_buf * W2;
    A_buf = A_buf + Matritsa2;

    b_buf = b_buf * W2;
    b_buf = b_buf + Stolbets;
  }
}

//------------------------------------------------------------------------------    

void __fastcall  LSM::Del(void)
{
  A_buf.de_allocate();
  b_buf.de_allocate();
  Stolbets.de_allocate();
  Matritsa1.de_allocate();
  Matritsa2.de_allocate();
}

//------------------------------------------------------------------------------


//---------------------------������������ ��������------------------------------

bool __fastcall  PROJECTION::Ini0(int cols, int thr)
{
int  i;


k = 0;                         // ���

try
{   
  X.Ini(1, cols, 1, 1);       // ������ ������� ���������� �������
  C.Ini(1, cols, 1, 1);       // ������ ���������� ������
  for (i = 0; i < C.n; i++)      
    C.data[0][i] = i + 1;                 // ��������� �������� ������� C:   1, 2, 3, 4, 5, ...
  A.Ini(cols, cols, cols, cols);
  Z.Ini(cols, 1, cols, cols);
  BS.Ini(cols, 1, cols, cols);            // ������ ������������� ���������
  Matritsa.Ini(cols, cols, cols, cols);   // ����� - �������
  Stroka.Ini(1, cols, 1, 1);              // ����� - ������
  Stolbets.Ini(cols, 1, cols, cols);      // ����� - �������
  Chislo.Ini(1, 1, 1, 1);                 // ����� - ������

  X.Thr = thr;  C.Thr = thr;  A.Thr = thr;  Z.Thr = thr;  BS.Thr = thr;
  Matritsa.Thr = thr;  Stroka.Thr = thr;  Stolbets.Thr = thr;  Chislo.Thr = thr;
}
catch ( ... )
{
  Application->MessageBox("������ ��� �������������� ��������� ������ � iniProjection!","",MB_OK);
  return false;
}


AIsE = 0;
Superior = 1;
return true;
}

//------------------------------------------------------------------------------

void __fastcall PROJECTION::Ini1()
{
int i, j;


S = 1;                             // ������� ������� ������ 

for (i = 0; i < A.k; i++)          // ���������� ���������
{
  for (j = 0; j < A.n; j++)
  {
    if(i==j)  A.data[i][j] = 1;
    else      A.data[i][j] = 0;
  }
}
AIsE = 1;     // A - ���������


Superior = 0;
}

//------------------------------------------------------------------------------

int __fastcall  PROJECTION::Go(DMatrix *X0, DMatrix *Y0, int SMAX, double Z2F)
{
int   i;


  for(i = 0; i < X.n; i++)  X.data[0][i] = X0->data[X0->k - 1][i];
  y = Y0->data[Y0->k - 1][0];

  if(Superior)  Ini1();
  
  k++;


  if(AIsE)  Z = X.T();      // ��������� �������� �������
  {
    Stolbets = X.T();
    Z = A * Stolbets;
  }

  Stroka = Z.T();
  Chislo = Stroka * Z;
  if(Z.oblom || Stroka.oblom || Chislo.oblom)  { Application->MessageBox("������ ��� ��������� � ���������!", "", MB_OK);  return -1; }
  Z2 = Chislo.data[0][0];
  if(Z2<=Z2F)
  { Superior = 1;  return 0; }   // �� ��������� ���� ���������, �.�. Z2 ����� ���� ����� ��������� � ��������� - ������� � ����
                                       
  dbuf = 1 / Z2;
  BS = Z * dbuf;  


  Stolbets = C.T();
  Chislo = X * Stolbets;
  dy = y - Chislo.data[0][0];

  Stolbets = BS * dy;
  Stroka = Stolbets.T();
  C = C + Stroka;

  if(S == SMAX)
  { Superior = 1;  return 1; }


  Stroka = Z.T();
  Matritsa = BS * Stroka;
  Matritsa = Matritsa * (-1);
  A = A + Matritsa;
  AIsE = 0;


  S++;

  return 1;
}

//------------------------------------------------------------------------------    

void __fastcall  PROJECTION::Del(void)
{                 
  X.de_allocate();
  C.de_allocate();
  A.de_allocate();
  Z.de_allocate();
  BS.de_allocate();
  Matritsa.de_allocate();
  Stroka.de_allocate();
  Stolbets.de_allocate();
  Chislo.de_allocate();
}

//------------------------------------------------------------------------------
