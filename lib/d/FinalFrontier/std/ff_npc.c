// /d/FinalFrontier/std/ff_npc.c
// Crew. Same typed-chat design as the Avakuma NPC base: lines declare
// whether they are speech or action so the message class is right.
#include <mudlib.h>
#include "/d/FinalFrontier/frontier.h"

inherit MONSTER;

void create() {
    ::create();
    seteuid(getuid());
    set("frontier", 1);
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("bulk", 250);
}

void set_chat(int chance, mixed *lines) {
    set("chat_chance", chance);
    set("chat_output", lines);
}

void set_inquiry(mapping topics, string fallback) {
    set("inquiry", topics);
    if (fallback) set("inquiry_default", fallback);
}

void set_range(int speed, string *rooms) {
    set("moving", 1);
    set("speed", speed);
    set("range", rooms);
    call_out("move_around", speed);
}

void emit_line(mixed line) {
    object env;
    string msg;

    env = environment();
    if (!env || !line) return;
    if (stringp(line)) { tell_room(env, line); return; }
    if (!pointerp(line) || sizeof(line) < 2) return;

    if (line[0] == "say" && sizeof(line) >= 3) {
        msg = (string)query("cap_name") + " " + line[1] + ": " + line[2] + "\n";
        message("say", msg, env);
        return;
    }
    if (line[0] == "emote") {
        msg = replace_string(line[1], "$N", (string)query("cap_name")) + "\n";
        message("emote", msg, env);
        return;
    }
    tell_room(env, line[sizeof(line) - 1] + "\n");
}

void monster_chat() {
    mixed *chats;

    if (attackers && sizeof(attackers)) chats = query("att_chat_output");
    else chats = query("chat_output");
    if (!chats || !sizeof(chats)) return;
    emit_line(chats[random(sizeof(chats))]);
}

void move_around() {
    mapping exits, doors;
    string *dirs, *range;
    string dir, dest;
    object env;

    if (query("moving") == 1) set("moving", -1);
    env = environment();
    if (!env || !env->query("exits")) return;
    call_out("move_around", query("speed"));
    if (attackers && sizeof(attackers)) return;

    exits = env->query("exits");
    dirs = keys(exits);
    if (!dirs || !sizeof(dirs)) return;

    dir = dirs[random(sizeof(dirs))];
    dest = exits[dir];
    if (dest == base_name(env)) return;

    range = query("range");
    if (range && member_array(dest, range) == -1) return;

    doors = env->query("doors");
    if (doors && sizeof(doors) && doors[dir] && doors[dir]["status"] != "open")
        return;

    move_player(dest, query_mout(dir));
}
