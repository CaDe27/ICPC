function[V] = eigQR(A, Q, tol)
    
    %{
    funcion que devuelve los eigenvectores de V
    dado que   Q'A Q es una matriz triangular superior
    con Q una matriz ortogonal
    
    es decir, QR= AQ
    
    Entrada:
        A - una matriz cuadrada
        Q - una matriz ortogonal tal que Q'*A*Q sea triangular superior
    
    Salida
        V - una matriz con los eigenvalores de A
            el i-esimo vector asociado al eigenvalor de la i-esima entrada
            de la diagonal de la matriz triangular superior
    %}
    
    R = Q'*A*Q;
    
    n = length(A);
    V = zeros(n,n);
    
    for i = 1:n
        coefs = zeros(n, 1);
        
        %el i - esimo eigenvector está asociado a R(i,i) y es de la forma 
        %  vi = coef(1)q1 + coef(2)q2 + ... + coeg(i)qi
        % los coeficientes de cada vector los almacenamos en coefs, pues se
        % utilizan recursivamente
        
        % por hipotesis sabemos que Aqi = R(1,i)*q1 + R(2,i)q2 + ... + R(i,i)qi
        % y como vi es eigenvector 
        % R(i,i)vi = Avi = coef(i)R(i,i)qi + (coef(i)R(i-1,i) +coef(i-1)*R(i-1,i-1))*q_(i-1)  ... 
        
        %como la expresion de vi como combinacion lineal de la base Q es
        %unica, queda planteado el sistema
        
        %  R(i,i)coef(i)   = R(i,i)coef(i)
        %  R(i,i)coef(i-1) =  coef(i)R(i-1,i) +coef(i-1)*R(i-1,i-1)
        %  ... 
        %  R(i,i) coef(k) = coef(k)R(k,k) + coef(k+1)R(k,k+1) + ... + coef(i)*R(k,i)
        
        % de este modo coef(k) = (coef(k+1)R(k,k+1) + ... + coef(i-1)*R(k, i-1)) / (R(i,i) - R(k,k)
        
        % y podemos resolver primero coef(i), luego coef(i-1), y asi hasta
        % llegar a coef(1)
        
        % el unico problemas es si R(i,i) = R(k,k), pues estariamos
        % dividiendo por cero
        % en este caso nos fijams en que el numerador sea cero
        % si este es el caso, realmente no era necesario qk para este
        % eigenvector, y lo omitimos
        % en caso de que el numerador sea distinto de cero, quiere decir
        % que si se necesitaba de qk, pero no hay manera de equilibrar sus
        % coeficientes en ambos lados de la matriz y no hay tal eigenvector
        
        %esto sucede cuando la matriz no es semisimple, por ejemplo con la
        %matriz 
        % [ 1 1]
        % [ 0 1]
        
        % si tenemos Q = I, A = Q'AQ, y  A es triangular superior
        % aun asi, A solo tiene un eigenvalor y la dimension de su
        % eigensapcio es 1, que es el span de [1,0]'
        
        qi = Q(:, i);
        coefs(i) = 1;
        
        for k = i-1: -1 : 1
            
           % aqui es donde checamos la condicion para no dividir por cero
           if( R(i,i) == R(k,k))
               
               %usamos un contador para ver cuantos de terminos del
               %numerador son cero, y cada termino es cero si uno de sus
               %multiplicando es cero
               
               
               contador = 0;
               for j = k+1 : i
                    contador = contador + ( (abs(coefs(j)) < tol) || (abs(R(k,j)) < tol) );
               end
               
               % como hay exactamente i-k terminos en el numerador de
               % coef(k), el que el contador sea menor nos indica que no
               % puede existir el eigenvector
               if(contador < (i-k))
                  qi = zeros(n,1);
                  break;
               end
               % si todos fueron cero, como dijimos, omitimos qk
               
           else
               %si no se cumple R(i,i) = R(k,k), podemos calcular el
               %coeficiente
               for j = k+1:i
                    coefs(k) = coefs(k) + coefs(j)*R(k,j);
               end
               
               coefs(k) = coefs(k) / (R(i,i) - R(k,k));
               
               %sumo la aportacion del k - esimo vector
               qi = qi + coefs(k)*Q(:, k);
               
           end
            
           
        end
        
        %guardamos el eigenvector
        V(:, i) = qi;
        
    end
    
    
end