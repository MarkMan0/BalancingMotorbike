clear;
close all;
g = 9.80665;
[time, ACCX, ACCY, ACCZ, GX, GY, GZ] = getData2("C:\Users\Mark\Dropbox\project_VRS\SensorData\putty1.log", [1, Inf]);

time = time - time(1);
time = time./1000000;

ACCX = (ACCX)/100;
ACCY = (ACCY)/100;
ACCZ = (ACCZ)/100;
GX = GX/100;
GY = GY/100;
GZ = GZ/100;

means = [mean(ACCX), mean(ACCY), -1, mean(GX), mean(GY), mean(GZ)]


GX = (GX - mean(GX));
GY = (GY - mean(GY));
GZ = (GZ - mean(GZ));

data = [time, ACCX, ACCY, ACCZ, GX, GY, GZ];

for i = 2:7
    figure;
    plot(time, data(:, i));
end

dt = 0.01;
cutoff = 100;

G = tf([1/cutoff, 0], [1/cutoff, 1]);

[y2, t2] = resample(GX, time, 50);

q = lsim(G, y2, t2);