#include "visualisation.h"
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>


#define BOX_HEIGHT				1
#define BOX_WIDTH				3
#define BOX_LENGTH				4
#define BOUNDING_RADIUS			(sqrt( BOX_HEIGHT*BOX_HEIGHT + BOX_WIDTH*BOX_WIDTH + BOX_LENGTH*BOX_LENGTH )/2*1.2)
#define CAMERA_LIFT				5
#define DISTANCE                30
#define VERTEX_NUMBER			8


typedef struct {
	GLfloat		coordinate[3];
	GLfloat		normals[3];
	//GLfloat		color[3];
	//GLfloat		textureCoordinate[2];
} Vertex;


Visualisation::Visualisation(QWidget *parent) : QOpenGLWidget(parent) {
	QSurfaceFormat surf = format();
	surf.setSamples(8);
	setFormat(surf);

	// create repaint timer
	repaintTimer = new QTimer(this);
	connect(
		repaintTimer,
		SIGNAL(timeout()),
		this,
		SLOT(update()) );
	repaintTimer->start(40);

	xAxisRotation = 0;
	yAxisRotation = 0;
}

Visualisation::~Visualisation() {
	if( context()!=0 ) {
		makeCurrent();
		glDeleteBuffers(1, &verticesBuffer);
		glDeleteBuffers(1, &indicesBuffer);
		doneCurrent();
	}
}

void Visualisation::parameterReceive( Value parameter, double value ) {
    switch( parameter ) {
        case Value::Q0:
            _quaternion.setScalar(value);
            break;
        case Value::Q1:
            _quaternion.setX(value);
            break;
        case Value::Q3:
            _quaternion.setY(value);
            break;
        case Value::Q2:
            _quaternion.setZ(-value);
            break;
    }
}

void Visualisation::initializeGL() {
	initializeOpenGLFunctions();

	connect(
		&Connection::instance(),
		&Connection::valueReceived,
		this,
		&Visualisation::parameterReceive );

	//qDebug() << "OpenGL version" << QString::fromLocal8Bit( (const char *) glGetString(GL_VERSION) );

	// background color
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);

	// enable light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	// prepare board buffers
	Vertex verticies[VERTEX_NUMBER] = {
        { {-BOX_LENGTH/2.0, BOX_HEIGHT/2.0, BOX_WIDTH/2.0},   {-1, 1, 1} },
        { { BOX_LENGTH/2.0, BOX_HEIGHT/2.0, BOX_WIDTH/2.0},   { 1, 1, 1} },
        { { BOX_LENGTH/2.0, BOX_HEIGHT/2.0,-BOX_WIDTH/2.0},   { 1, 1,-1} },
        { {-BOX_LENGTH/2.0, BOX_HEIGHT/2.0,-BOX_WIDTH/2.0},   {-1, 1,-1} },

        { {-BOX_LENGTH/2.0,-BOX_HEIGHT/2.0, BOX_WIDTH/2.0},   {-1,-1, 1} },
        { { BOX_LENGTH/2.0,-BOX_HEIGHT/2.0, BOX_WIDTH/2.0},   { 1,-1, 1} },
        { { BOX_LENGTH/2.0,-BOX_HEIGHT/2.0,-BOX_WIDTH/2.0},   { 1,-1,-1} },
        { {-BOX_LENGTH/2.0,-BOX_HEIGHT/2.0,-BOX_WIDTH/2.0},   {-1,-1,-1} },
	};

	GLuint indices[6][4] = {
		{ 0, 1, 2, 3 },
		{ 0, 4, 5, 1 },
		{ 1, 5, 6, 2 },
		{ 2, 6, 7, 3 },
		{ 0, 3, 7, 4 },
		{ 4, 7, 6, 5 }
	};

	glGenBuffers( 1, &verticesBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, verticesBuffer );
	glBufferData( GL_ARRAY_BUFFER, VERTEX_NUMBER*sizeof(Vertex), verticies, GL_STATIC_DRAW_ARB );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	glGenBuffers( 1, &indicesBuffer );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indicesBuffer );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, 6*4*sizeof(GLfloat), indices, GL_STATIC_DRAW_ARB );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

void Visualisation::resizeGL(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);
	GLdouble ratio = (GLdouble)width/height;
	if(height >= width) {
		glFrustum(-BOUNDING_RADIUS, BOUNDING_RADIUS, -BOUNDING_RADIUS/ratio-CAMERA_LIFT, BOUNDING_RADIUS/ratio-CAMERA_LIFT, DISTANCE-BOUNDING_RADIUS, DISTANCE+BOUNDING_RADIUS);
	} else {
		glFrustum(-BOUNDING_RADIUS*ratio, BOUNDING_RADIUS*ratio, -BOUNDING_RADIUS-CAMERA_LIFT, BOUNDING_RADIUS-CAMERA_LIFT, DISTANCE-BOUNDING_RADIUS, DISTANCE+BOUNDING_RADIUS);
	}

	currentWidth = width;
	currentHeight = height;
}

void Visualisation::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef( 0, -CAMERA_LIFT, -DISTANCE);
    glRotatef(90, 0.0, 1.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
//    glRotatef(yAxisRotation, 0.0, 1.0, 0.0);
	//glRotatef(xAxisRotation, 1.0, 0.0, 0.0);

    double sinAlpha = sqrt( 1-_quaternion.scalar()*_quaternion.scalar() );
    glRotatef(RAD_DEG(2*acos(_quaternion.scalar())), _quaternion.x()/sinAlpha, _quaternion.y()/sinAlpha, _quaternion.z()/sinAlpha);

	// paint board
	GLfloat whiteColor[4] = {0.5, 0.5, 0.5, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteColor);

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indicesBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, verticesBuffer );

	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), 0 );

	glEnableClientState( GL_NORMAL_ARRAY );
	glNormalPointer( GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex,normals) );

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ARRAY_BUFFER_ARB, 0 );
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );
}

void Visualisation::mousePressEvent(QMouseEvent *event) {
	pressPosition = event->pos();
}

void Visualisation::mouseMoveEvent(QMouseEvent *event) {
	xAxisRotation += (180 * ((GLfloat)event->y() - (GLfloat)pressPosition.y())) / (currentHeight);
	yAxisRotation += (180 * ((GLfloat)event->x() - (GLfloat)pressPosition.x())) / (currentWidth);

	pressPosition = event->pos();
}
