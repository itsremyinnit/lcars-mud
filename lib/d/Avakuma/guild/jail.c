// /d/Avakuma/guild/jail.c
// Two ways in. Walk in wearing a green ring and you are a visitor: south
// works. Get thrown in by the guard and you are shackled: south is refused
// until a Framsburg barracks guard comes for you.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

#define SENTENCE 150   // seconds

void create() {
    ::create();
    set("short", "Framsburg's jail");
    set("long", @EndText
    The jail is anything but spectacular. There is a bed to rest on for
as long as you are here, and a small pile of droppings in the corner. The
walls, the ceiling and the floor have nothing on them worth the name of
decoration. Whoever built this place did not want anyone comfortable in
it. From time to time a guard turns and glances in through the bars. There
is nothing for a prisoner to do here but wait.
EndText
    );
    set("item_desc", ([
        "ball" : @EndText
    A heavy iron mass roughly the size of a ship's cannonball, cast
around a thick chain that is set firmly into the cell wall, which puts
paid to any hope of escape. It does not give enough slack to lie down
comfortably or to make many simple movements, which you consider cruel
and unusual.
EndText
        ,
        "shackles" : @EndText
    A heavy iron mass roughly the size of a ship's cannonball, cast
around a thick chain that is set firmly into the cell wall, which puts
paid to any hope of escape. It does not give enough slack to lie down
comfortably or to make many simple movements, which you consider cruel
and unusual.
EndText
        ,
        "door" : @EndText
    A metal door with a barred window, leading back to the entrance hall.
EndText
        ,
        "walls" : @EndText
    Very mundane, being ordinary stonework meeting at perfect angles. The
corners where the walls meet the ceiling and the floor are all dark. One
of them has the droppings in it.
EndText
        ,
        "bed" : @EndText
    A bed, in the sense that it is off the floor. Nobody expected anyone
to sleep well on it.
EndText
        ,
        "droppings" : @EndText
    In the corner, and not recent. Nobody has been keen to deal with
them.
EndText
        ,
        "bars" : @EndText
    Set into the window of the door, at about the height of a guard's
face.
EndText
        ,
    ]));
    set("exits", ([
        "south" : "/d/Avakuma/guild/entrance_hall",
    ]));
    set("exit_order", ({ "south" }));
    set("pre_exit_func/south", "leaving");
}

// Called by the guard when someone is thrown in rather than walking in.
void sentence(object who) {
    if (!who) return;
    who->set("avakuma_jailed", time() + SENTENCE);
    call_out("release", SENTENCE, who);
}

void release(object who) {
    if (!who || !who->query("avakuma_jailed")) return;
    who->delete("avakuma_jailed");
    if (environment(who) == this_object())
        tell_object(who,
            "\nA guard from the Framsburg barracks comes to let you out.\n");
}

int leaving() {
    object who = this_player();

    if (!who->query("avakuma_jailed")) return 0;
    if (time() >= (int)who->query("avakuma_jailed")) {
        who->delete("avakuma_jailed");
        return 0;
    }
    write(
"    Even were the door not shut against you, you would not get very \n"
"far, being shackled with a heavy iron ball as you are. You really \n"
"have no choice other than to wait for your sentence to expire.\n");
    return 1;
}
