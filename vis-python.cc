#include "vis-python.hh"
#include "vis-core.hh"
#include "util.hh"
#include <iostream>


#if !CONFIG_PYTHON

bool vis_py_path_add(Vis *vis, const char *path) { return true; }
const char *vis_py_paths_get(Vis *vis) { return NULL; }
void vis_py_init(Vis *vis) { }
void vis_py_start(Vis *vis) { }
void vis_py_quit(Vis *vis) { }
void vis_py_file_open(Vis *vis, File *file) { }
void vis_py_file_save(Vis *vis, File *file) { }
void vis_py_file_close(Vis *vis, File *file) { }
void vis_py_win_open(Vis *vis, Win *win) { }
void vis_py_win_close(Vis *vis, Win *win) { }
void vis_py_win_highlight(Vis *vis, Win *win, size_t horizon) { }
bool vis_py_win_syntax(Vis *vis, Win *win, const char *syntax) { return true; }
bool vis_theme_load(Vis *vis, const char *name) { return true; }
void vis_py_win_status(Vis *vis, Win *win) { window_status_update(vis, win); }

#else

bool vis_py_path_add(Vis*, const char *path) {
	std::cout << "HI" << std::endl;
}

/* get semi colon separated list of paths to load py files */
const char *vis_py_paths_get(Vis* vis) {

}

/* various event handlers, triggered by the vis core */
void vis_py_init(Vis* vis) {
	Py_Initialize();
	PyObject* py_modname = PyUnicode_DecodeFSDefault("vis");

	Py_Finalize();
}
void vis_py_start(Vis* vis){
	std::cout << "HI" << std::endl;

}
void vis_py_quit(Vis* vis){}
void vis_py_file_open(Vis* vis, File* file){
	auto filename = file->name ? file->name : "unnamed";
	std::cout << filename << std::endl;
	if (strstr(filename, "hi") != nullptr) {
		exit(0);
	} else {
		std::cout << "no exit: " << filename << std::endl;
		exit(0);
	}
}
void vis_py_file_save(Vis* vis, File*){}
void vis_py_file_close(Vis* vis, File*){}
void vis_py_win_open(Vis* vis, Win*){}
void vis_py_win_close(Vis* vis, Win*){}
void vis_py_win_highlight(Vis* vis, Win*, size_t horizon){}
bool vis_py_win_syntax(Vis* vis, Win*, const char *syntax){}
void vis_py_win_status(Vis* vis, Win*){}

#endif
