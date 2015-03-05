classdef EMGGesture < handle
    
    properties
        
        name            % The display name of the gesture.
        
        training_set    % Set of features that are used as the
                        % reference set for the classifier.
    end
    
    methods
                
        function obj = EMGGesture(name)
            obj.name = name;
        end
        
        function add_training_set(obj, features)
            % Adds a set of features to the training set.
            
            % features : A horizontal vector of features to add to the
            %            training set. Different sets of features may
            %            be on its own row. 
            
            obj.training_set = vertcat(obj.training_set, features);
        end
        
        function distance = mahal_distance(obj, features)
            % Gets the Mahalanobis distance for a feature vector
            % from this gesture's training set.
            
            % features : A horizontal vector of features of the signal
            %            to be classified. Features should be ordered
            %            the same way as the training set.
            
            % distance : The Mahalanobis distance. This can be used as
            %            a measure of confidence for how alike this
            %            signal is to this class.
            
            distance = mahal(features, obj.training_set);
        end
    end
end
