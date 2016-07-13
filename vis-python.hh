#ifndef VIS_PY_H
#define VIS_PY_H

#if CONFIG_PYTHON
#include <Python.h>
#else
typedef struct py_State py_State;
#endif

#include "vis.hh"

/* add a directory to consider when loading py files */
bool vis_py_path_add(Vis*, const char *path);
/* get semi colon separated list of paths to load py files */
const char *vis_py_paths_get(Vis*);

/* various event handlers, triggered by the vis core */
void vis_py_init(Vis*);
void vis_py_start(Vis*);
void vis_py_quit(Vis*);
void vis_py_file_open(Vis*, File*);
void vis_py_file_save(Vis*, File*);
void vis_py_file_close(Vis*, File*);
void vis_py_win_open(Vis*, Win*);
void vis_py_win_close(Vis*, Win*);
void vis_py_win_highlight(Vis*, Win*, size_t horizon);
bool vis_py_win_syntax(Vis*, Win*, const char *syntax);
void vis_py_win_status(Vis*, Win*);

#endif
