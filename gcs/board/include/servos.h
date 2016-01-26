#ifndef	SERVOS_H
#define	SERVOS_H


#include <QObject>
#include "plot.h"


class Servo;

class Servos : public QObject {
    Q_OBJECT
	friend class Servo;

	public:
		static Servos&		instance();
		Servo*				servo(int id);
		void				powerStausGot(bool);
	public slots:
		void				servoPower(int);
	private:
							Servos(QObject* parent = 0);
						   ~Servos();
							Servos(Servos const&);
							Servos& operator= (Servos const&);

		bool				isPowerStateChanging;
		QVector<Servo*>		_servo;
	};



	class Servo : public QObject {
		Q_OBJECT

	public:
							Servo(QObject* parent, int id);
						   ~Servo();

        void				addData(double time, double value);
		int					id();
	private slots:
		void				valueChanged(double);
		void				valueChanged(int);

	private:
        int					_id;
        QString             _name;

		QSlider*			setSlider;
		QDoubleSpinBox*		setSpinBox;
		QSlider*			indicateSlider;
		QLabel*				indicateLabel;
};


#endif // SERVO_H
