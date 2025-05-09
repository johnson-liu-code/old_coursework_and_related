% qp_rules.m
% Transition rates and selection rules
% Ian Cooper
% School of Physics, University of Sydney
% calls simpson1d.m to find area under curve:  num must be an ODD number

% The plot for the prob density can be changed by commenting /
%   uncommenting out the lines of code for the plot.

% The code for the animated gif can be commented if you do not want it
%   saved.

clear all
close all
clc

% Inputs ----------------------------------------------------------------
state = [1 0 0 5 1 1];
n(1) = state(1);   n(2) = state(4);
L(1) = state(2);   L(2) = state(5);
mL(1) = state(3);  mL(2) = state(6);

num = 201;        % must be an ODD number

% CONSTANTS ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
h = 6.626e-34;         % J.s
hbar = 1.055e-34;      % J.s
e = 1.602e-19;         % C
me = 9.109e-31;        % kg
eps0 = 8.854e-12;      % F/m
c = 3e8;               % m./s

% Initialize arryas
N = zeros(1,2);
IP = zeros(1,3);
IT = zeros(1,3);
IR = zeros(1,3);
Ixyz = zeros(1,3);


% Azimuthal -------------------------------------------------------------
phi = linspace(0,2*pi,num)';
PHI = zeros(num,2);
PHI_PHI = zeros(1,num);
f_PHI = zeros(num,3);

PHI(:,1) = exp((1i*mL(1)).* phi)./sqrt(2*pi);
PHI(:,2) = exp((-1i*mL(2)).* phi)./sqrt(2*pi);

PHI_PHI = PHI(:,2) .* PHI(:,1);

f_PHI(:,1) = cos(phi) .* PHI_PHI;
f_PHI(:,2) = sin(phi) .* PHI_PHI;
f_PHI(:,3) = PHI_PHI;

