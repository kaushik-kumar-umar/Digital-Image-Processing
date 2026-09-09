clc;
clear;
close all;

%% Time settings
dt = 0.1;
t = 0:dt:20;

%% True signal (ideal sensor output)
true_signal = sin(t);

%% Noisy measurement (what sensor gives)
noise_variance = 0.2;
measurement_noise = noise_variance * randn(size(t));
z = true_signal + measurement_noise;

%% Kalman Filter Initialization
x_est = 0;        % Initial state estimate
P = 1;            % Initial estimation error covariance

Q = 0.01;         % Process noise covariance
R = noise_variance; % Measurement noise covariance

x_estimated = zeros(size(t));

%% Kalman Filter Loop
for k = 1:length(t)
    
    % Prediction step
    x_pred = x_est;
    P_pred = P + Q;
    
    % Kalman Gain
    K = P_pred / (P_pred + R);
    
    % Update step
    x_est = x_pred + K * (z(k) - x_pred);
    P = (1 - K) * P_pred;
    
    % Save estimate
    x_estimated(k) = x_est;
end

%% Plot results
figure;
plot(t, true_signal, 'g', 'LineWidth', 2); hold on;
plot(t, z, 'r', 'MarkerSize', 8);
plot(t, x_estimated, 'b', 'LineWidth', 2);
grid on;

legend('True Signal', 'Noisy Measurement', 'Kalman Output');
xlabel('Time');
ylabel('Signal Value');
title('Kalman Filter on Noisy Sensor Data');
