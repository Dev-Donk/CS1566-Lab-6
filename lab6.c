

/*
*   Author: Dante Samarco
*
*   Lab 6
*/

#ifdef __APPLE__  // include Mac OS X verions of headers
    #include <OpenGL/OpenGL.h>
    #include <GLUT/glut.h>
#else // non-Mac OS X operating systems
    #include <GL/glew.h>
    #include <GL/freeglut.h>
    #include <GL/freeglut_ext.h>
#endif  // __APPLE__

#include "initShader.h"

#include <stdio.h>
#include "myLib.h"

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

#define IDENTITY_MAT {{1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0}}



unsigned int num_vertices   = 24; // Changes based on program

GLuint ctm_location;
mat4 ctm                    = IDENTITY_MAT;

GLuint model_view_location;
mat4 model_view             = IDENTITY_MAT;

GLuint projection_location;
mat4 projection             = IDENTITY_MAT;

unsigned char isAnimating   = 0;

vec4 *positions; 
vec4 *colors;
vec2 *tex_coords;



void init(void)
{
    positions       = (vec4 *) malloc(sizeof(vec4) * num_vertices);

    // NEXT TIME DO THIS IN ANOTHER ANOTHER FUNCTION
    // Square Top Left
    positions[0]    = (vec4) { 0.0f,  0.0f, 0.0f, 1.0f }; // Tri 1
    positions[1]    = (vec4) {-1.0f,  1.0f, 0.0f, 1.0f };
    positions[2]    = (vec4) {-1.0f,  0.0f, 0.0f, 1.0f };
    positions[3]    = (vec4) { 0.0f,  0.0f, 0.0f, 1.0f }; // Tri 2
    positions[4]    = (vec4) { 0.0f,  1.0f, 0.0f, 1.0f };
    positions[5]    = (vec4) {-1.0f,  1.0f, 0.0f, 1.0f };

    // Square Top Right
    positions[6]    = (vec4) { 1.0f,  0.0f, 0.0f, 1.0f }; // Tri 1
    positions[7]    = (vec4) { 0.0f,  1.0f, 0.0f, 1.0f };
    positions[8]    = (vec4) { 0.0f,  0.0f, 0.0f, 1.0f };
    positions[9]    = (vec4) { 1.0f,  0.0f, 0.0f, 1.0f }; // Tri 2
    positions[10]   = (vec4) { 1.0f,  1.0f, 0.0f, 1.0f };
    positions[11]   = (vec4) { 0.0f,  1.0f, 0.0f, 1.0f };

    // Square Bottom Left
    positions[12]   = (vec4) { 0.0f, -1.0f, 0.0f, 1.0f }; // Tri 1
    positions[13]   = (vec4) {-1.0f,  0.0f, 0.0f, 1.0f };
    positions[14]   = (vec4) {-1.0f, -1.0f, 0.0f, 1.0f };
    positions[15]   = (vec4) { 0.0f, -1.0f, 0.0f, 1.0f }; // Tri 2
    positions[16]   = (vec4) { 0.0f,  0.0f, 0.0f, 1.0f };
    positions[17]   = (vec4) {-1.0f,  0.0f, 0.0f, 1.0f };

    // Square Bottom Right
    positions[18]   = (vec4) { 1.0f, -1.0f, 0.0f, 1.0f }; // Tri 1
    positions[19]   = (vec4) { 0.0f,  0.0f, 0.0f, 1.0f };
    positions[20]   = (vec4) { 0.0f, -1.0f, 0.0f, 1.0f };
    positions[21]   = (vec4) { 1.0f, -1.0f, 0.0f, 1.0f }; // Tri 2
    positions[22]   = (vec4) { 1.0f,  0.0f, 0.0f, 1.0f };
    positions[23]   = (vec4) { 0.0f,  0.0f, 0.0f, 1.0f };

    /* Not needed for the purpose of this lab, but eh */
    colors          = (vec4 *) malloc(sizeof(vec4) * num_vertices);

    // Texture coordinate of the square
    
    tex_coords      = (vec2 *) malloc(sizeof(vec2) * num_vertices);
    // Square Top Left
    tex_coords[0]   = (vec2) {0.25f, 0.25f}; // Tri 1
    tex_coords[1]   = (vec2) {0.00f, 0.00f};
    tex_coords[2]   = (vec2) {0.00f, 0.25f};
    tex_coords[3]   = (vec2) {0.25f, 0.25f}; // Tri 2
    tex_coords[4]   = (vec2) {0.25f, 0.00f};
    tex_coords[5]   = (vec2) {0.00f, 0.00f};

    // Square Top Right
    tex_coords[6]   = (vec2) {0.50f, 0.50f}; // Tri 1
    tex_coords[7]   = (vec2) {0.25f, 0.25f};
    tex_coords[8]   = (vec2) {0.25f, 0.50f};
    tex_coords[9]   = (vec2) {0.50f, 0.50f}; // Tri 2
    tex_coords[10]  = (vec2) {0.50f, 0.25f};
    tex_coords[11]  = (vec2) {0.25f, 0.25f};

    // Square Bottom Left
    tex_coords[12]  = (vec2) {1.00f, 0.75f}; // Tri 1
    tex_coords[13]  = (vec2) {0.75f, 0.50f};
    tex_coords[14]  = (vec2) {0.75f, 0.75f};
    tex_coords[15]  = (vec2) {1.00f, 0.75f}; // Tri 2
    tex_coords[16]  = (vec2) {1.00f, 0.50f};
    tex_coords[17]  = (vec2) {0.75f, 0.50f};

    // Square Bottom Right
    tex_coords[18]  = (vec2) {0.50f, 1.00f}; // Tri 1
    tex_coords[19]  = (vec2) {0.25f, 0.75f};
    tex_coords[20]  = (vec2) {0.25f, 1.00f};
    tex_coords[21]  = (vec2) {0.50f, 1.00f}; // Tri 2
    tex_coords[22]  = (vec2) {0.50f, 0.75f};
    tex_coords[23]  = (vec2) {0.25f, 0.75f};

    // Load Texture in -------------------------------------------------

    unsigned int tex_width  = 64;
    unsigned int tex_height = 64;
    GLubyte my_texels[tex_width][tex_height][3];

    FILE *fp = fopen("textures01.raw", "r");
    if(fp == NULL) {
        printf("Texture not found.");
        exit(0);
    }

    fread(my_texels, tex_width * tex_height * 3, 1, fp);
    fclose(fp);

    // -----------------------------------------------------------------


    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    // Texture & Color Mapping -----------------------------------------

    GLuint mytex[1];
    glGenTextures(1, mytex);
    glBindTexture(GL_TEXTURE_2D, mytex[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, my_texels);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int param;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &param);

    GLuint vao;
    #ifdef __APPLE__
        glGenVertexArraysAPPLE(1, &vao);
        glBindVertexArrayAPPLE(vao);
    #else
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    #endif


    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(vec4) * num_vertices) + (sizeof(vec4) * num_vertices) + (sizeof(vec2) * num_vertices), NULL, GL_STATIC_DRAW);

    /* Tells the buffer what is at what position essentially */
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4) * num_vertices, positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4) * num_vertices, sizeof(vec4) * num_vertices, colors);
    glBufferSubData(GL_ARRAY_BUFFER, (sizeof(vec4) * num_vertices) + (sizeof(vec4) * num_vertices), sizeof(vec2) * num_vertices, tex_coords);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (sizeof(vec4) * num_vertices));

    GLuint vTexCoord = glGetAttribLocation(program, "vTexCoord");
    glEnableVertexAttribArray(vTexCoord);
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (sizeof(vec4) * num_vertices) + (sizeof(vec4) * num_vertices));

    // -----------------------------------------------------------------

    ctm_location = glGetUniformLocation(program, "ctm");
    model_view_location = glGetUniformLocation(program, "model_view");
    projection_location = glGetUniformLocation(program, "projection");

    GLuint texture_location = glGetUniformLocation(program, "texture");
    glUniform1i(texture_location, 0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *) &model_view);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) &projection);
    // glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);

    glDrawArrays(GL_TRIANGLES, 0, num_vertices);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    if(key == 'q') {
	    #ifndef __APPLE__
	        exit(0);
	    #else
	        glutLeaveMainLoop();
	    #endif
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    //printf("%d %d %d %d\n", button, state, x, y);

    //glutPostRedisplay(); // <-- Uncomment if function does something
}

void motion(int x, int y) {

    //glutPostRedisplay(); // <-- Uncomment if function does something
}

void idle(void) {
    if(!isAnimating)
	return;

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Lab 6");

    glewInit();
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
