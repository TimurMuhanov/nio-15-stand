#include "magnetometervisualiser.h"


#define SPHERE_RADIUS           1
#define DISTANCE                10
#define ROTATION_SPEED_X        0
#define ROTATION_SPEED_Y        1
#define ROTATION_DEFAULT_X      10
#define ROTATION_DEFAULT_Y      0


MagnetometerVisualiser::MagnetometerVisualiser(QWidget *parent) : QOpenGLWidget(parent) {
    QSurfaceFormat surf = format();
    surf.setSamples(8);
    setFormat(surf);

    // create repaint timer
    repaintTimer = new QTimer(this);
    QObject::connect(
        repaintTimer,
        SIGNAL(timeout()),
        SLOT(update()) );
    repaintTimer->start(40);

    xAxisRotation = ROTATION_DEFAULT_X;
    yAxisRotation = ROTATION_DEFAULT_Y;
    autoRotation = true;
}

MagnetometerVisualiser::~MagnetometerVisualiser() {
    if( context()!=0 ) {
        makeCurrent();
        glDeleteBuffers(1, &verticesBuffer);
        doneCurrent();
    }
}

GLfloat MagnetometerVisualiser::wrap_180(GLfloat angle) {
    if(angle > 180) {
        angle -= 360;
    } else if(angle < -180) {
        angle +=360;
    }
    return angle;
}

void MagnetometerVisualiser::appendMag( double x, double y , double z ) {
    makeCurrent();
    vertex vert = { (GLfloat) x, (GLfloat) y, (GLfloat) z };
    vertices.append( vert );
    glBindBuffer( GL_ARRAY_BUFFER, verticesBuffer );
    glBufferData( GL_ARRAY_BUFFER, vertices.length()*3*sizeof(GLfloat), vertices.data(), GL_DYNAMIC_DRAW_ARB );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    doneCurrent();

    if( !repaintTimer->isActive() )
        repaintTimer->start(40);
}

void MagnetometerVisualiser::clear() {
    vertices.clear();
    repaintTimer->stop();
}


void MagnetometerVisualiser::initializeGL() {
    initializeOpenGLFunctions();

    //qDebug() << "OpenGL version" << QString::fromLocal8Bit( (const char *) glGetString(GL_VERSION) );

    // background color
    glClearColor(1.0, 1.0, 1.0, 1.0);


    GLfloat whiteColor[4] = {0.5, 0.5, 0.5, 1};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, whiteColor);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    // enable light
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    // prepare board buffers
    glGenBuffers( 1, &verticesBuffer );

    connect(
        &Connection::instance(),
        &Connection::connected,
        this,
        &MagnetometerVisualiser::clear
    );

    /*for(int i=0; i<3000; i++) {
        float rad = .3;
        float alpha = (rand()%500 - 250)/250.0*M_PI/2;
        float betta = (rand()%250)/250.0*M_PI*2;
        addPoint( rad*cos(alpha)*cos(betta), rad*sin(alpha), rad*cos(alpha)*sin(betta) );
    }*/
}



void MagnetometerVisualiser::resizeGL(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, width, height);
    GLdouble ratio = (GLdouble)width/height;
    if(height >= width) {
        glFrustum(-SPHERE_RADIUS, SPHERE_RADIUS, -SPHERE_RADIUS/ratio-DISTANCE*0.2, SPHERE_RADIUS/ratio-DISTANCE*0.2, DISTANCE-SPHERE_RADIUS, DISTANCE+SPHERE_RADIUS);
    } else {
        glFrustum(-SPHERE_RADIUS*ratio, SPHERE_RADIUS*ratio, -SPHERE_RADIUS-DISTANCE*0.2, SPHERE_RADIUS-DISTANCE*0.2, DISTANCE-SPHERE_RADIUS, DISTANCE+SPHERE_RADIUS);
    }

    currentWidth = width;
    currentHeight = height;
}


void MagnetometerVisualiser::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glNormal3f( 0, 0, 1 );
    paintAxes();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef( 0, -DISTANCE*0.2, -DISTANCE);
    glRotatef(yAxisRotation, 0.0, 1.0, 0.0);
    glRotatef(xAxisRotation, 1.0, 0.0, 0.0);


    glBindBuffer(GL_ARRAY_BUFFER_ARB, verticesBuffer);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glNormalPointer(GL_FLOAT, 0, 0);
    //glEnableClientState(GL_COLOR_ARRAY);

    glDrawArrays( GL_POINTS, 0, vertices.length()*3 );

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    /*float blackColor[4] = {0, 0, 0, 1};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blackColor);
    glPointSize(2);

    glVertexPointer( 3, GL_FLOAT, 0, vertices.begin());
    glDrawArrays(GL_POINTS, 0, vertices.length()/3);*/

    // Rotation
    if(autoRotation) {

       xAxisRotation = wrap_180(xAxisRotation + ROTATION_SPEED_X);
       yAxisRotation = wrap_180(yAxisRotation + ROTATION_SPEED_Y);
    }
}


