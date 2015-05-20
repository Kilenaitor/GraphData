#GraphData
GraphData is a library used for visualizing data structures in image format.
##Inspiration
Normally when debugging or teaching data structures, the developer has to write
a `print` function for the data structure so that they can visualize what the
structure looks like at that current point. This is usually done in some crude,
ASCII art-style, mess of `cout` statements just to get a structure that's semi-coherent.

With GraphData, all of the work is handled by another library called GraphViz that
when supplied with a txt file containing data pertaining to a graph/chart/tree/etc.
will draw the diagram to spec and output an image file. Done in sequence, 
an instructor or developer can simply call the library's `print` function as many
times as desired and get a sequences of images (named by date and time created) that
visualize the changes made to the data structure! Awesome :D

##Dependencies
GraphData depends on the GraphViz library to be installed on the machine.
A link for which can be found here:

http://www.graphviz.org/Download.php

##Usage
Pseudo-install will be written so until then,

`#include "graphviz.h"`

Yeah. It's... that easy... 

##Work in Progress
Currently, separate functions have to be called for each type of data structure
that you want to have visualized. Currently supported are array, vector, 
and klist (which is a custom data structure used for testing). Support will be
added soon for `stacks`, `queues`, `trees`, `dequeus`, `lists`, `maps`, `sets`, 
and hopefully maybe soon some custom data structures. 

After the implementation has been added, [template metaprogramming](http://i.imgur.com/zsFrWLe.gif) 
will be used to remove the specific function calls and will be reduce to 
a single function named `visualize`. It's basically magic, but not really
secret magic... since you can always just look at the code... Shhhhhh

In the future, going to try to get it included as a pluging for gdb. 
BUT, until then, this is the best I can do. I hope you enjoy!

Feel free to open an issue if something isn't working or you just want something addd. 
My QA department isn't exactly overstaffed. 

##Current Examples
This is what an array would look like:
![Array](http://puu.sh/hU0F3/25bdfc5b8b.png)

This is what klist looks like:
![klist](http://puu.sh/hU0FT/33d7cbf5d1.png)