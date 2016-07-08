/* Configure your desired default key bindings. */

#include "vis.hh"
#include <vector>
#include <map>
#include <array>

#define ALIAS(name) nullptr, name
#define ACTION(id) &vis_action[VIS_ACTION_##id], nullptr




template<std::size_t... Is> struct seq {};

template<std::size_t N, std::size_t... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...> {};

template<std::size_t... Is>
struct gen_seq<0, Is...> : seq<Is...> {};

template<typename T, std::size_t N1, std::size_t... I1, std::size_t N2, std::size_t... I2>
inline std::array<T, N1+N2> concat(
    std::array<T, N1> a1,
    std::array<T, N2> a2,
    seq<I1...>,
    seq<I2...>) {
    return {{ std::move(a1[I1])..., std::move(a2[I2])... }};
}

template<typename T, std::size_t N1, std::size_t N2>
inline std::array<T, N1+N2> concat(std::array<T, N1> a1, std::array<T, N2> a2) {
    return concat(std::move(a1), std::move(a2), gen_seq<N1>(), gen_seq<N2>());
}

static const char *keymaps[] = {
	NULL
};

struct BindingsBasic {
	KeyBinding bindings[100];
	BindingsBasic() {
		static const KeyBinding initValue[] = {
		{ "<C-z>",              ACTION(EDITOR_SUSPEND)                      },
		{ "<Down>",             ACTION(CURSOR_LINE_DOWN)                    },
		{ "<End>",              ACTION(CURSOR_LINE_END)                     },
		{ "<Home>",             ACTION(CURSOR_LINE_BEGIN)                   },
		{ "<Left>",             ACTION(CURSOR_CHAR_PREV)                    },
		{ "<PageDown>",         ACTION(WINDOW_PAGE_DOWN)                    },
		{ "<PageUp>",           ACTION(WINDOW_PAGE_UP)                      },
		{ "<Right>",            ACTION(CURSOR_CHAR_NEXT)                    },
		{ "<S-Left>",           ACTION(CURSOR_LONGWORD_START_PREV)          },
		{ "<S-PageDown>",       ACTION(WINDOW_HALFPAGE_DOWN)                },
		{ "<S-PageUp>",         ACTION(WINDOW_HALFPAGE_UP)                  },
		{ "<S-Right>",          ACTION(CURSOR_LONGWORD_START_NEXT)          },
		{ "<Up>",               ACTION(CURSOR_LINE_UP)                      }
		};
		memcpy(bindings, initValue, sizeof(initValue));
	}
} bindings_basic;

