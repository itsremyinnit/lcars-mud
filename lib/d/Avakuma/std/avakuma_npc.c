// /d/Avakuma/std/avakuma_npc.c
// Base for every NPC in Avakuma.
//
// WHY THIS EXISTS: stock /std/monster.c's monster_chat() picks a random
// pre-formatted string and emits it with tell_room(), which tags every
// line with the message class "tell_room". That makes an NPC's speech
// indistinguishable from its emotes to anything downstream, so colour
// coding, ignore handling and anything else keyed on message class
// cannot tell them apart. On the original T2T this meant every NPC had
// to be retuned by hand when colours were added.
//
// Here, chat lines are typed and emitted with the matching class:
//
//   set_chat(10, ({
//       ({ "say",   "says",    "I KNOW there's got to be a way..." }),
//       ({ "say",   "murmurs", "I can't believe I was injured by that Orc." }),
//       ({ "emote", "$N ponders something." }),
//   }));
//
// "say" lines go out as class "say" and render as
//     Clark says: I KNOW there's got to be a way...
// with the verb under the NPC's control, so murmurs, whispers and yells
// all stay available and still classify as speech, which is what they are.
//
// "emote" lines go out as class "emote", the same class player emotes
// use. $N is replaced with the NPC's capitalised name.
//
// Plain strings are still accepted and fall through to the stock
// tell_room behaviour, so an NPC can be ported a line at a time.

#include <mudlib.h>
#include "/d/Avakuma/avakuma.h"

inherit MONSTER;

void create() {
    ::create();
    seteuid(getuid());
    set("avakuma", 1);
}

// chance is a percentage rolled each heart beat by /std/monster.c.
void set_chat(int chance, mixed *lines) {
    set("chat_chance", chance);
    set("chat_output", lines);
}

// Lines used while the NPC is in combat.
void set_combat_chat(int chance, mixed *lines) {
    set("chat_chance", chance);
    set("att_chat_output", lines);
}

void emit_line(mixed line) {
    object env;
    string msg;

    env = environment();
    if (!env || !line) return;

    // Stock behaviour for un-ported lines.
    if (stringp(line)) {
        tell_room(env, line);
        return;
    }
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
    // Unknown type: do not guess, and do not mislabel it.
    tell_room(env, line[sizeof(line) - 1] + "\n");
}

// Dialogue. /cmds/std/_ask.c reads "inquiry" for topics and
// "inquiry_default" for the brush-off when the topic is unknown.
void set_inquiry(mapping topics, string fallback) {
    set("inquiry", topics);
    if (fallback) set("inquiry_default", fallback);
}

// Wandering, bounded to a whitelist of rooms.
//
// /std/monster.c's move_around() supports a "forbidden_rooms" blacklist,
// which is the wrong shape here: keeping a townsperson out of the orc camp
// would mean listing every room they must not enter, and every room added
// later. This takes the list of rooms they MAY enter instead, so a new
// room is out of bounds by default.
//
//   set_range(12, ({ "/d/Avakuma/framsburg/road_north",
//                    "/d/Avakuma/framsburg/road_south" }));
//
// speed is seconds between moves.
void set_range(int speed, string *rooms) {
    set("moving", 1);
    set("speed", speed);
    set("range", rooms);
    call_out("move_around", speed);
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

    // Sealed exits point back at their own room; going nowhere loudly
    // is worse than staying put.
    if (dest == base_name(env)) return;

    range = query("range");
    if (range && member_array(dest, range) == -1) return;

    // Shut doors stay shut. An NPC opening doors behind itself is a
    // separate decision from an NPC wandering.
    doors = env->query("doors");
    if (doors && sizeof(doors) && doors[dir] && doors[dir]["status"] != "open")
        return;

    move_player(dest, query_mout(dir));
}

void monster_chat() {
    mixed *chats;

    if (attackers && sizeof(attackers))
        chats = query("att_chat_output");
    else
        chats = query("chat_output");

    if (!chats || !sizeof(chats)) return;
    emit_line(chats[random(sizeof(chats))]);
}