void MagnetometerVisualiser::mousePressEvent(QMouseEvent *event) {
    pressPosition = event->pos();
    autoRotation = false;
}


void MagnetometerVisualiser::mouseMoveEvent(QMouseEvent *event) {
    xAxisRotation = wrap_180( xAxisRotation + (180 * ((GLfloat)event->y() - (GLfloat)pressPosition.y())) / (currentHeight));
    yAxisRotation = wrap_180( yAxisRotation + (180 * ((GLfloat)event->x() - (GLfloat)pressPosition.x())) / (currentWidth));

    pressPosition = event->pos();
}

void MagnetometerVisualiser::mouseDoubleClickEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    xAxisRotation = ROTATION_DEFAULT_X;
    autoRotation = true;
}



void MagnetometerVisualiser::paintAxes() {
    float grayColor[4] = {0.6, 0.6, 0.6, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, grayColor);

    glBegin(GL_LINES);
        // z
        glVertex3d( 0, 0, -SPHERE_RADIUS*1.2 );
        glVertex3d( 0, 0, SPHERE_RADIUS*1.2 );
        glVertex3d( 0, 0, SPHERE_RADIUS*1.2 );                      // arrow
        glVertex3d( -SPHERE_RADIUS*.02, 0, SPHERE_RADIUS*1.05 );
        glVertex3d( 0, 0, SPHERE_RADIUS*1.2 );
        glVertex3d( SPHERE_RADIUS*.02, 0, SPHERE_RADIUS*1.05 );
        glVertex3d( SPHERE_RADIUS*.1, 0, SPHERE_RADIUS*1.1 );       // symbol
        glVertex3d( SPHERE_RADIUS*.17, 0, SPHERE_RADIUS*1.1 );
        glVertex3d( SPHERE_RADIUS*.17, 0, SPHERE_RADIUS*1.1 );
        glVertex3d( SPHERE_RADIUS*.1, 0, SPHERE_RADIUS*1.17 );
        glVertex3d( SPHERE_RADIUS*.1, 0, SPHERE_RADIUS*1.17 );
        glVertex3d( SPHERE_RADIUS*.17, 0, SPHERE_RADIUS*1.17 );


        // x
        glVertex3d( -SPHERE_RADIUS*1.2, 0, 0 );
        glVertex3d( SPHERE_RADIUS*1.2, 0, 0 );
        glVertex3d( SPHERE_RADIUS*1.2, 0, 0 );                      // arrow
        glVertex3d( SPHERE_RADIUS*1.05, 0, -SPHERE_RADIUS*.02 );
        glVertex3d( SPHERE_RADIUS*1.2, 0, 0 );
        glVertex3d( SPHERE_RADIUS*1.05, 0, SPHERE_RADIUS*.02 );
        glVertex3d( SPHERE_RADIUS*1.1, 0, SPHERE_RADIUS*.1 );       // symbol
        glVertex3d( SPHERE_RADIUS*1.17, 0, SPHERE_RADIUS*.17 );
        glVertex3d( SPHERE_RADIUS*1.17, 0, SPHERE_RADIUS*.1 );
        glVertex3d( SPHERE_RADIUS*1.1, 0, SPHERE_RADIUS*.17 );

        // y
        glVertex3d( 0, -SPHERE_RADIUS*1.2, 0 );
        glVertex3d( 0, SPHERE_RADIUS*1.2, 0 );
        glVertex3d( 0, SPHERE_RADIUS*1.2, 0 );                      // arrow
        glVertex3d( -SPHERE_RADIUS*.02, SPHERE_RADIUS*1.05, 0 );
        glVertex3d( 0, SPHERE_RADIUS*1.2, 0 );
        glVertex3d( SPHERE_RADIUS*.02, SPHERE_RADIUS*1.05, 0 );
        glVertex3d( SPHERE_RADIUS*.1, SPHERE_RADIUS*1.17, 0 );          // symbol
        glVertex3d( SPHERE_RADIUS*.135, SPHERE_RADIUS*1.135, 0 );
        glVertex3d( SPHERE_RADIUS*.17, SPHERE_RADIUS*1.17, 0 );
        glVertex3d( SPHERE_RADIUS*.1, SPHERE_RADIUS*1.1, 0 );
    glEnd();
}