struct BindingsMotions {
	KeyBinding bindings[100];
	BindingsMotions() {
		static const KeyBinding initValue[] = { 
		{ "|",                  ACTION(CURSOR_COLUMN)                       },
		{ "]]",                 ACTION(CURSOR_FUNCTION_END_NEXT)            },
		{ "[]",                 ACTION(CURSOR_FUNCTION_END_PREV)            },
		{ "][",                 ACTION(CURSOR_FUNCTION_START_NEXT)          },
		{ "[[",                 ACTION(CURSOR_FUNCTION_START_PREV)          },
		{ "[{",                 ACTION(CURSOR_BLOCK_START)                  },
		{ "]}",                 ACTION(CURSOR_BLOCK_END)                    },
		{ "[(",                 ACTION(CURSOR_PARENTHESE_START)             },
		{ "])",                 ACTION(CURSOR_PARENTHESE_END)               },
		{ "$",                  ACTION(CURSOR_LINE_END)                     },
		{ "^",                  ACTION(CURSOR_LINE_START)                   },
		{ "}",                  ACTION(CURSOR_PARAGRAPH_NEXT)               },
		{ "{",                  ACTION(CURSOR_PARAGRAPH_PREV)               },
		{ "%",                  ACTION(CURSOR_PERCENT)                      },
		{ "#",                  ACTION(CURSOR_SEARCH_WORD_BACKWARD)         },
		{ "*",                  ACTION(CURSOR_SEARCH_WORD_FORWARD)          },
		{ ")",                  ACTION(CURSOR_SENTENCE_NEXT)                },
		{ "(",                  ACTION(CURSOR_SENTENCE_PREV)                },
		{ "`",                  ACTION(MARK_GOTO)                           },
		{ "'",                  ACTION(MARK_GOTO_LINE)                      },
		{ "?",                  ACTION(PROMPT_SEARCH_BACKWARD)              },
		{ "/",                  ACTION(PROMPT_SEARCH_FORWARD)               },
		{ ";",                  ACTION(TOTILL_REPEAT)                       },
		{ ",",                  ACTION(TOTILL_REVERSE)                      },
		{ "+",                  ALIAS("j^")                                 },
		{ "-",                  ALIAS("k^")                                 },
		{ " ",                  ALIAS("<Space>")                            },
		{ "<Space>",            ALIAS("l")                                  },
		{ "<Backspace>",        ALIAS("h")                                  },
		{ "B",                  ACTION(CURSOR_LONGWORD_START_PREV)          },
		{ "b",                  ACTION(CURSOR_WORD_START_PREV)              },
		{ "<C-h>",              ALIAS("<Backspace>")                        },
		{ "<C-j>",              ALIAS("j")                                  },
		{ "<C-n>",              ALIAS("j")                                  },
		{ "<C-p>",              ALIAS("k")                                  },
		{ "E",                  ACTION(CURSOR_LONGWORD_END_NEXT)            },
		{ "e",                  ACTION(CURSOR_WORD_END_NEXT)                },
		{ "<Enter>",            ALIAS("j")                                  },
		{ "F",                  ACTION(TO_LEFT)                             },
		{ "f",                  ACTION(TO_RIGHT)                            },
		{ "g0",                 ACTION(CURSOR_SCREEN_LINE_BEGIN)            },
		{ "g_",                 ACTION(CURSOR_LINE_FINISH)                  },
		{ "G",                  ACTION(CURSOR_LINE_LAST)                    },
		{ "g$",                 ACTION(CURSOR_SCREEN_LINE_END)              },
		{ "g<Down>",            ALIAS("gj")                                 },
		{ "gE",                 ACTION(CURSOR_LONGWORD_END_PREV)            },
		{ "ge",                 ACTION(CURSOR_WORD_END_PREV)                },
		{ "gg",                 ACTION(CURSOR_LINE_FIRST)                   },
		{ "gj",                 ACTION(CURSOR_SCREEN_LINE_DOWN)             },
		{ "gk",                 ACTION(CURSOR_SCREEN_LINE_UP)               },
		{ "gm",                 ACTION(CURSOR_SCREEN_LINE_MIDDLE)           },
		{ "g<Up>",              ALIAS("gk")                                 },
		{ "h",                  ACTION(CURSOR_CHAR_PREV)                    },
		{ "H",                  ACTION(CURSOR_WINDOW_LINE_TOP)              },
		{ "j",                  ACTION(CURSOR_LINE_DOWN)                    },
		{ "k",                  ACTION(CURSOR_LINE_UP)                      },
		{ "l",                  ACTION(CURSOR_CHAR_NEXT)                    },
		{ "L",                  ACTION(CURSOR_WINDOW_LINE_BOTTOM)           },
		{ "M",                  ACTION(CURSOR_WINDOW_LINE_MIDDLE)           },
		{ "n",                  ACTION(CURSOR_SEARCH_NEXT)                  },
		{ "N",                  ACTION(CURSOR_SEARCH_PREV)                  },
		{ "T",                  ACTION(TILL_LEFT)                           },
		{ "t",                  ACTION(TILL_RIGHT)                          },
		{ "W",                  ACTION(CURSOR_LONGWORD_START_NEXT)          },
		{ "w",                  ACTION(CURSOR_WORD_START_NEXT)              }
		};
		memcpy(bindings, initValue, sizeof(initValue));
	}
} bindings_motions;

