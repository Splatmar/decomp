# ![](https://media.discordapp.net/attachments/731330616158716004/785283273759653918/party_sonic.gif?ex=6662ebca&is=66619a4a&hm=2e481bff7c1862c36cb1aef0fd5a6e03102a96eed8a8e8edcbd39cdf8c350380&) DrahckerSM64 ![](https://media.discordapp.net/attachments/731330616158716004/785283273759653918/party_sonic.gif?ex=6662ebca&is=66619a4a&hm=2e481bff7c1862c36cb1aef0fd5a6e03102a96eed8a8e8edcbd39cdf8c350380&)

Forked from HackerSM64 2.1.2 (5 Dec 2023), Add a bunch of new things !

**Credits**
- **HackerSM64**: The OG repo

So what's new :

**Add new characters:**
- Diacritics support for characters like -é -à -ï -ô
- You can now use a bunhc of new special character such as -@ -# -ß -Ç -/ -\

**Better object finding methods:**
- add some new methods to find more specific objects, for example : the nearest bob-omb with o->oAction == 2

**Behavior flags for star requirement:**
- A new flag desactivating an object if you have not enough stars
- A new flag making the object appear if you have enough stars

**Reset Course new menu option:**
- A new reset course menu option that allows you restart a level (enable it in config_menu.h where you can change the area and warp node used by it)

**Text boxes debug mode:**
- A new debug configuration that allows you to display the wanted dialog by his ID

**Better coin formation module:**
- customize the vanilla coin formations by modifying the offset, or enable flying !
- you can create a custom coin formation shape and place it in your levels

**Warps:**
- Warp hole can now have a custom hitbox height !
- each area can get a unique "exit level" destination

**Surface collisions**
- New conveyor surface with settable speed and angle
- New vertical wind collision with configurable stabilization height


Go read the original HackerSM64 repo README.md
