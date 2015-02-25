classdef EMGGesture
    
    properties
        
        name            % The display name of the gesture.
        
    end
    
    methods
        
        % ---- Constructor
        
        function obj = EMGGesture(name)
            obj.name = name;
        end
        
        
        function read_trial(obj, sig)
        
        end
        
        
        function ans = is_recognizable(obj, sig)
        
        end
        
    end
    
end


% End EMGGesture.m