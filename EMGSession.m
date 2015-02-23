classdef EMGSession < handle
        
    properties
        
        classifier      % EMGClassifier object that performs signal
                        % classification and retains training data.
        
        is_running      % Flag that indicates whether classification is
                        % occurring or not.
                    
        is_live         % Flag that indicates whether data should be
                        % read from a live feed or not.
                    
        sampling_rate   % The sampling rate of the session (Hz).
        
        timer_period    % The period of which the session updates data.
        
        figure          % The figure in the GUI to edit.
        
        session_text    % The session_text static text field
                        
        classifier_text % The classifier_text static text field
        
        recorder        % The audiorecorder object for the session
                    
    end
    
    
    methods
            
        % ---- Constructor
        
        function obj = EMGSession(figure, session_text, classifier_text)
            fprintf('EMGSession: Creating session.\n');
            
            obj.figure          = figure;
            obj.session_text    = session_text;
            obj.classifier_text = classifier_text;
            
            obj.classifier = EMGClassifier();
            
            obj.is_running    = 0;
            obj.is_live       = 0;
            
            obj.sampling_rate = 1000;
            obj.timer_period  = 0.1;
            
            obj.recorder = audiorecorder(obj.sampling_rate, 16, 1);
        end
        
        % ---- GUI Handlers
        
        function start(obj)
            fprintf('EMGSession: Starting session.\n');
            
            % Display information
            
            str = sprintf(['Session running\n',         ...
                           '\n',                        ...
                           'Sampling Rate: %d Hz\n',    ...
                           'Timer Period: %0.2f s'],       ...
                obj.sampling_rate, obj.timer_period);

            set(obj.session_text, 'String', str);

            obj.is_running = 1;
                                    
            % Set up audiorecorder and begin recording.
            
            stop(obj.recorder);
            
            obj.recorder.TimerFcn = @obj.recorderCallback;
            obj.recorder.TimerPeriod = obj.timer_period;
            
            record(obj.recorder)
        end
        
        
        function stop(obj)
            fprintf('EMGSession: Stopping session.\n');
            set(obj.session_text, 'String', 'Session stopped');
            
            obj.is_running = 0;
            
            stop(obj.recorder);
        end
        
        
        function open_file(obj)
            
            if obj.is_live
                obj.stop_live_capture(); end
            
            fprintf('EMGSession: Opening file.\n');
            
        end
        
        
        function start_training(obj)
            
            if obj.is_running
                obj.stop(); end
            if obj.is_live
                obj.stop_live_capture(); end
            
            fprintf('EMGSession: Beginning training.\n');
            
            % Begin training session GUI... (TODO)
            
        end
        
        
        function start_live_capture(obj)
            fprintf('EMGSession: Enabling live capture.\n');
            
            obj.is_live = 1;
        end
        
        
        function stop_live_capture(obj)
            fprintf('EMGSession: Disabling live capture.\n');
            
            obj.is_live = 0;
        end
        
        
        % ---- audiorecorder callback
        
        function recorderCallback(obj, srcHandle, eventData) %#ok<INUSD>
            
            sig = getaudiodata(obj.recorder);

            % Only take the last second of samples
            sig = sig(max(1, end-obj.sampling_rate+1): end);
            t = 0:4/length(sig):1-4/length(sig);
            
            % Plot waveform
            plot(obj.figure, t, sig(1:4:end)); % Only plot every 4th sample
            ylim(obj.figure, [-1 1]);
            
            drawnow;
            
            % Perform analysis and classification
            
            obj.classifier.classify(sig);
        end
        
        
        % ---- Classification
        
        function classify(obj, sig) %#ok<INUSD>
            % TODO~
        end
            
    end % methods
    
end % classdef


% End EMGSession.m