#ifndef MATRIX_H
#define MATRIX_H


static inline void matmmltf(const float _matrix_x[],
					   int _rows_x, int _columns_x,
					   const float _matrix_y[],
					   int _columns_y,
					   float _product[]) {

	int i,j,k;
	for(i=0; i<_rows_x; i++)
		for(j=0; j<_columns_y; j++) {
			_product[i*_columns_y+j] = 0;
			for(k=0; k<_columns_x; k++)
				_product[i*_columns_y+j] += _matrix_x[i*_columns_x+k]*_matrix_y[k*_columns_y+j];
		}
}

static inline void matsmltf(const float _matrix[],
									  float _scalar,
									  int _rows, int _columns,
									  float _product[]) {
	int i,j;
	for(i=0; i<_rows; i++)
		for(j=0; j<_columns; j++) {
			_product[i*_columns+j] = _matrix[i*_columns+j]*_scalar;
		}
}

static inline void matmaddf (const float _matrix_x[],
									 const float _matrix_y[],
									 int _rows, int _columns,
									 float _sum[]) {
	int i,j;
	for(i=0; i<_rows; i++)
		for(j=0; j<_columns; j++) {
			_sum[i*_columns+j] = _matrix_x[i*_columns+j]+_matrix_y[i*_columns+j];
		}
}

static inline void transpmf (const float _matrix[],
					   int _rows, int _columns,
					   float _transpose[]) {
	int i,j;
	for(i=0; i<_rows; i++)
		for(j=0; j<_columns; j++) {
			_transpose[j*_rows+i] = _matrix[i*_columns+j];
		}
}


#endif // MAINWINDOW_H
