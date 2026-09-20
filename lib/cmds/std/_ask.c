// _ask.c
// Lets a player ask a monster about a subject. If the monster has set
// the inquiry property to a mapping, then if that mapping has an entry under
// the subject, then the monster will say that string.
// Written by Pyrosius@TMI-2
// He and Mobydick integrated it into the lib on 8-18-93.
// Added help. Lucas@Avatar (5May96)

#include <mudlib.h>
inherit DAEMON;

int cmd_ask(string str) {

   string mon_name, subject;
   object mon_obj;
   mapping cmd_map;
   string reply;


  if (!str) {
     notify_fail("Ask <monster> about <what>?\n");
     return 0;
     }
  if (sscanf(str, "%s about %s", mon_name, subject) != 2) {
     notify_fail("Ask <monster> about <what>?\n");
     return 0;
     }

  mon_name = lower_case(mon_name);
  mon_obj = find_living(mon_name);

  if (!present(mon_name, environment(this_player()))) {
     notify_fail(capitalize(mon_name) + " is nowhere to be found.\n");
     return 0;
     }

  if (!mon_obj) {
     notify_fail("Do you like talking to inanimate objects?\n");
     return 0;
  }

  if (mon_obj->query("user")) {
	write ("You ask "+capitalize(mon_name)+ " about "+subject+".\n") ;
	tell_object(mon_obj,this_player()->query("cap_name")+" asks you: Know anything about "+subject+"?\n") ;
	say (this_player()->query("cap_name")+" asks "+capitalize(mon_name)+": Know anything about "+subject+"?\n", mon_obj) ;
    return 1 ;
    }

  cmd_map = ([ ]);
  cmd_map = mon_obj-> query("inquiry");

  if (sizeof(cmd_map)==0) {
	write (capitalize(mon_name)+" looks at you blankly.\n") ;
	return 1 ;
    }

// LCARS-MUD: answers used to go out through tell_room(), which tags them
// with the message class "tell_room" rather than "say", so nothing
// downstream could tell an NPC's speech from anything else it emitted.
// They now go out as class "say", like real speech. The asker is also told
// what they asked, which the original left out. An NPC may set
// "inquiry_default" for its own brush-off in place of the stock line.
  reply = cmd_map[subject];
  if (undefinedp(reply)) {
     reply = mon_obj->query("inquiry_default");
     if (!reply) reply = "I don't know about that.";
  }

  message("say", "You ask " + capitalize(mon_name) + " about " +
          subject + ".\n", this_player());
  message("say", this_player()->query("cap_name") + " asks " +
          capitalize(mon_name) + " about " + subject + ".\n",
          environment(this_player()), this_player());
  message("say", capitalize(mon_name) + " says: " + reply + "\n",
          environment(this_player()));
  return 1;
  }

string help()
	{
	return(@HELP
Syntax: ask <monster> about <question>

This command allows you to ask a living object a question. If the
objects knows anything about the question, it will reply with an
answer.
HELP
  );
	}
