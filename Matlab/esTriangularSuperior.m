function [band] = esTriangularSuperior(A, tol)
    %función para determinar su una matriz es triangular superior con
    %cierta tolerancia absoluta 
    [n,m] = size(A);
    
    % band será falsa si alguna entrada ya no es cero
    band = true;
    
    for i = 1:m
        for j = i+1 :n
           %una entrada que debería ser cero, no lo es, entonces no es
           %triangular superior
           %como ya detectamos que no es triangular superior, cortamos el proceso 
           if( abs(A(j, i)) > tol )
               band = false;
               break;
           end
        end
        
        % si la bandera ya es falsa, no tiene caso seguir con el proceso
        if(band == false)
            break;
        end
    end
    
    % si todas fueron cero, band sigue en verdadero
    
end