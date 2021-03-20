clear;
data_list = table2array(readtable('data_array.csv'));
for i = 4:15
	x(i-3) = 2^i;
    x1(i-3) = 2^i;
    x(i-3) = x(i-3)^2 + x(i-3);
    b = data_list(i,:);
	y(i-3) = mean(b);
    y1(i-3) = y(i-3);
    error(i-3) = sqrt(sum((b - y(i-3)).^2)/29);
    error1(i-3) = error(i-3);
    error(i-3) = sqrt(3)*error(i-3);
    output(i-3, 1) = x1(i-3);
    output(i-3, 2) = y1(i-3);
    output(i-3, 3) = error1(i-3);
    output(i-3, 4) = x(i-3);
    output(i-3, 5) = y(i-3);
    output(i-3, 6) = error(i-3);
    output(i-3, 7) = 0;
end
%ПОДСЧЕТ МЕТОДОМ ПИРСОНА
weighs = (1./error).^2;
k_list = (sum(x.*y.*weighs)*sum(weighs) - sum(x.*weighs)*sum(y.*weighs))/(sum(x.^2.*weighs)*sum(weighs) - sum(x.*weighs)^2);
b_list = sum(y.*weighs)/sum(weighs) - k_list*sum(x.*weighs)/sum(weighs);
dk = 0;
db = 0;
while (sum((y - ((k_list + dk)*x + b_list)).^2.*weighs)/20 - sum((y - (k_list*x + b_list)).^2.*weighs)/20 < 1)
    dk = dk + 0.001;
end
while (sum((y - (k_list*x + b_list + db)).^2.*weighs)/20 - sum((y - (k_list*x + b_list)).^2.*weighs)/20 < 1)
    db = db + 0.001;
end
chi = sum((y - (k_list*x + b_list)).^2.*weighs)/20;
hold on;
errorbar(x, y, error, '.');
y = k_list*x + b_list;
plot(x, y);
hold off;
figure;
hold on;
ox = 0:100:35000;
oy = k_list*(ox.^2 + ox);
plot(ox, oy);
errorbar(x1, y1, error1, '.');
hold off;
output(1, 7) = k_list;
output(2, 7) = dk;
output(3, 7) = b_list;
output(4, 7) = db;
output = table(output);
writetable(output, 'out_array.csv','WriteVariableNames', false);
