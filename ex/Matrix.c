// Matrix.c -- matrix of type double

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Matrix.c,v 3.0 90/05/15 22:43:51 kgorlen Rel $

/*
Author:
    S. M. Orlow
    Systex, Inc.
    Beltsville, MD 20705
    301-474-0111
    sandy@alw.nih.gov
*/

#include <libc.h>
#include <iostream.h>

#include "Matrix.h"

void Matrix::sizeError(char* where,const Matrix& m,int a, int b)
{
    cerr << where << ": " 
         << m.nRow() << "x" << m.nCol() << " Matrix expected, "
         << a << "x" << b << " found" << endl;
    abort();
}
void Matrix::v_alloc(int a, int b)
{
    nrow = a; ncol = b;
#ifdef TRACE
cerr << "v_alloc: nrow=" << nrow << " ncol=" << ncol << endl;
#endif
    _v = new double[a*b];
}
Matrix::Matrix(int nr,int nc,double* f)
{
    v_alloc(nr,nc);

    int i,j;
        if ( f==0 ) { // initilize 0 matrix
      for (i=0; i<nrow; i++)
        for (j=0; j<ncol; j++)
          at(i,j) = 0;
      }
   else if ( nrow==1 ) { // initialize row
      for (j=0; j<ncol; j++) at(0,j) = f[j];
      }
   else if ( ncol==1 ) { // initialize column
      for (i=0; i<nrow; i++) at(i,0) = f[i];
      }
         else { // initialize matrix
      for (i=0; i<nrow; i++)
        for (j=0; j<ncol; j++)
          at(i,j) = f[i*ncol+j];
      }      
}
Matrix::Matrix(const Matrix& m)
{
    v_alloc(m.nrow,m.ncol);
    *this = m;
}
Matrix::Matrix(const MatrixRow& v)
{
    v_alloc(1,v.nCol());
    for (int j=0; j<ncol; j++) at(0,j) = v.at(j);
}
Matrix::Matrix(const MatrixCol& v)
{
    v_alloc(v.nRow(),1);
    for (int i=0; i<nrow; i++) at(i,0) = v.at(i);
}
Matrix::Matrix(int k, double* f)
{
    v_alloc(k,k);
    for (int i=0; i<nrow; i++)
      for (int j=0; j<ncol; j++)
        at(i,j) = (i==j)? f[i]:0;
}
Matrix::Matrix(int k, diagonal f)
{
    v_alloc(k,k);
    for (int i=0; i<nrow; i++)
      for (int j=0; j<ncol; j++)
        at(i,j) = (i==j)? (double)f:0;
}
Matrix::~Matrix()
{
    delete _v;
}

double& Matrix::operator()(int irow, int icol) const
{
    if ( irow<0||irow>=nrow||icol<0||icol>=ncol ) {
      cerr << "at: [" 
           << irow << "," << icol
           << "] out of range [" 
           << nrow << "," << ncol 
           << "]" << endl;
      abort();
      }
    return at(irow,icol);
}
MatrixRow Matrix::row(int k) const
{
    return MatrixRow(k,*this);
}
MatrixRow Matrix::row(int k,const MatrixRow& v) const
{
    for ( int i=0; i<ncol; i++ )
      at(k,i) = v.at(i);
    return v;
}
MatrixCol Matrix::col(int k) const
{
    return MatrixCol(k,*this);
}
MatrixCol Matrix::col(int k,const MatrixCol& v) const
{
    for ( int i=0; i<nrow; i++ )
      at(i,k) = v.at(i);
    return v;
}

void Matrix::operator=(const Matrix& m)
{
    if ( ! sameSize(m.nrow,m.ncol) ) 
          Matrix::sizeError("operator=",*this,m.nrow,m.ncol);
    for (int i=0; i<nrow; i++)
      for (int j=0; j<ncol; j++)
        at(i,j) = m.at(i,j);
}
int Matrix::operator==(const Matrix& m) const
{
    if ( ! sameSize(m.nrow,m.ncol) ) return 0;
    for (int i=0; i<nrow; i++)
      for (int j=0; j<ncol; j++)
        if ( at(i,j)!= m.at(i,j) ) return 0;
    return 1;
}