struct BindingsTextObjects {
	KeyBinding bindings[100];
	BindingsTextObjects() {
		static const KeyBinding initValue[] = {
	{ "a<",                 ACTION(TEXT_OBJECT_ANGLE_BRACKET_OUTER)     },
	{ "a`",                 ACTION(TEXT_OBJECT_BACKTICK_OUTER)          },
	{ "a{",                 ACTION(TEXT_OBJECT_CURLY_BRACKET_OUTER)     },
	{ "a(",                 ACTION(TEXT_OBJECT_PARANTHESE_OUTER)        },
	{ "a\"",                ACTION(TEXT_OBJECT_QUOTE_OUTER)             },
	{ "a\'",                ACTION(TEXT_OBJECT_SINGLE_QUOTE_OUTER)      },
	{ "a[",                 ACTION(TEXT_OBJECT_SQUARE_BRACKET_OUTER)    },
	{ "a>",                 ALIAS("a<")                                 },
	{ "a)",                 ALIAS("a(")                                 },
	{ "a]",                 ALIAS("a[")                                 },
	{ "a}",                 ALIAS("a{")                                 },
	{ "ab",                 ALIAS("a(")                                 },
	{ "aB",                 ALIAS("a{")                                 },
	{ "ae",                 ACTION(TEXT_OBJECT_ENTIRE_OUTER)            },
	{ "af",                 ACTION(TEXT_OBJECT_FUNCTION_OUTER)          },
	{ "al",                 ACTION(TEXT_OBJECT_LINE_OUTER)              },
	{ "ap",                 ACTION(TEXT_OBJECT_PARAGRAPH)               },
	{ "as",                 ACTION(TEXT_OBJECT_SENTENCE)                },
	{ "a<Tab>",             ACTION(TEXT_OBJECT_INDENTATION)             },
	{ "aW",                 ACTION(TEXT_OBJECT_LONGWORD_OUTER)          },
	{ "aw",                 ACTION(TEXT_OBJECT_WORD_OUTER)              },
	{ "gN",                 ACTION(TEXT_OBJECT_SEARCH_BACKWARD)         },
	{ "gn",                 ACTION(TEXT_OBJECT_SEARCH_FORWARD)          },
	{ "i<",                 ACTION(TEXT_OBJECT_ANGLE_BRACKET_INNER)     },
	{ "i`",                 ACTION(TEXT_OBJECT_BACKTICK_INNER)          },
	{ "i{",                 ACTION(TEXT_OBJECT_CURLY_BRACKET_INNER)     },
	{ "i(",                 ACTION(TEXT_OBJECT_PARANTHESE_INNER)        },
	{ "i\"",                ACTION(TEXT_OBJECT_QUOTE_INNER)             },
	{ "i\'",                ACTION(TEXT_OBJECT_SINGLE_QUOTE_INNER)      },
	{ "i[",                 ACTION(TEXT_OBJECT_SQUARE_BRACKET_INNER)    },
	{ "i>",                 ALIAS("i<")                                 },
	{ "i)",                 ALIAS("i(")                                 },
	{ "i]",                 ALIAS("i[")                                 },
	{ "i}",                 ALIAS("i{")                                 },
	{ "ib",                 ALIAS("i(")                                 },
	{ "iB",                 ALIAS("i{")                                 },
	{ "ie",                 ACTION(TEXT_OBJECT_ENTIRE_INNER)            },
	{ "if",                 ACTION(TEXT_OBJECT_FUNCTION_INNER)          },
	{ "il",                 ACTION(TEXT_OBJECT_LINE_INNER)              },
	{ "ip",                 ACTION(TEXT_OBJECT_PARAGRAPH)               },
	{ "is",                 ACTION(TEXT_OBJECT_SENTENCE)                },
	{ "i<Tab>",             ACTION(TEXT_OBJECT_INDENTATION)             },
	{ "iW",                 ACTION(TEXT_OBJECT_LONGWORD_INNER)          },
	{ "iw",                 ACTION(TEXT_OBJECT_WORD_INNER)              }
		};
		memcpy(bindings, initValue, sizeof(initValue));
	}
} bindings_textobjects;

