

t = linspace(0, 10)

x = 3*t - t.*log(t) + 2*log(t) + 4
fdx = 2 - log(t) + 2./t
sdx = -1./t - 2./t.^2

f1 = t.^2 .* sdx - t .* fdx + x
f2 = 2.*log(t)


hold on

plot(t, f1, '+')
plot(t, f2)