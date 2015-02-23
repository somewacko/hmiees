function varargout = EMGGui(varargin)

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @EMGGui_OpeningFcn, ...
                   'gui_OutputFcn',  @EMGGui_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before EMGGui is made visible.
function EMGGui_OpeningFcn(hObject, eventdata, handles, varargin)

% Choose default command line output for EMGGui
handles.output = hObject;

fprintf('\n---- EMGGui // Debug log ----\n\n');

% Create EMGSession object for the GUI
handles.session = EMGSession(handles.axes);

% Update handles structure
guidata(hObject, handles);


% --- Outputs from this function are returned to the command line.
function varargout = EMGGui_OutputFcn(hObject, eventdata, handles) 

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in run_toggle.
function run_toggle_Callback(hObject, eventdata, handles)

if get(hObject, 'Value')
    handles.session.start();
else
    handles.session.stop();
end


% --- Executes on button press in train_button.
function train_button_Callback(hObject, eventdata, handles)

set(handles.run_toggle, 'Value', 0);

handles.session.start_training();


% --- Executes on button press in open_file_button.
function open_file_button_Callback(hObject, eventdata, handles)

set(handles.live_capture_toggle, 'Value', 0);

handles.session.open_file();


% --- Executes on button press in live_capture_toggle.
function live_capture_toggle_Callback(hObject, eventdata, handles)

if get(hObject, 'Value')
    handles.session.start_live_capture();
else
    handles.session.stop_live_capture();
end


% End EMGGui.m