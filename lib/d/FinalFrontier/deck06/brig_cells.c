// /d/FinalFrontier/deck06/brig_cells.c
// Three cells with working forcefields.
//
//   status                   list the cells
//   enter cell <n>           step in yourself (field must be down)
//   activate [cell] [<n>]    raise a field; number optional when only one
//                            cell is a candidate
//   deactivate [cell] [<n>]  drop a field, same rule
//   brig <person> [<n>]      put somebody in a cell and raise the field
//   release <person|cell>    drop the field and let them out
//
// Occupancy is pruned on every command, because a prisoner can leave by
// means this room does not control: a wizard's recall, a goto, a summon.
// What is tracked here is a hint, never truth.
//
// _look.c reads query("long") directly and query is nomask, so there is
// no long() to override. The property is rewritten instead whenever
// occupancy or a field changes.
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

#define CELLS 3

nosave mapping fields;
nosave mapping occupants;
nosave string base_long;

private void refresh_long();
private void prune();
private int cell_of(object who);
private int parse_cell(string str, int want_up);

void create() {
    ::create();
    set("short", "Detention Cells");
    base_long =
"    A short hall with three cells along the outboard wall, each a bare\n"
"compartment with a bench, a recessed light, and no door. The doorway of\n"
"each is framed by emitter strips top and bottom. When a field is up it is\n"
"visible only as a faint vertical shimmer and a low hum you stop hearing\n"
"after a minute. There is a control panel on the inboard wall listing the\n"
"three cells and their status.\n";
    set("long", base_long);
    set("item_desc", ([
        "cells" : @EndText
    Three, identical, bare: a moulded bench, a light, a blank wall. There
is nothing in any of them to take apart, which is the entire design
philosophy.
EndText
        ,
        "emitters" : @EndText
    Strips set into the head and foot of each doorway. Inactive they are
matte grey and easy to miss.
EndText
        ,
        "panel" : @EndText
    A control panel listing cells one through three and their status.
Below it: activate, deactivate, brig, release.
EndText
        ,
        "bench" : "    Moulded into the wall of each cell. It is not comfortable and is not meant to be.\n",
    ]));
    set("exits", ([ "out" : "/d/FinalFrontier/deck06/brig_entry" ]));
    set("exit_order", ({ "out" }));
    set("pre_exit_func/out", "leaving");
}

void init() {
    add_action("do_status", "status");
    add_action("do_activate", "activate");
    add_action("do_deactivate", "deactivate");
    add_action("do_enter", "enter");
    add_action("do_brig", "brig");
    add_action("do_release", "release");
}

private void prune() {
    int i;
    object who;

    if (!occupants) return;
    for (i = 1; i <= CELLS; i++) {
        who = occupants[""+i];
        if (!who) continue;
        if (environment(who) != this_object()) {
            map_delete(occupants, ""+i);
            if (who) who->delete("ff_cell");
        }
    }
}

private void refresh_long() {
    string res;
    int i;

    res = base_long;
    for (i = 1; i <= CELLS; i++)
        if (occupants && occupants[""+i])
            res += "    " + (string)occupants[""+i]->query("cap_name") +
                   " is in cell " + i +
                   ((fields && fields[""+i]) ? ", behind a live field.\n"
                                             : ".\n");
    set("long", res);
}

private int cell_of(object who) {
    int i;

    if (!occupants) return 0;
    for (i = 1; i <= CELLS; i++)
        if (occupants[""+i] == who) return i;
    return 0;
}

private int parse_cell(string str, int want_up) {
    int n, i, found, count;

    if (str && sscanf(str, "cell %d", n) == 1) return n;
    if (str && sscanf(str, "%d", n) == 1) return n;
    if (str && str != "field" && str != "the field") return -1;

    found = 0; count = 0;
    for (i = 1; i <= CELLS; i++) {
        if (want_up && fields && fields[""+i]) { found = i; count++; }
        if (!want_up && (!fields || !fields[""+i])) { found = i; count++; }
    }
    if (count == 1) return found;
    return 0;
}

int do_status(string str) {
    int i;

    prune();
    refresh_long();
    write("Detention control:\n");
    for (i = 1; i <= CELLS; i++)
        write(sprintf("  Cell %d: %s%s\n", i,
              (fields && fields[""+i]) ? "field up  " : "field down",
              (occupants && occupants[""+i]) ?
                  "  occupied by " + (string)occupants[""+i]->query("cap_name")
                : ""));
    return 1;
}

