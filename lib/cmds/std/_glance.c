// _glance.c
// shortdesc, obvious exits, and inventory of room
// Shakespeare/Empacher@TMI-2
//
// LCARS-MUD: takes an optional direction. "glance west" gives the brief
// view of whatever lies west, the same way "look west" gives the full one.

#include <commands.h>
#include <mudlib.h>

inherit DAEMON ;

string help();

// Single letters reach movement as global aliases ("e" -> "go east"),
// which expand before a command runs, so glance never sees them. Expand
// them here instead.
private mapping dir_abbrev = ([
	"n" : "north",     "s"  : "south",     "e"  : "east",      "w" : "west",
	"ne": "northeast", "nw" : "northwest", "se" : "southeast",
	"sw": "southwest", "u"  : "up",        "d"  : "down",
]);

private string expand_dir(string str) {
	if (dir_abbrev[str]) return dir_abbrev[str];
	return str;
}

int cmd_glance(string str) {
	int oldbrief;
	mapping exits;
	object env;

	if (str) {
		str = expand_dir(str);
		env = environment(this_player());
		exits = env ? env->query("exits") : 0;
		if (!exits || !exits[str]) {
			notify_fail("You cannot glance that way.\n");
			return 0;
		}
	}

	oldbrief = this_player()->query("brief");
	this_player()->set("brief",1);
	this_player()->set_temp("force_to_look",1);
	CMD_LOOK->cmd_look(str);
	this_player()->delete_temp("force_to_look");
	this_player()->set("brief",oldbrief);
return 1;
}

string help() {
return(@HELP
Syntax: glance
        glance <direction>

This command gives you a brief glance at the room, providing the short
room description, obvious exits and objects within.

Given a direction, it glances that way instead, showing the brief view
of the room beyond that exit.

See also: look, brief, exits
HELP
  );
}
