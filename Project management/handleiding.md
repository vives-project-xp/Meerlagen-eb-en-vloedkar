# Handleiding

## Code

In de code heb je meerdere files. Je hebt de main.cpp en functions.h. De connection en sensor files zijn van Home Assistant, deze zijn al geconfigureerd en hoef je niet aan te passen.

In de functions.h file staan alle pinouts en functie definities. In main.cpp staan de declaraties van de functies en de setup() en loop() functie. In de setup kan je functies aanroepen die enkel bij het opstarten moet aangeroepen worden. In de loop() roep je functies aan die meerdere keren gebeuren.

Eenmaal aanpassingen gemaakt, kan je via het icoontje van PlatformIO (1) builden (2). Eenmaal dat het project succesvol gebuild is, dan kan je uploaden (3). Als je problemen hebt tijdens het builden, zullen er problemen in je code staan. Als je problemen hebt met het uploaden, heb je de verkeerde COMpoort staan of is er een slechte verbinding tussen je computer en de ESP.

![Schema](/Afbeeldingen/Handleiding.png)

## Knoppen

Als je de kar een functie wil laten uitvoeren of hem afzetten, kan je het via onze knoppensysteem aan de blackbox van onze kar doen.

De water toevoer knop opent het ventiel van het GreenhouseWateringSystem naar ons reservoir. De pomp knop activeert de pomp en opent het eerste niveau ventiel, zodat water naar de eerste bak kan vloeien en daarna naar de tweede bak. Met de bak legen knop stroomt het water terug naar het reservoir door het openen van beide ventielen. De water afvoer knop laat vuil water uit het reservoir vloeien. De leds knop schakelt de LEDs aan of uit. De off-knop, of killswitch, schakelt alle functionaliteit van de kar uit, inclusief de andere knoppen, zodat de kar veilig verplaatst of bewerkt kan worden.
