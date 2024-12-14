# Meerlagen-eb-en-vloedkar

## Over

Dit is het project meerlagen eb- en vloedkar. Dit project maakt deel van het vak Project Experience van [VIVES](https://www.vives.be/en).
Het doel van dit project is een proof of concept maken van een automatisch watersysteem om planten te laten groeien op een meerlagenkar.

## Inhoud

- [Probleemstelling](#probleemstelling)
- [Opdracht](#opdracht)
- [Hardware](#hardware)
- [Elektronische hardware](#elektronische-hardware)
- [Software](#software)
- [Handleiding](#handleiding)
- [Eindproduct](#eindproduct)
- [Uitbreidingen](#uitbreidingen)
- [Het Team](#het-team)

## Probleemstelling

Bij VIVES is nieuwe serre geïnstalleerd, die niet alleen een functionele maar ook een inspirerende ruimte zal vormen voor zowel medewerkers als bezoekers. Deze serre zal een centrale rol spelen in diverse projecten die gekoppeld zijn aan het vak 'Project Experience', waarbij studenten van de opleiding "Elektronica-ICT" ervaring opdoen met innovatieve toepassingen. Een van de kernopdrachten binnen deze setting is het ontwikkelen van een automatisch irrigatiesysteem voor de planten in de serre. Het doel van dit systeem is om planten te voorzien van water zonder menselijke tussenkomst, maar er moet tegelijkertijd ook een mogelijkheid bestaan om het water handmatig te regelen wanneer dat nodig is.

Het systeem moet worden ontworpen als een meerlagensysteem, zodat op de meerdere lagen planten op efficiënte wijze gelijktijdig bewaterd kunnen worden. Daarnaast wordt er verwacht dat de kar die in dit irrigatiesysteem wordt geïntegreerd, een eb- en vloedfunctie heeft. Dit betekent dat het overtollige water na het bewateren van de planten gemakkelijk moet kunnen weglopen uit de bak waarin de planten zich bevinden, om waterophoping te voorkomen en de gezondheid van de planten te bevorderen.

Een belangrijke vereiste voor dit project is dat de kar volledig autonoom functioneert. Dit houdt in dat het systeem onafhankelijk moet kunnen werken zonder dat er input van andere projecten in de serre vereist is. De kar moet zelfstandig alle noodzakelijke taken kunnen uitvoeren, waardoor het irrigatiesysteem een betrouwbare en efficiënte oplossing biedt voor het onderhoud van de planten in de serre.

Op deze manier zal de serre niet alleen dienen als een praktische ruimte voor projectwerk, maar ook als een voorbeeld van technologische innovatie binnen de context van duurzaam beheer en automatisering. Dit project kan ook gasten aantrekken, en de biologische groei van VIVES bevorderen.

## Opdracht

Wij ontwikkelen een geavanceerde eb- en vloedkar, die speciaal ontworpen is om optimale omstandigheden te bieden voor de groei van planten. De kar is uitgerust met twee bakken van elk 31 liter, waarin aarde met daarin de planten wordt geplaatst. Boven deze bakken zijn LED-lampen geïnstalleerd die een specifieke lichtkleur uitstralen, zorgvuldig gekozen om de groei van de planten te stimuleren en te optimaliseren. Dit is belangrijk voordeel van dit project. In plaats van te investeren in duurdere gespecialiseerde lampen, kunnen we met dit systeem de kleur van de LED-verlichting handmatig instellen. Dit biedt niet alleen flexibiliteit in het aansturen van de lichtomstandigheden die de plantengroei bevorderen, maar zorgt ook voor aanzienlijke kostenbesparingen. Door zelf de lichtkleuren te beheren, vermijden we de hoge kosten van lampen die specifiek voor deze functie zijn ontworpen, zonder in te leveren op effectiviteit. Hierdoor combineren we kostenefficiëntie met een optimale groeiondersteuning voor de planten.

Om efficiënt om te gaan met waterbeheer, is er een apart reservoir geïntegreerd in het systeem, dat dient om het overtollige water dat uit de bakken vloeit op te vangen. Dit water wordt via een buizensysteem teruggeleid naar het reservoir, waarna het door een pomp opnieuw naar de planten kan worden getransporteerd. Dit zorgt voor een duurzaam en herbruikbaar irrigatiesysteem dat waterverbruik minimaliseert.

De bediening van de kar is eenvoudig en gebruiksvriendelijk gemaakt door middel van zes knoppen. De eerste knop opent het ventiel van het GreenhouseWateringSystem naar ons reservoir. De tweede knop is activeert de pomp en opent het eerste niveau ventiel, zodat water naar de eerste bak kan vloeien en daarna naar de tweede bak. De derde knop laat het water terugstromen naar het reservoir door het openen van beide ventielen. De vierde knop zorgt ervoor dat het vuil water uit het reservoir gaat vloeien. De vijfde knop schakelt de LEDs aan of uit.De laatste knop is een "killswitch", deze zorgt ervoor dat alle automatische functionaliteiten uitgezet worden, zodat de kar kan verplaatst worden zonder problemen.

Met deze combinatie van functionaliteit en eenvoud biedt de eb- en vloedkar een compleet systeem voor de verzorging van planten, dat zowel efficiënt als duurzaam is. Het stelt gebruikers in staat om op een gemakkelijke manier de watergift en verlichting te beheren, met de optie om het proces volledig te automatiseren indien gewenst. Het nadeel is wel dat je iets van technische kennis zal nodig hebben om dit project te laten werken, en als je het project wil wisselen tussen standalone en deel van de serre.

## Elektronische hardware

- ESP32 Wroom
- 2 x Bodemsensor OT2019-D69
- Waterpomp 12V
- 5 x waterventiel
- 2 x LEDstrip 5V
- 6 x schakelaars
- Meerdere weerstanden van verschillende waardes
- 2 x transistor BC547B
- 6 x mosfet IRL540NPBF

### ESP32 Wroom

#### Beschrijving

Voor dit project gebruiken we de ESP32 Wroom. Met behulp van deze microcontroller kunnen we de verschillende sensoren inlezen en weergeven. Deze data kan doorgestuurd worden naar het project GreenhouseNetwork-Monitoring om de data op die manier te kunnen monitoren. Daarnaast kunnen we met behulp van deze data de waterventielen, LED's, knoppen en pomp aansturen. Hieronder kan je de pinout van de ESP32 Wroom bekijken.

#### Pinout

![Pinout](/Afbeeldingen/esp32-pinout.png)

### Bodemsensor OT2019-D69

We gebruiken de bodemsensor OT2019-D69 om de vochtigheid van de aarde in de bakken te meten. We beschikken over twee sensoren, één voor elke bak. Deze data wordt in de code omgevormd naar een percentage en doorgezonden naar de dashboard van de Home Assistant groep. Hoe hoger het percentage, hoe vochtiger het is in de bak. Met deze data kan je zien hoe vochtig het is op dat moment in de bakken, zo kan je weten als je op een warmere dag extra water moet toevoegen.

![Sensor](/Afbeeldingen/sensor.jpg)

### Waterpomp

#### Beschrijving

Om het water tot aan de planten te krijgen, maken we gebruik van een waterpomp. Deze pomp moet in staat zijn het water vanuit het reservoir naar de bovenkant van de kast te pompen. Hiervoor gebruiken we de Whadda WPM421 waterpomp. Deze pomp werkt op 12 volt en kan tot 240 liter per uur, 3 meter de lucht in te pompen. Ideaal aan deze pomp is dat hij waterdicht is, want de pomp zal in het waterreservoir zitten. Deze pomp heeft ook een diameter van 8mm, wat ideaal is aangezien onze waterbuizen een binnendiameter hebben van 8mm.

![Pomp](/Afbeeldingen/pomp.jpg)

#### Aansluiting

Aangezien de esp niet genoeg stroom kan leveren om de pomp aan te sturen, maken we gebruik van een MOSFET. De MOSFET die we hiervoor gebruiken is de IRL540NPBF-ND. Met behulp van deze MOSFET kunnen we de 12 volt van de pomp schakelen met de 3.3 volt van de ESP32.

![MOSFET](/Afbeeldingen/mosfet.jpg)

Om dit allemaal te testen, hebben we een elektrisch schema opgebouwd via het online programma EasyEDA. Dit schema toont alles dat we gebruiken van elektronische componenten, en op welke pins ze geconnecteerd zijn.

![Elektrisch schema](/Afbeeldingen/Schema.png)

Deze elektronische connectie hebben we eerst geprobeerd uit te bouwen op een breadboard. Dit hebben we gedaan zodat we alles van code kunnen testen, en om eventuele fouten uit het schema te halen.

![Breadboard](/Afbeeldingen/breadboard.jpg)

### Waterventiel

#### Beschrijving

Om het  project volledig automatisch te kunnen laten werken, maken we gebruik van vijf waterventielen. Deze ventielen zorgen ervoor dat het water naar de juiste plekken wordt geleid. De ventielen die we hiervoor gebruiken zijn de Water Valve-8mm-12VDC. Deze ventielen hebben ook een diameter van 8mm, wat zoals eerder vermeld ook de diameter is van de binnenkant van onze buizen.

![Ventiel](/Afbeeldingen/ventiel.jpg)

Er zijn een aantal reden waarom we waterventielen gebruiken:

- #### Toevoer water reservoir

Wanneer het reservoir leeg is, moet er water toegevoerd worden. Dit gebeurt door het waterventiel die de connectie van het waterreservoire van het project GreenhouseWateringSystem naar het waterreservoir van onze kast open te zetten.

- #### Toevoer water 1ste plantenbak

Voor het omhoog pompen van het water uit het reservoir naar de bakken gebruiken we een waterpomp. De leiding naar de verschillende bakken wordt gesplitst met een T-stuk van 8mm om elke bak te kunnen bereiken. Om te voorkomen dat het water altijd naar het eerste niveau gaat, gebruiken we een waterventiel om de toevoer van water op het eerste niveau te belemmeren. Eerst krijgt de bak op het eerste niveau water, dan sluit de ventiel zodat het water naar de bak op het tweede niveau kan stromen. 

- #### Afvoer water plantenbakken

Om het water uit de plantenbakken te legen, maken we ook hier gebruik van een waterventiel. Elk niveau van de kast krijgt een eigen ventiel om op die manier volledige controle te krijgen over het waterpeil in de bakken. Als er teveel water zit, worden de waterventielen geopend en stroomt het water uit de bakken weg naar het waterreservoir.

- #### Afvoer water reservoir

Wanneer het water te vuil wordt of wanneer de voedingstoffen uit het water zijn verdwenen, moet het water uit het reservoir worden afgevoerd. Dit gebeurt door een ventiel onderaan het reservoir open te zetten met een afvoer naar buiten.

### Aansluiting

Ook voor de waterventielen is de 3.3 volt die de ESP32 kan geven niet genoeg. Daarom maken we ook hiervoor gebruik van vijf MOSFETs, één MOSFET per ventiel. Dit is dezelfde als voor de waterpomp, namelijk de IRL540NPBF-ND.

### LEDstrip 5V

Op elk niveau met een bak zijn er twee LEDstrips bevestigd. In het begin van dit project hebben we met een expert van plantengroei in VIVES Roeselaere gepraat. Deze expert heeft meegegeven dat het ideaal is dat de planten bestraalt worden met extra LED verlichting naast zonlicht. Met zijn advies hebben we geïnvesteerd in een SK6812 RGBW LEDstrip van 5 volt. Van deze expert kregen we ook mee wat de ideale LED configuratie is om de plantengroei te stimuleren. Dit was namelijk R:100, G:30, B:25. Hieronder kan je zien hoe dit eruit ziet.

![LEDs](/Afbeeldingen/leds.jpg)

### Knoppen

Aan onze kar hebben we onze "black box". In deze box steken we de ESP32 en andere elektronische componenten zodat dit beschermt is tegen het water en zodat er geen onbevoegde mensen aankomen. Aan het deksel van de blackbox zitten zes knoppen bevestigd. Deze knoppen zorgen ervoor dat je een functie onmiddellijk kan uitvoeren, want deze kar moet automatisch werken, maar ook op aanvraag. Hieronder kan je de knoppen zien.

![LEDs](/Afbeeldingen/knoppen.png)

Elke knop heeft zijn eigen functie:

- #### Water toevoer

Als je op deze knop drukt, opent de ventiel van het waterreservoir van het team GreenhouseWateringSystem naar ons reservoir.

- #### Pomp

Door het drukken op deze knop, laat je de pomp werken. Hiermee wordt de ventiel op het eerste niveau ook geopend, zodat het water in de eerste bak kan vloeien. Na enige tijd zal deze ventiel sluiten zodat het water ook naar de tweede bak kan vloeien.

- #### Bak legen

Met deze knop laten we het water van de bakken terug naar het waterreservoir vloeien. Hiermee openen beide ventielen die aan de kant van het wegvloeien staan, zodat het "vuil" water terug in het waterreservoir kan vloeien.

- #### Water Afvoer

Via deze knop laat je het vuil water uit het waterreservoir vloeien.

- #### Leds

Deze knop laat de LEDs aan of uit gaan.

- #### Off

De laatste, maar wel belangrijkste knop is de off-knop, oftewel de killswitch. Deze knop zorgt ervoor dat alle functionaliteit van de kar uit staat. Hiermee zet je ook de andere knoppen uit. Deze knop is belangrijk, want de kar is bedoeld voor de serre, maar moet ook apart kunnen staan. Als alle functionaliteit uit staat, kan je zonder zorgen de kast verplaatsen of bewerkingen maken, zonder te prutsen aan de ESP.

### Lichtsensor UPRtek PAR200

De lichtsensor mochten we gebruiken van VIVES Roeselaere. Met deze sensor kunnen we heel wat info over het licht krijgen. Hiermee kunnen we ondermeer de CCT (Correlated Color Temperature), LUX (Verlichting) en de PPFD (Photosynthetic Photon Flux Density) meten. Dit is interessant om zo de LED's te meten, zodat we ervoor kunnen zorgen dat de uitstraling van de LED's correleert met de groei van de planten.

![Licht](/Afbeeldingen/licht.png)

# Software

Voor dit project werken we met Platform IO. Dit gebruiken we zodat we de library Adafruit Neopixel kunnen gebruiken om de LED's aan te sturen. Verder werken we ook met Alarm() om het automatisch proces te laten werken, en verder hebben we een apart bestand waar alles van functie definities en pin definities staan. We hebben ook een integratie met Home Assistant. Hiervoor hebben we de nodige libraries gebruikt, onze twee sensoren via hun gedefinieerd en de data van de sensoren laten doorzenden.

# Handleiding

Als je code wilt aanpassen of nog eens wil herstarten, kan je [hier](/Project%20management/handleiding.md) een handleiding van de code vinden.

# Eindproduct

![Eindproduct](/Afbeeldingen/eindproduct.jpg)

# Uitbreidingen

Mogelijke uitbreidingen:

- Een lagensysteem van drie lagen gebruiken. Hierbij zou je extra buizen, een nieuwe doos, ventiel en sensor moeten voorzien en de code moet aangepast worden.

- Een systeem dat ervoor zorgt dat de bakken apart werken. Hiermee zou het mogelijk zijn om planten die meer of minder water nodig hebben te combineren met andere, zonder dat er interferentie van beide zou komen.

- Een filtratiesysteem, om het vuiligheid in het water niet laten gepompt worden naar de dozen.

- Automatische vochtigheiddetectie, zodat er automatisch water wordt toegevoegd als het waterniveau begint te zakken.

## Het Team

- [Alberiek Depreytere](https://github.com/AlberiekDepreytere) SCRUMmaster
- [William Rogov](https://github.com/Rwill03)
- [Jonas De Rous](https://github.com/JonasTBUP)
- [Vic Verbiest](https://github.com/Vic-Verbiest)
