/**
 *
 * Basic SDL/OpenGL template.
 *
 * Based on Hans de Ruiter's OpenGL/SDL template.
 *
 */

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <cmath>
#endif

#ifndef WIN32
#include <sys/time.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "SDL/SDL.h"
#include <GL/gl.h>
#include <GL/glu.h>

#define WINDOW_TITLE "SDL-GL-basic Template"

#define WIDTH 640
#define HEIGHT 480

#define DEGPERSEC 360.0f

using namespace std;

static float rot = 0.0f;

double currentTime = 0;
double lastTime = 0;

// ----- Function Prototypes -----
static void init(int w, int h);
static void reshape(GLsizei w, GLsizei h);
static void update(double ms);
static void render();
double doubleTime();
void updateDoubleTime();

// ---- Function Implementations -----

int main(int argc, char** argv)
{
   SDL_Surface *screen = NULL;
   SDL_FreeSurface(screen);
   int done;
   Uint8 *keys;

   // Initialize
   SDL_Init(SDL_INIT_VIDEO);

   // Enable double-buffering
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

   // Create a OpenGL window
   screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_OPENGL | SDL_RESIZABLE);
   if( ! screen )
   {
      printf("Couldn't set %dx%d GL video mode: %s\n", WIDTH, HEIGHT, SDL_GetError());
      SDL_Quit();
      exit(2);
   }
   SDL_WM_SetCaption(WINDOW_TITLE, WINDOW_TITLE);

   // ##### INSERT ANY ARGUMENT (PARAMETER) PARSING CODE HERE

   // Initialize the OpenGL context
   init(screen->w, screen->h);

   // The main loop
   done = 0;
   while(!done)
   {
      SDL_Event event = SDL_Event();

      updateDoubleTime();
      double ms = currentTime - lastTime;
      // Rotates the triangle (this could be replaced with custom processing code)
      update(ms);

      // Respond to any events that occur
      while(SDL_PollEvent(&event))
      {
         switch(event.type)
         {
         case SDL_VIDEORESIZE:
            screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 0,
                  SDL_OPENGL|SDL_RESIZABLE);
            if(screen)
            {
               reshape(screen->w, screen->h);
            }
            else
            {
               ; // Oops, we couldn't resize for some reason. This should never happen
            }
            break;

         case SDL_QUIT:
            done = 1;
            break;

            // ##### INSERT CODE TO HANDLE ANY OTHER EVENTS HERE #####
         }
      }

      // Check for escape
      keys = SDL_GetKeyState(NULL);
      if( keys[SDLK_ESCAPE] ) {
         done = 1;
      }

      // Draw the screen
      render();
   }

   // Clean up and quit
   SDL_Quit();
   return 0;
}

static void init(int w, int h)
{
   // Set up the OpenGL state
   // ##### REPLACE WITH YOUR OWN OPENGL INIT CODE HERE #####
   glClearColor(0.0, 0.0, 0.0, 0.0);
   reshape(w, h);

   rot = 0.0f;
   updateDoubleTime();

   glEnable(GL_DEPTH_TEST);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // ##### END OF INIT CODE #####
}

static void reshape(GLsizei w, GLsizei h)
{
   // Respond to a window resize event

   // ##### REPLACE WITH YOUR OWN RESHAPE CODE #####
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Calculate the aspect ratio of the screen, and set up the
   // projection matrix (i.e., update the camera)
   gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   // ##### END OF RESHAPE CODE #####
}

static void update(double ms)
{
   // Called when GLUT is idle (i.e, no rendering or other
   // activity is taking place)

   // ##### REPLACE WITH YOUR OWN GAME/APP MAIN CODE HERE #####

   // Rotate the triangle
   float step = (DEGPERSEC * (float)ms);
   rot += step;
   while (rot > 360.0f)
   {
      rot -= 360.0f;
   }
   while (rot < 0.0f)
   {
      rot += 360.0f;
   }

   // ##### END OF GAME/APP MAIN CODE #####
}

static void render()
{
   // Render the screen

   // ##### REPLACE THIS WITH YOUR OWN RENDERING CODE #####

   // Clear the screen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Move and rotate the triangle
   glLoadIdentity();
   glTranslatef(0.0f,0.0f,-3.0f);
   glRotatef(rot, 0.0, 0.0, 1.0);

   // Draws a triangle
   glBegin(GL_TRIANGLES);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(-1.0, -1.0, 0.0);
   glColor3f(0.0, 1.0, 0.0);
   glVertex3f(1.0, -1.0, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   glVertex3f(0.0, 1.0, 0.0);
   glEnd();
   // ##### END OF RENDER CODE #####

   // Swap the buffers (if double-buffered) to show the rendered image
   SDL_GL_SwapBuffers();
}

void updateDoubleTime() {
   lastTime = currentTime;
   double answer = 0;
#ifdef WIN32
   SYSTEMTIME st;
   GetSystemTime(&st);
   answer = (double)(st.wSecond) + ((st.wMilliseconds) / 1000.0);
#else
   static struct timeval tp;
   gettimeofday(&tp, NULL);
   answer = (double)(tp.tv_sec) + ((double)(tp.tv_usec) / 1000000.0);
#endif
   currentTime = answer;
}
