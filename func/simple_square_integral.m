function ssi = simple_square_integral(sig)
    % Calcuates the simple square integral of the signal,
    % or just a summation of the entire squared signal.
    ssi = sum(sig.^2);
end

