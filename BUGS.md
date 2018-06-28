#### Spell Bugs

> All bugs in this category are related to spells and spellcasting.

##### CHARGED BOLT

If you stand in a tile of a bookcase or shrine and cast Charged Bolt, the spell effect will be terminated immediately. No bolts will form, but you will lose mana.

##### FIRE WALL

Fire Walls do more damage than listed in the spell book.

When you walk through a firewall in a way against its alignment, you will not be damaged if you step through its gaps. For instance, walking through a horizontal straight firewall diagonally won't damage you if you walk through at the correct tiles. The same effect applies to monsters and other players.

##### TELEKINESIS

If you Telekinesis a monster too much, it's possible for it to disappear into a wall. You will see the graphic in the wall, but no monster.

You cannot drink a potion from your belt using number keys while the Telekinesis cursor is active.

Telekinesis won't work on a monster unless it is activated. These means you can't mess with them if you can only see them with Infravision.

##### TOWN PORTAL

If a character goes to pick up an item as he/she is entering a Town Portal, a dupe will appear on the other side, thus creating the same item in town and in the dungeon. Neither item will be destroyed.

If a character dies while entering a Town Portal he/she will arrive in town dead, being unable to restart in town. The character must be resurrected, or he/she can drink a potion to heal to a living state. Also, if the character was killed by a monster, his/her equipment will fall in town - in a position relative to the level he/she left (sometimes in impossible locations, such as inside buildings).

Casting a spell just as you enter a Town Portal can cause a casting of the spell in town, producing an Illegal Spell warning.

On levels in which "Gargoyles" (i.e. Winged Demons, Gargoyles, Blood Claws, and Death Wings) are present, if a player leaves via Town Portal and re-enters the level, upon arrival all Gargoyles' "stone status" is not preserved. They'll activate normally, but they'll behave differently had they been in "stone status."

You cannot drink a potion from your belt using number keys while the Town Portal cursor is active.

##### FLASH

If you stand in the X in the diagram below and cast Flash, monsters in squares 1, 3, and 5 will receive about 1/10 of the normal Flash damage for some weird reason. Conversely, if the MONSTER is in the X, standing in 4, 6, and 8 will limit the damage you will be doing to that monster with flash. This rule also applies for when the monsters are casting Flash.

**Code:**

```
   1
  2 3
 4 X 5
  6 7
   8
```

When casting Flash, your character becomes temporarily invulnerable (but cannot move or take any other action).

##### STONE CURSE

Enemy mages can be Stone Cursed in mid-teleport, which makes them invisible and invincible until Stone Curse wears off. Golems will even (unsuccessfully) attack mages in this state.

##### FLAME WAVE

Flame Wave misses every other square when cast in the diagonal, direct left, right, top and bottom screen orientation.

##### FIREBALL

Fireball actually does far more damage than listed in the spell book, as a Fireball hit causes initial damage to the target and then splash damage on top of it.

Splash damage from Fireballs (possibly other spells) is removed when traveling over objects like spikes, chests, etc. Try casting a Fireball into a pack of Snow Witches behind a spike or something, and only the direct damage will be applied; one witch will be hit, the rest won't be scratched.

##### MANA SHIELD

Any attack causing more damage than a character's current hit points will not stun the character if they are using Mana Shield. Furthermore, the game considers the character to be in a state of death for a small period of time before his/her hit points are "refunded" by the Mana Shield. During this period of death (fraction of a second) the character is actually rendered immune to attacks, and cannot be knocked backward as well.

Players can "block" stairways when they enter them. A "ghost" image of the character remains at the stair entrance to the other players, and remains until the stair-taking player finishes loading up the next level. This blocking effect occurs 100% of the time when the player has a Mana Shield cast.

All spell levels of Mana Shield have the same damage reduction effect, 33%.

Mana Shields only reduce the damage caused by a Constricting Ring by 25%, not 33%.

##### GOLEM

The damage listed under the Golem spell in the Spell Book has no meaning. Golems do not do a constant rate of damage; their hit points are controlled by the caster's max mana.

If a character steps into a square the Golem was swinging at (to kill a monster) and the Golem hits the character, it then treats the character as an enemy and will attack him.

If, while standing adjacent to an enemy, you cast a golem with your cursor on yourself, the golem will appear on your tile. Your golem takes no damage with this bug.

