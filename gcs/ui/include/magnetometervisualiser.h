#ifndef MAGNETOMETERVISUALIATION_H
#define MAGNETOMETERVISUALIATION_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>
#include "connection.h"


typedef struct {
	GLfloat x, y, z;
} vertex;


class MagnetometerVisualiser : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT

	public:
						MagnetometerVisualiser(QWidget* parent = 0);
					   ~MagnetometerVisualiser();
					   
        void			appendMag( double x, double y , double z );
		void			clear();
		GLfloat         wrap_180(GLfloat angle);

	protected:
		void			initializeGL();
		void			paintGL();
		void			resizeGL(int width, int height);
		void            mousePressEvent(QMouseEvent* event);
		void            mouseMoveEvent(QMouseEvent* event);
		void            mouseDoubleClickEvent(QMouseEvent *event);

	private:
		void			paintAxes();

		QTimer*			repaintTimer;

		QVector<vertex>	vertices;
        GLuint          verticesBuffer;

		bool            autoRotation;
		QPoint          pressPosition;
		GLfloat         xAxisRotation;
		GLfloat         yAxisRotation;
		GLfloat         currentWidth;
		GLfloat         currentHeight;
};



#endif // MAGNETOMETERVISUALIATION_H
