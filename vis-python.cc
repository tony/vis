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

static PyObject *VisError;

static PyObject *
vis_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    if (sts < 0) {
        PyErr_SetString(VisError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyMethodDef VisMethods[] = {
    {"system",  vis_system, METH_VARARGS, "Execute a shell command."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

char *vis_doc = (char *)"Python API for vis editor";

static struct PyModuleDef vismodule = {
   PyModuleDef_HEAD_INIT,
   "vis",   /* name of module */
   vis_doc, /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   VisMethods
};

PyMODINIT_FUNC
PyInit_vis(void)
{
    return PyModule_Create(&vismodule);
}

/* various event handlers, triggered by the vis core */
void vis_py_init(Vis* vis) {
	char* modname = (char *)"vis";
    PyImport_AppendInittab(modname, PyInit_vis);
	Py_SetProgramName((wchar_t *)modname);

	Py_Initialize();

	PyObject* py_modname = PyUnicode_DecodeFSDefault(modname);
	if (!py_modname) {
		if (PyErr_Occurred())
			PyErr_Print();
		std::cout << "Can't decode module " << modname << std::endl;
	}

	PyObject* py_module = PyImport_Import(py_modname);
	Py_DecRef(py_module);

	if (!py_module) {
		PyErr_Print();
		std::cout << "Failed to load " << modname << std::endl;
		return;
	}

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
	} else {
		std::cout << "no exit: " << filename << std::endl;
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
