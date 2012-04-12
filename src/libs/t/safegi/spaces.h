#ifndef _SPACES_H_
#define _SPACES_H_

struct mirror_s { }; // normal along mirror direction, x,y whatever
struct local_s { };  // normal along z, x,y over tangents, o on the surface location
struct world_s { };  // world
struct shape_s { };  // shape
struct lens_s { };   // lens
struct source_s { }; // source
struct clip_s { }; // clip space

#endif
