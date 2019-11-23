clear;


cutoff = 2*pi*2;
T = 1/cutoff;
G = tf([T, 0], [T, 1]);

G2 = c2d(G, 1/1000);

bode(G2);

P = bodeoptions; P.FreqUnits = 'Hz';
h = bodeplot(G2,P);

HP = filt(G2.Numerator{1}, G2.Denominator{1}, 1/1000);

cutoff = 2*pi*5;
T = 1/cutoff;

G = tf([1], [T, 1]);

G2 = c2d(G, 1/1000);

LP = filt(G2.Numerator{1}, G2.Denominator{1}, 1/1000)