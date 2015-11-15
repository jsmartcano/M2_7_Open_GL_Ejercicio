#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>

// ==== Definicion de constantes y variables globales =============
static int hombro = -60;
static int codo = 30;
static int toroide = 310;
static float pinza = 0.2;

GLfloat matVerde[] = {0.0, 1.0, 0.0, 1.0};
GLfloat matAzul[] = {0.0, 0.0, 1.0, 1.0};
GLfloat matNaranja[] = {1.0, 0.5, 0.0};
GLfloat matBlanco[] = {1.0, 1.0, 1.0, 1.0};


// ==== Funcion de callback del teclado ===========================
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case '1': toroide++; break;
        case '2': toroide--; break;
        case 'q': hombro++; break;
        case 'w': hombro--; break;
        case 'a': codo++; break;
        case 's': codo--; break;
        case 'z':
        	if (pinza<0.4) {
        		pinza=pinza+0.01;
        	};
        	break;
        case 'x':
        	if (pinza>0.2) {
        	    pinza=pinza-0.01;
        	};
        	break;
    }
        glutPostRedisplay();
}

// ==== Funci�n de dibujado =======================================
void dibujar() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 1.0, 6.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);

    // Dibuja toroide
    glRotatef(-90,1.0,0.0,0.0);
    glRotatef(toroide, 0.0,0.0,1.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matNaranja);
    glutSolidTorus(0.3, 2, 8, 10);

    // Dibujar brazo 1
    glRotatef(hombro, 0.0, 1.0, 0.0);
    glTranslatef(0.7, 0.0, 0.0);
    glPushMatrix();
    glScalef (1.5, 0.7, 0.5);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matVerde);
    glutSolidCube(1.0);
    glPopMatrix();

    // Dibuja brazo 2
    glTranslatef(0.5,0.0,0.0);  // Avanzamos al extremo
    glRotatef(codo, 0.0, 1.0, 0.0);
    glTranslatef(1.0,0.0,0.0);  // Hasta la mitad
    glPushMatrix();
    glScalef (1.5, 0.7, 0.5);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matAzul);
    glutSolidCube(1.0);
    glPopMatrix();

    // Dibuja cono 1
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matBlanco);
    glTranslatef(0.75,0,0.0);  // Avanzamos al extremo
    glPushMatrix();   // guardo matriz para luego recuperar el centro y poner el otro cono
    glTranslatef(0.0,pinza,0.0);  // Avanzamos al extrem
    glRotatef(90, 0.0, 1.0, 0.0);
    glutSolidCone(0.2,0.6,6,6);

    // Dibuja cono 2, antes recupero matriz para ir al centro
    glPopMatrix();
    glTranslatef(0.0,-pinza,0.0);  // Avanzamos al extremo
    glRotatef(90, 0.0, 1.0, 0.0);
    glutSolidCone(0.2,0.6,6,6);
    glPopMatrix();

    glutSwapBuffers();
}

void escalar(int w, int h)
{
    // Viewport para dibujar en toda la ventana
    glViewport( 0, 0, w, h );

    // Actualizamos en la matriz de proyecci�n el ratio ancho/alto
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60., (double)w/(double)h, 1., 20. );

    // Volvemos al modo Vista de Modelo
    glMatrixMode( GL_MODELVIEW );
}

int main( int argc, char** argv )
{
    GLfloat posluz[] = {0.0, 4.0, 8.0, 0.0};
    GLfloat luz[] = {1.0, 1.0, 1.0, 1.0};

    glutInit( &argc, argv );

    glutInitDisplayMode( GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(640, 480);
    glutCreateWindow( "Practicas IG - Sesion 3" );

    glClearColor(0.2, 0.2, 0.2, 1.0);
    glShadeModel(GL_FLAT);
    glLightfv(GL_LIGHT0, GL_POSITION, posluz);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    // Registro de funciones de callback
    glutDisplayFunc(dibujar);
    glutReshapeFunc(escalar);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}
