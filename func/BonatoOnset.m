%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   function firstOnset = BonatoOnset(X, restVar, threshold)
%       X - matrix containing raw EMG data
%       restVar - array of variance for each channel
%       threshold - Bonato threshold value
%       firstOnset - index of X indicating onset of movement
%   Author: Christopher Miller, 20 Feb 08
%   Modified by Flynn, Michael, 2 March 15
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function firstOnset = BonatoOnset(X, threshold)
restVar = var(X(1:200,:)); % establish rest variance from 1st 200ms
h = threshold; % threshold value
n = 1; % number of samples that must exceed threshold
m = 5; % in m successive samples
T1 = 50; % number of samples that must be in active state
channels = size(X,2);
samples = size(X,1);
onset = [];
% one over the size of sample indicates failure to find onset
onset(1:channels)=samples+1; % onset tracks the onset point per channel
% ta stores the values of g for each channel along with their time index
ta = zeros(ceil(samples/2),2,channels);
% Calculate Bonato values for odd channels
for channel = 1:channels
    for k = 1:2:samples-1
        g = 1/restVar(channel)*(X(k,channel)^2+X(k+1,channel)^2);
        ta(ceil(k/2),:,channel) = [k g];
    end
end
% track number of active states by channel
activeCount = zeros(1,channels);
index = 1; % starting index for search
onsetFound = false; % flag to stop search once onset is located
firstk = zeros(1,channels); % tracks the starting points for onset
while index+m<size(ta,1) && ~onsetFound
    % loop through m samples for every channel to check threshold
    count = zeros(1,channels);
    for k = index:index+m-1
        for channel = 1:channels
            if ta(k,2,channel)>=h
                count(channel) = count(channel)+1;
                if activeCount(channel) == 0 && count(channel) == 1
                    firstk(channel) = ta(k,1,channel);
                end
            end
        end
    end
    index = index+m;
    for channel = 1:channels
        % increment active state counts if n exceeded during m samples
        if count(channel) >= n
            activeCount(channel) = activeCount(channel)+1;
        else activeCount(channel) = 0;
        end
        % if T1 active states exceeded, then onset has been found
        if activeCount(channel)*m >= T1
            onset(channel) = firstk(channel); %#ok<AGROW>
            onsetFound = true;
        end
    end
end
firstOnset = min(onset);
