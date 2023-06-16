#include <iostream>
#include <cmath>

std::pair<double, double> calculate_pixel_rotation(double target_direction, double wind_direction, double wind_speed, double target_distance, double target_height, std::pair<int, int> screen_resolution) {
    // Calculate the angle by which the barrel needs to be rotated to fire in the direction the user is looking
    double angle_difference = target_direction - wind_direction;

    // If the difference is negative, add 360 degrees to convert it to a positive angle
    if (angle_difference < 0) {
        angle_difference += 360;
    }

    // Calculate the horizontal and vertical velocity components applied to the bullet due to wind
    double horizontal_speed_component = wind_speed * std::cos(M_PI * angle_difference / 180);
    double vertical_speed_component = wind_speed * std::sin(M_PI * angle_difference / 180);

    // Calculate the angles by which the barrel needs to be rotated in order for the bullet to reach the target
    double required_angle_x = std::atan(horizontal_speed_component / 9.81) * 180 / M_PI;
    double required_angle_y = std::atan((vertical_speed_component + (target_height / target_distance) * 9.81) / horizontal_speed_component) * 180 / M_PI;

    // Convert the rotations to pixel units
    double pixel_rotation_x = required_angle_x * screen_resolution.first / 360;
    double pixel_rotation_y = required_angle_y * screen_resolution.second / 360;

    return std::make_pair(pixel_rotation_x, pixel_rotation_y);
}

int main() {
    // Get user inputs
    double target_direction = 180;
    double wind_direction = 180;
    double wind_speed = 10;
    double target_distance = 200;
    double target_height = 2;
    std::pair<int, int> screen_resolution = std::make_pair(1920, 1080);

    // Perform the calculations
    std::pair<double, double> pixel_rotation = calculate_pixel_rotation(target_direction, wind_direction, wind_speed, target_distance, target_height, screen_resolution);

    // Print the result
    std::cout << "You should rotate the barrel by " << std::fixed << pixel_rotation.first << " pixels in the x-axis and " << pixel_rotation.second << " pixels in the y-axis." << std::endl;

    return 0;
}
