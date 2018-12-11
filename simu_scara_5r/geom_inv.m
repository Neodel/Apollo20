function [q1,q2] = geom_inv(x,y)
%% Initialisation des variables
l1 = 0.065;
l2 = 0.080;
d = 0.02;
O1 = [0 0];
O2 = [d 0];
% O1 actionneur gauche, O2 actionneur droit, G 2eme pivot gauche D deuxieme
% pivot droit X organe terminal
%% Résolution équation intersection deux cercles 
%Système équation O1-X
a1 = (l1*l1 - l2*l2 + x*x - O1(1)*O1(1) + y*y - O1(2)*O1(2))/(2*(y-O1(2)));
d1 = (x-O1(1))/(y-O1(2));
A1 = d1*d1 + 1;
B1 = 2*y*d1 -2*a1*d1 - 2*x;
C1 = x*x + y*y + a1*a1 - l2*l2 - 2*y*a1;
delta1 = B1*B1 -4*A1*C1;
%Système O2-X
a2 = (l1*l1 - l2*l2 + x*x - O2(1)*O2(1) + y*y - O2(2)*O2(2))/(2*(y-O2(2)));
d2 = (x-O2(1))/(y-O2(2));
A2 = d2*d2 + 1;
B2 = -2*x + 2*y*d2 -2*a2*d2;
C2 = x*x + y*y - 2*y*a2 +a2*a2 - l2*l2;
delta2 = B2*B2 -4*A2*C2;
%Si le point n'est pas atteignable
if(delta1 <0 || delta2 <0)
    disp('Pas possible');
    return;
else
    OG1X = (-B1+sqrt(delta1))/2*A1;
    OG2X = (-B1-sqrt(delta1))/2*A1;
    Og = min(OG1X,OG2X);
    OG = [ Og (a1 -Og*d1)];
    OG1 = [ OG1X (a1 -OG1X*d1)];
    OG2 = [OG2X (a1-OG2X*d1)];
      
    OD1X = (-B2+sqrt(delta2))/2*A2;
    OD2X = (-B2-sqrt(delta2))/2*A2;
    Od = max(OD1X,OD2X);
    OD = [ Od (a2-Od*d2)];
    OD1 = [ OD1X (a2 -OD1X*d2)];
    OD2 = [OD2X (a2-OD2X*d2)];
end
%% Calcul orientation du modèle
% Création des vecteurs
O1G = [OG(1)-O1(1) OG(2)-O1(2)];
O2D = [OD(1)-O2(1) OD(2)-O2(2)];
GX = [x-OG(1) y-OG(2)];
DX = [x-OD(1) y-OD(2)];
L11 = norm(O1G)
L12 = norm(O2D)
L21 = norm(GX)
L22 = norm(DX)
% Calcul de l'orientation
q1 = acos(dot(O1G,[1 0])/norm(O1G));
q2 = acos(dot(O2D, [1 0])/norm(O2D));

%% Dessin 
th = 0:pi/50:2*pi;
xunit1 = l1 * cos(th) + O1(1);
yunit1 = l1 * sin(th) + O1(2);

xunit2 = l1 * cos(th) + O2(1);
yunit2 = l1 * sin(th) + O2(2);

xunit3 = l2 * cos(th) + x;
yunit3 = l2 * sin(th) + y;

figure;
%Points :
plot(O2(1),O2(2),'o');
hold on;
plot(O1(1),O1(2),'o');
hold on;
plot(OG(1),OG(2),'o');
hold on;
plot(OD(1),OD(2),'o');
hold on;
plot(x,y,'o');
hold on;
% Segments
plot([O1(1) OG(1)],[O1(2) OG(2)],'b');
hold on;
%plot([O1(1) OG1(1)],[O1(2) OG1(2)],'b');
%hold on;

plot([O2(1) OD(1)],[O2(2) OD(2)],'r');
hold on;
%plot([O2(1) OD(1)],[O2(2) OD(2)],'r');
%hold on;
plot([OG(1) x],[OG(2) y],'y');
hold on;
%plot([OG1(1) x],[OG1(2) y],'y');
%hold on;
plot([OD(1) x],[OD(2) y],'black');
hold on;
%plot([OD2(1) x],[OD2(2) y],'black');
%hold on;
% Cercles :
plot(xunit1, yunit1);
hold on;
plot(xunit2, yunit2);
hold on;
plot(xunit3, yunit3);
hold on;
end