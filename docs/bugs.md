# Diablo bugs

This page tracks bugs that are native to the original retail game and were
discovered while documenting the source. These notes are intended to preserve
vanilla behavior accurately and provide a backlog for later modding or porting
work.

Existing references:

- [The DSF Buglist for Diablo v1.09 (Lurker Lounge)](http://www.lurkerlounge.com/forums/thread-12422.html)

## New bugs discovered

### Town portal created in a quest level can be relocated into the dungeon

If a player casts a town portal in a quest level, returns to town, and then
uses the stairs to enter the matching dungeon level, the portal appears in the
dungeon at the same X/Y position instead of remaining tied to the quest level.

Example: `Chamber of Bone` is quest level 2, so a portal cast there can later
appear on dungeon level 2.

### Diablo is not immune to the squelch radius

Diablo is meant to be immune to the squelch radius, but the game checks the AI
of Diablo's monster type rather than the monster type itself. That condition
always fails, so the immunity is never applied.

Relevant code path: `monster.cpp -> ProcessMonsters`
