#include "visualisation.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


#define MODEL_LENGTH			4
#define MODEL_WIDTH				2
#define MODEL_THICK				0.5/2
#if (MODEL_LENGTH > MODEL_WIDTH)
#define MODEL_DIMENSION			MODEL_LENGTH*1.41
#else
#define MODEL_DIMENSION			MODEL_WIDTH*1.41
#endif

#define VIEW_DISTANCE			20


Visualisation::Visualisation(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {
	// create repaint timer
	repaintTimer = new QTimer(this);
	QObject::connect(
		repaintTimer,
		SIGNAL(timeout()),
		SLOT(updateGL()) );
	repaintTimer->start(40);
}

Visualisation::~Visualisation() {
	repaintTimer->stop();
}

void Visualisation::setAttitude(float roll, float pitch, float yaw) {
}

void Visualisation::setRoll(float roll) {
	//qDebug() << "roll:" << roll;
	Visualisation::roll = roll;
}

void Visualisation::setPitch(float pitch) {
	//qDebug() << "pitch:" << pitch;
	Visualisation::pitch = pitch;
}

void Visualisation::setYaw(float yaw) {
	//qDebug() << "yaw:" << yaw;
	Visualisation::yaw = yaw;
}

void Visualisation::initializeGL() {
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glShadeModel(GL_FLAT);

	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glEnable(GL_NORMALIZE);
}

void Visualisation::resizeGL(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, (GLint)width, (GLint)height);
	if( width > height ) {
		glFrustum(
			-(GLdouble)MODEL_DIMENSION,
			 (GLdouble)MODEL_DIMENSION,
			-(GLdouble)MODEL_DIMENSION*((GLdouble)height/(GLdouble)width),
			 (GLdouble)MODEL_DIMENSION*((GLdouble)height/(GLdouble)width),
			(GLdouble)VIEW_DISTANCE-MODEL_DIMENSION/2.0,
			(GLdouble)VIEW_DISTANCE+MODEL_DIMENSION/2.0
		);
	} else {
		glFrustum(
			-(GLdouble)MODEL_DIMENSION*((GLdouble)width/(GLdouble)height),
			 (GLdouble)MODEL_DIMENSION*((GLdouble)width/(GLdouble)height),
			-(GLdouble)MODEL_DIMENSION,
			 (GLdouble)MODEL_DIMENSION,
			(GLdouble)VIEW_DISTANCE-MODEL_DIMENSION/2.0,
			(GLdouble)VIEW_DISTANCE+MODEL_DIMENSION/2.0
		);
	}
}

void Visualisation::paintGL() {\
	static double t = 0;
	t += 0.01;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef( 0, 0, -VIEW_DISTANCE);
	/*glRotatef(Visualisation::yaw/3.1415*180, 0.0, 1.0, 0.0);
	glRotatef(-Visualisation::pitch/3.1415*180, 1.0, 0.0, 0.0);
	glRotatef(Visualisation::roll/3.1415*180, 0.0, 0.0, 1.0);*/
	glRotatef(t/3.1415*180, 0.0, 1.0, 0.0);
	glRotatef(-t/3.1415*180, 1.0, 0.0, 0.0);
	glRotatef(t/3.1415*180, 0.0, 0.0, 1.0);


	float redColor[4] = {1, 0.0, 0.0, 1.0};
	float blackColor[4] = {0.0, 0.0, 0.0, 1.0};
	glColor3d(0,0,0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blackColor);

	glBegin(GL_QUADS);
		glNormal3f( 0,-1, 0);
		glVertex3d( MODEL_WIDTH/2,-MODEL_THICK/2, MODEL_LENGTH/2);
		glVertex3d(-MODEL_WIDTH/2,-MODEL_THICK/2, MODEL_LENGTH/2);
		glColor3d(1,0,0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redColor);
		glVertex3d(-MODEL_WIDTH/2,-MODEL_THICK/2,-MODEL_LENGTH/2);
		glVertex3d( MODEL_WIDTH/2,-MODEL_THICK/2,-MODEL_LENGTH/2);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f( 0, 1, 0);
		glColor3d(0,0,0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackColor);
		glVertex3d( MODEL_WIDTH/2, MODEL_THICK/2, MODEL_LENGTH/2);
		glColor3d(1,0,0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redColor);
		glVertex3d( MODEL_WIDTH/2, MODEL_THICK/2,-MODEL_LENGTH/2);
		glVertex3d(-MODEL_WIDTH/2, MODEL_THICK/2,-MODEL_LENGTH/2);
		glColor3d(0,0,0);
		glVertex3d(-MODEL_WIDTH/2, MODEL_THICK/2, MODEL_LENGTH/2);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f( 1, 0, 0);
		glColor3d(1,0,0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redColor);
		glVertex3d( MODEL_WIDTH/2,-MODEL_THICK/2,-MODEL_LENGTH/2);
		glVertex3d( MODEL_WIDTH/2, MODEL_THICK/2,-MODEL_LENGTH/2);
		glColor3d(0,0,0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackColor);
		glVertex3d( MODEL_WIDTH/2, MODEL_THICK/2, MODEL_LENGTH/2);
		glVertex3d( MODEL_WIDTH/2,-MODEL_THICK/2, MODEL_LENGTH/2);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glVertex3d(-MODEL_WIDTH/2,-MODEL_THICK/2, MODEL_LENGTH/2);
		glVertex3d(-MODEL_WIDTH/2, MODEL_THICK/2, MODEL_LENGTH/2);
		glColor3d(1,0,0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redColor);
		glVertex3d(-MODEL_WIDTH/2, MODEL_THICK/2,-MODEL_LENGTH/2);
		glVertex3d(-MODEL_WIDTH/2,-MODEL_THICK/2,-MODEL_LENGTH/2);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f( 0, 0, 1);
		glColor3d(0,0,0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackColor);
		glVertex3d( MODEL_WIDTH/2,-MODEL_THICK/2, MODEL_LENGTH/2);
		glVertex3d( MODEL_WIDTH/2, MODEL_THICK/2, MODEL_LENGTH/2);
		glVertex3d(-MODEL_WIDTH/2, MODEL_THICK/2, MODEL_LENGTH/2);
		glVertex3d(-MODEL_WIDTH/2,-MODEL_THICK/2, MODEL_LENGTH/2);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f( 0, 0,-1);
		glColor3d(1,0,0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redColor);
		glVertex3d(-MODEL_WIDTH/2,-MODEL_THICK/2,-MODEL_LENGTH/2);
		glVertex3d(-MODEL_WIDTH/2, MODEL_THICK/2,-MODEL_LENGTH/2);
		glVertex3d( MODEL_WIDTH/2, MODEL_THICK/2,-MODEL_LENGTH/2);
		glVertex3d( MODEL_WIDTH/2,-MODEL_THICK/2,-MODEL_LENGTH/2);
	glEnd();

}

