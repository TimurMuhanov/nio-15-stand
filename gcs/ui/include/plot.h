#ifndef	PLOT_H
#define	PLOT_H


#include <QObject>
#include "qcustomplot.h"


#define REPLOT_TIME_MS		30


enum DataRange{
	all,
	period,
};



class PlotItem : public QObject {
	Q_OBJECT

	friend class Plot;
	public:
							PlotItem(QObject *parent, const QString& name, const QString& color);
						   ~PlotItem();

		void				addData(const double key, const double value);
        void				clear();
	private slots:
		void				setVisible(bool);

	private:
		const QString		name;
		QCPGraph*			graph;
};



class Plot : public QObject {
    Q_OBJECT

	friend class PlotItem;
	public:
		static Plot&			instance();
	/*signals:
		void					newPlotParameter(PlotParameter* parameter);*/

	public slots:
		void					addData(const QString& name, const double key, const double data);

	private slots:
        void					reset();
		void					replot();
		void					plotRangeChangeToAll();
		void					plotRangeChangeToPeriod();
        void					plotPauseStop();


	private:
		const QString&			getNewColor();

								Plot(QObject *parent = 0);
							   ~Plot();
								Plot(Plot const&);
								Plot& operator= (Plot const&);
		QMap<QString, bool>		colors;
		DataRange				dataRange;
		QTimer*					replotTimer;
        QVector<PlotItem*>		plots;
};





#endif // PLOT_H
