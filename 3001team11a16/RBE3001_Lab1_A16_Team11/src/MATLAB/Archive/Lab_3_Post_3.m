pos_pot = t1(1,:);
vel_pot = 0;
acc_pot = 0;

pos_enc = t1(2,:);
vel_enc = 0;
acc_enc = 0;

pos_acc = 0;
vel_acc = 0;
acc_acc = t1(4,:);

acc_acc = acc_acc - 2048;

pos_enc = -pos_enc * 1.83;

for i = 2:300
    vel_pot(end + 1) = (pos_pot(i) - pos_pot(i-1))/0.01;
    vel_enc(end + 1) = (pos_enc(i) - pos_enc(i-1))/0.01;
    vel_acc(end+1) = vel_acc(end) + acc_acc(i) * 0.01;
end
for i = 2:300
    acc_pot(end + 1) = (vel_pot(i) - vel_pot(i-1))/0.01;
    acc_enc(end + 1) = (vel_enc(i) - vel_enc(i-1))/0.01;
    pos_acc(end+1) = pos_acc(end) + vel_acc(i) * 0.01;
end

plot_time = [1:1:300];

figure;
plot(plot_time, pos_pot, plot_time, pos_enc, plot_time, pos_acc);

figure;
plot(plot_time, vel_pot, plot_time, vel_enc, plot_time, vel_acc);

figure;
plot(plot_time, acc_pot, plot_time, acc_enc, plot_time, acc_acc);


