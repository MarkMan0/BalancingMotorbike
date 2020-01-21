# Zhrnutie
## Ovládanie
Motorku vieme ovládať vytvorenou aplikáciou z androidu. Z aplikácie vieme ovládať motorku dopredu, dozadu a natáčať predné koleso do strán. Všetky parametre pre regulátory vieme meniť taktiež z prostredia aplikácie. 

## Návod na použitie
Po spárovaní telefónu s robotom musíme poslať štartovací signál po ktorom sa motorka začne inicializovať. V tom čase musí byť motorka v kľudnom stave. Následne po tejto inicializácií posielame druhý signál, ktorým spustíme balancovanie. Motorka sa musí nachádzať pred odoslaním druhého signálu vo vodorovnom stave. 

## Dokumentácia
![alt text](/Documentation/Pics/Program_logic.png)\
Naklonenie motorky čítame v hlavnej slučke programu cez I2C zbernicu s približnou frekvenciou 1 kHz. \
Príkazy pre ovládanie prijímame cez UART1 (bluetooth) a UART2 (USB). TIM1 generuje vysokofrekvenčný (22 kHz) PWM signál v Center aligned móde. Tento TIM1 spúšťa vzorkovane pomocou ADC. Na konniec konvertovania ADC zavolá DMA, ktorá kopíruje načítané hodnoty do pamäte.\
TIM6 volá funkciu prúdového regulátora s frekvenciou 10 kHz. \
TIM2 funguje v encoder móde, ktorý meria polohu zotrvačníka.\
TIM16 generuje PWM signál pre servo, ktorým otáčame predné koleso. Na update evente tohto časovača rátame rýchlosť zotrvačníka. \
TIM3 generuje PWM sinál pre zadný motor, ktorým poháňame motorku. 

## Príkazy
* Q - rýchlosť
* W - servo
* M - prúdový regulátor Kp
* N - prúdový regulátor Ki
* B - prúdový regulátor želaná hodnota
* V - pozastaviť PR
* C - pokračovať PR
* X - resetovať PR integrátor
* L - balance regulátor Kp
* K - balance regulátor Ki
* J - balance regulátor Kd


## Zhodnotenie 
Programová časť kódu spĺňa všetky body špecifikácie, ktoré sme si stanovili na začiatku práce. Pre nedostatočné skusenosti s vlasnosťami PETG materiálov sme neodhadli pevnosť a preto sa nám nepodarilo dosiahnuť rovnováhu motorky. Regulátor sa pokúša dostať motorku do rovnovážneho stavu vyvijaním veľkého momentu, ktorý nám zakaždým zničí naše vytlačené komponenty. 

