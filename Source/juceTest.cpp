/*
 Copyright (C) 2018 Rory Walsh

 You should have received a copy of the GNU Lesser General Public
 License along with Csound; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 02110-1301 USA
 */

#include <plugin.h>
#include <string>
#include <modload.h>
#include <fstream>
#include "../JuceLibraryCode/JuceHeader.h"


class OpenGLWindow : public Component, public Timer
{
    OpenGLContext openGLContext;

public:
    OpenGLWindow():Component("OpenGL")
    {
// openGLContext.setRenderer (this);
// openGLContext.setContinuousRepainting (false);
// startTimer(1000);
    };

    ~OpenGLWindow(){};

    void timerCallback() override
    {
// jassertfalse;
// csound->message("Hello from timer");
    }

    void paint(Graphics& g)
    {
// jassertfalse;
        g.fillAll(Colours::red);
        g.setColour(Colours::blue);
        Random rand;
        g.fillEllipse(rand.nextFloat()*100, rand.nextFloat()*100, 10, 10);
    }
// void newOpenGLContextCreated() override
// {
// jassertfalse;
// };
//
// void start()
// {
// jassertfalse;
// }
//
// void openGLContextClosing() override
// {
// jassertfalse;
// }
// void renderOpenGL() override
// {
// glBegin(GL_POLYGON);
// glColor3d(255,0,0);
// int x1 = 20;
// int y1 = 20;
// double halfside = 40 / 2;
// glVertex2d(x1 + halfside, y1 + halfside);
// glVertex2d(x1 + halfside, y1 - halfside);
// glVertex2d(x1 - halfside, y1 - halfside);
// glVertex2d(x1 - halfside, y1 + halfside);
// glEnd();
// }
};



struct gcFillEllipse : csnd::Plugin<1, 4>
{
    OpenGLWindow* openGLWindow;


    int init()
    {
        initialiseJuce_GUI();
        openGLWindow = new OpenGLWindow();
// openGLWindow->addToDesktop(ComponentPeer::windowHasTitleBar);
        Component** gc = (Component**)csound->query_global_variable("component");
        *gc = openGLWindow;
        return OK;
    }

    int kperf() {
        ->repaint();
// if(openGLWindow != nullptr)
// openGLWindow->start();
// csound->create_global_variable("component", sizeof(Component*));
  //      Component** gc = (Component**)csound->query_global_variable("component");
//
// if(gc != NULL && firstTimeCallback)
// {
////
// openGLContext.setRenderer (this);
// openGLContext.setContinuousRepainting (false);
// firstTimeCallback = false;
//// renderOpenGL();
// }

// csound->message("Hello");
// if(openGLContext.isAttached() == false && gc != NULL) {
// const MessageManagerLock mml(ThreadPoolJob::getCurrentThreadPoolJob());
// if (mml.lockWasGained()) {
// return OK;
// }
// openGLContext.attachTo(**gc);
// }





// Colour** c = (Colour**)csound->query_global_variable("currentColour");
// if(*image != nullptr){
// Graphics graphics(**image);
// graphics.setColour(**c);
// graphics.fillEllipse(inargs[0], inargs[1], inargs[2], inargs[3]);
// }
// else
// csound->message("graphics context not found");

        return OK;
    }
};

struct gcFillAll : csnd::Plugin<1, 4>
{

    Image** gc;

    int init() {
        gc = (Image**)csound->query_global_variable("graphics1");
        if(*gc != nullptr){
            csound->message("graphics Context is valid");
            Graphics g(**gc);
            g.fillAll(Colour(uint8(inargs[0]), uint8(inargs[1]), uint8(inargs[2]), uint8(inargs[3])));
        }
        else
            csound->message("graphics context not found");

        return OK;
    }

    int kperf() {
        if(*gc != nullptr)
        {
            Graphics g(**gc);
            g.fillAll(Colour(uint8(inargs[0]), uint8(inargs[1]), uint8(inargs[2]), uint8(inargs[3])));
        }
        return OK;
    }
};

struct gcSetColour : csnd::Plugin<1, 4>
{

    Image** gc;

    int init() {
        csound->create_global_variable("currentColour", sizeof(Colour*));
        Colour** c = (Colour**)csound->query_global_variable("currentColour");
        *c = new Colour(0.f, 0.f, 0.f, 0.f);//image;
        if(*c != nullptr){
            csound->message("graphics Context is valid");
            *c = new Colour(uint8(inargs[0]), uint8(inargs[1]), uint8(inargs[2]), uint8(inargs[3]));
        }
        else
            csound->message("graphics context not found");

        return OK;
    }

    int kperf() {
        Colour** c = (Colour**)csound->query_global_variable("currentColour");
        *c = new Colour(0.f, 0.f, 0.f, 0.f);//image;
        if(*c != nullptr){
            *c = new Colour(uint8(inargs[0]), uint8(inargs[1]), uint8(inargs[2]), uint8(inargs[3]));
        }
        else
            csound->message("graphics context not found");

        return OK;
    }
};
#include <modload.h>

/* The mult opcode is overloaded for
 a, k, and i inputs. For these cases, it is
 recommended to append an identifier extension .
 to the name for debugging purposes (not strictly required).
 For the user, the extension is not used and all
 overloads are called "mult"
 */
void csnd::on_load(Csound *csound) {
    csnd::plugin<gcFillEllipse>(csound, "gcFillEllipse.ii", "i", "iiii", csnd::thread::i);
    csnd::plugin<gcFillEllipse>(csound, "gcFillEllipse.ik", "k", "kkkk", csnd::thread::ik);
    csnd::plugin<gcFillAll>(csound, "gcFillAll.ii", "i", "iiii", csnd::thread::i);
    csnd::plugin<gcFillAll>(csound, "gcFillAll.ik", "k", "kkkk", csnd::thread::ik);
    csnd::plugin<gcSetColour>(csound, "gcSetColour.ii", "i", "iiii", csnd::thread::i);
    csnd::plugin<gcSetColour>(csound, "gcSetColour.ik", "k", "kkkk", csnd::thread::ik);
}