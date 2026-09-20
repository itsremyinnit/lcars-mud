// /d/Avakuma/framsburg/obj/beer.c
// Open-topped: carried in the hands, and it will not go in a container.
#include <mudlib.h>
inherit OBJECT;

void create() {
    set("id", ({ "beer", "homemade beer", "bottle" }));
    set("short", "Homemade beer");
    set("long", @EndText
    You hold this bottle of beer up to the light and can see the time and
effort that has been put into brewing it.  You believe it will give you
just the lift you need.
EndText
    );
    set("bulk", 15); set("mass", 60);
    set("value", ({ 0, "copper" }));
    // Open-topped. Nothing carries it but a hand.
    set("no_container", 1);
    set("hands", 1);
}

void init() {
    add_action("do_drink", "drink");
}

int do_drink(string str) {
    object empty;

    if (!str || !id(str)) return 0;
    if (environment() != this_player()) {
        notify_fail("You are not holding that.\n");
        return 0;
    }
    write("You drink the beer and burp.\n");
    say((string)this_player()->query("cap_name") + " drinks a beer.\n");
    empty = clone_object("/d/Avakuma/framsburg/obj/empty_bottle");
    if (empty) empty->move(this_player());
    "/adm/daemons/disposal_d"->kill_object(this_object());
    return 1;
}
