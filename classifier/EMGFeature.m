classdef EMGFeature
    
    enumeration
        MAV     ('Mean Absolute Value',         []   ),
        MAVSLP  ('Mean Absolute Value Slope',   10   ),
        ZC      ('Zero Crossings',              0.15 ),
        WL      ('Waveform Length',             []   ),
        WAMP    ('Willison Amplitude',          0.20 )
    end
    
    properties
        name    % The name of the feature.
        value   % An additional parameter for the feature.
    end
    
    methods
        function obj = EMGFeature(name, val)
            obj.name  = name;
            obj.value = val;
        end
        
        function feat = extract(obj, signal)
            % Returns the feature for the given signals.
            
            % signal : The signal(s) to extract features from. Each
            %          signal must be in its own column.
            
            if obj == EMGFeature.MAV
                feat = mean_absolute_value(signal);
                
            elseif obj == EMGFeature.MAVSLP
                feat = mean_absolute_value_slope(signal, obj.value);
                
            elseif obj == EMGFeature.ZC
                feat = zero_crossings(signal, obj.value);
                
            elseif obj == EMGFeature.WL
                feat = waveform_length(signal);
                
            elseif obj == EMGFeature.WAMP
                feat = willison_amplitude(signal, obj.value);
                
            else
                feat = 0;
            end
        end
    end
end
