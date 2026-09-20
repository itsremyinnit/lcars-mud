// /d/Avakuma/framsburg/obj/stew.c
// Lidded, so unlike the beer and whiskey this can go in a pack and be
// carried off to eat later.
#include <mudlib.h>
inherit OBJECT;

void create() {
    set("id", ({ "stew", "bowl", "bowl with a lid" }));
    set("short", "A bowl with a lid");
    set("long", @EndText
    The stew is made of various kinds of vegetables and a couple of types
of meat.  From the thickness of the sauce, you can tell it has been 
cooking for quite some time.  If you think the stew has gone bad, you can
always dump it out.
EndText
    );
    set("bulk", 30); set("mass", 200);
    set("value", ({ 0, "copper" }));
}

void init() {
    add_action("do_eat", "eat");
    add_action("do_dump", "dump");
}

private void leave_bowl() {
    object bowl;

    bowl = clone_object("/d/Avakuma/framsburg/obj/stew_bowl");
    if (bowl) bowl->move(this_player());
    "/adm/daemons/disposal_d"->kill_object(this_object());
}

int do_eat(string str) {
    if (!str || !id(str)) return 0;
    if (environment() != this_player()) {
        notify_fail("You are not holding that.\n");
        return 0;
    }
    write("You lap up the stew like a dog.\n");
    say((string)this_player()->query("cap_name") + " eats a bowl of stew.\n");
    leave_bowl();
    return 1;
}

int do_dump(string str) {
    if (!str || !id(str)) return 0;
    if (environment() != this_player()) {
        notify_fail("You are not holding that.\n");
        return 0;
    }
    write("You tip the bowl over, emptying it.\n");
    leave_bowl();
    return 1;
}
