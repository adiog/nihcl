#ifndef MatrixH
#define MatrixH

// Matrix.h -- matrix of type double

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Matrix.h,v 3.0 90/05/15 22:43:53 kgorlen Rel $

class ostream;
class MatrixCol;
class MatrixRow;

typedef double diagonal;

class Matrix {
protected:
    int nrow, ncol;

    double* _v;
    void v_alloc(int,int);
public:
    Matrix(int nr =1,int nc =1,double* =0);
    Matrix(const Matrix&);
    Matrix(const MatrixRow&);
    Matrix(const MatrixCol&);
    Matrix(int,double*);
    Matrix(int,diagonal);
    ~Matrix();

    double& at(int irow,int icol) const
      { return *(_v+irow*(ncol)+icol); }
//    double& at(int i) const { return at(i,i); }
    double& operator()(int irow,int icol) const;
    MatrixRow row(int) const;
    MatrixRow row(int,const MatrixRow&) const;
    MatrixCol col(int) const;
    MatrixCol col(int,const MatrixCol&) const;

    int sameSize(int a,int b) const { return (nrow==a&&ncol==b); }
    int nRow() const { return nrow; }
    int nCol() const { return ncol; }
    void operator=(const Matrix&);
    int operator==(const Matrix&) const;

    Matrix t() const;  // transpose
    void operator*=(double);

    void switchRows(int,int);
    void switchCols(int,int);
    void combineRows(int i,double b,int j); // row(i) += b*row(j)
    void combineCols(int i,double b,int j); // col(i) += b*col(j)

    int isUpperTriangle() const;
    Matrix upperTriangle();
    Matrix coFactor(int,int) const;
    Matrix coFactor(int,int,Matrix&) const;
    Matrix operator~() const; //  inverse matrix, if any
    
    virtual void printOn(ostream&) const;
    virtual void dumpOn(ostream&) const;
    static void sizeError(char* where,const Matrix&,int,int);
};

//determinent
extern double det(const Matrix&);
extern double norm(const Matrix&);
extern Matrix operator+(const Matrix&,const Matrix&);
extern Matrix operator-(const Matrix&,const Matrix&);
extern Matrix operator*(const Matrix&,const Matrix&);
extern Matrix operator-(const Matrix&);
// concatenate columns
extern Matrix operator&(const Matrix&,const Matrix&);
// scalar multiply    
extern Matrix operator*(double,const Matrix&);
    
class MatrixCol {
    Matrix* pm;
    int _col;    // index of this column
public:
    MatrixCol(int,const Matrix&);
    MatrixCol(const MatrixCol&);
    int nRow() const { return pm->nRow(); }
    double& at(int i) const { return pm->at(i,_col); }
    double& operator()(int i) const
      { return pm->operator()(i,_col); }
    void operator=(const MatrixCol&);
    void operator+=(const MatrixCol&);
    virtual void printOn(ostream&) const;
};

class MatrixRow {
    Matrix* pm;
    int _row;    // index of this row
public:
    MatrixRow(int,const Matrix&);
    MatrixRow(const MatrixRow&);
    int nCol() const { return pm->nCol(); }
    double& at(int i) const { return pm->at(_row,i); }
    double& operator()(int i) const
      { return pm->operator()(_row,i); }
    double operator^(const MatrixCol&) const; // dot product
    void operator=(const MatrixRow&);
    virtual void printOn(ostream&) const;
};

extern ostream& operator<<(ostream& strm,const Matrix& m);
extern ostream& operator<<(ostream& strm,const MatrixRow& m);
extern ostream& operator<<(ostream& strm,const MatrixCol& m);
#endif/*MatrixH*/