A Golem has an infinite light radius to anything that uses Succubus, Goat Archer, or Skeleton Archer AI. Any such creature in a line of sight to it will fire at it but will not necessarily be otherwise activated.

Golems do very minimal damage against witches when the witches are trapped inside a Hell stairwell.

##### SPELL MEMORY CARRYOVER

Upon starting the Diablo program (before you play any other games of Diablo), start a game; click on the spell speedbook square and press 'S' at the same time. You'll get to use the Null Skill, which does nothing and looks like a fire-based spell.

If you use a spell on one character and then switch to a new one who doesn't have that spell, you can use the same technique above to load the old spell on the new character. If the character doesn't have that spell, it'll show up as a level zero spell.

##### SPELL QUEUING

You can queue spells by casting one while another's already being cast, and this can cause lots of problems. Examples are Teleporting only a space or two because the spell queued where your cursor was at the time, casting a spell when you don't have enough mana for it (you get a free cast and end up with negative mana), and firing spells in completely wrong directions because your mouse cursor was moved after the first cast.

You can queue a spell before entering a level (while it's still loading), which causes it to take effect to where your cursor was on the level beforehand. So, if the stairs down were on the left side of the upper level, and the entranceway below was on the right side of the lower level, you could cast Teleport and cross the entire lower level instantly. Same goes with other spells such as Town Portal. You can also cause illegal spells in town to occur this way, although the timing is very difficult to get right.

Certain spells from scrolls can be cast twice if a character casts a read, known spell and interrupts it with the scroll spell, casting twice in rapid succession. This is because the game queues the scroll spell before it realizes it can only be cast once.

A spell from a staff can be cast even if you run out by queuing the spell before the last spell casts.

##### SCROLL SPELL LEVELS

Scrolls of spells that you cannot read books of (i.e. Infravision) will be cast at the spell level of whatever book-read spell you have selected in your speedbook, when the scroll is cast from the belt. A level 15 Infravision can last a long time.

##### INCORRECT SCROLL DESCRIPTIONS

Scrolls often have the wrong directions for casting. Scrolls either have a "Right-click to read" description or a "Right-click to read. Left-click to target" description. On many spells, the description is wrong. For instance, the Flash spell scroll has the 'left-click to target' description, even though left clicking is not required.

##### INCORRECT SIGNED/UNSIGNED VALUES

A bug exists where you can cast spells while you have negative mana. This can result in incorrect values for spells that depend on mana. For example, a golem is nearly invincible if it is cast while you have negative mana. The game treats the negative value as unsigned and thus an enormous HP value is applied.

#### LAG AND DESYNC BUGS

> All bugs in this category are generally caused by lag and game desyncronization.

##### TOWN PLACEMENT OF "HOTPOINTS"

Occasionally the characters ("hotpoints") in town will be in a wildly different location than normal (such as a cow placed right next to Griswold). This is caused by clients arguing over the true position of these hotpoints.

##### TOWN PLACEMENT OF DROPPED ITEMS

When dropping items in town and entering the dungeon, upon return to town the items dropped will have sometimes moved, even to impossible locations - such as inside buildings or across the Tristram borders. This is caused by other players entering the game and not receiving the correct information as to town placement, so the entering client "moves" all the items around (as long as no other clients are in town).

##### DISAPPEARING ITEMS

Occasionally an item will simply disappear when a character tries to pick it up. It is believed to be caused by lag, although there are reports of occurrences in Single Player mode - which may be a wholly different bug. Generally however this is a result of a game desync, when clients do not agree as to the items that were "generated" by dying monsters.

##### DESYNCED LEVELS

When playing with a partner, it is possible to play in a disjointed level (possibly related to previous bug). This occurs when the level layouts are different for each player. This causes strange effects such as watching your partner walk through walls. You may also see completely different monsters. It is highly dangerous to play this way, and both players should leave the level immediately.

##### WRONG CHARACTER STATUS

Characters can sometimes appear dead, permanently stunned, equipment-less, or other ways due to game desyncs when the player changes his/her status, or when suddenly leaving the game.

##### PLAYER GHOSTS

If a player leaves the game while in a "trouble" situation (i.e. swarmed by monsters), it may not have a graceful exit. The character's "ghost" remains, the picture of the player. It can be highlighted by another player, even attacked. On other players' screens that can see the ghost, they may see monsters try to attack the ghost.

##### EXITING PLAYERS

When a player is lagged out, or "times out" of a game, the other clients will occasionally see a "Player has left the game" message instead of the time out message.

#### EQUIPMENT BUGS

> All bugs in this category are related to effects caused by equipment or equipment generation.

##### STEALTH EFFECTS

When using items that reduce a character's light radius, a character will only activate monsters who are in that light radius. However, the character's light radius for attracting monsters depends upon the highest light radius the character had on a level until he/she exits the level. If the light radius is increased/decreased while on the level, it will alter the player's light radius, but not in terms of monster attraction - they will be attracted to the highest radius that existed at any time on the character. In other words, always have stealth equipment equipped BEFORE entering a level, and if you drop a stealth item, you'll have to leave the level and come back to use its effect on monster attraction again.

When at full stealth level (-80% light radius), walls sometimes cannot be mapped even when the character is right next to them. Also, portions of the map for a level will appear as revealed very far away from the character's position. And, last of all, you won't see a monster one square away from you if it's at a diagonal angle. It won't see you, either.

##### HIGH DURABILITY WRAPAROUND

When a character is saved with an item that has over 255 durability, its durability wraps around back to 1 to 10 durability. This can cause strange effects when using Hidden Shrines or finding items with durability-boosting suffixes that would normally cause its durability to be higher than 255.

If you use Hidden Shrines to take an item to exactly 255 durability, the item will transform to an indestructible item. This is because Blizzard used 255 in their code that checks whether an item is indestructible.

Items raised to 256 durability with Hidden Shrines have a number of problems. When starting a new game, the item will have zero maximum durability. Any attempt to repair the item at Griswold will then crash the game. Any attempt to repair the item with a warrior's Repair Skill (when it is something other than 0/0 durability) will result in the either the immediate disappearance of the item, or the item will become unselectable and will disappear when clicked on again.

##### GRISWOLD'S REPAIRS

Occasionally Griswold will charge you for repairing an item and yet not repair it, forcing you to have to pay for repairs again, and possibly multiple times.

Griswold will not repair a cursed item because its value to him is negative or less than one.

Griswold can only repair an item when at least 1% of its durability has been lost; therefore, items over 100 durability can only be repaired after they've lost more than one durability point (over 200, 2 points).

##### ADRIA'S ISSUES

Occasionally Adria will charge you for recharging a staff and yet not recharge it, forcing you to have to pay for recharge again, and possibly multiple times.

Adria will recharge a staff for free if the number of charges to be reset is less than 1% of the total number of charges on the staff.

If you sell an item at Adria and you don't have enough room for the cash to be placed in your inventory, the excess gold is lost.

##### DEADLY HUNTER

This unique bow is listed as doing +200% damage versus demons, just as the BloodSlayer (axe) and Civerb's Cudgel (mace). However, while the Civerb's Cudgel and Bloodslayer have the effect of tripling a characters total damage to demons (not the weapon damage, but the total), the Deadly Hunter does not. This is caused by the way the game engine handles arrows differently than melee weapons.

##### IMPOSSIBLE ITEMS

Due to the item generation rules of Diablo, these unique items cannot be found: Bramble, Crackrust, Lightforge, The Deflector, Gonnagal's Dirk, and The Mangler.

##### KING'S VS. CHAMPION'S PREFIX

The prefix "Champion's," while being weaker than "King's," is considered more valuable in terms of rarity in the game. This causes "Champion's" to be unfindable from any monster; it can only be bought from Wirt. This is a result of a hasty change in the value of the "King's" prefix before the release of the game - it was lowered to make it easier to obtain, and "Champion's" was not.

##### SWING SPEED

The suffix "of Haste" is supposed to be faster than "of Speed," but they both produce the same swing speed as they eliminate the same number of animation frames on an attack. Blizzard incorrectly claims this was fixed in the 1.07 patch.

The suffix "of readiness" (designed to drop one frame of animation) is useless.

##### DEATH WITH CURSED ITEMS

When dying from monsters' attacks, a character loses all items. If he/she was carrying items that lower hitpoints, he/she will regain the hitpoints that were drained by those (either cursed items or certain uniques). Upon dropping the items, the player will sometimes reach a value of hit points greater than zero - but the character will remain dead on his/her screen. For other players in the game this character has positive hitpoints, though, and thus they will not see a corpse and thus be unable to cast resurrect on him/her.

##### SHARP PREFIX

The prefix "Sharp" is considered a cursed prefix by the game (it shouldn't be), so you can't buy it in town.

##### CURSED AC ROUNDING

When a cursed prefix or suffix modifies the AC value of an item, it is supposed to lower the AC. However, if the amount of AC to be lowered rounds down to zero, the AC is actually raised by 1. For example, an AC 3 helm with -26% AC will yield an AC of 4, since 26% of 3 is rounded to 1.

##### "RED" ITEMS

"Red" items (i.e. items that you are "wearing" but cannot use because you don't meet the requirements), put on your character by using an item that gave you the requirements, equipping it, and then removing the item that allowed you to use it, will lose durability just like items you're allowed to use.

Even though a red item cannot be used by your character, it will still modify your damage based on weapon type. If you use a "red" sword, for instance, your fist damage will be raised by 1.5 times when you punch animals, and lowered by 0.5 times when you punch undead.

##### GRISWOLD/WIRT PRICING INCONSISTENCY

If you buy an item from Wirt and then go to sell it to Griswold, he will offer you one fourth of the price you paid Wirt for it. If you then start a new game, however, Griswold will only offer you one fourth of what HE would sell it for (less money).

##### CORRUPTION SUFFIX

Equipping an item "of Corruption" when you have negative mana will actually GIVE you mana, setting your mana to zero.

If you equip an item of corruption and afterwards equip mana adding items, mana will still be added. Also, when you take off the corruption item and re-equip it, mana will not be reset to 0, but instead to what it previously was (i.e., mana from items equipped after equipping the corruption item will still be added).

More seriously, if your character has negative max mana (possible with mana-reducing items such as the Cranium Basher), using an item of Corruption will set your mana to zero. Removing it keeps your current mana at zero (of a max of a negative number). If you then unequip the item(s) which gave you negative max mana, the game will immediately crash. Don't try this at home.

##### GOLD IMAGE STABILITY

Images of gold piles are updated incorrectly sometimes. For instance, if you have two piles of gold totaling between 5,000 and 10,000 gold, you can merge one gold pile with the other and the amounts will switch. If this causes one pile to obtain a "smaller" shape, drop it on the ground and pick it back up - it will have the older image of a larger pile again.

##### UNFINDABLE ITEMS IN DUNGEONS

Monsters in each level of difficulty have the same value for item drops in terms of prefixes and suffixes; therefore, many high-end prefixes and suffixes can never be dropped by a monster. Specifically, these prefixes and suffixes cannot be found on items dropped by monsters: Mammoth, Whale, Holy, Godly, Weird, Strange, Champion's, Ruthless, Merciless, Carnage, Slaughter, Osmosis, Burning, and Thunder. Only Wirt can sell you these prefixes and suffixes. Hydra's and Wyrm's enchantments cannot be generated in town or in dungeon.

##### FIRE/LIGHTNING SUFFIX ISSUES

Damage from Fire or Lightning elemental arrows will occasionally be highly excessive. It is caused by the calculation for the damage occurring multiple times as it hits its target. This occurs on traps sometimes, as well.

When a monster is hit by a fire damage arrow, it stops regenerating hit points. This even applies to the Dark Lord, Diablo.

#### DUNGEON LAYOUT/POSITIONAL BUGS

> All bugs in this category are related to problems with dungeon layouts, level transitions, the positions of objects, and other errors caused by the tile layout design of the game.

##### SCREEN DRAW ERRORS IN CAVES

Certain wall formations in the caves can cause screen draw problems which are harmless. This is caused by spots on the level map that do not contain graphics, usually seen as stalagmites. Images in them will "ripple."

"Mirroring" effects can be seen where a character's image will appear in lava pools.

##### LEVEL RESETS

Occasionally, if you go down a set of stairs, back up, and back down again, the entire level changes. This includes wall placements, creatures, etc...which can lead to you arriving in the middle of a pack of monsters, or a wall.

##### HELL'S INVISIBLE WALLS

Sometimes in Hell levels, especially level 16, hidden walls exist which cannot be seen by the player but are treated as physical barriers that also block sight and shots. There seems to be a correlation between dead body parts hung on walls (aka "Shish Kebabs") and hidden wall squares.

##### HOLES IN THE WALL

Many walls in the game have holes in them that allow arrows and spells to leak through. One such hole exists on the left side of Lazarus' chamber.

##### IMPOSSIBLE LEVELS

Very rarely will a level be generated that is not continuous - it is split into sides that can only be accessed by casting Phasing or Teleport.

##### FAR OFF MAP SQUARES

Occasionally dotted map squares, corresponding to walls and inaccessible areas, will be visible on the map upon level entry - even when being very far away.

##### MONSTERS IN WALLS

Monsters will occasionally appear inside closed doors or walls, as they are generated there. As soon as they enter your light radius they simply walk out of the wall/door they were "in."

##### RANGED ATTACK ANGLES

Certain angles of ranged attack against monsters will result in a character being unable to hit them; the character will have to move a square to be able to score a hit. Shots fired in straight lines to the target are much easier to connect.

##### SHARING SQUARES

When a character teleports/phases onto a square that a monster was moving in to, they will overlap. The character will have to move off the square to hit the monster. The monster, however, can attack the same square it's standing on.

If two characters wind up occupying the same square, which can happen rarely when casting Teleport or when Resurrecting while standing over a body, the player who does not move will become invisible to both players, until he/she moves. Further, the player first on the internal list of players may be the first targeted and attacked if a monster approaches.

The player can also share a square with a Golem.

##### STAIRWAY PROBLEMS

A character can teleport/phase into a stairway leading down in Hell levels and "levitate" in the open area inside the "cage" of the stairway. He/she can then shoot ranged attacks out of the mouth of the stairway, but no ranged attacks from monsters can get in from certain angles.

If you enter the caves via the cave mouth entrance near Wirt, you can run the mouse cursor over the stairs on level 9, and a small spot on the right side of the stairs will read "up to level 8." If you left click on that spot your character will begin walking towards the level 8 stairs (even if you can't see them on the map), unless the way is blocked by lava, grates, or some other obstacle. If you teleport onto that spot, your character will teleport all the way to the level 8 stairs and go up!

Players can "block" stairways when they enter them. A "ghost" image of the character remains at the stair entrance to the other players, and remains until the stair-taking player finishes loading up the next level. This blocking effect occurs 100% of the time when the player has a Mana Shield cast.

Monsters that use Hidden AI are always active. Unless there's a barrier between them and the player (e.g. closed door, barrels completely blocking a path), they'll reach the player without any action on the player's part.

The game normally doesn't generate monsters within a certain range of the stairs. This does not apply to rooms, however. For example, you may enter a level of the caves and find Storm Demons waiting 7 squares away, placed there because they are inside a fenced area. They will fire at you immediately, open the door, and come after you.

##### BOSS LIGHT RADII

All bosses in Diablo emit a light radius visible to players. If they move, their light radius moves as well. However, if you leave the level and re-enter, the bosses original positions will have a light radius on the floor, even when the boss' dead body is located at a different position on the level.

##### LEVEL ENTRANCE DISPLACEMENT

When players use stairwells to go down, each player will see the other in the wrong spot at next level, with their player being in the "correct" position and the partner displaced. When the characters move, the game engine corrects this situation by showing the other player walk one space over.

In a similar fashion, a player taking another player's Town Portal down to a level can wind up on the other side of a wall if the portal was placed just to the "north" of the wall. This is due to a displacement of one square, as the player cannot land on the exact square of the Portal (they'd head right back up again, then).

##### TRAP RESETTING

If a door with a trap is opened, thus setting off the trap, and the door is closed again, you can "reset" the trap. Leave the level and come back to it, and the trap will be reset.

##### 127 LIMIT

You cannot drop more than 127 items on the floor in any one level, including town. Note that this can cause you to lose monster drops if you have 127 items on the floor of a level, since a dying monster will have no "room" to drop it and it will simply never exist. Remember that every pile of gold is an "item."

Diablo also has a 127 limit as to the number of ongoing spell effects (including arrows) that can appear on a level at any one time, which is 127. Some spells, especially Chain Lightning, can use up several effects.

##### ITEM DROPS ON SHRINE/BOOKCASE TILES

If an item drops on the tile for a shrine or bookcase, you cannot highlight or pick up the item until activating the shrine or bookcase.

##### MOONBENDER'S LIGHT RADIUS

The light square of Moonbender (a Blink boss) will freeze in place if it 'blinks' next to you, and won't follow the boss even if the boss moves afterward.

##### UNHITTABLE WHEN WALKING HORIZONTALLY

When a character (or monster) walks horizontally on the screen (as in on your monitor), he/she/it cannot be hit by most spells and ALL arrows, even when fired on the same line of action of the walker.

##### GOING UP AND DOWN STAIRS

You will only descend a stairwell while you're in "walk" mode. Other actions, such as swinging or casting, will prevent you from descending a staircase.

#### MISCELLANEOUS BUGS

> Everything else.

##### DUPLICATES

Various duplication bugs/quirks exist in Diablo.

Vendors can occasionally sell duplicates. Duplicates of potions are somewhat common since the range of ID numbers assigned to potions is rather small

You'll occasionally find the exact same item twice (or even thrice) in the same dungeon. After ID'ing, these items will produce a duplicate item message when simultaneously dropped.

The commonly abused duplication has to do with the item-pickup routine. Blizzard has never fixed the item-pickup bug. They claim that it cannot be fixed without an overhaul of the game engine, but this seems incorrect as it has been fixed in modifications.

##### FIFTH SPELL BOOK PAGE

Clicking on the small area between the number 4 and the right edge of the spellbook causes a blank page to appear.

##### PRICE LIMIT

The upper limit to the price of items Griswold or Adria can sell you is 140,000 gold, even though a character could still buy an item that takes up six slots and carry 170,000 gold. Wirt's limit is 135,000 gold.

##### FAMILIARS

Familiars are demons and not animals like all of the other bat types.

##### BOSS AND MONSTER APPEARANCE

Due to the dungeon level assignments of bosses and their corresponding monster types in the code, certain bosses can never appear in the game. For example, Lord of the Pit (Azure Drake boss) is assigned to appear on dlvl 13 whereas Azure drakes cannot appear on 13; thus, no boss.

Some bosses are assigned monster types which don't appear in-game. Monsters that don't appear: Invisible Lord, Lord Sayter, Wyrm, Cave Slug, Devil Wyrm, Devourer, Bone Demon, Red Death, Litch Demon, Undead Balrog, Incinerator, Flame Lord, Doom Fire, Hell Burner, Devil Kin Brute, Unraveler, Hollow One, Pain Master, Reality Weaver, The Arch-Litch Malignus. (Satyr Lords, Devil Kin Brutes, Bone Demons, and Unravelers do make an appearance in Hellfire, however.) Bosses not appearing in the game:

###### Name - Type: Dungeon level

* *Blightstone the Weak* - Lord Sayter: 4
* *Hazeshifter* - Unseen: 5
* *Warmaggot the Mad* - Wyrm: 6
* *Glasskull the Jagged* - Red Storm: 7
* *Wrathfire the Doomed* - Incinerator: 8
* *Bronzefist Firestone* - Hellstone: 8
* *Doomgrin the Rotting* - Red Death: 8
* *Stormbane* - Storm Rider: 9
* *Madburner* - Flame Lord: 9
* *Lord of the Pit* - Azure Drake: 13
* *Bonesaw the Litch* - Litch Demon: 9
* *Grimspike* - Obsidian Lord: 19
* *Devilskull Sharpbone* - Red Death: 9
* *Doomlock* - Storm Lord - 28
* *Warpfire Hellspawn* - Hell Burner: 11
* *Blacktongue* - Counselor: 12
* *Festerskull* - Undead Balrog: 11
* *Soulslash* - Unraveler: 12
* *Howlingire the Shade* - Hollow One: 13
* *Bloodmoon Soulfire* - Pain Master: 13
* *Zamphir* - Reality Weaver: 15

##### SHRINES

An Enchanted Shrine will reduce a spell by two levels if it is base level 15, instead of just one spell level reduction. This is caused by how the shrine works - it raises all spell levels by one and then picks a spell to reduce by 2 levels. A level 15 spell will not raise to 16 and then go down to 14, it will stay 15 and be reduced to 13.

Mysterious Shrines, Tainted Shrines, and Fountains of Tears do the same kind of thing with character stats - they can pick a stat to be raised that's already maxed, and wind up lowering all the other stats.

Due to a design flaw in how the game engine handles the random effects in shrines, Hidden Shrines will tend to reduce the durability of the item in the right slot (left hand) more often. Mysterious Shrines will tend to raise Dexterity more often than other stats. Enchanted shrines will tend to reduce Chain Lightning more often than the other spells. This effect becomes less noticeable the more you play in a single gaming session, i.e. the shrine effects will become more 'random.' Namely, the "random seed" stored with ANY shrine is not initialized properly, and the shrine uses whatever happens to be in that memory location. At startup this memory will mostly be "empty", which is read as zero, which then causes the non-random behavior. After the game is played for a while, the memory is much less likely to be zero, and therefore tends to approach randomness.

##### ZERO HIT POINT ISSUES

Under special circumstances a character can wind up with 0 hit points and yet not die. The character then is invincible to all forms of attack unless he/she heals or has Heal Other cast upon the character. This is apparently caused by some portions of the code treating -1 HP as death, not 0.

A character with negative hit points will be killed by any sort of Healing.

##### RESURRECT IN TOWN

Occasionally when a character is resurrected by another player in the dungeons, players in town can see the beam of light in town corresponding to the player's position on a level in the dungeon.

##### DUPE MESSAGE ON GAME ENTRY

If a player enters a game at the exact same time that another player drops an item in town, the entering player will see a "A duplicate item has been detected from another player" message.

##### PLAYER FRIENDLY MODE IN DUELS

If you use a melee weapon against a character who has set themselves on "Player Friendly" you cannot stun lock him/her. This does not apply to attacks with a a bow.

##### KNOCKBACK PROBLEMS

When being hit by a creature with knockback power (or a character with a knockback weapon) such as Diablo or a charging beast, you can be knocked back physically, but your light radius does not move unless your character makes some form of move (either walking or attacking). Thus, you can eventually be knocked outside of your own light radius and all creatures will disappear.

Knockback bows do not knock enemies back 100% of the time.

Hitting a monster/player will knock them back according to the direction they are facing; thus, you can technically knock a creature back towards you if it's facing away from you.

##### SINGLE PLAYER DIFFICULTY LEVELS

If you start a multiplayer game at Nightmare or Hell difficulty and then quit to start a single player game, the single player game will be the same difficulty as the multiplayer one, including the value of experience per monster, gold drops, etc.

##### BOSS ERRORS

Powerful bosses in higher levels of difficulty have their experience level overflow, as the game calculates the experience level for them too many times.

Bosses in Nightmare and Hell difficulties are sometimes far weaker than they should be, with poor AC and to-hit%. This is because these values are byte values and they overflow with higher difficulty bonuses.

Diablo in Nightmare and Hell difficulties suffers from the same problem as the bosses above.

##### LEVEL 50 CROSSOVER PROBLEMS

Any partners in a game where a player levels up to 50 will still see the player as level 49 in that game.

A character does not receive a hit point or mana point bonus on leveling to 50.

##### SINGLE PLAYER LEVEL BONUSES

Players get an extra 1/64th HP and MP on leveling up in single player in addition to a full 64/64.

##### GOLD LOSS ON DEATH

If you are carrying a large amount of gold in your inventory, you stand to lose much more than half of it when you die. The game won't drop enough piles of it and the piles themselves will have less than 5,000 gold each. It apparently doesn't generate the gold correctly when you are defeated.

##### EARS

Ears from the same character are duplicates.

If a player dies from a PK attack and an ear from that character is already on the floor somewhere, a new ear will not be generated (related to bug above).

##### YEAR 2039 RANDOMIZER ISSUE

The game engine will stop creating random levels after midnight of January 1, 2039. Any game started before January 1, 1970, will also not be random.

##### CHARACTER DAMAGE UPDATE UPON LEVEL UP

When a character levels up, the damage displayed in the character screen may be incorrect until the status of the character changes. Status changes include the removal and/or applying of equipment or a raise in character attributes.

##### TRAP DAMAGE

Trap damage does not get increased by difficulty. Traps in Nightmare and Hell difficulties do the same amount of damage as the ones in Normal. This makes traps for high-level characters meaningless.

##### ATTRIBUTE WRAPAROUND

If an attribute of a character becomes negative, which can be accomplished through the use of Mysterious and Tainted Shrines (by partners touching them), on starting a new game the character's attribute will wrap around to 255-value. If magic or vitality wrap around this way, the character will NOT gain the hit points and mana one would expect from this "gain." For example, if a warrior obtains -2 magic, in the next game he starts he'll have 253 magic (which will then be limited to 50 magic, his max). However, a character will not gain mana from this wrap around, thus harshly corrupting the character.

##### BLOCK BONUS LOSS

Characters in Diablo are supposed to have a blocking bonus; 30 for a warrior, 20 for a rogue, and 10 for a sorcerer. This would be equivalent to a warrior having 30 more dexterity in terms of blocking ability, and likewise for the other two classes. However, this bonus is not saved with the character when it is saved (via Save Game in Single Player or Exit Game in Multiplayer). Thus, a character has a blocking bonus when it is started which is lost forever after the first session - a huge loss for ironman characters.

##### TOWN TALKING

If you press F1 to open the help screen and then talk to a townsperson, pressing F1 to clear the help screen overlay causes the talk menu to stretch out across the screen. When this happens, you cannot select any of the talk menu's options and must clear it using the Esc key.

#### Gameplay Bugs Fixed In Previous or Current Versions of Diablo

##### VERSION 1.08

* [Mac Only] Improved Mac vs. PC multiplayer, modem, and direct connect.

##### VERSION 1.07

* Fixed crashes associated with being attacked or killed by a Black Death (Zombie class). This includes the crash upon resurrecting after being killed by a Black Death.
* Fixed the freeze upon touching a Hidden Shrine while equipped with only indestructible items.
* Prevented players from becoming stuck inside a wall when Town Portalling down into a dungeon.
* Fixed bug that made some Hell difficulty monsters too easy to hit. Beware.
* Fixed the Mana Shield bugs that could make a player invulnerable and/or invisible to other players.
* Fixed the bug that prevented Rogues from properly disarming traps on levels 13 through 15.
* Fixed bug that rarely transformed unique items (like the Optic Amulet) into some other (usually mundane) item when saving the game and then starting a new game.
* Prevented repeated castings (128 or more) of Mana Shield from disabling the casting of any more spells.
* Fixed bugs that prevented items with the suffixes Thieves, Balance/Stability/Harmony, and Piercing/Bashing/Puncturing from working properly.
* Fixed the bug that caused Mana Shield to become less effective with increasing spell level.
* Fixed the bug that caused excessive damage when a Mana Shield expired due to an attack.
* Prevented bows with fire-hit damage from interfering with the behavior of Gargoyle class monsters.
* Allowed right-clicking (casting/drinking) belt items in positions 5 through 8, while the Spellbook is open.
* Fixed the bug that froze Lazarus (and made him invulnerable to arrows and spells) after player had entered his lair, then left (or died), and finally returned.
* When in effect, the Mana Shield graphic appears to all players.
* The casting of a Nova spell is now visible to all nearby players.
* Adria's books appear white now only if a player can read them.
* Equipped shields always appear properly to all players.
* Nightmare and Hell difficulty monsters now display the correct number of hit-points (HP).
* In single player, the sound is no longer shut off by loading a saved game while Diablo is in his death throes.

##### VERSION 1.05

* Fixed potential memory corruption bug that occurred when casting town portal

##### VERSION 1.04

* Fixes the Hidden Shrine freeze which was caused by touching the shrine when not holding an item with durability
* Fixes the Black Death crash which occurred when fighting the monsters with an active Mana Shield and Full Health
* Corrects the functionality of the Rogue's Disarm Trap skill

##### VERSION 1.03

* Prevents other players from casting illegal spells in town
* Fixes duplicate item generation at the Blacksmith and Witch within the same game
* Improves game speed over previous version
* Improves the game's handling of latency and packet loss over the Internet

##### VERSION 1.02

* Corrects the NULL cell buffer errors and other draw problems in Single Player
* Improves error handling for dropped network packets
* Fixes the problem with some equipped items not being seen by other players in multiplayer games
* Numerous fixes to item integrity. NOTE: With this patch, when the game detects duplicate items they will be removed from the game.
* Prevents Lazarus's red portal from disappearing after leaving his lair in Single Player games
* Fixes the Level Advance Indicator remaining on screen after character attributes are maxed