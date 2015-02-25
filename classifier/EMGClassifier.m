classdef EMGClassifier
    
    properties
        
        gestures        % List of EMGGesture objects that are the gestures
                        % the classifier is trained to recognize.
                        
    end
    
    methods
        
        % ---- Constructor
        
        function obj = EMGClassifier()
            obj.gestures = [];
        end
        
        
        % ---- Methods
        
        function register_gestures(obj, g)
        end
        
        
        function g = classify(obj, sig)
        end
        
    end
    
end


% End EMGClassifier.m