

t = linspace(0, 10*pi);
initial_x = 0;
initial_dxdt = 0;

[t1, x1] = ode45(@rhs1, t, [initial_x initial_dxdt]);
[t2, x2] = ode45(@rhs2, t, [initial_x initial_dxdt]);
[t3, x3] = ode45(@rhs3, t, [initial_x initial_dxdt]);

hold on
grid on
xlabel('t')
ylabel('x')

plot(t, x1(:,1))
plot(t, x2(:,1))
plot(t, x3(:,1))

a = 10;
b = .01;
y1 = -a*cos(t) - b*sin(t) + b*t + a;
plot(t, y1, 'o')

a = -.5;
b = .5;
y2 = -a*cos(t) - b*sin(t) + b*t + a;
plot(t, y2, 'o')

a = -1;
b = 1;
y3 = -a*cos(t) - b*sin(t) + b*t + a;
plot(t, y3, 'o')


function dxdt = rhs1(t, x)
    a = 10;
    b = .01;
    dxdt_1 = x(2);
    dxdt_2 = a*cos(t) + b*sin(t);
    
    dxdt = [dxdt_1; dxdt_2];
end

function dxdt = rhs2(t, x)
    a = -.5;
    b = .5;
    dxdt_1 = x(2);
    dxdt_2 = a*cos(t) + b*sin(t);
    
    dxdt = [dxdt_1; dxdt_2];
end

function dxdt = rhs3(t, x)
    a = -1;
    b = 1;
    dxdt_1 = x(2);
    dxdt_2 = a*cos(t) + b*sin(t);
    
    dxdt = [dxdt_1; dxdt_2];
end