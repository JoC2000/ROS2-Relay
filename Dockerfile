# Use ROS Humble as image
FROM ros:humble

# Avoid prompts
ENV DEBIAN_FRONTEND=noninteractive


# Install dependencies
RUN apt-get update && apt-get install -y \
    python3-pip \
    python3-rosdep \
    && rm -rf /var/lib/apt/lists/*

# Create workspace
WORKDIR /ros2_ws/src

# Copy ROS2 packages into de container
COPY ./packages.xml .
COPY ./CMakeLists.txt .

COPY ./simple_relay/ ./simple_relay/
COPY ./src/ ./src/
COPY ./launch/ ./launch/

# Install dependencies
RUN rosdep init && && rosdep update && \
    rosdep install --from-paths . --ignore-src -y

# Build the workspace
WORKDIR /ros2_ws
RUN colcon build --symlink-install

# Source the workspace
CMD [ "bash", "-c", "source install/setup.bash && ros2 launch simple_relay relay_launch.py" ]