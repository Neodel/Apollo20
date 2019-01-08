function [q1,q2] = geom_inv(x,y)
%% Initialisation des variables
COSPI_4 = sqrt(2)/2;
L1 = 0.065 ;
L2 = 0.08;
D = 0.02;
LT = 0.01;
R_OT_O2 = sqrt( (L2 + LT*sqrt(2)/2)*(L2 + LT*sqrt(2)/2) +  (LT*sqrt(2)/2)*(LT*sqrt(2)/2) );

% % O1 actionneur gauche, O2 actionneur droit, G 2eme pivot gauche D deuxieme
% % pivot droit X organe terminal
% %% Résolution équation intersection deux cercles 
% %Système équation O1-X
% R1 = sqrt((x-O1(1))*(x-O1(1))+(y-O1(2))*(y-O1(2))); % distance entre centres
% ua1 = [(x-O1(1))/R1 (y-O1(2))/R1];%vecteur colinéaire 
% ub1 = [ ua1(2) -ua1(1)]; %vecteur orthogonal
% c1 = [(x+O1(1))/2 (y+O1(2))/2]; % centre segment cercle
% if(R1 > l1+l2)
%     disp('Pas possible O1');
%     return;
% end
% a1 = (l1*l1 - l2*l2)/(2*R1);
% b11 = sqrt((l1*l1+l2*l2)/2 -(l1*l1-l2*l2)*(l1*l1-l2*l2)/(4*R1*R1) -R1*R1/4);
% b12 = -sqrt((l1*l1+l2*l2)/2 -(l1*l1-l2*l2)*(l1*l1-l2*l2)/(4*R1*R1) -R1*R1/4);
% OG1 = c1 + a1*ua1 + b11*ub1; % premiere solution
% OG2 = c1 + a1*ua1 + b12*ub1; % deuxieme solution
% if(OG1(1) < OG2(1)) % prendre solution la plus a gauche
%     OG = OG1;
% else
%     OG = OG2;
% end
% %Système d'équation 02-X
% R2 = sqrt((x-O2(1))*(x-O2(1))+(y-O2(2))*(y-O1(2)));
% ua2 = [(x-O2(1))/R2 (y-O2(2))/R2];
% ub2 = [ ua2(2) -ua2(1)];
% c2 = [(x+O2(1))/2 (y+O2(2))/2];
% if(R2 > l1+l2)
%     disp('Pas possible O2');
%     return;
% end
% a2 = (l1*l1 - l2*l2)/(2*R2);
% b21 = sqrt((l1*l1+l2*l2)/2 -(l1*l1-l2*l2)*(l1*l1-l2*l2)/(4*R2*R2) -R2*R2/4);
% b22 = -sqrt((l1*l1+l2*l2)/2 -(l1*l1-l2*l2)*(l1*l1-l2*l2)/(4*R1*R1) -R2*R2/4);
% OD1 = c2 + a2*ua2 + b21*ub2;
% OD2 = c2 + a2*ua2 + b22*ub2;
% if(OD1(1) < OD2(1)) % prendre solution la plus a droite
%     OD = OG2;
% else
%     OD = OD1;
% end
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
q1 = acos(dot(O1G,[1 0])/norm(O1G))
q2 = acos(dot(O2D, [1 0])/norm(O2D))

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