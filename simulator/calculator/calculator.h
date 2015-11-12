#ifndef CALCULATOR_H
#define CALCULATOR_H


#include "mainwindow.h"


#define CALCULATOR_CLOSE_WAIT_TIME_MS		2000


class Calculator : public QThread {
	Q_OBJECT

	public:
		static Calculator&		instance();
		void			reset();

	signals:
		void			newPlot(QString name, double key, double value);
	private slots:
		void			startStop();
		void			startUI();
		void			stopUI();

	private:
						Calculator(QObject* parent = 0);
					   ~Calculator();
						Calculator(Calculator const&);
						Calculator& operator= (Calculator const&);

		bool			_isStop;
		void			run();
		void			updateAlgorythm();

		void			aer_loads_mig29_moments( double al, double be, double wx, double wy, double wz, double fi, double df, double da, double dr, double dx );
		double 			cx_al( double al );
		double 			cy_al_fi( double al, double fi );
		double 			cz0( double al );
		double 			dcz_al_be( double al, double be );
		double 			dcz_da( double al );
		double 			dcz_al_dr( double al, double dr );
		double 			dcz_al_fi( double al, double fi );
		double 			mx0( double al );
		double 			dmx_al_be( double al, double be );
		double 			dmx_da( double al );
		double 			dmx_al_dr( double al, double dr );
		double 			dmx_al_fi( double al, double fi );
		double 			mxwx_al( double al );
		double 			mxwy_al( double al );
		double 			my0( double al );
		double 			dmy_al_be( double al, double be );
		double 			dmy_da( double al );
		double 			dmy_al_dr( double al, double dr );
		double 			dmy_al_fi( double al, double fi );
		double 			mywx_al( double al );
		double 			mywy_al_fi( double al, double fi );
		double 			mz_al_fi( double al, double fi );
		double 			dmz_al_be( double al, double be );
		double 			mzwz_al( double al );
		double			interp1l( double* x, int xNum, double* y, int yNum, double xi );
		double			interp1l( double x[20], double y[20], double xi );
		double			interp2l( double* x, int xNum, double* y, int yNum, double *z, double xi, double yi );

		double			dtAl;
		double			dtAt;
		double			timeAt;
		double			timeAl;

		double			Jx;
		double			Jy;
		double			Jz;

		double			Mx;
		double			My;
		double			Mz;
		double			MxPrevious;
		double			MyPrevious;
		double			MzPrevious;

		double			wx;
		double			wy;
		double			wz;
		double			wxPrevious;
		double			wyPrevious;
		double			wzPrevious;

		double			theta;
		double			psi;
		double			gamma;
		double			thetaPrevious;
		double			psiPrevious;
		double			gammaPrevious;

		double			rho;
		double			V;
		double			S;
		double			L;
		double			ba;

		double			alpha;
		double			betta;
		double			fi;
		double			df;
		double			da;
		double			dr;
};

#endif // CALCULATOR_H
