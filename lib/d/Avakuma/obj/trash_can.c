// /d/Avakuma/obj/trash_can.c
// Put something in, it is gone. Stands in the shops and the kitchen.
//
// receive_object() is the hook move() calls on the destination to ask
// whether an object is welcome. Accepting and then destroying on a
// zero-delay callout lets the move finish first; destructing inside
// receive_object would pull the object out from under the mover.
#include <mudlib.h>
inherit CONTAINER;

void create() {
    ::create();
    seteuid(getuid());
    set("id", ({ "can", "trash can", "trash", "trashcan", "bin" }));
    set("short", "A trash can");
    set_open_long(@EndText
     You are looking at a tall, dark, and ugly trash can. It has a big sign
on it "DON'T THROW AWAY ANYTHING YOU WANT!  STUFF WILL BE DESTROYED!"
To throw something away, put it in the trash can.
EndText
    );
    set("bulk", 400);
    set("mass", 3000);
    set("capacity", 1000000);
    set("volume", 1000000);
    set("no_get", 1);
    set("prevent_get", 1);
}

void burn_one(object ob) {
    object env;

    if (!ob) return;
    if (!(int)"/adm/daemons/disposal_d"->kill_object(ob)) return;

    env = environment(this_object());
    if (env)
        tell_room(env,
            "From deep inside the trash can you hear a muffled BOOM! " +
            "It is then silent.\n");
}

void burn_it() {
    object env;
    int burned;

    // The can cannot destroy what it does not own; DISPOSAL_D can.
    // See the header of /adm/daemons/disposal_d.c.
    burned = (int)"/adm/daemons/disposal_d"->empty(this_object());
    if (!burned) return;

    env = environment(this_object());
    if (env)
        tell_room(env,
            "From deep inside the trash can you hear a muffled BOOM! " +
            "It is then silent.\n");
}

int receive_object(object ob) {
    if (!ob) return 0;
    // Never eat a living thing, and never eat something bound to its
    // bearer: a ring that cannot be dropped should not be binnable.
    if (living(ob)) return 0;
    if (ob->query("prevent_drop")) return 0;
    // Refusing the move and destroying the object here gives T2T's
    // behaviour: the item never lands in the can, so the mudlib's
    // "You put X in Y" line is replaced by a bare "Ok." and the can
    // never shows contents. Destroying during the move rather than on
    // a callout is what removes the timing artifact.
    if (this_player())
        tell_object(this_player(),
            "You feel a lot better by helping the environment.\n");
    call_out("burn_one", 0, ob);
    return 1;
}
