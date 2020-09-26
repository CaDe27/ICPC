function [lambdas, Qm, it]= MQR_simple(A, k, tol)
    %{
    %funcion que usa el algoritmo QR para aproximar los eigenvalores de A
    
    entrada:
        A - matriz de la que obtenemos eigenpares
        k - limite de iteraciones del algoritmo
        tol - tolerancia de error absoluto

    Salida:
        lambdas - vector con eigenvalores de A
        Q - una matriz con los eigenvectores de A si llega a que Qm'*A*Qm es
            triangular superior o Q matriz unitaria 
    
    %}
    
    %hacemos el algoritmo sobre la hessiana
    [P, H] = hess(A);
    
    
    it = 0;
    Qm = eye(size(A));
    
    
    while(  (norm(diag(H, -1)) > tol) && (it < k) )
        [Q, R]  = qr(H);
        H = R*Q;
        
        Qm = Qm*Q;
        it = it + 1;
    end
    
    lambdas = diag(H);
    % regresamos lambdas y Q
    % en este momento tenemos Q'HQ triangular superior
    % como H = P'AP, entonces Q'P'APQ = (PQ)'A(PQ) es triangular superior
    %entonces nuestra Q de A es PQ que tambien es unitaria por ser producto
    %de unitarias
    Qm = P*Qm;
    
    %si converge a una triangular superior, devolvemos los eigenvectores, 
    %sino, solo Q
    if( esTriangularSuperior(Qm'*A*Qm, tol) )
        Qm = eigQR(A, Qm , tol);
    end
    
end