Matrix operator+(const Matrix& m,const Matrix& n)
{
    if ( ! m.sameSize(n.nRow(),n.nCol()) ) 
       Matrix::sizeError("operator+",m,n.nRow(),n.nCol());
// C++2.0 bug
//    Matrix rm(m.nRow(),m.nCol());
    int nr = m.nRow(), nc =m.nCol();
    Matrix rm(nr,nc);
    for (int i=0; i<m.nRow(); i++)
      for (int j=0; j<m.nCol(); j++)
        rm.at(i,j) = m.at(i,j)+n.at(i,j);
    return rm;
}
Matrix operator-(const Matrix& m,const Matrix& n)
{
    if ( ! m.sameSize(n.nRow(),n.nCol()) ) 
      Matrix::sizeError("operator-",m,n.nRow(),n.nCol());
// C++2.0 bug
//    Matrix rm(m.nRow(),m.nCol());
    int nr = m.nRow(), nc =m.nCol();
    Matrix rm(nr,nc);
    for (int i=0; i<m.nRow(); i++)
      for (int j=0; j<m.nCol(); j++)
        rm.at(i,j) = m.at(i,j)-n.at(i,j);
    return rm;
}
Matrix operator-(const Matrix& m)
{
// C++2.0 bug
//    Matrix rm(m.nRow(),m.nCol());
    int nr = m.nRow(), nc =m.nCol();
    Matrix rm(nr,nc);
    for (int i=0; i<m.nRow(); i++)
      for (int j=0; j<m.nCol(); j++)
        rm.at(i,j) = -m.at(i,j);
    return rm;
}
double det(const Matrix& m)
{
    if (m.nRow()!=m.nCol()) {
      cerr << "det: not a square matrix" << endl;;
      abort();
      }
    if (m.nRow()==1) return m.at(0,0);
    if (m.nRow()==2)
      return m.at(0,0)*m.at(1,1)-m.at(0,1)*m.at(1,0);
    if (m.nRow()==3) 
      return (  m.at(0,0)*m.at(1,1)*m.at(2,2)
                   -m.at(0,1)*m.at(1,2)*m.at(2,0)
                   +m.at(0,2)*m.at(2,1)*m.at(0,1) );
    if ( m.isUpperTriangle() ) {
       double val = 1;
       for (int i=0;i<m.nRow(); i++) val *=m.at(i,i);
       return val;
       }
    double val = 0;
    int sign = 1;
    for(int j=0; j<m.nCol(); j++) {
      val += sign*m.at(0,j)*det(m.coFactor(0,j));
      sign *= -1;
      }
    return val;
}
double norm(const Matrix& m)
{
    double val =0;
    for(int i=0; i<m.nRow(); i++)
      for(int j=0; j<m.nCol(); j++)
        if ( m.at(i,j)>val ) val = m.at(i,j);
    return val;
}
Matrix operator*(const Matrix& m,const Matrix& n)
{
    if ( m.nCol()!=n.nRow() ) {
         cerr << "operator*: " << m.nCol() <<
           "x* Matrix expected " 
           << n.nRow() << "x* found." << endl;
         abort();
       }
// C++2.0 bug
//    Matrix rm(m.nRow(),n.nCol());
    int nr = m.nRow(), nc =n.nCol();
    Matrix rm(nr,nc);
    for (int i=0; i<rm.nRow(); i++)
      for (int j=0; j<rm.nCol(); j++)
        rm.at(i,j) = m.row(i)^n.col(j);
    return rm;
}
Matrix operator&(const Matrix& m, const Matrix& n)
{
    if ( m.nRow()!=n.nRow() ) {
       cerr << "operator&: " << m.nRow() << " rows expected, "
        << n.nRow() << " found" << endl;
       abort();
       }
// C++2.0 bug
//    Matrix rm(m.nRow(),m.nCol()+n.nCol());
    int nr = m.nRow(), nc =m.nCol()+n.nCol();
    Matrix rm(nr,nc);
    for (int i=0; i<m.nCol(); i++ )
       rm.col(i,m.col(i));
    for (int j=0; j<n.nCol(); j++ )
       rm.col(m.nCol()+j,n.col(j));
    return rm;      
}
Matrix Matrix::t() const
{
    Matrix rm(ncol,nrow);
    for (int i=0; i<rm.nrow; i++)
      for (int j=0; j<rm.ncol; j++)
        rm.at(i,j) = at(j,i);
    return rm;
}

