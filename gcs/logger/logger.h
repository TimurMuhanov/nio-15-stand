#ifndef	LOGGER_H
#define	LOGGER_H

#include "mainwindow.h"

class Logger : public QObject {
    Q_OBJECT

    public:
        static Logger&			instance();

    public slots:
        void					addData(const QString& name, const double time, std::initializer_list<double> data);

    private slots:
        void                    loggingPathChange();

    private:
                                Logger(QObject *parent = 0);
                               ~Logger();
                                Logger(Logger const&);
                                Logger& operator= (Logger const&);

        QString					_path;
        QHash<QString, QFile*>  _logs;
};


#endif // LOGGER_H
