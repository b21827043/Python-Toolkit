import math

def calculate_pixel_rotation(target_direction, wind_direction, wind_speed, target_distance, target_height, screen_resolution):
    # Calculate the angle by which the barrel needs to be rotated to fire in the direction the user is looking
    angle_difference = target_direction - wind_direction

    # If the difference is negative, add 360 degrees to convert it to a positive angle
    if angle_difference < 0:
        angle_difference += 360

    # Calculate the horizontal and vertical velocity components applied to the bullet due to wind
    horizontal_speed_component = wind_speed * math.cos(math.radians(angle_difference))
    vertical_speed_component = wind_speed * math.sin(math.radians(angle_difference))

    # Calculate the angles by which the barrel needs to be rotated in order for the bullet to reach the target
    required_angle_x = math.degrees(math.atan(horizontal_speed_component / 9.81))
    required_angle_y = math.degrees(math.atan((vertical_speed_component + (target_height / target_distance) * 9.81) / horizontal_speed_component))

    # Convert the rotations to pixel units
    pixel_rotation_x = required_angle_x * screen_resolution[0] / 360
    pixel_rotation_y = required_angle_y * screen_resolution[1] / 360

    return pixel_rotation_x, pixel_rotation_y


# Get user inputs
target_direction = float(input("Enter the target direction in degrees: "))
wind_direction = float(input("Enter the wind direction in degrees: "))
wind_speed = float(input("Enter the wind speed in m/s: "))
target_distance = float(input("Enter the target distance in meters: "))
target_height = float(input("Enter the target height in meters: "))
screen_resolution = (1920, 1080)

# Perform the calculations
pixel_rotation_x, pixel_rotation_y = calculate_pixel_rotation(target_direction, wind_direction, wind_speed, target_distance, target_height, screen_resolution)

# Print the result
print(f"You should rotate the barrel by {pixel_rotation_x:.2f} pixels in the x-axis and {pixel_rotation_y:.2f} pixels in the y-axis.")
