# Beskrivelse
Det udviklede program skal kunne køres udelukkende fra terminalen og skal kunne kompileres og køre på den udleverede Ubuntu 22.04 maskine uden installation af yderligere pakker. 

Spillet skal udvikles i c++ skrevet som objekt orienteret. Der skal laves git commits ofte, og som minimum når nye klasser bliver implementeret. (Git branching strategy skal i selv vælge og beskrive i porteføljen)

#Aflevering

Projektet skal aflevers som en samlet zip fil indeholdende:

Mappe med en linux executable, alt kode, CMakeLists.txt og .git folder.

PDF Document med følgende indhold:
   * Gennemgang af hver iteration (programmets nuværende status, og udviklings flow)
   * Beskrivelse af det nuværende system.
   * Use Case Diagram, med Use Cases
   * Domain Model
   * Udvalgte Sekvens Diagrammer
   * UML - Class Diagram
   * Evt. Backlog
   * Git - Log*

∗ For every new class there should at minimum be a commit.

# Første Iteration
Der skal udvikles et simpelt spil med en simpel “karakter” der har “monstre”.  
I første iteration skal man kunne lave en ”karakter” der kan have op til 4 “monstre”, og monstre skal kunne kæmpe med andre monstre. 
Man skal kunne vælge hvilket “monstre” man ønsker at kæmpe i mod.  
Man skal kunne lave en ny ” karakter”. Desuden skal man kunne lukke spillet. 
Man behøver ikke at kunne gemme noget, og alt mistes når man lukker spillet. 

Den første iteration af systemet skal kunne klare følgende funktionalitet: 
* Man har en ” karakter” der har et ”navn”.  
* karakter” har også op til fire “monstre”. 
* “monstre” har “navn”,  hitpoints ”hp”, og hvor meget skade de giver til fjender ”styrke”. 
* Når man er i gang med et eventyr skal der kunne vælges om man vil kæmpe 
* mod en fjende eller forlade spillet. 
* Man vælger hvilket “monster” man vil kæmpe mod. 
* I kamp afgøres hvem der starter med skade tilfældigt og så skiftes de. 
* Hvis alle af karakters monstere bliver besejret så vender man tilbage til “hovedmenu” 
* ---- Hvis man har nogen “monstre” tilbage sendes de ind 
* Hvis man besejrer et “monster” kan man tilføje det som sit eget. 
* ---- Har man fire allerede skal man udskifte det hvis man vil beholde det. 
* I en hovedmenu skal man kunne starte en ny “karakter”.
* En ny “karakter” starter med to “hest” (valgfrit)


## Monster liste

Den følgende liste af "monstre” er givet som eksempel, men må gerne ændres: 

* ”Hest”, hp 4, styrke 1 
* ”Weak Goblin”, hp 4, styrke 2 
* ”Strong Goblin”, hp 8, styrke 3 
* ”Stronger Goblin”, hp 10, styrke 4 
* ”Den stærkeste Goblin”, hp 15, styrke 5 
* ”Abe Kongen”, hp 30, styrke 5 
* ”Enhjørning”, hp 50, styrke 8 
* ”Drage”, hp 100, styrke 10 

# Anden Iteration

Til anden iteration skal spillet gøres mere interessant, så kampsystemet ikke er helt simpelt. Der skal derfor tilføjes “Ting”, “Status” og “Grotter”.

“Ting” kan bruges i stedet for angreb og har kun inflydelse undervejs i kampen.

“Status” bliver givet til et monster undervejs i kampen vha “Ting” og bliver udført i starten af hver monsters tur.

“TIng” bliver skaffet ved at gennemføre “Grotter” som er en samling af “Monstre” ligesom spilleren.

 

Den anden iteration af systemet skal kunne klare følgende funktionalitet: 

*Monstre skal kunne have “Ting” som har effekter der kan bruges i stedet for angreb
* Spilleren kan give “Ting” til monstre
* “Ting” kan give “Status” til monstret selv eller modstanderen
* “Monstre” kan have mange “Ting” og mange “Status”
* Hver “Status” bliver afviklet i starten af monster tur
* Der skal tilføjes grotter som spilleren kan vælge at kæmpe i mod.
* “Grotter har en samling af monstre ligesom en spiller og alle monstre skal besejres for at færdiggøre grotten
* Ved at besejre “Grotter” får spilleren en Ting som kan gives til et af sine monstre
* Grotter skal generes automatisk så de passer til spillerens niveau af monstre.

Noter:

* Fjendtlige monstre behøver ikke at bruge items (men i må gerne inkludere det og lave en strategi for det)
* Man behøver ikke at kunne fjerne “Ting” fra monstre
* I må selv vælge om monstre har en maks grænse af ting
* Ideerne nedenunder er til inspiration, i kan frit tilføje eller ændre


## Ideer til "Ting"

* Bombe: Giver 10 skade
* Ildbombe: Giver 5 skade og 35% sansynlighed for Stunned
* Tordenbombe: Giver 10 skade og 50% for Paralyzed
* Kølle: Giver 20 skade
* Blæser: 80% for Frozen
* Forbandelse: Hvis fjenden har en status allerede så er sansynligheden for Curse 100% ellers 20%
* Gift: Hvis fjenden har modtaget skade, så er sansynligheden for Poison 100% ellers 20%

## Ideer til "Status"

* Poisoned – Takes small damage each turn.
* Frozen – Cannot act for 1–2 turns.
* Paralyzed – 30% chance to lose turn.
* Stunned – Guaranteed to miss next turn.
* Cursed – Takes damage when dealing damage.