Matrix operator*(double f,const Matrix& m)
{
// C++2.0 bug
//    Matrix rm(m.nRow(),m.nCol());
    int nr = m.nRow(), nc =m.nCol();
    Matrix rm(nr,nc);
    for (int i=0; i<rm.nRow(); i++)
      for (int j=0; j<rm.nCol(); j++)
        rm.at(i,j) = f*m.at(i,j);
    return rm;
}
void Matrix::operator*=(double f)
{
    for (int i=0; i<nrow; i++)
      for (int j=0; j<ncol; j++)
        at(i,j) *= f;
}
void Matrix::switchRows(int i,int j)
{
    Matrix tmp(row(i));
    row(i,row(j));
    row(j,tmp.row(0));    
}
void Matrix::combineRows(int i, double a, int j)
{
    for(int h=0; h<ncol; h++)
      at(i,h) = at(i,h) + a*at(j,h);
}

int Matrix::isUpperTriangle() const
{
    for(int j=0; j<ncol; j++)
       for(int i=j+1; i<nrow; i++)
         if ( at(i,j)!=0 ) return 0;
    return 1;
}

Matrix Matrix::upperTriangle()
{
    Matrix I(nrow,(diagonal)1);

    if ( this->isUpperTriangle() ) return I;

    for(int j=0; j<ncol; j++) {
       int b_row = nrow-1;  // 1st non-zero entry from bottom
       int t_row = j;       // 1st zero entry from the top

       // switch rows until all zeros are at
       // the bottom of jTH column 
       while ( b_row>=t_row ) { 
         while (b_row>j&&at(b_row,j)==0) --b_row;
         if ( b_row==j ) break; // bottom at diagonal
         while (b_row>=t_row&&at(t_row,j)!=0) ++t_row;
         if ( t_row==nRow() ) break; // top at last row
#ifdef TRACE
cerr << "switchRows(" << b_row << "," << t_row << ")" << endl;
#endif
         switchRows(b_row,t_row); 
         I.switchRows(b_row,t_row);
         }
/*
       // put maximum entry on the diagonal in jTH column
       for(int h=0; h<j; h++)
         if (at(h,j) > at(j,j)) {
           switchRows(h,j); 
           I.switchRows(h,j);
           }        
*/
       // now b_row is last non-zero entry from the top
       // now t_row is first zero entry from the bottom
       // combine until all entries below diagonal in jTH column =)
       if ( b_row<=j ) continue;
       for(int i=j+1; i<=b_row; i++) {
          double f = -at(i,j)/at(j,j);
#ifdef TRACE
cerr << "combineRows(" << i << "," << f << "," << j << ")" << endl;
#endif
          combineRows(i,f,j);
               I.combineRows(i,f,j);
          }
       }
    return I;
}
Matrix Matrix::coFactor(int irow, int jcol) const
{
    if ( irow==1||jcol==1 ) {
      cerr << "coFactor: can't coFactor row or column matrix" <<
        endl;
      abort();
      }
    Matrix val(nrow-1,ncol-1);
    int getcol, getrow =0;
    for(int i=0; i<val.nRow(); i++) {
      if ( getrow==irow ) ++getrow;
      if ( getrow==nrow ) break;
      getcol = 0;
      for(int j=0; j<val.nCol(); j++) {
        if ( getcol==jcol ) ++getcol;
        if ( getcol==ncol ) continue;
        val.at(i,j) = at(getrow,getcol);
        ++getcol;
        }
      ++getrow;
      }
    return val;
}
Matrix Matrix::coFactor(int irow, int jcol,Matrix& m) const
{
    if ( irow==1||jcol==1 ) {
      cerr << "coFactor: can't coFactor row or column matrix" <<
        endl;
      abort();
      }
    if ( m.nRow()!=nrow-1||m.nCol()!=ncol-1 ) {
      cerr << "coFactor: argument is wrong size" << endl;
      abort();
      } 
    Matrix val = coFactor(irow,jcol);
    int putcol, putrow =0;
    for(int i=0; i<m.nRow(); i++) {
      if ( putrow==irow ) ++putrow;
      if ( putrow==nrow ) break;
      putcol = 0;
      for(int j=0; j<m.nCol(); j++) {
        if ( putcol==jcol ) ++putcol;
        if ( putcol==ncol ) continue;
        at(putrow,putcol) = m.at(i,j);
        ++putcol;
        }
      ++putrow;
      }
    return val;
}
Matrix Matrix::operator~() const
// 1. triangulate: *this = ~P*T
// 2. when T isUpperTriangle ~T isUpperTriangle
// 3. split: T = T.row(0) + subT
// 4. I = ~T*T
// 5. ~T.at(0,0) = 1/T.at(0,0)
// 6. sub~T = ~(subT)
// 7. ~T.row(0) = [1/T.at(0,0)]&B
//    where T.at(0,0)*B = [t21 ... t2n]*~subT
// 8. ~*this = ~T*P
{
    if ( nrow!=ncol ) {
       cerr << "operator~: can't invert a non-square matrix" <<
         endl;
       abort();
       }
    if ( nrow==1 ) {
       Matrix T(1,1);
       T.at(0,0) = 1/at(0,0);
       return T;
       }
    Matrix T(*this);
// 1. triangulate: *this = ~P*T
    Matrix P(nrow,ncol);
    P = T.upperTriangle();
    if ( det(T)==0 ) {
      cerr << "operator~: can't invert singular matrix" << endl;
      abort();
      }      

// 2. when T isUpperTriangle ~T isUpperTriangle
// 3. split: T = T.row(0) + subT
    Matrix& r = *new Matrix(1,ncol-1,&(T.at(0,1)));
    Matrix& _subT = *new Matrix(~(T.coFactor(0,0)));
    Matrix& B = *new Matrix(-(1/T.at(0,0))*r*_subT);
    Matrix& val = *new Matrix(nrow,ncol);
    val.at(0,0) = 1/T.at(0,0);
    for(int i=1; i<ncol; i++) val.at(0,i)=B.at(0,i-1);
    val.coFactor(0,0,_subT);
    return val*P; // P is now the row-reduction transformation    
}
void Matrix::printOn(ostream& strm) const
{
    for(int i=0; i<nrow; i++ )
       strm << row(i) << endl;
}
void Matrix::dumpOn(ostream& strm) const
{
    strm << "Matrix[" << nrow << " " << ncol << endl;
    printOn(strm);
    strm << "]" << endl;
}
MatrixRow::MatrixRow(const MatrixRow& r)
{
    pm = r.pm;
    _row = r._row;
}
MatrixRow::MatrixRow(int k,const Matrix& m)
{
    pm = (Matrix*)&m;
    _row = k;
}
double MatrixRow::operator^(const MatrixCol& c) const
{
    if ( nCol()!=c.nRow() ) {
       cerr << "operator^: 1x" << nCol()
        << " mismatched with " << c.nRow() 
        << "x1." << endl;
       abort();
       }   
    double val = 0;
    for (int i=0; i< nCol(); i++ )
      val += at(i)*c.at(i);
    return val;    
}
void MatrixRow::operator=(const MatrixRow& r)
{
    if ( nCol()!=r.nCol() ) {
      cerr << "operator=: MatrixRow of size " << nCol()
           << " expected, size " << r.nCol() << " found." << endl,
      abort();
      }
    pm = r.pm;
    _row = r._row;
}
void MatrixRow::printOn(ostream& strm) const
{
    strm << "[ ";
    for( int i=0; i<nCol(); i++ )
      strm << at(i) << " ";
    strm << "]";
}
MatrixCol::MatrixCol(const MatrixCol& c)
{
    pm = c.pm;
    _col = c._col;
}
MatrixCol::MatrixCol(int k, const Matrix& m)
{
    pm = (Matrix*)&m;
    _col = k;
}
void MatrixCol::operator=(const MatrixCol& c)
{
    if ( nRow()!=c.nRow() ) {
      cerr << "operator=: MatrixCol of size " 
           << nRow() << " expected, size " 
           << c.nRow() << " found." << endl;
      abort();
      }
    pm = c.pm;
    _col = c._col;
}
void MatrixCol::operator+=(const MatrixCol& c)
{
    for(int i=0; i<nRow(); i++ )
      at(i) += c.at(i);
}
void MatrixCol::printOn(ostream& strm) const
{
    strm << "t[ ";
    for( int i=0; i<nRow(); i++ )
      strm << at(i) << " ";
    strm << "]";
}

ostream& operator<<(ostream& strm,const Matrix& m)
{
    m.printOn(strm);
    return strm;
}
ostream& operator<<(ostream& strm,const MatrixRow& m)
{
    m.printOn(strm);
    return strm;
}
ostream& operator<<(ostream& strm,const MatrixCol& m)
{
    m.printOn(strm);
    return strm;
}
