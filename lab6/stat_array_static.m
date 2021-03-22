clear;
data_list = table2array(readtable('data_array_static.csv'));
for i = 12:26
	x(i-11) = i;
    x1(i-11) = 2^i;
    b = data_list(i,:);
	y(i-11) = mean(b);
    y1(i-11) = y(i-11);
    error(i-11) = sqrt(sum((b - y(i-11)).^2)/29);
    error1(i-11) = error(i-11);
    y(i-11) = log2(y(i-11));
    error(i-11) = (error(i-11)/(mean(b)*log(2)))*y(i-11);
    output(i-11, 1) = x1(i-11);
    output(i-11, 2) = y1(i-11);
    output(i-11, 3) = error1(i-11);
    output(i-11, 4) = x(i-11);
    output(i-11, 5) = y(i-11);
    output(i-11, 6) = error(i-11);
    output(i -11, 7) = 0;
end
%ПОДСЧЕТ МЕТОДОМ ПИРСОНА
weighs = (1./error).^2;
k_list = (sum(x.*y.*weighs)*sum(weighs) - sum(x.*weighs)*sum(y.*weighs))/(sum(x.^2.*weighs)*sum(weighs) - sum(x.*weighs)^2);
b_list = sum(y.*weighs)/sum(weighs) - k_list*sum(x.*weighs)/sum(weighs);
dk = 0;
db = 0;
while (sum((y - ((k_list + dk)*x + b_list)).^2.*weighs) - sum((y - (k_list*x + b_list)).^2.*weighs) < 1)
    dk = dk + 0.001;
end
while (sum((y - (k_list*x + b_list + db)).^2.*weighs) - sum((y - (k_list*x + b_list)).^2.*weighs) < 1)
    db = db + 0.001;
end
chi = sum((y - (k_list*x + b_list)).^2.*weighs);
hold on;
errorbar(x, y, error, '.');
y = k_list*x + b_list;
plot(x, y);
hold off;
figure;
hold on;
ox = 0:1000:100000000;
oy = 2^b_list*ox.^k_list;
plot(ox, oy);
errorbar(x1, y1, error1, '.');
hold off;
output(1, 7) = k_list;
output(2, 7) = dk;
output(3, 7) = b_list;
output(4, 7) = db;
output = table(output);
writetable(output, 'out_array_static.csv','WriteVariableNames', false);
