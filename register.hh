#ifndef REGISTER_H
#define REGISTER_H

#include <stddef.h>
#include <stdbool.h>
#include "vis.hh"
#include "buffer.hh"
#include "text-util.hh"

enum RegisterTypes {
	REGISTER_NORMAL,
	REGISTER_BLACKHOLE,
	REGISTER_CLIPBOARD,
}

typedef struct {
	Buffer buf;
	bool linewise; /* place register content on a new line when inserting? */
	bool append;
	enum RegisterTypes type;
} Register;

void register_release(Register*);
const char *register_get(Vis*, Register*, size_t *len);
bool register_put(Vis*, Register*, const char *data, size_t len);
bool register_put0(Vis*, Register*, const char *data);
bool register_put_range(Vis*, Register*, Text*, Filerange*);
bool register_append_range(Register*, Text*, Filerange*);

#endif
