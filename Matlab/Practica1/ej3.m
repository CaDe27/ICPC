format long
clc; clear; close all;

A = [1, -2, 0; 
    1, 17, -2; 
    5, 7,   7]
[V, D] = eig(A);

%ejercicio 3
%usamos la base canonica
q0 = [0,0,1]'
[s, q, it] = metodo_potencia_invRayleigh(A, q0, 10)

q0 = [1,0 ,0]'
[s, q, it] = metodo_potencia_invRayleigh(A, q0, 10)

q0 = [0,1,0]'
[s, q, it] = metodo_potencia_invRayleigh(A, q0, 10)

%verificamos que la convergencia es cuadrática para el último
% para esto hay que ver que en+1 = k* en^2 
v = V(:, 3);
if( sum(v>0) < sum(v<0))
    v = -v;
end
%calculo de razones para j = 1:n
n = 4;
razones = zeros(n,1);
errores = zeros(n+1, 1);
[~, qj] = metodo_potencia_invRayleigh(A, q0, 1);
errores(1) = norm(qj - v, "inf");
for j = 1:n
    [~,qj1] = metodo_potencia_invRayleigh(A, q0,j+1);
    errores(j+1) = norm(qj1 - v, "inf");
    razones(j) = errores(j+1)/errores(j)^2;
    qj = qj1;
end
errores
razones

errores(4)^2
errores(5)

