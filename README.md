# Balancing motorbike
Cieľ nášho projektu je vytvoriť [motorku](https://www.youtube.com/watch?v=SUVtObDFFWY), ktorá dokáže sama udržiavať v stoji pomocou toačného kynetického telesa. Telo robota vyrobíme pomocou 3D tlačiarne, podľa vlastného návrhu. Robot budeme riadiť pomocou aplikácie z android telefónu, ktorý bude komunikovať s bluetooth modulom. Ten komunikuje cez UART s STM32, ktorý používame na riadenie všetkých komponentov. V našom modely máme motor na riadenie telesa pomocou ktorého riadime náklon, motor pre pohyb dopredu a dozadu, a servomotor pre natáčanie predného kolesa. V modely ďalej použivame MEMS snímač zrýchlenia a uhlovej rýchlosti, pre zistenie aktuálneho náklonu a ampérmeter spolu s H-most pre regulovanie motorov.
## Bloková schéma
![](Documentation/Pics/Diagram.png)
## Elektricé zapojenie
![](Documentation/Pics/Schematic.png)
## Komponenty
* H-most - BTS7960
* MEMS snímač - MPU6050
* Bluetooth modul - HC-05
* Vývojová doska - STM32F303K8
* H-most - L298N
* Snímač prúdu - ACS712
* Buck regulátory napätia
* Lineárny regulátor napätia - LM7805
* Pasívne komponenty - Odpory, kondenzátory
* Akumulátor
* Micro-servo motor
## Popis
Na riadiacej doske bežia 2 regulačné obvody, s vysokou frekvenciou. Prvý RO zabezpečuje riadenie momentu motora, ktorý poháňa zotrvačník. Druhý RO udržiava rovnovážnu polohu celého zariadenia. 
Spätná väzba od prúdu je zabezpečená senzorom ACS712. Výstup senzora je definovaná, ako V<sub>out</sub>=V<sub>cc</sub>/2 + k*I. V<sub>cc</sub> je napájacie napätie, I je prúd, k je konštanta senzora. Výstup zaznamenávame A/D prevodníkom. Akčný zásah generujeme pomocou 25kHz PWM signálu.
Náklon zariadenia je meraný senzorom MPU6050, ktorý obsahuje 3-osový accelerometer a gyroskop, s 12 bitovými rozlíšeniami. So senzorom komunikujeme cez I2C zbernicu.
Motorka je riadená užívateľom z Android aplikácie, cez bluetooth. Na komunikáciu využívame UART protokol.
