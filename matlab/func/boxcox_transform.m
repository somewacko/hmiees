function x_t = boxcox_transform(x, lambda)
    % Performs boxcox power transformation on x.

    if lambda == 0
        x_t = log(x);
    else
        x_t = zeros(size(x));
        
        for i = 1:size(x, 1)
            for l = 1:size(x, 2)
                x_t(i,l) = (x(i,l)^lambda-1)/lambda;
            end
        end
    end
end

