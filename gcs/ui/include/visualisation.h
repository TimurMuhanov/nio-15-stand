#ifndef VISUALIATION_H
#define VISUALIATION_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QQuaternion>
#include "connection.h"


class Visualisation : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT

	public:
						Visualisation( QWidget* parent = 0 );
					   ~Visualisation();

		void			parameterReceive( Value, double );

	protected:
		void			initializeGL();
		void			paintGL();
		void			resizeGL(int width, int height);
		void            mousePressEvent(QMouseEvent* event);
		void            mouseMoveEvent(QMouseEvent* event);

	private:
		void            paintCircle();
		void            generateTextures();

        QQuaternion     _quaternion;
		QTimer*			repaintTimer;
		QOpenGLTexture* texture;
		GLuint          verticesBuffer;
		GLuint          indicesBuffer;

		QPoint          pressPosition;
		GLfloat         xAxisRotation;
		GLfloat         yAxisRotation;
		GLfloat         currentWidth;
		GLfloat         currentHeight;
};



#endif // VISUALIATION_H
