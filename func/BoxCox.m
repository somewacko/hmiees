function Xn = BoxCox(X, lam)
% BoxCox
%   X - matrix of feature vectors
%   lam - lambda value for BoxCox equation
%   Xn - transformed matrix
%
% Original Author: Christopher Miller, 28 Feb 08
% http://medusa.sdsu.edu/Robotics/Neuromuscular...
%   /Theses/Miller/MillerThesis.htm

    Xn = [];
    [h, w] = size(X);
    % Loop thru entire matrix and transform each element individually
    if lam ~= 0
        for n = 1:h
            for m = 1:w
                Xn(n,m) = (power(X(n,m),lam)-1)/lam;
            end
        end
    else % lambda value of 0 uses only log transformation
        Xn = log(X);
    end
end
