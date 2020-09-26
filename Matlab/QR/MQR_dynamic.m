function [lambdas, Qm, itT] = MQR_dynamic(A, k, tol)
%{
    % Aplica el algoritmo QR dinámico para encontrar los eigenvalores de A
     Devuelve los eigenvectores de la matriz, si la matriz Q a la que llega
     es tal que Qm'*A*Qm es triangular, o solo la matriz Qm, con Qm'*A*Qm
     triangular superior por bloques de tamanio a lo más dos en los bloques
     de la diagonal

       Entrada:
            A - matriz de la que obtenemos vectores y valores propios
            k - limite de iteraciones para aproximar cada eigenvalor
            tol - tolerancia absoluta
    Salida:
        lambdas- vector con eigenvalores de A
        
        Q      - los eigenvectores de la matriz si Qm*A*Qm es triangular
                 o una matriz unitaria tal que Q'AQ es triangular superior
                 por bloques, con estos bloque siendo maximo de 2x2
        
%}
    
    %usamos la hessiana
    [P,H] = hess(A);
    itT=0;
    
    % aplicamos QR a H
        n = length(H);
        %guardamos la dimension original para la construcción de Qm
        nOriginal = n;
        Qm = eye(n);
        lambdas = zeros(n, 1);
        
        while( n > 1 )
           
            it = 0;
            while( abs(H(n, n-1)) > tol && it < k)
                %vemos que shift usar 
                % si es de la forma
                %    am-1    bm
                %   -bm    am
                % usamos el shift de wilkinson 
              
                if( abs(H(n, n-1) + H(n-1, n)) < tol)
                   %usamos el shift de wilkinson
                   s = (H(n-1,n-1) - H(n,n))/2;
                   b = abs(H(n-1,n));
                   if s == 0
                      rho = H(n,n) - b;
                   else
                      rho = H(n,n) - sign(s)*b^2/(abs(s) + sqrt(s^2 + b^2));
                     
                   end
                %si no, usamos el shift dado por el cociente de Rayleigh
                %del vector canónico en
                else
                    rho = H(n,n);
                end
                
                   
                %aplicamos la iteracion del método QR
                [Q, R ]= qr(H- rho.*eye(n));
                H = R*Q + rho.*eye(n);
                    
                %Para la construcción de Q, usamos Q y la rellenamos con
                %vectores canónicos, es claro que esta matriz es unitaria,
                %y lo unico no claro es que esta mantiene la relación de
                %similaridad
                
                % si Hn es nuestra H actual,
                %entonces sabemos que es similar unitaria a H_(n-1)
                % con Hn = Q' * H_(n-1) * Q
                % lo que queremos probar es que la matriz
                % [ Hn V ]  es similar unitaria a [H_(n-1)  X ]
                % [ 0  T ]                        [ 0       T ]
                % donde V, y X no nos importa que sean, y T es una matriz
                % triangular superior por bloques que guarda la informacion
                % de los eigenvalores que encontramos en iteraciones
                % anteriores
                
                %Pero veamos que Qn que proponemos mantiene la relacion 
                % unitaria entre ellas
                %  [Q'  0] [ H_(n-1) X ] [Q   0] =  [Q'  0] [ H_(n-1)Q+ X*0   H_(n-1)0 + XI]
                %  [0   I] [ 0       T ] [0   I]    [0   I] [ Q'0 + T0            0*0 + T*I] 
                %                                
                %                                =  [Q'  0] [ H_(n-1)Q   X]
                %                                   [0   I] [    0       T] 
                %
                %                                =  [Q'H_(n-1)Q  + 0*0   Q'X + 0T]
                %                                   [ 0*H_(n-1)Q + I*0   0*X + I*T]
                %
                %                                 = [ Hn   Q'X ]
                %                                   [ 0    T   ]
                
                % asi que esta Q mantiene la relacion unitaria entre
                % estas matrices, y al final tendremos que Qm'*A*Qm va a
                % ser triangular superior con bloques de dimension uno o
                % dos en su diagonal
                
                % T es la matriz triangular por bloques que se va formando por los eigenvalores
                % que recortamos porque ya han convergido. Cuando es un eigenvalor real,
                % se agrega un bloque de dimension 1 a T, y cuando son
                % complejos conjungados, se agrega un bloque de dimension 2
                
                Qn = eye(nOriginal);
                Qn(1:n, 1:n) = Q;
                Qm = Qm * Qn;
                    
                it = it+1;
                itT = itT + 1;
            end
            
            %esta parte es por si los eigenvalores son complejos
            %esta parte es la que hace que Qm'*A*Qm pueda no ser triangular
            %superior, pero si garantiza que sea triangular superior por
            %bloques, y seguimos teniendo una manera sencilla de obtener
            %los eigenvalores de Qm'*A*Qm
            
            %detectamos eigenvalores complejos si la entrada H(n, n-1) no
            %converge a cero 
            % si la entrada H(n-1, n-2) es menor a la tolerancia, entonces 
            % H es triangular superior por bloques y obtenemos los
            % eigenvalores complejos manualmente
            
            if( abs(H(n, n-1)) > tol && (n==2 || abs(H(n-1, n-2)) < tol ))
                
                a = H(n-1,n-1) + H(n,n);
                d = H(n-1,n-1)*H(n,n) - H(n-1,n)*H(n,n-1);
                lambdas(n) = (-a-sqrt(a^2 - 4*d))/2;
                lambdas(n-1) = -2*d/(a + sqrt(a^2 - 4*d));
                n = n-2;
            else
                lambdas(n) = H(n,n);
                n = n-1;
            end 
            %ahora solo nos fijamos en la parte restante de la matriz
            H = H(1:n, 1:n);
            
       end   
        %guardamos el ultimo eigenvalor
        %no necesitamos actualizar Qm porque para el caso de 1x1, Q es la
        %matriz identidad
       if n == 1
           lambdas(1) = H(1,1);
       end
    % regresaos lambdas y Q
    % en este momento tenemos Q'HQ triangular superior
    % como H = P'AP, Q'P'APQ = (PQ)'A(PQ) es triangular superior
    %entonces nuestra Q de A es PQ que tambien es unitaria 
    Qm = P*Qm;
    
    %si es triangular superior, eigQR obtiene los eigenvectores
    %usamos sort para ordenar los eigenvalores  eigenvectores
    if(esTriangularSuperior(Qm'*A*Qm, tol))
        
        Qm = eigQR(A, Qm, tol);
   
        [lambdas,P] = sort(abs(lambdas), 'descend');
        
        Q=Qm;
        for i = 1:nOriginal
            Qm(:, i) = Q(:, P(i));
        end
    end
        
    
end