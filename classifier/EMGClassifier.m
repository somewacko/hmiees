classdef EMGClassifier < handle
    
    properties
        
        gestures        % List of EMGGesture objects that are the 
                        % gestures the classifier can recognize.
                      
        features        % List of EMGFeature objects that are the
                        % features the classifier will extract.
                        
        sampling_period % The length of samples to read from when
                        % extracting features for a signal
    end
    
    
    methods % Public
        
        % ---- Constructor
        
        function obj = EMGClassifier(sampling_period)
                        
            obj.sampling_period = sampling_period;
            
            obj.features = [ EMGFeature.MAV,  ...
                             EMGFeature.ZC,   ...
                             EMGFeature.WL,   ...
                             EMGFeature.WAMP, ...
                             EMGFeature.VAR ];
        end
        
        
        % ---- Methods
        
        function gesture = register_gesture(obj, gesture_name)
            % Adds a gesture to the list of gestures the classifier
            % will try to classify a signal for.
            
            % gesture_name : The name of the gesture to register.
            
            % gesture      : A new EMGGesture object that the
            %                classifier will use.
            
            gesture = EMGGesture(gesture_name);
            
            obj.gestures = [obj.gestures, gesture];
        end
        
        
        function train(obj, signal, gesture)
            % Trains the classifier with a new signal that is of the
            % same class as the provided gesture.
            
            % signal  : The signal(s) to train with. Each signal must
            %           be in its own column
            % gesture : The gesture that is of the same class as the
            %           provided signal. Must be a gesture that is
            %           already registered with the classifier.
            
            obj.check_length(signal);
            
            N = obj.sampling_period;
            
            feats = obj.extract_features(signal(1:N,:));
            gesture.add_training_set(feats);
        end
        
        
        function [gesture, distance] = classify(obj, signal)
            % Classifies the signal as one of the registered gestures
            % by comparing the Mahalanobis distances from each gesture
            % class and choosing the shortest one.
            
            % signal   : The signal to classify. Must be only one
            %            signal in a single-column vector.
            
            % gesture  : The gesture that the signal was classified as.
            % distance : The 'winning' Mahal distance for the signal.
            %            This can also be used as a measure of
            %            confidence for the classification.
            
            obj.check_length(signal);
            
            if size(signal, 2) > 1
                error(['Only one signal is allowed to be ', ...
                    'classified at a time. Signals must ',  ...
                    'be a single-column vector.']);
            end
            
            gesture  = [];
            distance = Inf;
            
            N = obj.sampling_period;
            
            feat = obj.extract_features(signal(1:N,:));
            
            for i = 1:length(obj.gestures)
                
                d = obj.gestures(i).mahal_distance(feat);
                
                if d < distance
                    gesture = obj.gestures(i);
                    distance = d;
                end
            end
        end
        
        
        function feat = extract_features(obj, signal)
            % Extracts the features for a given signal according to the
            % EMGFeature objects that the classifier holds.
            
            % signal : The signal(s) to extract features from. Each
            %          signal must be in its own column.
            
            % feat   : The extracted features, with one row for each
            %          signal.
            
            obj.check_length(signal);
            
            N = obj.sampling_period;

            feat = zeros(size(signal(1:N,:), 2), length(obj.features));
            
            for i = 1:length(obj.features)
                feat(:,i) = obj.features(i).extract(signal(1:N,:), []);
            end
        end
        
        
        % ---- Setters
        
        function set.features(obj, value)            
            % NOTE: Setting this will invalidate all training and the
            % classifier will have to be retrained.
            
            obj.features = value;
            obj.reset_training();
        end
        
        
        function set.sampling_period(obj, value)
            % NOTE: Setting this will invalidate all training and the
            % classifier will have to be retrained.
            
            obj.sampling_period = value;
            obj.reset_training();
        end
        
    end % Public Methods
        
    
    methods (Access = private) 
        
        function reset_training(obj)
            % Resets training for all gestures in the classifier.
            
            for i = 1:length(obj.gestures)
                obj.gestures(i).training_set = [];
            end
        end
        
        
        function check_length(obj, signal)
            % Checks the signal to make sure that is the same size or
            % larger than the classifier's sampling period.
            
            % signal : The signal(s) to check. Each signal must be in
            %          its own column.
            
            if size(signal, 1) < obj.sampling_period
                error(['Signal(s) provided are shorter than the ', ...
                    'classifier''s sampling period']);
            end
        end
        
    end % Private Methods
    
end
