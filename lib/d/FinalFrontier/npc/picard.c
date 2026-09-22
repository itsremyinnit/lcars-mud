// /d/FinalFrontier/npc/picard.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("picard");
    set("short", "Captain Jean-Luc Picard");
    set("long", @EndText
    Straight-backed at the desk, reading, with a cup at his elbow that has
gone cold without his noticing. He looks up when you come in with the
courteous, unhurried attention of a man who has already decided how long
this is going to take.
EndText
    );
    set("id", ({ "picard", "captain", "jean-luc", "jean-luc picard" }));
    set("gender", "male");
    set("mass", 7000);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N turns a page, and does not hurry to turn the next." }),
        ({ "emote", "$N looks out through the window for a long moment." }),
        ({ "say", "says", "Tea. Earl Grey. Hot." }),
    }));
    set_inquiry(([
        "fish" : "Livingston. He has seen me through a great deal and has never once offered an opinion.",
        "livingston" : "Livingston. He has seen me through a great deal and has never once offered an opinion.",
        "vineyard" : "My brother's. It is a long way from here.",
        "borg" : "I would rather not.",
        "enterprise" : "She is a good ship. She has been asked for a great deal, and has always given it.",
    ]), "That is a matter for another time.");
}
