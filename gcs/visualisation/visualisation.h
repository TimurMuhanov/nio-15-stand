#ifndef VISUALIATION_H
#define VISUALIATION_H


#include <QGLWidget>
#include <QtOpenGL>


class Visualisation : public QGLWidget {
	Q_OBJECT

	public:
		Visualisation(QWidget* parent = 0);
	   ~Visualisation();

		void			setAttitude(float roll, float pitch, float yaw);
		void			setRoll(float roll);
		void			setPitch(float pitch);
		void			setYaw(float yaw);

	protected:
		void			initializeGL();
		void			paintGL();
		void			resizeGL(int width, int height);

	private:
		GLfloat			cubeVertexArray[8][3];
		GLfloat			cubeColorArray[8][3];
		GLubyte			cubeIndexArray[6][4];
		float			roll;
		float			pitch;
		float			yaw;
		QTimer*			repaintTimer;
};

#endif // VISUALIATION_H