struct BindingsOperators {
	KeyBinding bindings[100];
	BindingsOperators() {
		static const KeyBinding initValue[] = {
	{ "0",                  ACTION(COUNT)                               },
	{ "1",                  ACTION(COUNT)                               },
	{ "2",                  ACTION(COUNT)                               },
	{ "3",                  ACTION(COUNT)                               },
	{ "4",                  ACTION(COUNT)                               },
	{ "5",                  ACTION(COUNT)                               },
	{ "6",                  ACTION(COUNT)                               },
	{ "7",                  ACTION(COUNT)                               },
	{ "8",                  ACTION(COUNT)                               },
	{ "9",                  ACTION(COUNT)                               },
	{ "~",                  ACTION(OPERATOR_CASE_SWAP)                  },
	{ "!",                  ACTION(OPERATOR_FILTER)                     },
	{ "=",                  ALIAS("gq")                                 },
	{ "<",                  ACTION(OPERATOR_SHIFT_LEFT)                 },
	{ ">",                  ACTION(OPERATOR_SHIFT_RIGHT)                },
	{ "\"",                 ACTION(REGISTER)                            },
	{ "c",                  ACTION(OPERATOR_CHANGE)                     },
	{ "d",                  ACTION(OPERATOR_DELETE)                     },
	{ "g~",                 ACTION(OPERATOR_CASE_SWAP)                  },
	{ "gp",                 ACTION(PUT_AFTER_END)                       },
	{ "gP",                 ACTION(PUT_BEFORE_END)                      },
	{ "gq",                 ACTION(OPERATOR_FILTER_FMT)                 },
	{ "gu",                 ACTION(OPERATOR_CASE_LOWER)                 },
	{ "gU",                 ACTION(OPERATOR_CASE_UPPER)                 },
	{ "p",                  ACTION(PUT_AFTER)                           },
	{ "P",                  ACTION(PUT_BEFORE)                          },
	{ "y",                  ACTION(OPERATOR_YANK)                       }
		};
		memcpy(bindings, initValue, sizeof(initValue));
	}
} bindings_operators;

struct BindingsOperatorOptions {
	KeyBinding bindings[100];
	BindingsOperatorOptions() {
		static const KeyBinding initValue[] = {
		{ "v",                  ACTION(MOTION_CHARWISE)                     },
		{ "V",                  ACTION(MOTION_LINEWISE)                     }
		};
		memcpy(bindings, initValue, sizeof(initValue));
	}
    const KeyBinding& operator[](size_t idx) const{
        return bindings[idx];
    }
} bindings_operator_options;

