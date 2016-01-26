#ifndef	ENCODERS_H
#define	ENCODERS_H


#include <QObject>
#include <QVector>
#include <QLabel>


class Encoder;

class Encoders : public QObject {
    Q_OBJECT
	friend class Encoder;

	public:
		static Encoders&	instance();
		Encoder*			encoder(int id);

	private:
							Encoders(QObject* parent = 0);
						   ~Encoders();
							Encoders(Encoders const&);
							Encoders& operator= (Encoders const&);
		QVector<Encoder*>	_encoder;
};



class Encoder : public QObject {
	Q_OBJECT

	public:
							Encoder(QObject* parent, int id);
						   ~Encoder();

        void				addData(double time, double value);
        int					id();

	private:
		int					_id;
        QString             _name;
        QLabel*				_indicateLabel;
};


#endif // ENCODERS_H
