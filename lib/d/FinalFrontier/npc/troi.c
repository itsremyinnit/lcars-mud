// /d/FinalFrontier/npc/troi.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("troi");
    set("short", "Counselor Deanna Troi");
    set("long", @EndText
    Dark-haired and watchful, with the easy, patient attention of someone
reading the room and being polite about what it says. She smiles at you
as though you have already told her something, which you have not.
EndText
    );
    set("id", ({ "troi", "counselor", "deanna" }));
    set("gender", "female");
    set("mass", 7000);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N watches the room with the easy attention of someone reading it." }),
        ({ "say", "says", "You don't have to talk about it. But you could." }),
    }));
    set_inquiry(([
        "chocolate" : "A weakness. I don't pretend otherwise. Why do you ask?",
        "hot chocolate" : "A weakness. I don't pretend otherwise. Why do you ask?",
        "feelings" : "Yours, or everyone else's? Because the room has quite a few.",
    ]), "Is that really what you want to ask me?");
    set_range(70, ({
        "/d/FinalFrontier/deck10/ten_forward",
        "/d/FinalFrontier/deck10/corridor_ten",
    }));

}