struct BindingsNormal {
	KeyBinding bindings[100];
	BindingsNormal() {
		static const KeyBinding initValue[] = {
	{ "a",                  ACTION(APPEND_CHAR_NEXT)                    },
	{ "A",                  ACTION(APPEND_LINE_END)                     },
	{ "@",                  ACTION(MACRO_REPLAY)                        },
	{ ":",                  ACTION(PROMPT_SHOW)                         },
	{ ".",                  ACTION(REPEAT)                              },
	{ "~",                  ALIAS("<vis-operator-case-swap>ll")         },
	{ "<C-a>",              ACTION(NUMBER_INCREMENT)                    },
	{ "C",                  ALIAS("c$")                                 },
	{ "<C-b>",              ALIAS("<PageUp>")                           },
	{ "<C-c>",              ACTION(CURSORS_REMOVE_COLUMN)               },
	{ "<C-d>",              ACTION(CURSORS_NEXT)                        },
	{ "<C-e>",              ACTION(WINDOW_SLIDE_UP)                     },
	{ "<C-f>",              ALIAS("<PageDown>")                         },
	{ "<C-i>",              ACTION(JUMPLIST_NEXT)                       },
	{ "<C-j>",              ACTION(CURSORS_NEW_LINE_BELOW)              },
	{ "<C-k>",              ACTION(CURSORS_NEW_LINE_ABOVE)              },
	{ "<C-l>",              ACTION(CURSORS_REMOVE_COLUMN_EXCEPT)        },
	{ "<C-n>",              ACTION(CURSOR_SELECT_WORD)                  },
	{ "<C-o>",              ACTION(JUMPLIST_PREV)                       },
	{ "<C-p>",              ACTION(CURSORS_REMOVE_LAST)                 },
	{ "<C-r>",              ACTION(REDO)                                },
	{ "<C-u>",              ACTION(CURSORS_PREV)                        },
	{ "<C-w><Backspace>",   ALIAS("<C-w>k")                             },
	{ "<C-w>c",             ALIAS(":q<Enter>")                          },
	{ "<C-w><C-h>",         ALIAS("<C-w>k")                             },
	{ "<C-w><C-j>",         ALIAS("<C-w>j")                             },
	{ "<C-w><C-k>",         ALIAS("<C-w>k")                             },
	{ "<C-w><C-l>",         ALIAS("<C-w>j")                             },
	{ "<C-w><C-w>",         ALIAS("<C-w>j")                             },
	{ "<C-w>gf",            ACTION(OPEN_FILE_UNDER_CURSOR_NEW_WINDOW)   },
	{ "<C-w>h",             ALIAS("<C-w>k")                             },
	{ "<C-w>j",             ACTION(WINDOW_NEXT)                         },
	{ "<C-w>k",             ACTION(WINDOW_PREV)                         },
	{ "<C-w>l",             ALIAS("<C-w>j")                             },
	{ "<C-w>n",             ALIAS(":open<Enter>")                       },
	{ "<C-w>s",             ALIAS(":split<Enter>")                      },
	{ "<C-w>v",             ALIAS(":vsplit<Enter>")                     },
	{ "<C-w>w",             ALIAS("<C-w>j")                             },
	{ "<C-x>",              ACTION(NUMBER_DECREMENT)                    },
	{ "<C-y>",              ACTION(WINDOW_SLIDE_DOWN)                   },
	{ "D",                  ALIAS("d$")                                 },
	{ "<Delete>",           ALIAS("x")                                  },
	{ "<Escape>",           ACTION(CURSORS_REMOVE_ALL)                  },
	{ "<F1>",               ALIAS(":help<Enter>")                       },
	{ "ga",                 ACTION(UNICODE_INFO)                        },
	{ "g,",                 ACTION(CHANGELIST_NEXT)                     },
	{ "g;",                 ACTION(CHANGELIST_PREV)                     },
	{ "g-",                 ACTION(EARLIER)                             },
	{ "g+",                 ACTION(LATER)                               },
	{ "gf",                 ACTION(OPEN_FILE_UNDER_CURSOR)              },
	{ "gn",                 ALIAS("vgn")                                },
	{ "gN",                 ALIAS("vgN")                                },
	{ "gv",                 ACTION(SELECTION_RESTORE)                   },
	{ "I",                  ACTION(INSERT_LINE_START)                   },
	{ "i",                  ACTION(MODE_INSERT)                         },
	{ "J",                  ACTION(JOIN_LINE_BELOW)                     },
	{ "m",                  ACTION(MARK_SET)                            },
	{ "<M-C-j>",            ACTION(CURSORS_NEW_LINE_BELOW_LAST)         },
	{ "<M-C-k>",            ACTION(CURSORS_NEW_LINE_ABOVE_FIRST)        },
	{ "O",                  ACTION(OPEN_LINE_ABOVE)                     },
	{ "o",                  ACTION(OPEN_LINE_BELOW)                     },
	{ "q",                  ACTION(MACRO_RECORD)                        },
	{ "R",                  ACTION(MODE_REPLACE)                        },
	{ "r",                  ACTION(REPLACE_CHAR)                        },
	{ "S",                  ALIAS("^c$")                                },
	{ "s",                  ALIAS("cl")                                 },
	{ "<Tab>",              ACTION(CURSORS_ALIGN)                       },
	{ "u",                  ACTION(UNDO)                                },
	{ "v",                  ACTION(MODE_VISUAL)                         },
	{ "V",                  ACTION(MODE_VISUAL_LINE)                    },
	{ "x",                  ACTION(DELETE_CHAR_NEXT)                    },
	{ "X",                  ALIAS("dh")                                 },
	{ "Y",                  ALIAS("y$")                                 },
	{ "zb",                 ACTION(WINDOW_REDRAW_BOTTOM)                },
	{ "ZQ",                 ALIAS(":q!<Enter>")                         },
	{ "zt",                 ACTION(WINDOW_REDRAW_TOP)                   },
	{ "zz",                 ACTION(WINDOW_REDRAW_CENTER)                },
	{ "ZZ",                 ALIAS(":wq<Enter>")                         }
		};
	memcpy(bindings, initValue, sizeof(initValue));
	}
} bindings_normal;