int do_activate(string str) {
    int n;

    prune();
    if (cell_of(this_player())) {
        write("You cannot reach the panel from inside a cell.\n");
        return 1;
    }
    n = parse_cell(str, 0);
    if (n == -1 || n < 0 || n > CELLS) {
        notify_fail("Activate which cell? There are " + CELLS + ".\n");
        return 0;
    }
    if (!n) { notify_fail("Which cell? More than one is down.\n"); return 0; }
    if (!fields) fields = ([ ]);
    if (fields[""+n]) {
        write("Cell " + n + "'s field is already up.\n");
        return 1;
    }
    fields[""+n] = 1;
    refresh_long();
    write("The emitters in cell " + n + " come up with a low hum.\n");
    say("The emitters in cell " + n + " come up with a low hum.\n");
    return 1;
}

int do_deactivate(string str) {
    int n;

    prune();
    if (cell_of(this_player())) {
        write("You cannot reach the panel from inside a cell.\n");
        return 1;
    }
    n = parse_cell(str, 1);
    if (n == -1 || n < 0 || n > CELLS) {
        notify_fail("Deactivate which cell? There are " + CELLS + ".\n");
        return 0;
    }
    if (!n) {
        notify_fail("Which cell? No field is up, or more than one is.\n");
        return 0;
    }
    if (!fields || !fields[""+n]) {
        write("Cell " + n + "'s field is already down.\n");
        return 1;
    }
    map_delete(fields, ""+n);
    refresh_long();
    write("The field in cell " + n + " drops.\n");
    say("The field in cell " + n + " drops.\n");
    return 1;
}

int do_enter(string str) {
    int n;

    prune();
    n = parse_cell(str, 0);
    if (n < 1 || n > CELLS) {
        notify_fail("Enter which cell? There are " + CELLS + ".\n");
        return 0;
    }
    if (fields && fields[""+n]) {
        write("The field is up. You would not get through it.\n");
        return 1;
    }
    if (!occupants) occupants = ([ ]);
    if (occupants[""+n]) { write("Somebody is already in that one.\n"); return 1; }
    if (cell_of(this_player()))
        map_delete(occupants, ""+cell_of(this_player()));
    occupants[""+n] = this_player();
    this_player()->set("ff_cell", n);
    refresh_long();
    write("You step into cell " + n + ".\n");
    say((string)this_player()->query("cap_name") + " steps into cell " + n + ".\n");
    return 1;
}

int do_brig(string str) {
    object who;
    string name;
    int n, i;

    prune();
    if (!str) {
        notify_fail("Brig whom? Syntax: brig <person> [cell]\n");
        return 0;
    }
    if (sscanf(str, "%s %d", name, n) != 2) { name = str; n = 0; }

    who = present(name, this_object());
    if (!who || !living(who)) { notify_fail("They are not here.\n"); return 0; }
    if (who == this_player()) {
        notify_fail("Use 'enter cell <n>' for that.\n");
        return 0;
    }

    if (!fields) fields = ([ ]);
    if (!occupants) occupants = ([ ]);

    if (!n) {
        for (i = 1; i <= CELLS; i++)
            if (!occupants[""+i] && !fields[""+i]) { n = i; break; }
        if (!n) { write("Every cell is occupied or sealed.\n"); return 1; }
    }
    if (n < 1 || n > CELLS) {
        notify_fail("There are " + CELLS + " cells.\n");
        return 0;
    }
    if (occupants[""+n]) { write("Cell " + n + " is occupied.\n"); return 1; }

    occupants[""+n] = who;
    who->set("ff_cell", n);
    fields[""+n] = 1;
    refresh_long();

    write("You put " + (string)who->query("cap_name") + " in cell " + n +
          " and bring the field up.\n");
    tell_object(who, "You are put into cell " + n +
        ", and the emitters come up behind you with a low hum.\n");
    say((string)this_player()->query("cap_name") + " puts " +
        (string)who->query("cap_name") + " in cell " + n +
        ". The field comes up.\n", ({ this_player(), who }));
    return 1;
}

int do_release(string str) {
    object who;
    int n;

    prune();
    n = parse_cell(str, 1);
    if (n < 1 && str) {
        who = present(str, this_object());
        if (who) n = cell_of(who);
    }
    if (n < 1 || n > CELLS) {
        notify_fail("Release whom, or which cell?\n");
        return 0;
    }
    if (fields) map_delete(fields, ""+n);
    who = occupants ? occupants[""+n] : 0;
    if (who) {
        who->delete("ff_cell");
        tell_object(who, "The field drops. You are free to go.\n");
    }
    if (occupants) map_delete(occupants, ""+n);
    refresh_long();
    write("Cell " + n + " is open.\n");
    return 1;
}

int leaving() {
    int n;

    n = cell_of(this_player());
    if (!n) return 0;
    if (fields && fields[""+n]) {
        write("The field holds. You are not going anywhere.\n");
        return 1;
    }
    map_delete(occupants, ""+n);
    this_player()->delete("ff_cell");
    refresh_long();
    return 0;
}