% Dipole integral - azimuthal
for cc = 1 : 3
   IP(cc) = (simpson1d(real(f_PHI(:,cc))',0,2*pi));
end

% Angular ----------------------------------------------------------------
theta = linspace(0,pi,num)';
THETA = zeros(num,2);

THETA1 = legendre(L(1),cos(theta))';
THETA2 = legendre(L(2),cos(theta))';

THETA(:,1) = THETA1(:,mL(1)+1);
THETA(:,2) = THETA2(:,mL(2)+1);

sinT = sin(theta);

% Normalize angular wavefunctions
for cc = 1 : 2
   N(cc) = simpson1d((sinT .* THETA(:,cc) .* THETA(:,cc))',0,pi);
   THETA(:,cc) = THETA(:,cc) / sqrt(N(cc));
end

% Dipole integral - angular
sin2T = sinT.^2;
cosT = cos(theta);
THETA_THETA = THETA(:,1) .* THETA(:,2);

f_THETA(:,1) = sinT .* THETA_THETA .*sinT;
f_THETA(:,2) = f_THETA(:,1);
f_THETA(:,3) = cosT .* THETA_THETA .* sinT;

% Dipole integral - angular
for cc = 1 : 3
   IT(cc) = (simpson1d(real(f_THETA(:,cc))',0,pi));
end

% RADIAL WAVEFUNCTION ----------------------------------------------------
[ EB(1) R1 r ] = qp_fh(n(1), L(1), mL(1) );
[ EB(2) R2 r ] = qp_fh(n(2), L(2), mL(2) );

% Normalize radial wavefunctions
N(1) = simpson1d((R1 .* R1),0,max(r));
N(2) = simpson1d((R2 .* R2),0,max(r));
R1 = R1 ./ sqrt(N(1));
R2 = R2 ./ sqrt(N(2));


f_R = r .* R1 .* R2;

% Dipole integral - radial
for cc = 1 : 3
   IR(cc) = simpson1d(f_R,0,max(r));
end

% DIPOLE INTEGRAL / ELECTRIC DIPOLE MOMENT / TRANSITION RATE

for cc = 1: 3
   Ixyz(cc) = IR(cc) * IP(cc) * IT(cc);    
end

Idipole = sqrt(sum(Ixyz.^2));

p21 = e .* Idipole;

f = abs((EB(1) - EB(2)) * e /h);
wL = 1e9 * c /f;
TR = 16 * pi^3 * p21^2 * f^3 / (3 * eps0 * h * c^3);
lifeTime = 1e9/TR;


% Display results in Command Window
disp('state 2 and 1 ');
fprintf('  %0.0g ', state);
fprintf('  \n ');
disp('  ');
disp('EB: States 2 and 1 ');
fprintf(' %0.3f  ',EB);
disp('  ');
fprintf('  \n ');
fprintf('wL  %0.2f  \n ',wL);
disp('  ');
fprintf('TR  %0.4g  \n ',TR);
disp('  ');
fprintf('lifeTime  %0.2f \n  ',lifeTime);
disp('  ');
IP
IT
IR
Ixyz

% GRAPHICS - probability clouds

xp = 0; yp = 0; probS = 10; k = 0;



M = getframe(gcf);
[im,map] = rgb2ind(M.cdata,256,'nodither');  %RGB to indexed images
im(1,1,1,10) = 0;


for k = 1 : 20;
    
if k < 11; a1 = 1-k/10;  a2 = 1-a1;
   else  a2 = 1 - (k-10)/10; a1 = 1-a2;
end

nump = length(r);
maxp = max(r);

xp = zeros(1,nump); yp = zeros(1,nump);
xxx = zeros(1,num);
probS = zeros(nump,nump);
probcloud = zeros(nump,nump);

dp = 2*maxp/(nump-1);
xp = -maxp : dp : maxp; 
yp = -maxp : dp : maxp;

for c1 = 1 : nump
for c2 = 1 : nump
   
   rp = sqrt(xp(c1)^2 + yp(c2)^2);
   
if rp < maxp   
   
if xp(c1) >= 0 && yp(c2) >= 0
   theta = atan(abs(yp(c2)/(xp(c1)+eps)));
end;

if xp(c1) <= 0 && yp(c2) >= 0
   theta = pi - atan(abs(yp(c2)/(xp(c1)+eps)));
end;

if xp(c1) <= 0 && yp(c2) <= 0
   theta = pi + atan(abs(yp(c2)/(xp(c1)+eps)));
end;

if xp(c1) >= 0 && yp(c2) <= 0
   theta = 2*pi - atan(abs(yp(c2)/(xp(c1)+eps)));
end;

N = round(1 + (num-1)*(rp/max(r)));
leg01 = legendre(L(1),cos(theta));
leg01 = leg01(mL(1)+1,:);
psi1 = R1(N) .* leg01;

leg01 = legendre(L(2),cos(theta));
leg01 = leg01(mL(2)+1,:);
psi2 = R2(N) .* leg01;

psi = a1 .* psi1 + a2 .* psi2;

probcloud(c1,c2) = psi .* psi;  

else probcloud(c1,c2) = 0;

end   %if  rp < maxp 

end   %for c1
end   %for c2

%probcloud = probcloud./max(max(probcloud));
probS = probcloud .^0.5;

tm1 = num2str(k);  tm2 = '     ';
tm3 = num2str(state(1:3));   tm4 = num2str(state(4:6));
tm = [tm1 tm2 tm3 tm2 tm4];

if k == 1;
   figure(1);
   set(gcf,'Name','Cloud2','NumberTitle','off')
   set(gcf,'Units','normalized','Position',[0.3 0.3 0.3 0.3]);
   set(gcf,'color',[1 1 1]);
   set(gca,'ZLim',[0 60000]);
   pcolor(xp,yp,probS);
   colormap copper
   colorbar off;
   shading flat;
   axis square
   axis off
   M = getframe(gcf);
   [im,map] = rgb2ind(M.cdata,256,'nodither');  %RGB to indexed images
   im(1,1,1,10) = 0;
end

% ------------------------------------------------------------------------
% commment or uncomment for surf or pcolor plot

% surf(xp,yp,probS);
% shading interp;
% set(gca,'ZLim',[0 60000]);
 
pcolor(xp,yp,probS);
colormap copper
shading flat;
% ------------------------------------------------------------------------

colorbar off;
title(state);
axis square
axis off
tm1 = num2str(k);  
tm = [tm1 tm2 tm3 tm2 tm4];
title(tm);

%drawnow
M = getframe(gcf);
im(:,:,1,k) = rgb2ind(M.cdata,map,'nodither');

end  % for k


%  SAVE ANIMATED GIF ======================================================
% im - images to be saved
% map - color map for images
% ag_name - file name for animated gif
% DelayTime - time delay in seconds between viewing images
% LoopCount - animated gif will continuously
ag_name = 'ag_dipole3.gif';
delay = 0.3;
imwrite(im,map,ag_name,'DelayTime',delay,'LoopCount',inf);