struct BindingsVisual {
	KeyBinding bindings[100];
	BindingsVisual() {
		static const KeyBinding initValue[] = {
	{ "A",                  ACTION(CURSORS_NEW_LINES_END)               },
	{ ":",                  ACTION(PROMPT_SHOW)                         },
	{ "-",                  ACTION(SELECTIONS_ROTATE_LEFT)              },
	{ "+",                  ACTION(SELECTIONS_ROTATE_RIGHT)             },
	{ "\\",                 ACTION(SELECTIONS_TRIM)                     },
	{ "<",                  ALIAS("<vis-operator-shift-left>gv")        },
	{ ">",                  ALIAS("<vis-operator-shift-right>gv")       },
	{ "<Backspace>",        ALIAS("d")                                  },
	{ "<C-b>",              ALIAS("<PageUp>")                           },
	{ "<C-c>",              ACTION(CURSORS_REMOVE_COLUMN)               },
	{ "<C-d>",              ACTION(CURSORS_NEXT)                        },
	{ "<C-f>",              ALIAS("<PageDown>")                         },
	{ "<C-h>",              ALIAS("<Backspace>")                        },
	{ "<C-j>",              ALIAS("<C-d>")                              },
	{ "<C-k>",              ALIAS("<C-u>")                              },
	{ "<C-l>",              ACTION(CURSORS_REMOVE_COLUMN_EXCEPT)        },
	{ "<C-n>",              ACTION(CURSORS_NEW_MATCH_NEXT)              },
	{ "<C-p>",              ACTION(CURSORS_REMOVE_LAST)                 },
	{ "<C-u>",              ACTION(CURSORS_PREV)                        },
	{ "<C-x>",              ACTION(CURSORS_NEW_MATCH_SKIP)              },
	{ "<Delete>",           ALIAS("<Backspace>")                        },
	{ "<Escape>",           ACTION(MODE_NORMAL)                         },
	{ "I",                  ACTION(CURSORS_NEW_LINES_BEGIN)             },
	{ "J",                  ACTION(JOIN_LINES)                          },
	{ "o",                  ACTION(SELECTION_FLIP)                      },
	{ "r",                  ALIAS("c")                                  },
	{ "s",                  ALIAS("c")                                  },
	{ "<S-Tab>",            ACTION(CURSORS_ALIGN_INDENT_RIGHT)          },
	{ "<Tab>",              ACTION(CURSORS_ALIGN_INDENT_LEFT)           },
	{ "V",                  ACTION(MODE_VISUAL_LINE)                    },
	{ "v",                  ALIAS("<Escape>")                           },
	{ "x",                  ALIAS("d")                                  }
		};
	memcpy(bindings, initValue, sizeof(initValue));
	}
} bindings_visual;

struct BindingsVisualLine {
	KeyBinding bindings[100];
	BindingsVisualLine() {
		static const KeyBinding initValue[] = {
	{ "v",                  ACTION(MODE_VISUAL)                         },
	{ "V",                  ACTION(MODE_NORMAL)                         }
		};
		memcpy(bindings, initValue, sizeof(initValue));
	}
} bindings_visual_line;

struct BindingsReadline {
		KeyBinding bindings[100];
		BindingsReadline(){
			static const KeyBinding initValue[] = {
	{ "<Backspace>",        ACTION(DELETE_CHAR_PREV)                    },
	{ "<C-c>",              ALIAS("<Escape>")                           },
	{ "<C-d>",              ACTION(DELETE_CHAR_NEXT)                    },
	{ "<C-h>",              ALIAS("<Backspace>")                        },
	{ "<C-u>",              ACTION(DELETE_LINE_BEGIN)                   },
	{ "<C-v>",              ACTION(INSERT_VERBATIM)                     },
	{ "<C-w>",              ACTION(DELETE_WORD_PREV)                    },
	{ "<Delete>",           ACTION(DELETE_CHAR_NEXT)                    },
	{ "<Escape>",           ACTION(MODE_NORMAL)                         }
	};

		memcpy(bindings, initValue, sizeof(initValue));
	}
} bindings_readline;

const std::array<KeyBinding, 15> bindings_insert{{
		{ "<C-d>",              ALIAS("<Escape><<i")                        },
		{ "<C-i>",              ALIAS("<Tab>")                              },
		{ "<C-j>",              ALIAS("<Enter>")                            },
		{ "<C-n>",              ACTION(COMPLETE_WORD)                       },
		{ "<C-x><C-f>",         ACTION(COMPLETE_FILENAME)                   },
		{ "<C-m>",              ALIAS("<Enter>")                            },
		{ "<C-o>",              ACTION(MODE_OPERATOR_PENDING)               },
		{ "<C-r>",              ACTION(INSERT_REGISTER)                     },
		{ "<C-t>",              ALIAS("<Escape>>>i")                        },
		{ "<C-x><C-e>",         ACTION(WINDOW_SLIDE_UP)                     },
		{ "<C-x><C-y>",         ACTION(WINDOW_SLIDE_DOWN)                   },
		{ "<Enter>",            ACTION(INSERT_NEWLINE)                      },
		{ "<Escape>",           ACTION(MODE_NORMAL)                         },
		{ "<S-Tab>",            ACTION(CURSORS_ALIGN_INDENT_LEFT)           },
		{ "<Tab>",              ACTION(INSERT_TAB)                          }
}};

