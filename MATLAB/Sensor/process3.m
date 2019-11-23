clear;

data;

d(:, 1) = d(:, 1) - d(1, 1);
d(:, 1) = d(:, 1)/1000000;

d(:, 2) = d(:, 2) - mean(d(:, 2));

L = 180;
Fs = 1000;
Y = fft(d(:, 2));

P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);

f = Fs*(0:(L/2))/L;
stem(f,P1) 
title('Single-Sided Amplitude Spectrum of X(t)')
xlabel('f (Hz)')
ylabel('|P1(f)|')