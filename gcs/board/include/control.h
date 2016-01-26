#ifndef	CONTROL_H
#define	CONTROL_H


#include <QObject>


class Control : public QObject {
    Q_OBJECT

	public:
		inline static Control&	instance() {
			static Control instance;
			return instance;
		}

		bool			userCodeRunStatus();

	private slots:
		void			userCodeRun();

		/** Execute user code start/stop signal from UAV.
		@param	status
			@arg	TRUE		user code started
			@arg	FALSE		user code stopped */
		void			updateUserCodeRunStatus(bool status);

	private:
						Control(QObject *parent = 0);
					   ~Control();
						Control(Control const&);
						Control& operator= (Control const&);

		/** Code run status. */
		bool			_userCodeRunStatus;
};


#endif // CONTROL_H
