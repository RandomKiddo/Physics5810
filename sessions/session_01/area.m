% file: area.m
%
% Script file to calculate the area of a circle
%

% Programmer: Dick Furnstahl  furnstahl.1@osu.edu
% Revision history:
%   29-Dec-2006 -- original version, translated from C++ code

% Things to note compared to C++ version:
%  * we have to call the area variable "my_area" to avoid a
%     conflict with the filename.
%  * comments are marked by % rather than //
%  * ending a line with ; in MATLAB suppresses printing
%  * no loading of libraries here (e.g., no include files)
%  * pi is pre-defined
%  * variables are not declared

radius = input('Enter the radius of a circle: ');

my_area = pi * radius^2;   % area formula

disp('radius = ');  
disp(radius);

disp('area = ');
disp(my_area);     % put "format long" before to get more digits

% The following is a more sophisticated C-style output
% fprintf(1,'radius = %8.4f, area = %8.4f\n',radius,my_area);