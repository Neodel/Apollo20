function drawModel( q1, q5, l, l1, l2 )

figure; hold on

% Configurations Operationnal space
X1 = [0 ; 0];
X2 = [l1*cos(q1) ; l1*sin(q1) ];
X4 = [ l+l1*cos(q5) ; l1*sin(q5)];
X5 = [l ; 0];

% X3 computation
O2O4 = X4 - X2;
O2OI = 0.5*O2O4;

q2 = pi - acos(norm(O2OI)/l2) - acos( dot(-X2,O2OI)/(norm(X2)*norm(O2OI)) );
X3 = [l1*cos(q1) + l2* cos(q1-q2) ; l1*sin(q1) + l2* sin(q1-q2) ];

% Plot
plot([X1(1); X2(1)] , [X1(2); X2(2)], 'b');
plot([X2(1); X3(1)] , [X2(2); X3(2)], 'r');
plot([X3(1); X4(1)] , [X3(2); X4(2)], 'y');
plot([X4(1); X5(1)] , [X4(2); X5(2)], 'g');

axis([-0.1 0.2 -0.1 0.4]);

end

