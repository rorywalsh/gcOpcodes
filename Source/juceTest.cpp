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


struct gcGetContext : csnd::Plugin<1, 1>
{
    
    Image** image;
    Graphics** gc;
    
    int init() {
        image = (Image**)csound->query_global_variable("graphics1");
        if(*image != nullptr){
            csound->message("graphics Context is valid");
            csound->create_global_variable("graphicsContext1", sizeof(Graphics*));
            Graphics** gc = (Graphics**)csound->query_global_variable("graphicsContext1");
            *gc = new Graphics(**image);
        }
        else
            csound->message("graphics context not found");
        
        return OK;
    }
};

struct gcFillEllipse : csnd::Plugin<1, 4>
{
    Graphics** gc;

    int init() {
        gc = (Graphics**)csound->query_global_variable("graphicsContext1");
        if(*gc != nullptr){
            csound->message("graphics Context is valid");
            graphics->fillEllipse(inargs[0], inargs[1], inargs[2], inargs[3]);
        }
        else
            csound->message("graphics context not found");

        return OK;
    }
    
    int kperf() {
        if(*gc != nullptr)
        {
            *gc->fillAll(Colours::black);
            *gc->setColour(Colours::red);
            *gc->fillEllipse(inargs[0], inargs[1], inargs[2], inargs[3]);
        }
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
            g.fillAll(Colour(255, 0, 0));
        }
        else
            csound->message("graphics context not found");
        
        return OK;
    }
    
    int kperf() {
        if(*gc != nullptr)
        {
            Graphics g(**gc);
            g.fillAll(Colour(255, 0, 0));
        }
        return OK;
    }
};

struct gcSetColour : csnd::Plugin<1, 4>
{
    
    Image** gc;
    
    int init() {
        gc = (Image**)csound->query_global_variable("graphics1");
        if(*gc != nullptr){
            csound->message("graphics Context is valid");
            Graphics g(**gc);
            g.setColour(Colours::yellow);
        }
        else
            csound->message("graphics context not found");
        
        return OK;
    }
    
    int kperf() {
        if(*gc != nullptr)
        {
            Graphics g(**gc);
            g.setColour(Colours::yellow);
        }
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
    csnd::plugin<gcGetContext>(csound, "gcGetContext.i", "i", "i", csnd::thread::i);
    csnd::plugin<gcFillEllipse>(csound, "gcFillEllipse.ii", "i", "iiii", csnd::thread::i);
    csnd::plugin<gcFillEllipse>(csound, "gcFillEllipse.ik", "k", "kkkk", csnd::thread::ik);
    csnd::plugin<gcFillAll>(csound, "gcFillAll.ii", "i", "iiii", csnd::thread::i);
    csnd::plugin<gcFillAll>(csound, "gcFillAll.ik", "k", "kkkk", csnd::thread::ik);
    csnd::plugin<gcSetColour>(csound, "gcSetColour.ii", "i", "iiii", csnd::thread::i);
    csnd::plugin<gcSetColour>(csound, "gcSetColour.ik", "k", "kkkk", csnd::thread::ik);
}

