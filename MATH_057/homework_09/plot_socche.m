

% [t, y1, dy1, ddy1] = socche(1, 0, 2, .1, 0, 10);
% [t, y2, dy2, ddy2] = socche(1, .1, 2, .1, 0, 10);
% [t, y3, dy3, ddy3] = socche(1, 1, 2, .1, 0, 10);
% [t, y4, dy4, ddy4] = socche(1, 3, 2, .1, 0, 10);
% 
% subplot(2, 2, 1)
% plot(t, y1, t, dy1, t, ddy1)
% title('\gamma = 0')
% xlabel('t')
% legend('y', 'dy', 'ddy')
% grid on
% 
% subplot(2, 2, 2)
% plot(t, y2, t, dy2, t, ddy2)
% title('\gamma = 0.1')
% xlabel('t')
% legend('y', 'dy', 'ddy')
% grid on
% 
% subplot(2, 2, 3)
% plot(t, y3, t, dy3, t, ddy3)
% title('\gamma = 1')
% xlabel('t')
% legend('y', 'dy', 'ddy')
% grid on
% 
% subplot(2, 2, 4)
% plot(t, y4, t, dy4, t, ddy4)
% title('\gamma = 3')
% xlabel('t')
% legend('y', 'dy', 'ddy')
% grid on

[t, y1, dy1, ddy1] = socche(1, 0, 1, .1, 0, 50);
[t, y2, dy2, ddy2] = socche(3, 0, 1, .1, 0, 50);
[t, y3, dy3, ddy3] = socche(10, 0, 1, .1, 0, 50);
[t, y4, dy4, ddy4] = socche(100, 0, 1, .1, 0, 50);

subplot(2, 2, 1)
plot(t, y1, t, dy1, t, ddy1)
title('m = 1, \gamma = 0, k = 1')
xlabel('t')
legend('y', 'dy', 'ddy')
grid on

subplot(2, 2, 2)
plot(t, y2, t, dy2, t, ddy2)
title('m = 3, \gamma = 0, k = 1')
xlabel('t')
legend('y', 'dy', 'ddy')
grid on

subplot(2, 2, 3)
plot(t, y3, t, dy3, t, ddy3)
title('m = 10, \gamma = 0, k = 1')
xlabel('t')
legend('y', 'dy', 'ddy')
grid on

subplot(2, 2, 4)
plot(t, y4, t, dy4, t, ddy4)
title('m = 100, \gamma = 0, k = 1')
xlabel('t')
legend('y', 'dy', 'ddy')
grid on