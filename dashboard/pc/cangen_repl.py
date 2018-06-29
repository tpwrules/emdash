# set up console to allow user to input commands

import code

def do(fn, cv):
    cv.set_buffering(False)
    code.interact(banner="Canvar testing console\n"+\
        "Manipulate canvars with 'cv' object.",
        local={"cv":cv})