const std::array<KeyBinding, 15> bindings_replace{{
		{ "<C-d>",              ALIAS("<Escape><<i")                        },
		{ "<C-i>",              ALIAS("<Tab>")                              },
		{ "<C-j>",              ALIAS("<Enter>")                            },
		{ "<C-n>",              ACTION(COMPLETE_WORD)                       },
		{ "<C-x><C-f>",         ACTION(COMPLETE_FILENAME)                   },
		{ "<C-m>",              ALIAS("<Enter>")                            },
		{ "<C-o>",              ACTION(MODE_OPERATOR_PENDING)               },
		{ "<C-r>",              ACTION(INSERT_REGISTER)                     },
		{ "<C-t>",              ALIAS("<Escape>>>i")                        },
		{ "<C-x><C-e>",         ACTION(WINDOW_SLIDE_UP)                     },
		{ "<C-x><C-y>",         ACTION(WINDOW_SLIDE_DOWN)                   },
		{ "<Enter>",            ACTION(INSERT_NEWLINE)                      },
		{ "<Escape>",           ACTION(MODE_NORMAL)                         },
		{ "<S-Tab>",            ACTION(CURSORS_ALIGN_INDENT_LEFT)           },
		{ "<Tab>",              ACTION(INSERT_TAB)                          }
}};

/* For each mode we list a all key bindings, if a key is bound in more than
 * one array the first definition is used and further ones are ignored. */




const std::array<KeyBinding, 30> default_bindings = concat(bindings_replace, bindings_insert);

// struct DefaultBindings {
//
// 	std::map<VisMode, std::array<KeyBinding, 100>> bindings;
//
// 	DefaultBindings() {
//
// 	// std::array<KeyBinding> bindings[VIS_MODE_OPERATOR_PENDING].assign(
// 	// 		bindings_operator_options, bindings_operator_options.bindings + sizeof(bindings_operator_options) / sizeof(bindings_operator_options[0])
// 		// );
// 	// 	bindings_operator_options.bindings,
// 	// 	bindings_operator_options.bindings + sizeof(bindings_operator_options) / sizeof(bindings_operator_options[0])
// 	// };
// 	bindings[VIS_MODE_OPERATOR_PENDING].push_back(
// 		bindings[VIS_MODE_OPERATOR_PENDING].end(),
// 		bindings_operator_options[0],
// 		sizeof(bindings_operator_options) / sizeof(KeyBinding)
// 	);
// 	// 		(const std::vector<*KeyBinding>){
// 	// 	bindings_operator_options,
// 	// 	bindings_operators,
// 	// 	bindings_textobjects,
// 	// 	bindings_motions,
// 	// 	bindings_basic,
// 	// 	NULL
// 	// }},
// 	// {VIS_MODE_NORMAL, (const std::vector<KeyBinding*>){
// 	// 	bindings_normal,
// 	// 	bindings_operators,
// 	// 	bindings_motions,
// 	// 	bindings_basic,
// 	// 	NULL,
// 	// 									   }},
// 	// {VIS_MODE_VISUAL, (const std::vector<KeyBinding*>){
// 	// 	bindings_visual,
// 	// 	bindings_textobjects,
// 	// 	bindings_operators,
// 	// 	bindings_motions,
// 	// 	bindings_basic,
// 	// 	NULL,
// 	// }},
// 	// {VIS_MODE_VISUAL_LINE, (const std::vector<KeyBinding*>){
// 	// 	bindings_visual_line,
// 	// 	NULL,
// 	// }},
// 	// {VIS_MODE_INSERT, (const std::vector<KeyBinding*>){
// 	// 	bindings_insert,
// 	// 	bindings_readline,
// 	// 	bindings_basic,
// 	// 	NULL,
// 	// }},
// 	// {VIS_MODE_REPLACE, (const std::vector<KeyBinding*>){
// 	// 	bindings_replace,
// 	// 	NULL,
// 	// }}
// 	}
// } default_bindings;