
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Simulation : Scara Robot parallel 5R
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% System dimensions :
l = 0.02;
l1 = 0.065;
l2 = 0.08;

% motor cmd
q1 = pi/3;
q5 = 0;

% Simulation
drawModel( q1, q5, l, l1, l2 );