#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <iostream>

// Variabile pentru poziția și rotația Pământului
float earthOrbit = 0.0f;
float earthRotation = 0.0f;

// Variabile pentru poziția și rotația Lunii
float moonOrbit = 0.0f;
float moonRotation = 0.0f;

// Texturile
GLuint sunTexture;
GLuint earthTexture;
GLuint moonTexture;

// Funcția pentru a desena o sferă cu o textură dată
void drawTexturedSphere(float radius)
{
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, radius, 30, 30);
    gluDeleteQuadric(quadric);
}

// Funcția pentru a desena scena
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Soarele
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, sunTexture);
    drawTexturedSphere(1.0f);
    glPopMatrix();

    // Pământul
    glPushMatrix();
    glRotatef(earthOrbit, 0.0f, 1.0f, 0.0f);
    glTranslatef(3.0f, 0.0f, 0.0f);
    glRotatef(earthRotation, 0.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, earthTexture);
    drawTexturedSphere(0.5f);

    // Luna
    glPushMatrix();
    glRotatef(moonOrbit, 0.0f, 1.0f, 0.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);
    glRotatef(moonRotation, 0.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, moonTexture);
    drawTexturedSphere(0.2f);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

// Funcția pentru a actualiza starea scenei
void updateScene()
{
    // Actualizarea poziției și rotației Pământului
    earthOrbit += 0.5f;
    earthRotation += 1.0f;

    // Actualizarea poziției și rotației Lunii
    moonOrbit += 1.5f;
    moonRotation += 2.0f;

    glutPostRedisplay();
}

// Funcția pentru inițializarea OpenGL
void initOpenGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glEnable(GL_NORMALIZE);
}
// Funcția pentru încărcarea texturii
GLuint loadTexture(const char* filename)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

int width, height, channels;
unsigned char* image = SOIL_load_image(filename, &width, &height, &channels, SOIL_LOAD_RGB);

if (image)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
else
{
    std::cout << "Eroare la incarcarea texturii " << filename << std::endl;
    return 0;
}}

int main(int argc, char** argv)
{


glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(800, 600);
glutCreateWindow("Sistem Solar");


// Încărcarea texturilor
sunTexture = loadTexture("textures/sun.jpg");
earthTexture = loadTexture("textures/earth.jpg");
moonTexture = loadTexture("textures/moon.jpg");

// Inițializarea OpenGL
initOpenGL();

// Înregistrarea funcțiilor de desenare și actualizare
glutDisplayFunc(drawScene);
glutIdleFunc(updateScene);

// Rularea buclei principale a GLUT
glutMainLoop();

// Eliberarea texturilor
glDeleteTextures(1, &sunTexture);
glDeleteTextures(1, &earthTexture);
glDeleteTextures(1, &moonTexture);

return 0;
}
