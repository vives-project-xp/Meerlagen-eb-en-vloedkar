# Meerlagen-eb-en-vloedkar

# Over
Dit is het project Meerlagen eb- en vloedkar. Dit project is deel van het vak Project Experience van [VIVES](https://www.vives.be/en).
Het doel van dit project is een proof of concept maken van een automatisch watersysteem om planten te laten groeien op een kar.

# Inhoud
- [Probleemstelling](#probleemstelling)
- [Opdracht](#opdracht)
- [Hardware](#hardware)
- [Het Team](#het-team)

# Probleemstelling
Bij VIVES wordt een nieuwe serre geïnstalleerd, die niet alleen een functionele maar ook een inspirerende ruimte zal vormen voor zowel medewerkers als bezoekers. Deze serre zal een centrale rol spelen in diverse projecten die gekoppeld zijn aan het vak 'Project Experience', waarbij studenten van de opleiding "Elektronica-ICT" ervaring opdoen met innovatieve toepassingen. Een van de kernopdrachten binnen deze setting is het ontwikkelen van een automatisch irrigatiesysteem voor de planten in de serre. Het doel van dit systeem is om planten te voorzien van water zonder menselijke tussenkomst, maar er moet tegelijkertijd ook een mogelijkheid bestaan om het water handmatig te regelen wanneer dat nodig is.

Het systeem moet worden ontworpen als een meerlagensysteem, zodat op de meerdere lagen planten op efficiënte wijze gelijktijdig bewaterd kunnen worden. Daarnaast wordt er verwacht dat de kar die in dit irrigatiesysteem wordt geïntegreerd, een eb- en vloedfunctie heeft. Dit betekent dat het overtollige water na het bewateren van de planten gemakkelijk moet kunnen weglopen uit de bak waarin de planten zich bevinden, om waterophoping te voorkomen en de gezondheid van de planten te bevorderen.

Een belangrijke vereiste voor dit project is dat de kar volledig autonoom functioneert. Dit houdt in dat het systeem onafhankelijk moet kunnen werken zonder dat er input van andere projecten in de serre vereist is. De kar moet zelfstandig alle noodzakelijke taken kunnen uitvoeren, waardoor het irrigatiesysteem een betrouwbare en efficiënte oplossing biedt voor het onderhoud van de planten in de serre.

Op deze manier zal de serre niet alleen dienen als een praktische ruimte voor projectwerk, maar ook als een voorbeeld van technologische innovatie binnen de context van duurzaam beheer en automatisering. Dit project kan ook gasten aantrekken, en de biologische groei van VIVES bevorderen.

# Opdracht
Wij ontwikkelen een geavanceerde eb- en vloedkar, die speciaal ontworpen is om optimale omstandigheden te bieden voor de groei van planten. De kar is uitgerust met twee bakken van elk 31 liter, waarin aarde met daarin de planten wordt geplaatst. Boven deze bakken zijn LED-lampen geïnstalleerd die een specifieke lichtkleur uitstralen, zorgvuldig gekozen om de groei van de planten te stimuleren en te optimaliseren. Dit is belangrijk voordeel van dit project. In plaats van te investeren in duurdere gespecialiseerde lampen, kunnen we met dit systeem de kleur van de LED-verlichting handmatig instellen. Dit biedt niet alleen flexibiliteit in het aansturen van de lichtomstandigheden die de plantengroei bevorderen, maar zorgt ook voor aanzienlijke kostenbesparingen. Door zelf de lichtkleuren te beheren, vermijden we de hoge kosten van lampen die specifiek voor deze functie zijn ontworpen, zonder in te leveren op effectiviteit. Hierdoor combineren we kostenefficiëntie met een optimale groeiondersteuning voor de planten.

Om efficiënt om te gaan met waterbeheer, is er een apart reservoir geïntegreerd in het systeem, dat dient om het overtollige water dat uit de bakken vloeit op te vangen. Dit water wordt via een buizensysteem teruggeleid naar het reservoir, waarna het door een pomp opnieuw naar de planten kan worden getransporteerd. Dit zorgt voor een duurzaam en herbruikbaar irrigatiesysteem dat waterverbruik minimaliseert.

De bediening van de kar is eenvoudig en gebruiksvriendelijk gemaakt door middel van drie knoppen. De eerste knop regelt de waterstroom naar de bakken, waarmee het water kan worden toegelaten of gestopt. De tweede knop is verantwoordelijk voor het in- en uitschakelen van de LED-verlichting boven de planten. De derde knop biedt de mogelijkheid om te schakelen tussen handmatige en automatische werking van het systeem, waardoor gebruikers flexibiliteit hebben om het irrigatieproces naar wens te controleren.

Met deze combinatie van functionaliteit en eenvoud biedt de eb- en vloedkar een compleet systeem voor de verzorging van planten, dat zowel efficiënt als duurzaam is. Het stelt gebruikers in staat om op een gemakkelijke manier de watergift en verlichting te beheren, met de optie om het proces volledig te automatiseren indien gewenst. Het nadeel is wel dat je iets van technische kennis zal nodighebben om dit project te laten werken, en als je het project wil wisselen tussen standalone en deel van de serre.

# Elektrionische hardware
- ESP32 wroom 02
- 2 x Bodemsensor OT2019-D69
- Waterpomp 12V Waterventiel
- 5 x waterventiel 
- 2 x LEDstrip 24V
- Lichtsensor <vul type in als we het weten>
- 3 x drukknop
- weerstanden
- 2 x transistor
- 6 x mosfet

## esp32 wroom 
### Beschrijving
Voor dit project gebruiken we de esp32 wroom. Met behulp van deze microcontroller kunnen we de verschillende sensoren inlezen en met behulp van deze data de waterventielen en pompen aansturen. Daarnaast kan ale data later worden doorgestuurd naar het project GreenhouseNetwork-Monitoring om de data op die manier te kunnen monitoren.
### Pinout
<img title="esp32-wroom pinout" src="/foto/esp32-pinout.png">

## Bodemsensor OT2019-D69

## Waterpomp
### Beschrijving
Om het water to aan de planten te krijgen, moet gebruik worden gemaakt van een pomp. Deze pomp moet in staat zijn het water vanuit het reservoir naar de bovenkant bevenkant van de kast te pompen. Hiervoor gebruiken we de Whadda WPM421 waterpomp. Deze pomp werkt op 12 vold en kan tot 240 liter per uur , 3 meter de lucht in te pompen.
<img title="Whadda WPM421" src="/foto/esp32-pinout.png">

### Aansluiting
Aangezien de esp niet genoeg stroom kan leveren om de pomp aan te sturen, moet er gebruik worden gemaakt van een mosfet. De mosfet die we hier voor gebruiken is de IRL540NPBF-ND. Met behulp van deze mosfet kunnen we de De 12 volt van de pomp schakelen met de 3.3 volt van de esp32.
<img title="aansluiting pomp" src="/foto/esp32-pinout.png">

## waterventiel
### Beschrijving
Om het  project volledig automatisch te kunnen laten werken, zijn er 5 waterventielen nodig. Deze ventielen zorgen ervoor dat het water naar de juiste plekken wordt geleid. De ventielen die we hiervoor gebruiken zijn de Water Valve-8mm-12VDC.

Er zijn een aantal reden waarom we waterventielen gebruiken.
- #### toevoer water reservoir
Wanneer het reservoir leeg is, is het de bedoeling dat er water wordt toegevoerd. Dir kan gebeuren door een waterventiel open te zetten van het reservoire van het project GreenhouseWateringSystem naar het reservoire ven onze kast.
- #### afvoer water reservoir
Wanneer het water te vuil wordt of wanneer de voedingstoffen uit het water zijn verdwenen, moet water uit het reservoir worden afgevoerd. Dit kan de door een ventiel onderaan het reservoir open te zetten met een afvoer naar buiten.
- #### afvoer water plantenbakken
Om het water uit de planetenbakken te legen, maken ook hier gebruik van een waterventiel. elk niveau  van de kast krijgen een eigen ventiel om op die manier volledige controle te krijgen over het waterpeil in de bakken. 
- #### toevoer water 1ste plantenbak
Voor het omhoog pomppen van water gebruiken we 1 pompen. De leiding naar de verschillende bakken wordt gesplitst om elke bak te kunnen berijken. Om te voorkomen dat het water altijd naar het eerste niveau gaat, gebruiken we een waterventiel om de toevoer van water op het eerste niveau te belemmern.

### Aansluiting
Ook voor de waterventielen is de 3.3 volt die de esp kan geven niet genoeg. Daarom maken we ook hiervoor een gebruik van een mosfet. Dit is voor het gemak opnieuw de IRL540NPBF-ND. De werking  in deze situatie is gelijk aan de pomp.
<img title="waterventiel pomp" src="/foto/esp32-pinout.png">

## LEDstrip 24V


## Lichtsensor <vul type in als we het weten>

# Software
Voor dit project zullen we werken met Platform IO. Dit gebruiken we zodat we de library Adafruit Neopixel kunnen gebruiken om de LED's aan te sturen.

# Bouw van kast
- Kast 173x90x40cm
- Flexibele buizen 10Mx16mm
- 2 x Doos 31L

## Het Team
- [Alberiek Depreytere](https://github.com/AlberiekDepreytere) SCRUMmaster
- [William Rogov](https://github.com/Rwill03)
- [Jonas De Rous](https://github.com/JonasTBUP)
- [Vic Verbiest](https://github.com/Vic-Verbiest)


